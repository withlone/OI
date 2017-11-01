#include<cstdio>

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}
template< typename Type >inline Type max ( Type x,Type y ){ return x>y?x:y; }

static const int MAXN = 1e5 +1;
typedef long long LL;

int n,m;
int A[MAXN],B[MAXN],V[MAXN];LL f[MAXN];

int main(){
	
	Read( n );Read( m );
	for( int i=1;i<=n;i++ )Read( A[i] ),Read( B[i] ),Read( V[i] );
	for( int i=1;i<=n;i++ )
		for( int j=m;j>=0;j-- )
			if( j>=V[i] )f[j] = max( f[j] + A[i],f[j-V[i]] + B[i] );
			else f[j] = f[j] + A[i];
	printf("%lld\n",f[m]*5);
	return 0;
}
