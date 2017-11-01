#include<cstdio>

#define For( i , _Begin, _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

typedef long long LL;
#define Lson rt << 1 , l , mid
#define Rson rt << 1 | 1 , mid + 1 , r
static const int maxn = 1e5 +1;
static const int maxm = maxn * 5;
static const int mod = 19961993;

int m , Cnt;

bool V[282];
int p[61] , s;
LL Inv[282];

void Init(){
	For( i , 2 , 281 ){
		if( !V[i] )p[ ++s ] = i;
		for( int j = 1 ; j <= s && i * p[j] <= 281 ; j++ ){
			V[ i * p[j] ] = true;
			if( !( i % p[j] ) )break;
		}
	}
	Inv[1] = 1;
	For( i , 2 , 281 )
		Inv[i] = ( mod - mod / i ) * Inv[ mod % i ] % mod;
}

LL Hv[maxm] , sum[maxm];

int Up( int rt , int l , int r ){
	if( !( l * r ) )return l ^ r;
	sum[rt] = sum[l] * sum[r] % mod;
	Hv[rt] = Hv[l] | Hv[r];
	return rt;
}

void modify( int rt , int l , int r , int x , LL y , int z ){
	if( l == r )return Hv[rt] = y , sum[rt] = z , void();
	int mid = l + r >> 1;
	if( x <= mid )modify( Lson , x , y , z );else modify( Rson , x , y , z );
	Up( rt , rt << 1 , rt << 1 | 1 );
}

int Query( int rt , int l , int r , int L , int R ){
	if( l > R || r < L )return 0;
	if( l >= L && r <= R )return rt;
	int mid = l + r >> 1;
	return Up( ++Cnt , Query( Lson , L , R ) , Query( Rson , L , R ) );
}

void Build( int rt , int l , int r ){
	if( l == r )return Hv[rt] = 2 , sum[rt] = 3 , void();
	int mid = l + r >> 1;
	Build( Lson );Build( Rson );
	Up( rt , rt << 1 , rt << 1 | 1 );
}

int main(){
	
	Init();
	
	Read( m );
	
	Build( 1 , 1 , 1e5 );
		
	while( m-- ){
		LL opt , x , y;
		Read( opt );Read( x );Read( y );Cnt = maxn << 2;
		if( !opt ){
			int t = Query( 1 , 1 , 1e5 , x , y );
			LL ans = sum[t];
			For( i , 1 , 60 )
				if( Hv[t] & ( 1LL<< i - 1 ) )
					ans = ans * ( p[i] - 1 ) * Inv[ p[i] ] % mod;
			printf("%lld\n",ans);
		}
		else{
			int t = y , tmp = y;y = 0;
			for( int i = 1 ; i <= 60 && t != 1 ; i++ )
				if( !( t % p[i] ) ){
					y |= 1LL << i - 1;
					while( !( t % p[i] ) )t /= p[i];
				}
			modify( 1 , 1 , 1e5 , x , y , tmp );
		}
	}
	
	return 0;
}
