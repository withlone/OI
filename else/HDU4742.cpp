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
typedef pair< int , LL > par;
static const int mod = 1 << 30;
static const int maxn = 1e5 +1;

int Case , n;
int B[maxn] , C[maxn];

struct data{
	int x , y , z , id;par ant;
	bool operator < ( data t ) const {
		if( x != t.x )return x < t.x;
		if( y != t.y )return y < t.y;
		return z < t.z;
	}
	bool operator == ( data t ) const { return x == t.x && y == t.y && z == t.z; }
	bool operator != ( data t ) const { return !( *this == t ); }
}Q[maxn] , Qt[maxn];

namespace BIT{
	
	par T[maxn];
	
	int Lowbit( int x ){ return x & -x ; }
	
	void Merge( par &x , par y ){
		if( x.first < y.first )x = y;
		else if( x.first == y.first )x.second += y.second;
	}
	
	void Add( int x , par f ){
		for( int i = x ; i <= n ; i += Lowbit( i ) )
			Merge( T[i] , f );
	}
	
	void clear( int x ){
		for( int i = x ; i <= n ; i += Lowbit( i ) )
			T[i] = make_pair( 0 , 0 );
	}
	
	par Query( int x ){
		par Res = make_pair( 0 , 0 );
		for( int i = x ; i ; i -= Lowbit( i ) )Merge( Res , T[i] );
		return ++Res.first , Res;
	}
	
}using namespace BIT;

void CDQ( int l , int r ){
	if( l == r )return;
	int mid = l + r >> 1;
	
	CDQ( l , mid );
	
	For( i , l , r )Qt[i] = Q[i] , Qt[i].x = 0;
	
	sort( Qt + l , Qt + r + 1 );
	
	For( i , l , r )
		if( Qt[i].id <= mid )Add( Qt[i].z , Qt[i].ant );
		else Merge( Q[ Qt[i].id ].ant , Query( Qt[i].z ) );
	
	For( i , l , r )
		if( Qt[i].id <= mid )clear( Qt[i].z );
		
	CDQ( mid + 1 , r );
}

int main(){
	
	Read( Case );
	
	while( Case-- ){
		
		Read( n );
		For( i , 1 , n ){
			Read( Q[i].x );Read( Q[i].y );Read( Q[i].z );
			Q[i].ant = make_pair( 1 , 1 );B[i] = Q[i].y;C[i] = Q[i].z;
		}
		
		sort( 1 + Q , 1 + n + Q );
		sort( 1 + B , 1 + n + B );
		sort( 1 + C , 1 + n + C );
		
		int Cnt1 = unique( 1 + B , 1 + n + B ) - B - 1;
		int Cnt2 = unique( 1 + C , 1 + n + C ) - C - 1;
		For( i , 1 , n )
			Q[i].y = lower_bound( 1 + B , 1 + Cnt1 + B , Q[i].y ) - B ,
			Q[i].z = lower_bound( 1 + C , 1 + Cnt2 + C , Q[i].z ) - C ,
			Q[i].id = i;
		
		CDQ( 1 , n );
		
		par ans = make_pair( 0 , 0 );
		For( i , 1 , n )Merge( ans , Q[i].ant );
		printf("%d %lld\n",ans.first,ans.second % mod);
	}
	
	return 0;
}
