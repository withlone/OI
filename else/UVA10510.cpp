#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e5 + 10;

bool ans;
int Case;
int n;
int m;

int Ct;
int Ht[maxn];
int Nt[maxn];
int To[maxn];
int Cm[maxn];

void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	Cm[Ct] = x;
	To[Ct] = y;
}

bool V[maxn];

int dct;
int dfn[maxn];
int Low[maxn];
int num[maxn];
int dep[maxn];
int tp;
int stack[maxn];

int cnt;

int Fa[maxn];

bool Find( int x , int y ){
	if( dep[x] > dep[y] )x ^= y ^= x ^= y;
	while( x != y && Fa[y] ){
		if( ++num[ Fa[y] ] > 1 )return true;
		y = Cm[ Fa[y] ];
	}
	return false;
}

void tarjan( int x ){
	if( ans )return;
	int y;
	V[x] = true;
	stack[ ++tp ] = x;
	dfn[x] = Low[x] = ++dct;
	Rep( i , Ht[x] , Nt[i] ){
		int y = To[i];
		if( !dfn[y] ){
			Fa[y] = i;
			dep[y] = dep[x] + 1;
			tarjan( y );
			Low[x] = min( Low[x] , Low[y] );
		}
		else if( V[y] ){
			Low[x] = min( Low[x] , dfn[y] );
			if( Find( x , y ) )return ans = true , void();
		}
	}
	if( dfn[x] != Low[x] )return;
	++cnt;
	do
		V[ y = stack[ tp-- ] ] = false;
	while( x != y );
}

int main(){
	
	Read( Case );
	
	while( Case-- ){
		
		#define mem( x ) memset( x , 0 , sizeof x )
		
		Ct = dct = cnt = tp = 0;
		mem( Ht );mem( dfn );mem( Low );mem( V );mem( Fa );mem( num );mem( dep );
		
		Read( n );Read( m );
		
		For( i , 1 , m ){
			int x , y;
			Read( x );Read( y );
			Ins( x + 1 , y + 1 );
		}
		
		ans = 0;
		
		For( i , 1 , n )if( !dfn[i] )
			dep[i] = 1 , tarjan( i );
		
		if( cnt > 1 )ans = true;
		
		puts( ans ? "NO" : "YES" );
		
	}
	
	return 0;
}
