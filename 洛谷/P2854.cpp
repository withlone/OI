#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e3 +1;
static const int MAXM = 1e4 +1;
typedef long long LL;

int L,n,B;LL Ans=-1;
LL f[MAXN][MAXN];

struct Data{
	int x,w,f,c;
	bool operator < ( Data T )const{ return x<T.x||x==T.x&&w<T.w; }
}d[MAXM];

int main(){
	
	memset( f,-1,sizeof f );
	Read( L );Read( n );Read( B );
	for( int i=1;i<=n;i++ )Read( d[i].x ),Read( d[i].w ),Read( d[i].f ),Read( d[i].c );
	sort( 1+d,1+n+d );
	
	f[0][0] = 0;
	for( int i=1;i<=n;i++ )
		for( int j=B;j>=d[i].c;j-- )
			if( f[d[i].x][j-d[i].c]>=0 )
				f[d[i].x+d[i].w][j] = max( f[d[i].x+d[i].w][j],f[d[i].x][j-d[i].c]+d[i].f );
	for( int i=1;i<=B;i++ )Ans = max( Ans,f[L][i] );
	printf("%lld\n",Ans);
	return 0;
}
