#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##End = (_End) ; i <= (i##End) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

#define Lson rt<<1 , l , mid
#define Rson rt<<1|1 , mid + 1 , r
typedef long long LL;
static const int maxn = 3e5 +1;
static const int maxm = 4e6 +1;
static const int maxx = 1e7 + 1;

bool V[maxx];
int p[maxx] , phi[maxx] , Ct;

int T , n , m;
LL A[maxm] , sum[maxm] , lazy[maxm];

void Up( int rt ){
	sum[rt] = sum[ rt<<1 ] + sum[ rt<<1|1 ];
	A[rt] = ( A[ rt<<1 ] == A[ rt<<1|1 ] ? A[ rt<<1 ] : 0 );
}
void Pd( int rt , int L , int R ){
	int l = rt << 1 , r = rt << 1 | 1;
	A[l] = A[r] = lazy[l] = lazy[r] = lazy[rt];
	sum[l] = L * lazy[rt];sum[r] = R * lazy[rt];
	lazy[rt] = -1;
}
void Build( int rt , int l , int r ){
	lazy[rt] = -1;
	if( l == r ){ Read( A[rt] );sum[rt] = A[rt];return; }
	int mid = l + r >> 1;
	Build( Lson );Build( Rson );
	Up( rt );
}
void modify( int rt , int l , int r , int L , int R , LL k ){
	if( l > R || r < L )return;
	if( l >= L && r <= R ){
		if( k != -1 ){ sum[rt] = ( r - l + 1 ) * ( lazy[rt] = A[rt] = k );return; }
		else if( A[rt] ){ sum[rt] = ( r - l + 1 ) * ( lazy[rt] = A[rt] = phi[ A[rt] ] );return; }
	}
	int mid = l + r >> 1;
	if( lazy[rt] != -1 && l != r )Pd( rt , mid - l + 1 , r - mid );
	modify( Lson , L , R , k );modify( Rson , L , R , k );
	Up( rt );
}
LL Query( int rt , int l , int r , int L , int R ){
	if( l > R || r < L )return 0;
	if( l >= L && r <= R )return sum[rt];
	int mid = l + r >> 1;
	if( lazy[rt] != -1 && l != r )Pd( rt , mid - l + 1 , r - mid );
	return Query( Lson , L , R ) + Query( Rson , L , R );
}

int main(){
	
	phi[1] = 1;
	For( i , 2 , maxx - 1 ){
		if( !V[i] )phi[i] = i - 1 , p[ ++Ct ] = i;
		for( int j = 1; j <= Ct && p[j] * i <= maxx - 1 ; j++ ){
			V[ p[j] * i ] = true;
			phi[ p[j] * i ] = phi[i] * ( p[j] - 1 );
			if( !( i % p[j] ) ){
				phi[ p[j] * i ] = phi[i] * p[j];
				break;
			}
		}
	}
	
	Read( T );
	
	while( T-- ){
		Read( n );Read( m );
		Build( 1 , 1 , n );
		while( m-- ){
			int opt , x , y;LL z;
			Read( opt );Read( x );Read( y );
			if( opt == 1 )modify( 1 , 1 , n , x , y , -1 );
			else if( opt == 2 )Read( z ) , modify( 1 , 1 , n , x , y , z );
			else printf("%lld\n",Query( 1 , 1 , n , x , y ));
		}
	}
	
	return 0;
}
