#include<algorithm>
#include<cstdio>
#include<queue>
#include<map>

using namespace std;

#define Lson Ch[rt][0] , l , mid
#define Rson Ch[rt][1] , mid + 1 , r
#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}

typedef long long LL;
static const LL Inf = 1e13;
static const int maxn = 1e5 +10;
static const int maxm = 1e7;

int n , m , cnt;
int A[maxn] , Nxt[maxn];
LL sum[maxn];bool Vis[maxn];

map< int , int >mp;

int Rt[maxn] , Ch[maxm][2];
LL mx[maxm] , Lazy[maxm] , pos[maxm];

namespace Segment{
	
	void Up( int rt ){
		mx[rt] = max( mx[ Ch[rt][0] ] , mx[ Ch[rt][1] ] ) + Lazy[rt];
		pos[rt] = ( mx[ Ch[rt][0] ] > mx[ Ch[rt][1] ] ) ? pos[ Ch[rt][0] ] : pos[ Ch[rt][1] ];
	}
	
	void Build( int &rt , int l , int r , LL *B ){
		rt = ++cnt;
		if( l == r )return pos[rt] = l , mx[rt] = B[l] , void();
		int mid = l + r >> 1;
		Build( Lson , B );Build( Rson , B );
		Up( rt );
	}
	
	void modify( int &rt , int l , int r , int k ){
		int pt = rt;rt = ++cnt;
		mx[rt] = mx[pt];pos[rt] = pos[pt];Lazy[rt] = Lazy[pt];Ch[rt][0] = Ch[pt][0];Ch[rt][1] = Ch[pt][1];
		if( l == r )return Lazy[rt] = mx[rt] = -Inf , void();
		int mid = l + r >> 1;
		if( k <= mid )modify( Lson , k );else modify( Rson , k );
		Up( rt );
	}
	
	void modify_add( int pt , int &rt , int l , int r , int L , int R , LL k ){
		if( l > R || r < L )return;
		rt = ++cnt;
		mx[rt] = mx[pt];pos[rt] = pos[pt];Lazy[rt] = Lazy[pt];Ch[rt][0] = Ch[pt][0];Ch[rt][1] = Ch[pt][1];
		if( l >= L && r <= R ){
			Lazy[rt] += k;
			mx[rt] += k;
			return;
		}
		int mid = l + r >> 1;
		modify_add( Ch[pt][0] , Lson , L , R , k );modify_add( Ch[pt][1] , Rson , L , R , k );
		Up( rt );
	}
	
}using namespace Segment;

priority_queue< pair< LL , int > >quq;

void Init(){
	For( i , 1 , n ){
		Vis[ Nxt[i] ] = true;
		sum[i] = sum[i-1];
		if( Vis[i] )continue;
		sum[i] += A[i];
	}
	Build( Rt[1] , 1 , n , sum );
	For( i , 2 , n )modify_add( Rt[i-1] , Rt[i] , 1 , n , i , Nxt[i-1] - 1 , -A[i-1] )
	, modify( Rt[i] , 1 , n , i - 1 );
	For( i , 1 , n )quq.push( make_pair( mx[Rt[i]] , i ) );
}

int main(){
	
	mx[0] = -Inf;
	
	Read( n );Read( m );
	For( i , 1 , n )Read( A[i] ) , mp[ A[i] ] = n + 1;
	Rep( i , n , 1 )Nxt[i] = mp[ A[i] ] , mp[ A[i] ] = i;
	
	Init();
	
	while( --m ){
		int x = quq.top().second;quq.pop();
		modify( Rt[x] , 1 , n , pos[Rt[x]] );
		quq.push( make_pair( mx[Rt[x]] , x ) );
	}
	printf("%lld\n",quq.top().first);
	return 0;
}
