#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 5e5 + 10;
static const int maxm = 2e5 + 10;
static const int maxx = maxm << 2;

int n , Qct , Ct;
int ans[maxm];

struct query{ int x , y , z , id , f , sum ; }Q[maxx] , Qt[maxx];

namespace BIT{
	
	int T[maxn];
	
	int Lowbit( int x ){ return x & -x ; }
	
	void Add( int x , int f ){
		for( int i = x ; i <= n ; i += Lowbit( i ) )
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
	int qt = l - 1 , ps = l;
	For( i , mid + 1 , r ){
		while( ps <= mid && Q[ps].x <= Q[i].x ){
			if( !Q[ps].f )Add( Q[ps].y , Q[ps].z );
			Qt[ ++qt ] = Q[ ps++ ];
		}
		if( Q[i].f )Q[i].sum += Query( Q[i].y );
		Qt[ ++qt ] = Q[i];
	}
	For( i , l , ps - 1 )if( !Q[i].f )Add( Q[i].y , -Q[i].z );
	while( ps <= mid )Qt[ ++qt ] = Q[ ps++ ];
	For( i , l , r )Q[i] = Qt[i];
}

int main(){
	
	Read( n );
	
	while( 1 ){
		int f , x1 , y1 , x2 , y2 , z;
		Read( f );if( f == 3 )break;
		Read( x1 );Read( y1 );
		if( f == 1 )Read( z );
		else Read( x2 ) , Read( y2 );
		if( f == 1 )
			Q[ ++Qct ] = (query){ x1 , y1 , z , 0 , 0 , 0 };
		else{
			++Ct;
			++Qct;Q[ Qct ] = (query){ x2 , y2 , 0 , Ct , 1 , 0 };
			++Qct;Q[ Qct ] = (query){ x1 - 1 , y1 - 1 , 0 , Ct , 1 , 0 };
			++Qct;Q[ Qct ] = (query){ x1 - 1 , y2 , 0 , Ct , -1 , 0 };
			++Qct;Q[ Qct ] = (query){ x2 , y1 - 1 , 0 , Ct , -1 , 0 };
		}
	}
	
	CDQ( 1 , Qct );
	
	For( i , 1 , Qct )
		if( Q[i].f )ans[ Q[i].id ] += Q[i].f * Q[i].sum;
	
	For( i , 1 , Ct )printf("%d\n",ans[i]);
	
	return 0;
}
