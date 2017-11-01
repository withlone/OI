#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline Type min ( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

typedef long long LL;
static const int maxn = 2e5 +1;
static const int maxm = maxn << 2;

int n , Cnt , Ct;LL sum1 , sum2 , ans;
int val[maxm];int Ch[maxm][2];
int Rt[maxm] , Sz[maxm] , Ls[maxm] , Rs[maxm];
int Stk[maxm] , tp;

void Insert( int &rt , int l , int r , int k ){
	if( !rt )rt = ( tp ? Stk[ tp-- ] : ++Ct );
	Sz[rt]++;
	int mid = l + r >> 1;
	return l == r ? void() : k <= mid ?
		Insert( Ls[rt] , l , mid , k ) : Insert( Rs[rt] , mid + 1 , r , k );
}

void Read_In( int x ){
	Read( val[x] );
	if( val[x] )return;
	Read_In( Ch[x][0] = ++Cnt );Read_In( Ch[x][1] = ++Cnt );
}

int merge( int x , int y ){
	if( !( x * y ) )return x + y;
	sum1 += (LL)Sz[ Ls[y] ] * Sz[ Rs[x] ];
	sum2 += (LL)Sz[ Rs[y] ] * Sz[ Ls[x] ];
	Ls[y] = merge( Ls[x] , Ls[y] );
	Rs[y] = merge( Rs[x] , Rs[y] );
	Sz[y] = Sz[ Ls[y] ] + Sz[ Rs[y] ];
	Stk[ ++tp ] = x;Ls[x] = Rs[x] = Sz[x] = 0;
	return y;
}

void Dfs( int x ){
	if( !x )return;
	Dfs( Ch[x][0] );Dfs( Ch[x][1] );
	if( val[x] )return Insert( Rt[x] , 1 , n , val[x] );
	sum1 = sum2 = 0;
	Rt[x] = merge( Rt[ Ch[x][0] ] , Rt[ Ch[x][1] ] );
	ans += min( sum1 , sum2 );
}

int main(){
	
	Read( n );
	Read_In( ++Cnt );
	Dfs( 1 );
	
	printf("%lld\n",ans);
	
	return 0;
}
