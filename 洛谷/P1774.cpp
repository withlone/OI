#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch=='-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}

static const int MAXN = 5e5 +1;
typedef long long LL;

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
#define Lop( i , _End , _Begin ) for( int i=_End;i>=_Begin;i-- )

int n;LL Ans;int A[MAXN];
pair<LL,int>D[MAXN];

struct BIT{
	int d[MAXN];
	int Lowbit( int k ){ return k&-k; }
	void Add( int x ){
		for( ;x<=n;x += Lowbit( x ) )d[x]++;
	}
	LL Get( int x ){
		LL Res = 0;
		for( ;x;x -= Lowbit( x ) )Res += d[x];
		return Res;
	}
}Bit;

int main(){
	
	Read( n );
	For( i , 1 , n )Read( D[i].first ),D[i].second = i;
	sort( 1+D , 1+n+D );
	For( i , 1 , n )A[D[i].second] = i;
	Lop( i , n , 1 )Ans += Bit.Get( A[i]-1 ),Bit.Add( A[i] );
	printf("%lld\n",Ans);
	return 0;
}
