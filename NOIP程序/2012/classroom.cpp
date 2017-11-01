#include<cstdio>

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e6 +1;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

int n,m,l,r,Last;
int R[MAXN],d[MAXN],s[MAXN],t[MAXN];
int Sum[MAXN];

bool Ch( int x ){
	if( x>Last )
		For( i , Last+1 , x )Sum[s[i]] += d[i],Sum[t[i]+1] -= d[i];
	else
		For( i , x+1 , Last )Sum[s[i]] -= d[i],Sum[t[i]+1] += d[i];
	Last = x;int Tot = 0;
	For( i , 1 , n ){
		Tot += Sum[i];
		if( Tot>R[i] )return false;
	}
	return true;
}

int main(){
	
	freopen( "classroom.in" , "r" , stdin ) ;
	freopen( "classroom.out" , "w" , stdout ) ;
	
	Read( n );Read( m );
	For( i , 1 , n )Read( R[i] );
	For( i , 1 , m )Read( d[i] ),Read( s[i] ),Read( t[i] );
	l = 1,r = m;bool Flag=0;
	while( l<r ){
		int Mid = l+r>>1;
		if( Ch(Mid) )l = Mid+1;
		else r = Mid,Flag=1;
	}
	if( !Flag )puts("0");
	else printf("-1\n%d\n",l);
	return 0;
}
