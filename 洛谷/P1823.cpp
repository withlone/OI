#include<cstdio>

static const int MAXN = 5e5 +1;

int n,Ans,h;
int St[MAXN],Tp;

int main(){
	
	scanf("%d",&n);
	for( int i=1;i<=n;i++ ){
		scanf("%d",&h);
		int Tmp = Tp;
		while( h>=St[Tmp]&&Tmp )Ans++,Tmp--;
		if( Tmp )Ans++;
		while( h> St[Tp] &&Tp  )Tp--;
		St[++Tp] = h;
	}
	printf("%d\n",Ans);
	return 0;
}
