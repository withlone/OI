#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

static const int MAXN = 11;
static const int Th[MAXN]={1,3,9,27,81,243,729,2187,6561,19683,59049};

int n,m,a,b,c,Ans;
int w[MAXN][MAXN],f[MAXN][MAXN*59049],Map[59049+1][MAXN];

int Check( int St,int t ){
	for( int i=1;i<=t;i++ )St/=3;
	return St%3;
}

bool Ok( int St ){
	for( int i=1;i<=n;i++ )if( !Map[St][i] )return false;
	return true;
}

int main(){
	
	for( int i=0;i<=Th[MAXN-1];i++ ){
		int t = i;
		for( int j=1;j<MAXN&&t;j++,t/=3 )
			Map[i][j] = t%3;
	}
	while( ~scanf("%d%d",&n,&m) ){
		memset( w,30,sizeof w );
		memset( f,30,sizeof f );
		Ans = w[0][0];
		for( int i=1;i<=m;i++ )scanf("%d%d%d",&a,&b,&c),w[a][b]=w[b][a]=min(w[a][b],c);
		for( int i=0;i<n;i++ )f[i+1][Th[i]]=0;
		for( int St=0;St<Th[n];St++ ){
			bool Vis_all=1;
			for( int i=1;i<=n;i++ ){
				for( int j=1;j<=n;j++ )
					if( Map[St][j]<=2&&i!=j )
							f[j][St+Th[j-1]] = min( f[j][St+Th[j-1]] , f[i][St] + w[i][j] );
				if( !Map[St][i] ) Vis_all=0;
			}
			if( Vis_all )
				for( int i=1;i<=n;i++ )Ans = min( Ans,f[i][St] );
		}
		printf("%d\n",Ans==w[0][0]?-1:Ans);
	}
	return 0;
}
