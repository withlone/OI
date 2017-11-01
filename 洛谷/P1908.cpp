#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 4e4 +1;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
#define Lop( i , _End , _Begin ) for( int i=_End;i>=_Begin;i-- )

int n,Ans;int A[MAXN];
pair<int,int>D[MAXN];

struct BIT{
	int d[MAXN];
	int Lowbit( int k ){ return k&-k; }
	void Add( int x ){
		for( ;x<=n;x += Lowbit( x ) )d[x]++;
	}
	int Get( int x ){
		int Res = 0;
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
	printf("%d\n",Ans);
	return 0;
}
