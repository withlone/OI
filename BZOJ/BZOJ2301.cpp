#include<cstdio>

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 5e4 + 10;

int n , a , b , c , d , k;

bool V[maxn];
int mu[maxn];int pri[maxn] , cnt;

void Init(){
	mu[1] = 1;
	for( int i = 2 ; i <= 5e4 ; i++ ){
		if( !V[i] )pri[ ++cnt ] = i , mu[i] = -1;
		for( int j = 1 ; j <= cnt && pri[j] * i <= 5e4 ; j++ ){
			V[ pri[j] * i ] = true;
			if( !( i % pri[j] ) )break;
			mu[ pri[j] * i ] = -mu[i];
		}
		mu[i] += mu[i - 1];
	}
}

LL Get( int x , int y ){
	x /= k;y /= k;
	LL Res = 0;int Nxt , top = min( x , y );
	for( int i = 1 ; i <= top ; i = Nxt + 1 ){
		Nxt = min( min( x / ( x / i ) , y / ( y / i ) ) , top );
		Res += 1LL * ( mu[Nxt] - mu[i - 1] ) * ( x / i ) * ( y / i );
	}
	return Res;
}

int main(){
	
	Init();
	
	Read( n );
	
	while( n-- ){
		
		Read( a );Read( b );Read( c );Read( d );Read( k );
		
		printf("%lld\n",Get( b , d ) - Get( a - 1 , d ) - Get( b , c - 1 ) + Get( a - 1 , c - 1 ));
		
	}
	
	return 0;
}
