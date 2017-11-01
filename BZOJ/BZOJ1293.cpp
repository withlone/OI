#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e6 +1;
typedef long long LL;

int n,k,T,Ct;LL Ans=0x7fffffff;
int Num[MAXN];

struct Data{
	LL x;int Col;
	bool operator < ( Data T )const{ return x<T.x; }
}Jew[MAXN];
queue< Data >Que;

int main(){
	
	Read( n );Read( k );
	for( int i=1;i<=k;i++ ){
		Read( T );
		while( T-- )Read( Jew[++Ct].x ),Jew[Ct].Col = i;
	}
	sort( 1+Jew,1+n+Jew );
	for( int i=1;i<=n;i++ ){
		Que.push( Jew[i] );
		if( !Num[Jew[i].Col]++ )k--;
		for( ;Num[Que.front().Col]>1;Que.pop() )
			Num[Que.front().Col]--;
		if( !k )Ans = min( Ans,Que.back().x-Que.front().x );
	}
	printf("%lld\n",Ans);
	return 0;
}
