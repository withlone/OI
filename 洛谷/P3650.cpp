#include<cstdio>
#include<algorithm>
using namespace std;

static const int MAXN = 1001;

int n,Ans=0x7ffffff;
int H[MAXN];

int main(){
	
	scanf("%d",&n);
	for( int i=1;i<=n;i++ )scanf("%d",&H[i]);
	for( int h=0;h<=100;h++ ){
		int Sum = 0;
		for( int i=1;i<=n;i++ )
			if( h - H[i]>17 )Sum += ( h - H[i] - 17)*( h - H[i] - 17);
			else if( h < H[i] )Sum += ( H[i]-h )*( H[i]-h );
		Ans = min( Ans,Sum );
	}
	printf("%d\n",Ans);
	return 0;
}
