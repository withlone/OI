#include<cstdio>

int n,a0,a1,b0,b1;

int Gcd(int x,int y){
	while(x^=y^=x^=y%=x);return y;
}

bool Check(int x){
	return !(x%a1)&&1==Gcd(x/a1,a0/a1)&&1==Gcd(b1/b0,b1/x);
}

int main(){
	scanf("%d",&n);
	while(n--){
		scanf("%d%d%d%d",&a0,&a1,&b0,&b1);
		int Ans=0;
		for(int x=1;x*x<=b1;x++){
			if(!(b1%x)){
				Ans+=Check(x);
				if(x*x!=b1) Ans+=Check(b1/x);
			}
		}
		printf("%d\n",Ans);
	}
		
	return 0;
}
