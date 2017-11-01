#include<set>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

char Getchar(){
	char ch = getchar();
	while( ch > 'Z' || ch < 'A' )ch = getchar();
	return ch;
}

static const int maxn = 30;
static const int maxm = 1e5 + 10;

int m;

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];

bool Vis[maxn];

void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
}

bool V[maxn];

int tp;
int stack[maxn];

int dct;
int dfn[maxn];
int Low[maxn];

int cnt;
set< char >st[maxn];
set< char >:: iterator it;

void tarjan( int x ){
	int y;
	V[x] = true;
	stack[ ++tp ] = x;
	dfn[x] = Low[x] = ++dct;
	Rep( i , Ht[x] , Nt[i] ){
		y = To[i];
		if( !dfn[y] )tarjan( y ) , Low[x] = min( Low[x] , Low[y] );
		else if( V[y] )Low[x] = min( Low[x] , dfn[y] );
	}
	if( dfn[x] != Low[x] )return;
	++cnt;
	do{
		y = stack[ tp-- ];
		V[y] = false;
		st[cnt].insert( y + 'A' - 1 );
	}while( x != y );
}

int main(){
	bool f = 0;
	while( Read( m ) , m ){
		
		if( f )puts("");f = 1;
		
		#define mem( x ) memset( x , 0 , sizeof x )
		
		Ct = tp = dct = cnt = 0;
		mem( Ht );mem( Vis );mem( dfn );mem( Low );
		
		For( i , 1 , m ){
			char T[6];
			For( j , 1 , 5 )Vis[ T[j] = Getchar() - 'A' + 1 ] = true;
			char ans = Getchar() - 'A' + 1;
			For( j , 1 , 5 )
				if( ans != T[j] )Ins( ans , T[j] );
		}
		
		For( i , 1 , maxn - 1 )if( Vis[i] )
			if( !dfn[i] )tarjan( i );
		
		sort( 1 + st , 1 + cnt + st );
		
		For( i , 1 , cnt ){
			while( !st[i].empty() ){
				it = st[i].begin();
				st[i].erase( *it );
				printf("%c%c",*it , st[i].empty() ? '\n' : ' ' );
			}
		}
	}
	
	return 0;
}
