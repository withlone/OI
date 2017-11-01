#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef pair< int , int > par;
static const int maxn = 1e5 +1;
static const int maxm = 5e3 +1;

int n , m;
int ans[maxm];
par d[maxn];
int A[maxn], B[maxn];

struct data{ int l , r , k , id ; }Q[maxm] , Q1[maxm] , Q2[maxm];

namespace BIT{
	
	int T[maxn];
	
	int Lowbit( int x ){ return x & -x ; }
	
	void Add( int x , int f ){
		for( int i = x ; i <= n ; i += Lowbit( i ) )T[i] += f;
	}
	
	int Query( int x ){
		int Res = 0;
		for( int i = x ; i ; i -= Lowbit( i ) )Res += T[i];
		return Res;
	}
	
}using namespace BIT;

void div( int l , int r , int L , int R ){
	if( L > R )return;
	if( l == r ){
		For( i , L , R )ans[ Q[i].id ] = B[l];
		return;
	}
	int mid = l + r >> 1 , q1 = 0 , q2 = 0;
	int t = lower_bound( 1 + d , 1 + n + d , make_pair( l , 0 ) ) - d;
	for( int i = t ; i <= n && d[i].first <= mid ; i++ )Add( d[i].second , 1 );
	For( i , L , R ){
		int tmp = Query( Q[i].r ) - Query( Q[i].l - 1 );
		if( tmp >= Q[i].k )Q1[ ++q1 ] = Q[i];
		else Q[i].k -= tmp , Q2[ ++q2 ] = Q[i];
	}
	for( int i = t ; i <= n && d[i].first <= mid ; i++ )Add( d[i].second , -1 );
	For( i , L , L + q1 - 1 )Q[i] = Q1[ i - L + 1 ];
	For( i , L + q1 , R )Q[i] = Q2[ i - L - q1 + 1 ];
	div( l , mid , L , L + q1 - 1 );
	div( mid + 1 , r , L + q1 , R );
}

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n )Read( A[i] ) , B[i] = A[i];
	For( i , 1 , m )Read( Q[i].l ) , Read( Q[i].r ) , Read( Q[i].k ) , Q[i].id = i;
	
	sort( 1 + B , 1 + n + B );
	int Cnt = unique( 1 + B , 1 + n + B ) - B - 1;
	For( i , 1 , n )A[i] = lower_bound( 1 + B , 1 + Cnt + B , A[i] ) - B , d[i] = make_pair( A[i] , i );
	
	sort( 1 + d , 1 + n + d );
	
	div( 1 , Cnt , 1 , m );
	
	For( i , 1 , m )printf("%d\n",ans[i]);
	
	return 0;
}
