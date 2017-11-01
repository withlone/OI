#include<cstdio>

const int MAXN = 2000;
const int MAXM = 1e6 +1;

int N,M;long long Ans;
bool V[MAXN][MAXN];
int p[MAXM],s,Phi[MAXM];
bool Vis[MAXM];

void Make(){
	for( int i=2;i<=N;i++ ){
		if( !Vis[i] ){
			p[++s] = i;
			Phi[i] = i-1;
		}
		for( int j=1;j<=s&&p[j]*i<=N;j++ ){
			Vis[p[j]*i] = true;
			Phi[p[j]*i] = Phi[i]*( p[j]-1 );
			if( !(i%p[j]) ){
				Phi[p[j]*i] = Phi[i]*p[j];
				break;
			}
		}
	}
}

int main(){
	
	freopen("indexthree.in","r",stdin);
	freopen("indexthree.out","w",stdout);
	scanf("%d%d",&N,&M);
	
	if( N==M ){
		Make();Phi[1] = 1;
		for( int i=1;i<=N;i++ ) Ans += Phi[i];
		printf("%lld\n",(Ans<<1)-1);
		return 0;
	}
	
	for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)if(!V[i][j])
		for(int I=i,J=j;I+i<=N&&J+j<=M;)
			V[I+=i][J+=j]=true;
	
	for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)Ans+=!V[i][j];
	
	printf("%d\n",Ans);
	return 0;
}
