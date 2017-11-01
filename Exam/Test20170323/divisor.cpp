#include<cstdio>

const int MAXN = 1e9 ;
typedef long long LL;

int n,Ans=1,Ct;
int Prm[11]={0,2,3,5,7,11,13,17,19,23,27},Num[11];

void Dfs( int Rank,int Last,LL Sum,int Tot ){
	if( Rank==11 ){
		if( Ct< Tot )Ans = Sum,Ct = Tot;
		if( Ct<=Tot&&Sum<Ans )Ans = Sum,Ct = Tot;
		return ;
	}
	Dfs( Rank+1,0,Sum,Tot );
	for( int i=1;i<=Last&&Sum*Prm[Rank]<=n;i++ )
		Dfs( Rank+1,i,Sum*=Prm[Rank],Tot*(i+1) );
}

int main(){
	
	freopen("divisor.in","r",stdin);
	freopen("divisor.out","w",stdout);
	
	scanf("%d",&n);
	
	Dfs( 1,30,1,1 );
	
	printf("%d\n",Ans);
	return 0;
}
