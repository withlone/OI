#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

static const int maxn = 2e5 +1;
static const int maxx = 71e5;

int Case , n , m;
int A[maxn] , ans[maxn] , Nxt[maxn];

namespace president_tree{
	
	int Cnt;
	int root[maxn] , Ch[maxx][2];
	int Sz[maxx];
	
	#define Lson Ch[rt][0] , l , mid
	#define Rson Ch[rt][1] , mid + 1 , r
	
	void modify( int pt , int &rt , int l , int r , int x , int f ){
		Sz[rt = ++Cnt] = Sz[pt] + f;
		if( l == r )return;
		int mid = l + r >> 1;
		if( x <= mid )Ch[rt][1] = Ch[pt][1] , modify( Ch[pt][0] , Lson , x , f );
		else Ch[rt][0] = Ch[pt][0] , modify( Ch[pt][1] , Rson , x , f );
	}
	
	int Query( int rt , int l , int r , int L , int R ){
		if( l > R || r < L || !rt )return 0;
		if( l >= L && r <= R )return Sz[rt];
		int mid = l + r >> 1;
		return Query( Lson , L , R ) + Query( Rson , L , R );
	}
	
	int Query( int rt , int k ){
		int l = 1 , r = n;
		while( l < r ){
			int mid = l + r >> 1;
			if( Sz[ Ch[rt][0] ] >= k )r = mid , rt = Ch[rt][0];
			else l = mid + 1 , k -= Sz[ Ch[rt][0] ] , rt = Ch[rt][1];
		}
		return l;
	}
	
}using namespace president_tree;

int main(){
	
	Read( Case );
	
	For( I , 1 , Case ){
		Cnt = 0;
		memset( Nxt , 0 , sizeof Nxt );
		Read( n );Read( m );
		For( i , 1 , n )Read( A[i] );
		
		root[n + 1] = 0;
		Rep( i , n , 1 ){
			root[i] = 0;
			modify( root[i + 1] , root[i] , 1 , n , i , 1 );
			if( Nxt[ A[i] ] )modify( root[i] , root[i] , 1 , n , Nxt[ A[i] ] , -1 );
			Nxt[ A[i] ] = i;
		}
		
		For( i , 1 , m ){
			int l , r;
			Read( l );Read( r );
			l = ( l + ans[i - 1] ) % n + 1;
			r = ( r + ans[i - 1] ) % n + 1;
			if( l > r )l ^= r ^= l ^= r;
			int tmp = Query( root[l] , 1 , n , l , r );
			tmp = ( tmp >> 1 ) + ( tmp & 1 );
			ans[i] = Query( root[l] , tmp );
		}
		printf("Case #%d:",I);
		For( i , 1 , m )printf(" %d",ans[i]);puts("");
	}
	
	return 0;
}
