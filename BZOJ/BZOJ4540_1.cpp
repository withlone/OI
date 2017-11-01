#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 1e5 +1;
static const int maxm = maxn << 2;

int n , m;
int Stk[maxn] , tp;
int A[maxn];LL ans[maxn];

struct data{
	int l , r , k;
	bool operator < ( data tmp ) const { return r < tmp.r ; }
}Q[maxn];

struct node{
	LL a , b , c , d;
	void clear(){ a = 1 ; b = c = d = 0; }
	node operator * ( node x ){ return (node){ a * x.a , x.b + x.a * b , a * x.c + c , d + x.d + b * x.c } ; }
}Lazy[maxm];

namespace Segment{
	
	#define Lson rt << 1 , l , mid
	#define Rson rt << 1 | 1 , mid + 1 , r
	
	LL val[maxm] , sum[maxm];
	
	void Up( int rt ){
		val[rt] = val[ rt << 1 ] + val[ rt << 1 | 1 ];
		sum[rt] = sum[ rt << 1 ] + sum[ rt << 1 | 1 ];
	}
	
	void Add( int rt , int l , int r , node t ){
		LL len = r - l + 1;
		sum[rt] += t.c * val[rt] + t.d * len;
		val[rt] = t.a * val[rt] + t.b * len;
		Lazy[rt] = Lazy[rt] * t;
	}
	
	void Pd( int rt , int l , int r ){
		int ls = rt << 1 , rs = rt << 1 | 1 , mid = l + r >> 1;
		Add( ls , l , mid , Lazy[rt] );
		Add( rs , mid + 1 , r , Lazy[rt] );
		Lazy[rt].clear();
	}
	
	void modify( int rt , int l , int r , int L , int R , node t ){
		if( l > R || r < L )return;
		if( l >= L && r <= R )return Add( rt , l , r , t ) , void();
		int mid = l + r >> 1;
		if( Lazy[rt].a != 1 || Lazy[rt].b || Lazy[rt].c || Lazy[rt].d )Pd( rt , l , r );
		modify( Lson , L , R , t );modify( Rson , L , R , t );
		Up( rt );
	}
	
	LL Query( int rt , int l , int r , int L , int R ){
		if( l > R || r < L )return 0;
		if( l >= L && r <= R )return sum[rt];
		int mid = l + r >> 1;
		if( Lazy[rt].a != 1 || Lazy[rt].b || Lazy[rt].c || Lazy[rt].d )Pd( rt , l , r );
		return Query( Lson , L , R ) + Query( Rson , L , R );
	}
	
	void Build( int rt , int l , int r ){
		Lazy[rt].clear();
		if( l == r )return;
		int mid = l + r >> 1;
		Build( Lson );Build( Rson );
	}
	
}using namespace Segment;

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n )Read( A[i] );
	For( i , 1 , m )Read( Q[i].l ) , Read( Q[i].r ) , Q[i].k = i;
	sort( 1 + Q , 1 + m + Q );
	
	Build( 1 , 1 , n );
	
	int pos = 1;
	For( i , 1 , n ){
		while( tp && A[Stk[tp]] >= A[i] )tp--;
		modify( 1 , 1 , n , Stk[tp] + 1 , i , ( node ){ 0 , A[i] , 0 , 0 } );
		Stk[ ++tp ] = i;
		Add( 1 , 1 , n , ( node ){ 1 , 0 , 1 , 0 } );
		for( ; pos <= m && i == Q[pos].r ; pos++ )ans[ Q[pos].k ] = Query( 1 , 1 , n , Q[pos].l , Q[pos].r );
	}
	
	For( i , 1 , m )printf("%lld\n",ans[i]);
	
	return 0;
}
