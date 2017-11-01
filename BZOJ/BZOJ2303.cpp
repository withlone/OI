#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int mod = 1e9;
static const int maxn = 1e6 + 10;
static const int maxm = maxn << 2;

int n , m , k , f = -1 , N;
int A[maxn] , B[maxn] , C[maxn];

int Fa[maxm];

int Find( int x ){
	int t = x;
	while( t != Fa[t] )t = Fa[t];
	while( t != x ){
		int temp = Fa[x];
		Fa[x] = t;
		x = temp;
	}
	return t;
}

int qpow( int x ){
	LL res = 1 , t = 2;
	for( ; x ; x >>= 1 , t = t * t % mod )
		if( x & 1 )res = res * t % mod;
	return res;
}

bool V[maxn];
int calc( int en ){
	
	For( i , 1 , n + m << 1 )Fa[i] = i , V[i] = 0;
	
	Fa[1] = 1 + n;
	Fa[1 + m + n] = 1 + N + m;
	
	For( i , 1 , k ){
		int x = A[i] , y = B[i] , z = C[i];
		bool temp = ( !( x & 1 ) && !( y & 1 ) ) ^ en ^ z;
		if( !temp ){
			if( Find( x ) == Find( y + N + m ) )return 0;
			Fa[ Find( x ) ] = Find( y + n );
			Fa[ Find( x + n + m ) ] = Find( y + N + m );
		}
		else{
			if( Find( x ) == Find( y + n ) )return 0;
			Fa[ Find( y + N + m ) ] = Find( x );
			Fa[ Find( x + n + m ) ] = Find( y + n );
		}
	}
	
	int res = -1;
	
	For( i , 1 , n )
		if( !V[ Find( i ) ] ){
			V[ Find( i ) ] = V[ Find( i + n + m ) ] = true;
			++res;
		}
	For( i , 1 , m )
		if( !V[ Find( i + n ) ] ){
			V[ Find( i + n ) ] = V[ Find( i + N + m ) ] = true;
			++res;
		}
	
	return qpow( res );
}

int main(){
	
	Read( n );Read( m );Read( k );N = n << 1;
	
	for( int i = 1 ; i <= k ; i++ ){
		Read( A[i] ) , Read( B[i] ) , Read( C[i] );
		if( A[i] == 1 && B[i] == 1 ){
			if( f != -1 && C[i] != f )return puts("0") , 0;
			f = C[i];
			--k;--i;
		}
	}
	
	int ans = 0;
	
	if( f == -1 )ans = calc( 0 ) + calc( 1 );
	else ans = calc( f );
	
	printf("%d\n",ans % mod);
	
	return 0;
}
