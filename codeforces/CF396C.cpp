#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
#define Lson rt << 1 , l , mid
#define Rson rt << 1 | 1 , mid + 1 , r
static const int mod = 1e9 + 7;
static const int maxn = 3e5 + 1;
static const int maxx = maxn << 2;

int n , m , rs;
int A[maxn];
int Fa[maxn] , Dep[maxn];
int Dfn[maxn] , End[maxn] , Cnt;
int H[maxn] , Nt[maxn] , To[maxn] , Ct;

void Ins( int x , int y ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
}

void Dfs( int x ){
	Dfn[x] = ++Cnt;A[Cnt] = Dep[x];
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		Dep[y] = Dep[x] + 1;
		Dfs( y );
	}
	End[x] = Cnt;
}

LL sum[maxx] , tag1[maxx] , tag2[maxx] , tot[maxx];
void Up( int rt , int len ){
	sum[rt] = ( sum[rt << 1] + sum[rt << 1 | 1] + tag1[rt] * len + tag2[rt] * tot[rt] + mod ) % mod;
}

void Build( int rt , int l , int r ){
	if( l == r )return tot[rt] = A[l], void();
	int mid = l + r >> 1;
	Build( Lson );Build( Rson );
	tot[rt] = tot[rt << 1] + tot[rt << 1 | 1];
}

void modify1( int rt , int l , int r , int L , int R , LL f ){
	if( l > R || r < L )return;
	if( l >= L && r <= R )return sum[rt] = ( sum[rt] + f * ( r - l + 1 ) + mod ) % mod , tag1[rt] = ( tag1[rt] + f + mod ) % mod , void();
	int mid = l + r >> 1;
	modify1( Lson , L , R , f );modify1( Rson , L , R , f );
	Up( rt , r - l + 1 );
}

void modify2( int rt , int l , int r , int L , int R , LL f ){
	if( l > R || r < L )return;
	if( l >= L && r <= R )return sum[rt] = ( f * tot[rt] + sum[rt] + mod ) % mod , tag2[rt] = ( tag2[rt] + f + mod ) % mod , void();
	int mid = l + r >> 1;
	modify2( Lson , L , R , f );modify2( Rson , L , R , f );
	Up( rt , r - l + 1 );
}

LL Query( int rt , int l , int r , int x ){
	if( l == r )return sum[ rs = rt ];
	int mid = l + r >> 1;LL ans = 0;
	if( x <= mid )ans += Query( Lson , x );
	else ans += Query( Rson , x );
	return ( ans + tag1[rt] + tag2[rt] * tot[rs] + mod ) % mod;
}

int main(){
	
	Read( n );
	For( i , 2 , n )Read( Fa[i] ) , Ins( Fa[i] , i );
	
	Dep[1] = 1;
	Dfs( 1 );
	
	Build( 1 , 1 , n );
	
	Read( m );
	
	while( m-- ){
		LL opt , x , y , z;
		Read( opt );Read( x );
		if( opt == 1 ){
			Read( y );Read( z );
			modify1( 1 , 1 , n , Dfn[x] , End[x] , y + z * Dep[x] );
			modify2( 1 , 1 , n , Dfn[x] , End[x] , -z );
		}
		else printf("%lld\n",( Query( 1 , 1 , n , Dfn[x] ) + mod ) % mod);
	}
	
	return 0;
}
