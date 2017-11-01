#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 17;

LL Luck,n,L,R,Ans,Pro=1,s;
LL Uluck[MAXN],Num[MAXN];

LL Calc( LL A ){
	return R/A-(L-1)/A;
}
LL Gcd( LL A,LL B ){
	return !B?A:Gcd( B,A%B );
}
LL Lcm( LL A,LL B ){
	return A/Gcd( A,B )*B;
}
void Dfs( int Dep ){
	if( Dep==n+1 ){
		Pro = Luck;
		for( int i=1;i<=s;i++){
			Pro = Lcm( Pro,Num[i] );
			if( Pro>R||Pro<0 )return;
		}
		Ans += ( s&1?-1:1 )*Calc( Pro );
		return ;
	}
	Dfs( Dep+1 );
	Num[++s] = Uluck[Dep];
	Dfs( Dep+1 );
	s--;
}

int main(){
	
	freopen("lucky.in","r",stdin);
	freopen("lucky.out","w",stdout);
	scanf("%lld%lld%lld%lld",&Luck,&n,&L,&R);
	for( int i=1;i<=n;i++ )scanf("%lld",&Uluck[i]);
	Dfs( 1 );
	printf("%lld\n",Ans);
	return 0;
}
