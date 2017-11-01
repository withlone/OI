#include<cstdio>
#include<cmath>

const int MAXN = 10005;
typedef long long LL;
const LL Mod  = 9901;

int A,B;

int Size;LL Xcc;
int p[MAXN];
bool V[MAXN]={1,1};

void Make(){
	for(int i=2;i<MAXN;i++){
		if(!V[i]) p[++Size]=i;
		for(int j=1;j<=Size && p[j]*i <=MAXN;j++){
			V[p[j]*i] = true;
			if(!(i%p[j])) break;
		}
	}
}

LL Mul(LL n,LL m){
	LL Ans=0;n %= Xcc;
	for(; m ; m>>=1 , n=(n+n) %Xcc)
		if(m&1)
			Ans = (Ans + n) %Xcc;
	return Ans;
}

LL Pow(LL n,LL m){
	LL Ans=1;n %= Xcc;
	for(; m ; m>>=1 , n= Mul(n,n) )
		if(m&1)
			Ans = Mul(Ans,n) ;
	return Ans%Xcc;
}

void Solve(){
	LL Ans=1;
	for(int i=1; p[i]*p[i] <=A ;i++)
		if(!(A % p[i])){
			int Num=0;
			while(!(A % p[i])){
				++Num;
				A /= p[i];
			}
			Xcc = ( p[i]-1 ) *Mod;
			Ans = (( Pow( p[i],Num*B+1 )-1 + Xcc ) / ( p[i]-1 ) *Ans )%Mod;
		}
	if( A>1 ){
		Xcc = ( A-1 ) *Mod;
		Ans = (( Pow( A,B+1 )-1 + Xcc ) / ( A-1 ) *Ans )%Mod;
	}
	printf("%lld\n",Ans);
}

int main(){
	scanf("%d%d",&A,&B);
	
	Make();
	
	Solve();
	
	return 0;
}
