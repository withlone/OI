#include<cstdio>
#include<cmath>
using namespace std;

const int MAXN = 32768 +1;

int A,B,Ans_A,Ans_B;

int Gcd( int x,int y ){
	return !y?x:Gcd( y,x%y );
}

int main(){
	
	freopen("near.in","r",stdin);
	freopen("near.out","w",stdout);
	scanf("%d/%d",&A,&B);
	for( int i=1;i<MAXN;i++ ){
		if( i==B )continue;
		int T = (int)floor(A*1.0/B*i+0.5);
		if( T/Gcd(T,i)==A&&i/Gcd(T,i) )continue;
		if( abs( T*1.0/i -A*1.0/B )< abs( Ans_A*1.0/Ans_B -A*1.0/B ) ||!Ans_A&&!Ans_B ){
			Ans_A = T;Ans_B = i;
		}
	}
	printf("%d/%d\n",Ans_A,Ans_B);
	return 0;
}
