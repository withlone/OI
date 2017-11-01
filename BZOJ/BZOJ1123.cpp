#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 1e5 + 10;
static const int maxm = 1e6 + 10;

int n , m;

int H[maxn] , Nt[maxm] , To[maxm] , Ct;
void Ins( int x , int y ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
}

LL ans[maxn];
int dfn[maxn] , Low[maxn] , V[maxn];
void tarjan( int x , int f ){
	int cnt = 0;
	dfn[x] = Low[x] = ++Ct;V[x] = 1;
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( y == f )continue;
		if( !dfn[y] ){
			tarjan( y , x );
			V[x] += V[y];
			Low[x] = min( Low[x] , Low[y] );
			if( Low[y] >= dfn[x] ){
				ans[x] += 1LL * cnt * V[y];
				cnt += V[y];
			}
		}
		else Low[x] = min( Low[x] , dfn[y] );
	}
	ans[x] += 1LL * cnt * ( n - cnt - 1 );
}

int main(){
	
	Read( n );Read( m );
	
	For( i , 1 , m ){
		int x , y;
		Read( x );Read( y );
		Ins( x , y );Ins( y , x );
	}
	
	Ct = 0;
	tarjan( 1 , 0 );
	
	For( i , 1 , n )
		printf("%lld\n",( ans[i] + n - 1 ) << 1);
	
	return 0;
}
