#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 3e4 +1;
static const int maxm = maxn << 2;

int n , K , m , Qct , Fac;
int A[maxn] , BL[maxn];
int num[maxn] , ans[maxn];

struct Query{
	int l , r , id , f;
	bool operator < ( Query t ) const { return BL[l] < BL[t.l] || BL[l] == BL[t.l] && BL[r] < BL[t.r] || BL[l] == BL[t.l] && BL[r] == BL[t.r] && r < t.r; }
}Q[maxm];

int Get( int x ){ return x >= 0 ? num[x] : 0 ; }

int main(){
	
	while( scanf("%d",&n) != EOF ){
		Qct = 0;
		memset( num , 0 , sizeof num );
		memset( ans , 0 , sizeof ans );
		Read( K );Fac = sqrt( n + 0.5 );
		For( i , 1 , n )Read( A[i] ) , BL[i] = i / Fac;
		Read( m );
		For( i , 1 , m ){
			int x , y , p , q;
			Read( x );Read( y );Read( p );Read( q );
			Q[ ++Qct ] = (Query){ x , q , i , 1 };
			Q[ ++Qct ] = (Query){ x , p - 1 , i , -1 };
			Q[ ++Qct ] = (Query){ y + 1 , q , i , -1 };
			if( y + 1 <= p - 1 )Q[ ++Qct ] = (Query){ y + 1 , p - 1 , i , 1 };
		}
		sort( 1 + Q , 1 + Qct + Q );
		
		int l = 1 , r = 0 , sum = 0;
		For( i , 1 , Qct ){
			while( r < Q[i].r )++r , sum += Get( K - A[r] ) , ++num[ A[r] ];
			while( l > Q[i].l )--l , sum += Get( K - A[l] ) , ++num[ A[l] ];
			while( r > Q[i].r )--num[ A[r] ] , sum -= Get( K - A[r] ) , --r;
			while( l < Q[i].l )--num[ A[l] ] , sum -= Get( K - A[l] ) , ++l;
			ans[ Q[i].id ] += Q[i].f * sum;
		}
		
		For( i , 1 , m )printf("%d\n",ans[i]);
		
	}
	
	return 0;
}
