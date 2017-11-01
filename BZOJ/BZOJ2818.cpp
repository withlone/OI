#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }

typedef long long LL;
static const int maxn = 1e7 + 10;

int n;
int cnt;
bool V[maxn];
int pri[maxn];
int mu[maxn];
LL sm[maxn];

void Init(){
	
	mu[1] = 1;
	For( i , 2 , n ){
		if( !V[i] )pri[ ++cnt ] = i , mu[i] = -1;
		For( j , 1 , cnt ){
			int t = pri[j] * i;
			if( t > n )break;
			V[t] = true;
			if( !( i % pri[j] ) )break;
			mu[t] = -mu[i];
		}
	}
	
	For( i , 1 , cnt )
		For( j , 1 , n / pri[i] )
			sm[pri[i] * j] += mu[j];
	
	For( i , 1 , n )sm[i] += sm[i - 1];
}

int main(){
	
	scanf("%d",&n);
	
	Init();
	
	LL ans = 0;
	int Nxt;
	for( int i = 1 ; i <= n ; i = Nxt + 1 ){
		Nxt = min( n , n / ( n / i ) );
		ans += ( sm[Nxt] - sm[i - 1] ) * ( n / i ) * ( n / i );
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
