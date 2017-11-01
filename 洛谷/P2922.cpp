#include<cstdio>

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 5e5 +1;

int n , m , L , In , Ct;
int Ch[MAXN][2] , Cnt[MAXN] , Sz[MAXN] , Fa[MAXN];
int A[MAXN];

void Insert( int len ){
	int p = 0;
	while( len-- ){
		Read( In );
		if( !Ch[p][In] )Ch[p][In] = ++Ct , Fa[Ch[p][In]] = p;
		p = Ch[p][In];
		Cnt[p]++;
	}
	Sz[p]++;
}
int Get(){
	int p = 0 , Res = 0;
	For( i , 1 , L ){
		if( !Ch[p][A[i]] )return Res;
		p = Ch[p][A[i]];
		Res += Sz[p];
	}
	return Res - Sz[p] + Cnt[p];
}

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n ){
		Read( L );
		Insert( L );
	}
	while( m-- ){
		Read( L );
		For( i , 1 , L )Read( A[i] );
		printf("%d\n",Get());
	}
	return 0;
}
