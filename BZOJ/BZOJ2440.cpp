#include<cstdio>

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 1e6 + 10;

int T , n;
bool V[maxn];
int mu[maxn];int pri[maxn] , Cnt;

void Init(){
	
	mu[1] = 1;
	
	for( int i = 2 ; i <= 1e5 ; i++ ){
		if( !V[i] )pri[ ++Cnt ] = i , mu[i] = -1;
		for( int j = 1 ; j <= Cnt && pri[j] * i <= 1e5 ; j++ ){
			V[ pri[j] * i ] = true;
			if( !( i % pri[j] ) )break;
			mu[ pri[j] * i ] = -mu[i];
		}
	}
	
}

int Get( LL x ){
	int Res = 0;
	for( LL i = 1 ; i * i <= x ; i++ )
		Res += mu[i] * ( x / ( i * i ) );
	return Res;
}

int main(){
	
	Init();
	
	Read( T );
	
	while( T-- ){
		Read( n );
		LL l = 1 , r = 2e9 , ans;
		while( l <= r ){
			LL mid = l + r >> 1;
			if( Get( mid ) >= n )ans = mid , r = mid - 1;
			else l = mid + 1;
		}
		printf("%lld\n",ans);
	}
	
	return 0;
}
