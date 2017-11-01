#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i=(_Begin),i##END=(_End);i<=(i##END);i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

static const int Inf = 0x7fffffff;
static const int MAXN = 2e5 +1;

int n , m;bool f;
char map[MAXN][2];

int Get( int );
char Getchar();

namespace Segment_tree{
	
	#define Lson rt<<1 , l , mid
	#define Rson rt<<1|1 , mid+1 , r
	
	struct data{
		int Dis[4];
		data(){ memset( Dis , -1 , sizeof Dis ) ; }
	}T[MAXN << 2] , quq , temp;
	
	data merge( data l , data r ){
		
		data res;
		int tmp = Inf;
		if( l.Dis[0] != -1 && r.Dis[0] != -1 )tmp = min( tmp , l.Dis[0] + r.Dis[0] + 1 );
		if( l.Dis[2] != -1 && r.Dis[3] != -1 )tmp = min( tmp , l.Dis[2] + r.Dis[3] + 1 );
		res.Dis[0] = ( tmp == Inf ? -1 : tmp );
		
		tmp = Inf;
		if( l.Dis[1] != -1 && r.Dis[1] != -1 )tmp = min( tmp , l.Dis[1] + r.Dis[1] + 1 );
		if( l.Dis[3] != -1 && r.Dis[2] != -1 )tmp = min( tmp , l.Dis[3] + r.Dis[2] + 1 );
		res.Dis[1] = ( tmp == Inf ? -1 : tmp );
		
		tmp = Inf;
		if( l.Dis[0] != -1 && r.Dis[2] != -1 )tmp = min( tmp , l.Dis[0] + r.Dis[2] + 1 );
		if( l.Dis[2] != -1 && r.Dis[1] != -1 )tmp = min( tmp , l.Dis[2] + r.Dis[1] + 1 );
		res.Dis[2] = ( tmp == Inf ? -1 : tmp );
		
		tmp = Inf;
		if( l.Dis[1] != -1 && r.Dis[3] != -1 )tmp = min( tmp , l.Dis[1] + r.Dis[3] + 1 );
		if( l.Dis[3] != -1 && r.Dis[0] != -1 )tmp = min( tmp , l.Dis[3] + r.Dis[0] + 1 );
		res.Dis[3] = ( tmp == Inf ? -1 : tmp );
		
		return res;
	}
	
	void Build( int rt , int l , int r ){
		if( l == r ){
			if( map[l][0] == '.' )T[rt].Dis[0] = 0;
			if( map[r][1] == '.' )T[rt].Dis[1] = 0;
			if( !( T[rt].Dis[0] + T[rt].Dis[1] ) )T[rt].Dis[2] = T[rt].Dis[3] = 1;
			return;
		}
		int mid = l + r >> 1;
		Build( Lson );Build( Rson );
		T[rt] = merge( T[ rt << 1 ] , T[ rt << 1 | 1 ] );
	}
	void Query( int rt , int l , int r , int L , int R ){
		if( l > R || r < L )return;
		if( l >= L && r <= R ){
			if( !f )quq = T[rt] , f = 1;
			else quq = merge( quq , T[rt] );
			return;
		}
		int mid = l + r >> 1;
		Query( Lson , L , R );Query( Rson , L , R );
	}
	
}using namespace Segment_tree;

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n << 1 )map[ i > n ? i - n : i ][ i > n ] = Getchar();
	Build( 1 , 1 , n );
	
	while( m-- ){
		f = 0;
		int x , y;
		Read( x );Read( y );
		if( Get( x ) > Get( y ) )swap( x , y );
		Query( 1 , 1 , n , Get( x ) , Get( y ) );
		if( x <= n && y <= n )printf("%d\n",quq.Dis[0]);
		else if( x <= n )printf("%d\n",quq.Dis[2]);
		else if( y <= n )printf("%d\n",quq.Dis[3]);
		else printf("%d\n",quq.Dis[1]);
	}
	
	return 0;
}

char Getchar(){
	char ch = getchar();
	while( ch != '.' && ch != 'X' )ch = getchar();
	return ch;
}
int Get( int x ){ return x > n ? x - n : x ; }
