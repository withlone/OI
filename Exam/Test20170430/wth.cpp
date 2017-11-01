#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch=='-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}

typedef long long LL;
static const LL MAXB = 1e12 +1;
static const int MAXA = 5e5 +1;
static const int MAXN = 13;
#define For( i , _Begin , _End   ) for( int i=_Begin;i<=_End;i++ )
#define Rep( i , _End   , _Begin ) for( int i=_End;i>=_Begin;i-- )

int n,Mn;LL Bmin,Bmax;
int A[MAXN];

LL Dt[MAXA];bool Vis[MAXA];
#define Pair pair< LL,int >
void Dijkstra(){
	priority_queue< Pair,vector< Pair >,greater< Pair > >Hp;
	memset( Dt,0x3f,sizeof Dt );
	Dt[0] = 0;
	Hp.push( make_pair( 0,0 ) );
	while( !Hp.empty() ){
		int p = Hp.top().second;Hp.pop();
		if( Vis[p] )continue;
		Vis[p] = true;
		For( i , 1 , n ){
			int t = ( p+A[i] )%Mn;
			if( Dt[t] > Dt[p] + A[i] ){
				Dt[t] = Dt[p] + A[i];
				Hp.push( make_pair( Dt[t],t ) );
			}
		}
	}
}

LL Count( LL R ){
	LL Res = 0;
	For( i , 0 , Mn-1 )
		if( Dt[i]<=R )Res += ( R-Dt[i] )/Mn+1;
	return Res;
}
#define OnlineJudge
int main(){
	
	#ifdef OnlineJudge
		freopen("wth.in","r",stdin);
		freopen("wth.out","w",stdout);
	#endif
	
	Mn = 0x7fffffff;
	Read( n );Read( Bmin );Read( Bmax );
	For( i , 1 , n )Read( A[i] ),Mn = min( Mn,A[i] );
	Dijkstra();
	printf("%lld\n",Count( Bmax )-Count( Bmin-1 ));
	return 0;
}
