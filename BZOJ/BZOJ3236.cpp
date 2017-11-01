#include<cmath>
#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 1e5 +1;
static const int maxm = 1e6 +1;
static const int maxx = maxn + ( maxm << 1 );

int n , m , Fac , Cnt;
int ans[maxm][2] , num[maxx];
int A[maxn] , B[maxx] , BL[maxn];

struct query{
	int l , r , p , q , id;
	bool operator < ( query t ) const { return BL[l] < BL[t.l] || BL[l] == BL[t.l] && r < t.r; }
}Q[maxm];

namespace BIT{
	
	int T[2][maxx];
	
	int Lowbit( int x ){ return x & -x ; }
	
	void Add( int t , int x , int f ){
		for( int i = x ; i <= Cnt ; i += Lowbit( i ) )
			T[t][i] += f;
	}
	
	int Query( int t , int x ){
		int Res = 0;
		for( int i = x ; i ; i -= Lowbit( i ) )Res += T[t][i];
		return Res;
	}
	
}using namespace BIT;

void modui(){
	int l = 1 , r = 0;
	For( i , 1 , m ){
		while( r < Q[i].r ){
			++r;
			Add( 0 , A[r] , 1 );
			if( ++num[ A[r] ] == 1 )Add( 1 , A[r] , 1 );
		}
		while( l > Q[i].l ){
			--l;
			Add( 0 , A[l] , 1 );
			if( ++num[ A[l] ] == 1 )Add( 1 , A[l] , 1 );
		}
		while( r > Q[i].r ){
				Add( 0 , A[r] , -1 );
			if( !--num[ A[r] ] )Add( 1 , A[r] , -1 );
			--r;
		}
		while( l < Q[i].l ){
			Add( 0 , A[l] , -1 );
			if( !--num[ A[l] ] )Add( 1 , A[l] , -1 );
			++l;
		}
		ans[ Q[i].id ][0] = Query( 0 , Q[i].q ) - Query( 0 , Q[i].p - 1 );
		ans[ Q[i].id ][1] = Query( 1 , Q[i].q ) - Query( 1 , Q[i].p - 1 );
	}
}

int main(){
	
	Read( n );Read( m );Fac = sqrt( n + 0.5 );
	For( i , 1 , n )Read( A[i] ) , BL[i] = ( i - 1 ) / Fac + 1 , B[ ++Cnt ] = A[i];
	For( i , 1 , m )Read( Q[i].l ) , Read( Q[i].r ) , Read( Q[i].p ) , Read( Q[i].q ) , Q[i].id = i , B[ ++Cnt ] = Q[i].p , B[ ++Cnt ] = Q[i].q;
	For( i , 1 , m )if( Q[i].p > Q[i].q )swap( Q[i].p , Q[i].q );
	
	sort( 1 + B , 1 + Cnt + B );
	Cnt = unique( 1 + B , 1 + Cnt + B ) - B - 1;
	For( i , 1 , n )A[i] = lower_bound( 1 + B , 1 + Cnt + B , A[i] ) - B;
	For( i , 1 , m )Q[i].p = lower_bound( 1 + B , 1 + Cnt + B , Q[i].p ) - B , Q[i].q = lower_bound( 1 + B , 1 + Cnt + B , Q[i].q ) - B;
	
	sort( 1 + Q , 1 + m + Q );
	
	modui();
	
	For( i , 1 , m )printf("%d %d\n",ans[i][0],ans[i][1]);
	
	return 0;
}
