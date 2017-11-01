#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e6 + 10;

int T;
bool V[maxn];
int cnt;
int phi[maxn];
int pri[maxn];
int mu[maxn];
long long ans[maxn];

void Init( int mx ){
	
	mu[1] = 1;phi[1] = 1;
	For( i , 2 , mx ){
		if( !V[i] )pri[ ++cnt ] = i , mu[i] = -1 , phi[i] = i - 1;
		For( j , 1 , cnt ){
			int t = pri[j] * i;
			if( t > mx )break;
			V[t] = true;
			if( !( i % pri[j] ) ){
				phi[t] = phi[i] * pri[j];
				break;
			}
			phi[t] = phi[i] * ( pri[j] - 1 );
			mu[t] = -mu[i];
		}
	}
	
	For( i , 1 , mx )
		for( int j = i ; j <= mx ; j += i )
			ans[j] += 1LL * phi[i] * i + ( i == 1 ) >> 1;
	ans[1] = 1;
}

int main(){
	
	Init( 1e6 );
	
	Read( T );
	
	while( T-- ){
		int n;
		Read( n );
		printf("%lld\n",ans[n] * n);
	}
	
	return 0;
}
