#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline Type max ( Type x , Type y ){ return x > y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e5 + 10;

int n;

bool V[maxn];

int Fa[maxn];
int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int main(){
	
	For( i , 1 , 10000 )Fa[i] = i;
	
	Read( n );
	
	For( i , 1 , n ){
		int x , y , fx , fy;
		Read( x );Read( y );
		fx = Find( x );fy = Find( y );
		if( fx == fy )V[fx] = true;
		else{
			if( fx > fy )fx ^= fy ^= fx ^= fy;
			Fa[fx] = fy;
			if( V[fx] )V[fy] = true;
			else V[fx] = true;
		}
	}
	
	For( i , 1 , n + 1 )
		if( !V[i] )return printf("%d\n",i - 1) , 0;
}
