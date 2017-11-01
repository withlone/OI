#include<cstdio>
#include<algorithm>
using namespace std;

static const int MAXN = 1e5 +1;
typedef long long LL;
#define p first
#define c second

int n;LL Ans,m;
pair<LL,LL>Seq[MAXN];

int main(){
	
	scanf("%d%lld",&n,&m);
	for( int i=1;i<=n;i++ )scanf("%lld%lld",&Seq[i].p,&Seq[i].c);
	sort( 1+Seq,1+n+Seq );
	for( int i=1;i<=n;i++ ){
		LL t = m/Seq[i].p;
		if( t>=Seq[i].c )m -= Seq[i].c*Seq[i].p,Ans += Seq[i].c;
		else Ans += t,m -= t*Seq[i].p;
	}
	printf("%lld\n",Ans);
	return 0;
}
