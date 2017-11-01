#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e5 +1;

int T,n,A,B;int x[MAXN],y[MAXN],e[MAXN];
int Mp[MAXN<<1];

int Fa[MAXN<<1];
int Find( int t ){ return t==Fa[t]?t:Fa[t] = Find( Fa[t] ); }

int main(){
	
	Read( T );
	while( T-- ){
		int Ct = 0;bool Flag = 1;
		Read( n );
		for( int i=1;i<=n<<1;i++ )Fa[i] = i;
		for( int i=1;i<=n;i++ ){
			Read( x[i] );Read( y[i] );Read( e[i] );
			Mp[++Ct] = x[i];Mp[++Ct] = y[i];
		}
		sort( 1+Mp,1+Ct+Mp );
		for( int i=1;i<=n;i++ )if( e[i] ){
			A = lower_bound( Mp+1,Mp+1+Ct,x[i] )-Mp;
			B = lower_bound( Mp+1,Mp+1+Ct,y[i] )-Mp;
			Fa[Find(A)] = Find(B);
		}
		for( int i=1;i<=n&&Flag;i++ )if( !e[i] ){
			A = lower_bound( Mp+1,Mp+1+Ct,x[i] )-Mp;
			B = lower_bound( Mp+1,Mp+1+Ct,y[i] )-Mp;
			if( Find(A)==Find(B) )Flag = 0;
		}
		puts( Flag?"YES":"NO" );
	}
	return 0;
}
