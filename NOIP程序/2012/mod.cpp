#include<cstdio>

int A,B,Tmp,Ans;

int Gcd(int a,int b,int &x,int &y){
	if(!b){
		x=1;y=0;
		return a;
	}
	int Result=Gcd(b,a%b,x,y);
	int Tmp=x;x=y;y=Tmp-a/b*y;
	return Result;
}

int main(){
	
	freopen( "mod.in" , "r" , stdin ) ;
	freopen( "mod.out" , "w" , stdout ) ;
	
	scanf("%d%d",&A,&B);
	Gcd(A,B,Ans,Tmp);
	printf("%d\n",(Ans%B+B)%B);
	return 0;
}
