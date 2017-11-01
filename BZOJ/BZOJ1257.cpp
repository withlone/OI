#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long LL;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

LL n,k,Ans;

int main(){
	
	scanf("%lld%lld",&n,&k);
	Ans = n*k;n = min( n,k );
	For( i , 1 , n ){
		LL L = i,R = min( n,k/(k/i) );
		Ans -= ( L+R )*( R-L+1 )/2*( k/i );
		i = R;
	}
	printf("%lld\n",Ans);
	return 0;
}
