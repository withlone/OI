#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

template < typename Type >inline void Read( Type &in ){
	in=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )in = in *10 + ch-'0';
}

const int MAXN = 1e5 +1;
typedef long long LL;

int n,m;
int A[MAXN],B[MAXN],C[MAXN];

double Get( int i,LL x ){
	double Delta = (B[i]*B[i]-4*A[i]*(C[i]-x));
	if( Delta<0 )return 0;
	return max( (-B[i]+sqrt(Delta))*1.0/(2*A[i]),0.0 );
}
bool Check( LL x ){
	double Sum = 0;
	for( int i=1;i<=n;i++ )Sum += Get( i,x );
	return Sum>=m*1.0;
}
void Div(){
	LL l=0,r=1e13;
	while( l<r ){
		LL Mid = l+r>>1;
		if( Check(Mid) )r = Mid;
		else l = Mid+1;
	}
	printf("%lld\n",Check(l)?l:r);
}

int main(){
	
	freopen("factory.in","r",stdin);
	freopen("factory.out","w",stdout);
	Read( n );Read( m );
	for( int i=1;i<=n;i++ )Read( A[i] ),Read( B[i] ),Read( C[i] );
	Div();
	return 0;
}
