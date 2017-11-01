#include<cstdio>

const int Mod = 1e9+7;
const int MAXN = 1e6 +1;
typedef long long LL;

LL N,M;LL Ans=1;

int main(){
	
	freopen("indexone.in","r",stdin);
	freopen("indexone.out","w",stdout);
	scanf("%lld%lld",&N,&M);
	if( M>N ) return printf("0\n"),0;
	for( int i=N;i>=2;i-- ){
		if( i>N-M&&i<N )Ans = Ans * i % Mod;
		Ans = Ans * i %Mod;
	}
	printf("%lld\n",Ans);
	return 0;
}
