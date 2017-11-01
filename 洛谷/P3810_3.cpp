#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e5 +1;
static const int maxm = 2e6 +1;

int n , m;
int ans[maxn] , num[maxn];

struct data{
	int x , y , z , size , id , sum;
	bool operator < ( data t ) const { return x < t.x || x == t.x && y < t.y || x == t.x && y == t.y && z < t.z; }
	bool operator == ( data t ) const { return x == t.x && y == t.y && z == t.z; }
	bool operator != ( data t ) const { return !( *this == t ); }
}Q[maxn] , Qt[maxn];

namespace BIT{
	
	int T[maxm];
	
	int Lowbit( int x ){ return x & -x ; }
	
	void Add( int x , int f ){
		for( int i = x ; i <= m ; i += Lowbit( i ) )
			T[i] += f;
	}
	
	int Query( int x ){
		int Res = 0;
		for( int i = x ; i ; i -= Lowbit( i ) )Res += T[i];
		return Res;
	}
	
}using namespace BIT;

void CDQ( int l , int r ){
	if( l == r )return;
	int mid = l + r >> 1;
	CDQ( l , mid );CDQ( mid + 1 , r );
	int pos = l , qt = l - 1;
	For( i , mid + 1 , r ){
		while( pos <= mid && Q[pos].y <= Q[i].y )Add( Q[pos].z , Q[pos].size ) , Qt[ ++qt ] = Q[pos++];
		Q[i].sum += Query( Q[i].z );Qt[ ++qt ] = Q[i];
	}
	For( i , l , pos - 1 )Add( Q[i].z , -Q[i].size );
	while( pos <= mid )Qt[ ++qt ] = Q[pos++];
	For( i , l , r )Q[i] = Qt[i];
}

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n )Read( Q[i].x ) , Read( Q[i].y ) , Read( Q[i].z ) , Q[i].size = 1;
	
	sort( 1 + Q , 1 + n + Q );
	
	int Cnt = 0;
	For( i , 1 , n )
		if( Q[i] != Q[Cnt] )Q[ ++Cnt ] = Q[i] , Q[i].id = Cnt;
		else Q[Cnt].size++;
	
	CDQ( 1 , Cnt );
	
	For( i , 1 , Cnt )ans[ Q[i].sum + Q[i].size - 1 ] += Q[i].size;
	
	For( i , 0 , n - 1 )printf("%d\n",ans[i]);
	
	return 0;
}
