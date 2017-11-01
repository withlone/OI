#include<cstdio>

int N,A,A1,B,B1;

int Gcd(int X,int Y){
	return !Y?X:Gcd(Y,X%Y);
}

bool Check(int X){
	return !(X%A1)&&Gcd(X/A1,A/A1)==1&&Gcd(B1/X,B1/B)==1;
}

int main(){
	
	freopen("homework.in","r",stdin);
	freopen("homework.out","w",stdout);
	scanf("%d",&N);
	while( N-- ){
		scanf("%d%d%d%d",&A,&A1,&B,&B1);
		if(A%A1||B1%B||B1%A1){printf("0\n");continue;}
		int Ans=0;
		for(int X=1;X*X<=B1;X++)
			if(!(B1%X)){
				Ans+=Check(X);
				if(X*X!=B1)Ans+=Check(B1/X);
			}
		printf("%d\n",Ans);
	}
	return 0;
}
