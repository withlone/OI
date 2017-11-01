#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline Type max ( Type x , Type y ){ return x > y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

typedef long long LL;
static const int maxn = 1e6 +1;
static const int maxm = maxn << 2;

int n , m;LL ans;
int A[maxn] , Nxt[maxn] , H[maxn] , W[maxn];

LL tag[maxm] , sum[maxm] , mx[maxm];

void modify( int rt , int l , int r , int L , int R , int f ){
	if( l > R || r < L )return;
	if( l >= L && r <= R )return mx[rt] += f ,tag[rt] += f , sum[rt] += f , void();
	int mid = l + r >> 1;
	modify( rt << 1 , l , mid , L , R , f );modify( rt << 1 | 1 , mid + 1 , r , L , R , f );
	mx[rt] = max( mx[ rt << 1 ] , mx[ rt << 1 | 1 ] ) + tag[rt];
	sum[rt] = sum[ rt << 1 ] + sum[ rt << 1 | 1 ] + tag[rt];
}

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n ){
		Read( A[i] );
		Nxt[i] = H[ A[i] ];
		H[ A[i] ] = i;
	}
	For( i , 1 , m )Read( W[i] );
	
	For( i , 1 , n ){
		modify( 1 , 1 , n , Nxt[i] + 1 , i , W[ A[i] ] );
		if( Nxt[i] )modify( 1 , 1 , n , Nxt[Nxt[i]] + 1 , Nxt[i] , -W[ A[i] ] );
		ans = max( ans , mx[1] );
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
