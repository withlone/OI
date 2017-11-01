#include<cstdio>

const int MAXN = 1001;

int n,T;
int p[MAXN],Phi[MAXN],s;bool V[MAXN];

void Make(){
	Phi[1] = 1;
	for( int i=2;i<MAXN;i++ ){
		if( !V[i] ) p[++s] = i,Phi[i] = i-1;
		for( int j=1;j<=s&&p[j]*i<MAXN;j++ ){
			V[p[j]*i] = true;
			Phi[p[j]*i] = Phi[i] * (p[j]-1);
			if( !(i%p[j]) ){
				Phi[p[j]*i] = Phi[i] * p[j];
				break;
			}
		}
	}
}

int main(){
	
	Make();
	scanf("%d",&T);
	for( int Case=1;Case<=T;Case++ ){
		scanf("%d",&n);
		int Ans = 0;
		for( int i=1;i<=n;i++ )Ans += Phi[i];
		printf("%d %d %d\n",Case,n,(Ans<<1)+1);
	}
	return 0;
}
