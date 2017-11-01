#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e5 +1;
typedef long long LL;
#define Pair pair<LL,int>

int n,k,H,T,A;
LL f[MAXN],Sum;
Pair Que[MAXN];

int main(){
	
	Read( n );Read( k );
	for( int i=1;i<=n;i++ ){
		Read( A );Sum += A;
		f[i] = Que[H].first + A;
		while( Que[T].first>=f[i]&&H<=T )T--;
		Que[++T] = make_pair( f[i],i );
		while( i-Que[H].second>k&&H<=T )H++;
	}
	for( int i=n-k;i<=n;i++ )f[n] = min( f[n],f[i] );
	printf("%lld\n",Sum-f[n]);
	return 0;
}
