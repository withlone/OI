#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )

template< typename Type >inline Type max ( Type x , Type y ){ return x > y ? x : y; }
template< typename Type >inline Type min ( Type x , Type y ){ return x < y ? x : y; }
template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

typedef long long LL;
static const int Inf  = 1e9;
static const int MAXN = 5e4 +1;
#define Mem( x ) memset( x , 0 ,sizeof x )

int n , limit , Tp;
int A[MAXN] , Sum[MAXN] , MinB[MAXN];
int f[MAXN] , Pos[MAXN] , Max[MAXN];

int Div();
bool Check( int );

bool Flag;
namespace Segment_Tree{
	#define Lc p<<1
	#define Rc Lc|1
	#define Lson Lc , l , Mid
	#define Rson Rc , Mid+1 , r
	int Min[MAXN<<2] , Minf[MAXN<<2] , Lz[MAXN<<2];
	void Pd( int p ){
		Lz[Lc] = Lz[Rc] = Lz[p];
		Min[Lc] = Lz[p] + Minf[Lc];
		Min[Rc] = Lz[p] + Minf[Rc];
		Lz[p] = 0;
	}
	void Mf( int p , int l , int r , int L , int R , int k ){
		if( l > R || r < L )return;
		if( l >=L && r <=R ){
			Lz[p] = k;Min[p] = k + Minf[p];
			if( Flag )Min[p] = Minf[p] = k;
			return;
		}
		if( Lz[p] )Pd( p );
		int Mid = l + r >>1;
		Mf( Lson , L , R , k );Mf( Rson , L , R , k );
		Min[p] = min( Min[Lc] , Min[Rc] );Minf[p] = min( Minf[Lc] , Minf[Rc] );
	}
	int Query( int p , int l , int r , int L , int R ){
		if( l > R || r < L )return 0x7fffffff;
		if( l >=L && r <=R )return Min[p];
		if( Lz[p] )Pd( p );
		int Mid = l + r >>1;
		return min( Query( Lson , L , R ) , Query( Rson , L , R ) );
	}
}using namespace Segment_Tree;

#define Judge

int main(){
	
	#ifdef Judge
		freopen("gold.in","r",stdin);
		freopen("gold.out","w",stdout);
	#endif
	
	Read( n );Read( limit );
	MinB[0] = Inf;
	For( i , 1 , n ){
		Read( A[++Tp] );Read( Sum[Tp] );
		MinB[Tp] = min( Sum[Tp] , MinB[Tp-1] );
		while( Tp > 1 && MinB[Tp-1] <= A[Tp] ){
			MinB[Tp-1] = min( MinB[Tp-1] , MinB[Tp] );
			A[Tp-1] = max( A[Tp-1] , A[Tp] );
			Sum[Tp-1] += Sum[Tp];Tp--;
		}
	}
	
	For( i , 1 , n = Tp )Sum[i] += Sum[i-1];
	
	printf("%d\n",Div());
	
	return 0;
}

bool Check( int V ){
	Mem( Min );Mem( Minf );Mem( Lz );
	int Str = Tp = 0;
	For( i , 1 , n ){
		while( Sum[i] - Sum[Str] > V )Str++;
		if( Str == i )return false;
		while( Tp && Max[Tp] <= A[i] )Tp--;
		Pos[++Tp] = i;Max[Tp] = A[i];
		Mf( 1 , 0 , n , Pos[Tp-1] , i-1 , A[i] );
		f[i] = Query( 1 , 0 , n , Str , i-1 );
		Flag = 1;
		Mf( 1 , 0 , n , i , i , f[i] );
		Flag = 0;
	}
	return f[n] <= limit;
}

int Div(){
	int l = 0 , r = Inf;
	while( l < r ){
		int Mid = l+r >>1;
		if( Check( Mid ) )r = Mid;
		else l = Mid +1;
	}
	return r;
}
