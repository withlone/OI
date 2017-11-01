#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

static const int MAXN = 200 +1;
static const int Inf  = 1e8;
#define For( i , _Begin , _End ) for( int i=_Begin;i<= _End;i++ )
typedef long long LL;

int n,m,k,q,u,v,w;int Sum;LL Tot;
int f[MAXN][MAXN];

void Floyd(){
	For( k , 1 , n )
		For( i , 1 , n )
			For( j , 1 , n )
				f[i][j] = min( f[i][j],f[i][k] + f[k][j] );
}

int main(){
	
	scanf("%d%d%d%d",&n,&m,&k,&q);
	For( i , 0 , n )For( j , 0 , n )f[i][j] = Inf;
	For( i , 1 , n )f[i][i] = 0;
	For( i , 1 , m )scanf("%d%d%d",&u,&v,&w),f[u][v] = min( f[u][v] , w );
	
	Floyd();
	while( q-- ){
		scanf("%d%d",&u,&v);
		int Res = Inf;
		For( i , 1 , k )Res = min( Res,f[u][i] + f[i][v] );
		if( Res!=Inf )Sum++,Tot += Res;
	}
	printf("%d\n%lld\n",Sum,Tot);
	return 0;
}
