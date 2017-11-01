#include<cstdio>
#include<algorithm>

using namespace std;

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;

static const int maxn = 1e7 + 10;
static const int mod = 20101009;

bool V[maxn];
int mu[maxn];
int pri[maxn] , cnt;
LL sum[maxn];
void Init(){
	mu[1] = 1;
	for( int i = 2 ; i <= 1e7 ; i++ ){
		if( !V[i] )pri[ ++cnt ] = i , mu[i] = -1;
		for( int j = 1 , t ; j <= cnt && ( t = pri[j] * i ) <= 1e7 ; j++ ){
			V[t] = true;
			if( !( i % pri[j] ) )break;
			mu[t] = -mu[i];
		}
	}
	for( int i = 1 ; i <= 1e7 ; i++ )
		sum[i] = (sum[i - 1] + 1LL * mu[i] * i * i % mod)%mod;
}

int calc2( int n , int m ){
	LL res = 0;
	for( int i = 1 , Nxt ; i <= n ; i = Nxt + 1 ){
		Nxt = min( n / ( n / i ) , m / ( m / i ) );
		res = ( res + ( ( sum[Nxt] - sum[i - 1] ) % mod )
		 * (( 1LL * ( n / i ) * ( n / i + 1 ) / 2 % mod )
		 * ( 1LL * ( m / i ) * ( m / i + 1 ) / 2 % mod ) % mod ) % mod ) % mod;
	}
	return res;
}

int calc1( int n , int m ){
	if( n > m )n ^= m ^= n ^= m;
	LL res = 0;
	for( int i = 1 , Nxt ; i <= n ; i = Nxt + 1 ){
		Nxt = min( n / ( n / i ) , m / ( m / i ) );
		res = ( res + 1LL * ( 1LL * ( i + Nxt ) * ( Nxt - i + 1 ) / 2 % mod ) * calc2( n / i , m / i ) ) % mod;
	}
	return ( res + mod ) % mod;
}

int main(){
	
	int n , m;
	
	Read( n );Read( m );
	
	Init();
	
	printf("%d\n",calc1( n , m ));
	
	return 0;
}
