#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long LL;

LL Exgcd( LL A,LL B,LL &x,LL &y ){
	if( !B ){
		x = 1;y = 0;
		return A;
	}
	LL Gcd = Exgcd( B,A%B,y,x );
	y -= A/B*x;
	return Gcd;
}

LL A,B,n,x0,y0;

int main(){
	
	freopen( "feed.in","r",stdin );
	freopen( "feed.out","w",stdout );
	scanf("%lld%lld",&A,&B);
	
	LL Gcd = Exgcd( A,B,x0,y0 );
	A /= Gcd;B/= Gcd;
	
	while( ~scanf("%lld",&n) ){
		if( n%Gcd ){printf("BeiJu!\n");continue;}
		n /= Gcd;
		x0 *= n;y0 *= n;
		LL t = ( y0-x0 )/( A+B )-1;
		LL Ans = 0x7ffffff;
		Ans = min( Ans,abs( x0+B*t ) + abs( y0-A*t ) );
		t++;
		Ans = min( Ans,abs( x0+B*t ) + abs( y0-A*t ) );
		t++;
		Ans = min( Ans,abs( x0+B*t ) + abs( y0-A*t ) );
		printf("%lld\n",Ans);
		x0 /= n;y0 /= n;
	}
	return 0;
}
