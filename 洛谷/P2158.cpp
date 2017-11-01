#include<cstdio>

const int MAXN = 4e4 +1;

int n,Ans;
int s,p[MAXN],Phi[MAXN];
bool Vis[MAXN]={1,1};

int main(){

	scanf("%d",&n);
	
	Phi[1] = 1;
	for( int i=2;i<=n;i++ ){
		if( !Vis[i] )p[++s] = i,Phi[i] = i-1;
		for( int j=1;j<=s&&p[j]*i<=n;j++ ){
			Vis[p[j]*i] = true;
			Phi[p[j]*i] = Phi[i] * ( p[j]-1 );
			if( !( i%p[j] ) ){
				Phi[p[j]*i] = Phi[i] * p[j];
				break;
			}
		}
	}
	for( int i=1;i< n;i++ )Ans += Phi[i];
	
	printf("%d\n",Ans<<1|1);
	return 0;
}
