#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 5e4 + 10;

int T;
bool V[maxn];
int cnt;
int pri[maxn];
int mu[maxn];

void Init(){
	
	mu[1] = 1;
	For( i , 2 , 5e4 ){
		if( !V[i] )pri[ ++cnt ] = i , mu[i] = -1;
		For( j , 1 , cnt ){
			int t = pri[j] * i;
			if( t > 5e4 )break;
			V[t] = true;
			if( !( i % pri[j] ) )break;
			mu[t] = -mu[i];
		}
	}
	
	For( i , 1 , 5e4 )mu[i] += mu[i - 1];
}

LL Solve( int n , int m , int x ){
	if( n > m )n ^= m ^= n ^= m;
	LL Res = 0;
	for( int i = 1 , Nxt ; i <= n ; i = Nxt + 1 ){
		Nxt = min( n , min( n / ( n / i ) , m / ( m / i ) ) );
		Res += 1LL * ( mu[Nxt] - mu[i - 1] ) * ( n / ( i * x ) ) * ( m / ( i * x ) );
	}
	return Res;
}

int main(){
	
	Init();
	
	Read( T );
	
	while( T-- ){
		int n , m , x;
		Read( n );Read( m );Read( x );
		printf("%lld\n",Solve( n , m , x ));
	}
	
	return 0;
}
