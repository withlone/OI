#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 2e4 +1;

int n,m,p;
int A[MAXN];

int main(){
	
	scanf("%d%d",&n,&m);
	while( m-- ){
		int Ans = 0,Sum = 1;
		scanf("%d",&p);
		A[p] ^= 1;
		for( int i=2;i<=n;i++ )
			if( A[i]^A[i-1] )Sum++;
			else{
				Ans = max( Ans,Sum );
				Sum = 1;
			}
		printf("%d\n",max( Ans,Sum ));
	}
	return 0;
}
