#include<cstdio>

const int MAXN = 10;
const int MAXM = 100;
typedef long long LL;

int n,k,Tp;LL Ans;
LL St[MAXM],Num[MAXM],f[MAXN][MAXM][MAXM];

bool Ok( int A ){
	return !(A&(A<<1));
}

int Get( int A ){
	int B = 0;
	for( ;A;A &= A-1,B++ );
	return B;
}

void Init(){
	for( int i=0;i<(1<<n);i++ )
		if( Ok(i)&&Get(i)<=k )St[++Tp] = i;
}

int main(){
	
	scanf("%d%d",&n,&k);
	Init();
	for( int i=1;i<=Tp;i++ )f[1][Num[i]=Get(St[i])][i] = 1;
	for( int i=2;i<=n;i++ )
		for( int j=0;j<=k;j++ )
			for( int Ts=1;Ts<=Tp;Ts++ )
				if( Num[Ts]<=j )
					for( int Ls=1;Ls<=Tp;Ls++ )
						if( Num[Ts]+Num[Ls]<=j&&
						!( St[Ts]&St[Ls]||St[Ts]&(St[Ls]<<1)||St[Ts]&(St[Ls]>>1) ) )
							f[i][j][Ts] += f[i-1][j-Num[Ts]][Ls];
	for( int i=1;i<=Tp;i++ )Ans += f[n][k][i];
	printf("%lld\n",Ans);
	return 0;
}
