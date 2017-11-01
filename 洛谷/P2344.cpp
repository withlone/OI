#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch=='-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}

static const int MAXN = 1e5 +1;
static const int Mod  = 1e9 +9;
#define Sm first
#define Rk second
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
typedef long long LL;
typedef pair<LL,int> Pair;

int n;LL Ans;
LL A[MAXN];
Pair d[MAXN];

LL Sum[MAXN+1];
int Lowbit( int k ){ return k&-k; }
void Add( int x,LL k ){
	for( ;x<=n;x += Lowbit(x) )Sum[x] = ( Sum[x] + k )%Mod;
}
LL Get( int x ){
	LL Res = 0;
	for( ;x;x -= Lowbit(x) )Res = ( Res + Sum[x] )%Mod;
	return Res;
}

int main(){
	
	Read( n );
	For( i , 1 , n )Read( A[i] );
	n++;d[1].Rk = 1;d[1].Sm = 0;
	For( i , 2 , n )d[i].Rk = i,d[i].Sm = d[i-1].Sm + A[i-1];
	sort( 1+d , 1+n+d );
	For( i , 1 , n )A[d[i].Rk] = i;
	Add( A[1] , 1 );
	For( i , 2 , n ){
		Ans = Get( A[i] );
		Add( A[i],Ans );
	}
	printf("%lld\n",Ans);
	return 0;
}
