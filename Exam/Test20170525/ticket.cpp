#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )
#define Rep( i , _Begin , _End ) for( int i=(_Begin);i>=(_End);i-- )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int Inf  = 2e9;
static const int MAXN = 1e4 +1;

int L[4] , C[4] , d[MAXN];
int n , A , B , M;

/*namespace TLE{
	int f[MAXN];
	int TLE(){
		memset( f , 0x3f , sizeof f );
		f[A] = 0;
		if( A <= B )
		For( i , A+1 , B )
			For( j , A , i-1 ){
				if( d[i] - d[j] <= L[1] )f[i] = min( f[i] , f[j] + C[1] );
				else if( d[i] - d[j] <= L[2] )f[i] = min( f[i] , f[j] + C[2] );
				else if( d[i] - d[j] <= L[3] )f[i] = min( f[i] , f[j] + C[3] );
			}
		else
		Rep( i , A-1 , B )
			Rep( j , A , i+1 ){
				if( d[j] - d[i] <= L[1] )f[i] = min( f[i] , f[j] + C[1] );
				else if( d[j] - d[i] <= L[2] )f[i] = min( f[i] , f[j] + C[2] );
				else if( d[j] - d[i] <= L[3] )f[i] = min( f[i] , f[j] + C[3] );
			}
		return f[B];
	}
}*/

namespace Zkw{
	int Tr[MAXN<<2];
	void Mf( int x , int k ){
		for( Tr[ x+=M ] = k,x>>=1;x;x>>=1 )
			Tr[x] = min( Tr[x<<1] , Tr[x<<1|1] );
	}
	int Query( int s , int t ){
		int Res = Inf;
		for( s += M-1 , t += M+1; s^t^1 ;s>>=1 , t>>=1 ){
			if( ~s&1 )Res = min( Res , Tr[s^1] );
			if(  t&1 )Res = min( Res , Tr[t^1] );
		}
		return Res;
	}
}using namespace Zkw;

namespace Div{
	int f[MAXN];
	int Div(){
		if( A > B )swap( A , B );
		for( M = 1 ; M < n + 2 ; M<<=1 );
		For( i , 1 , n )f[i] = Tr[ i+M ] = Inf;
		For( i , n+1 , MAXN-1 )Tr[i] = Inf;
		Rep( i , M , 1 )Tr[i] = min( Tr[i<<1] , Tr[i<<1|1] );
		Mf( A , 0 );f[A] = 0;
		For( i , A+1 , B ){
			int x1 = lower_bound( d+A,d+i,d[i]-L[1] ) - d;
			int x2 = lower_bound( d+A,d+i,d[i]-L[2] ) - d;
			int x3 = lower_bound( d+A,d+i,d[i]-L[3] ) - d;
			if( x1 < i )
			f[i] = min( f[i] , Query( x1 , i-1 ) + C[1] );
			if( x2 < i )
			f[i] = min( f[i] , Query( x2 , i-1 ) + C[2] );
			if( x3 < i )
			f[i] = min( f[i] , Query( x3 , i-1 ) + C[3] );
			Mf( i , f[i] );
		}
		return f[B];
	}
}

void Init();

int main(){
	
	#define Judge
	
	#ifdef Judge
		freopen("ticket.in","r",stdin);
		freopen("ticket.out","w",stdout);
	#endif
	
	Init();
	
	printf("%d\n",Div::Div());
	
	return 0;
}

void Init(){
	For( i , 1 , 3 )Read( L[i] );
	For( i , 1 , 3 )Read( C[i] );
	Read( n );
	Read( A );Read( B );
	For( i , 2 , n )Read( d[i] );
}
