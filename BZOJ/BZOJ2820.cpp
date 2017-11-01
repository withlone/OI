#include<cstdio>

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 1e7 +10;

int T , n , m;
bool V[maxn];int sum[maxn];
int mu[maxn] , pri[maxn] , cnt;

void Init(){
	
	mu[1] = 1;
	for( int i = 2 ; i <= 1e7 ; i++ ){
		if( !V[i] )pri[ ++cnt ] = i , mu[i] = -1;
		for( int j = 1 ; j <= cnt && pri[j] * i <= 1e7 ; j++ ){
			V[ pri[j] * i ] = true;
			if( !( i % pri[j] ) )break;
			mu[ pri[j] * i ] = -mu[i];
		}
	}
	
	for( int i = 1 ; i <= cnt ; i++ )
		for( int j = 1; pri[i] * j <= 1e7 ; j++ )sum[ pri[i] * j ] += mu[j];
	
	for( int i = 1 ; i <= 1e7 ; i++ )sum[i] += sum[i - 1];
}


LL Solve( int n , int m ){
	int top = min( n , m ) , Nxt;LL Res = 0;
	for( int i = 1 ; i <= top ; i = Nxt + 1 ){
		Nxt = min( min( n / ( n / i ) , m / ( m / i ) ) , top );
		Res += 1LL * ( sum[Nxt] - sum[i - 1] ) * ( n / i ) * ( m / i );
	}
	return Res;
}

int main(){
	
	Init();
	
	Read( T );
	
	while( T-- ){
		Read( n );Read( m );
		printf("%lld\n",Solve( n , m ));
	}
	
	return 0;
}
