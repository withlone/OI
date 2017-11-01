#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;

template <typename Type>inline void Read( Type &in ){
	in = 0;char ch=getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if(ch=='-')f=-1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )in = in *10 +ch-'0';in *= f;
}

const int MAXN = 2e4 +1;
const int MAXT = 1e5 +1;
const int MAXM = 0x7fffffff;
const int MAXV = 1e5 +1;
typedef long long LL;
#define Pair pair<LL,LL>

int n,T,m;LL Sum,w,v;
Pair Dt1[MAXT],Dt2[MAXT];

bool TLE_Check( int x ){
	if( x-1<(n>>1)||T-x<(n>>1) )return false;
	priority_queue<Pair> l,r;
	Sum = 0;
	for( int i=1;i< x;i++ )l.push( make_pair(-Dt1[i].second,-Dt1[i].first) );
	for( int i=x+1;i<=T;i++ )r.push( make_pair(-Dt1[i].second,-Dt1[i].first) );
	for( int i=1;i<=(n>>1);i++ ){
		if( l.empty()||r.empty() )return false;
		Sum += (-l.top().first) + (-r.top().first);
		l.pop();r.pop();
	}
	return Sum<=m-Dt1[x].second;
}

void TLE(){
	int l = 1,r = T;
	while( l<r-1 ){
		int Mid = l+r >>1;
		if( TLE_Check(Mid) )l = Mid;
		else r = Mid-1;
	}
	if( !l&&r<=0 )printf("-1\n");
	else printf("%lld\n",Dt1[TLE_Check(r)?r:l].first);
}

int main(){
	
	freopen("war.in","r",stdin);
	freopen("war.out","w",stdout);
	Read( n );Read( T );Read( m );
	for( int i=1;i<=T;i++ )Read( w ),Read( v ),Dt1[i] = make_pair( w,v ),Dt2[i] = make_pair( v,w );
	sort( 1+Dt1,1+T+Dt1 );
	sort( 1+Dt2,1+T+Dt2 );
	for( int i=1;i<=n;i++ ) Sum += Dt2[i].first;
	if( Sum>m||n>T )return printf("-1\n"),0;
	TLE();
	return 0;
}
