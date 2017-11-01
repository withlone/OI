#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 25e3+1;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

int n,x,y;
int A[MAXN],B[MAXN];
long long Ans;

int main(){
	
	Read( n );Read( x );Read( y );
	For( i , 1 , n )Read( A[i] ),Read( B[i] );
	sort( 1+A , 1+n+A );sort( 1+B , 1+n+B );
	For( i , 1 , n )
		if( A[i]>B[i] )Ans += ( A[i]-B[i] )*y;
		else Ans += ( B[i]-A[i] )*x;
	
	printf("%lld\n",Ans);
	return 0;
}
