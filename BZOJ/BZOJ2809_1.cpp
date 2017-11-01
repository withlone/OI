#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

typedef long long LL;
static const int maxn = 1e5 +1;
static const int maxm = maxn << 1;
static const int maxx = 2e6;

int n , m;
int B[maxn] , C[maxn] , D[maxn];

int H[maxn] , Nt[maxm] , To[maxm] , Ct;

int Dfn[maxn] , End[maxn] , Back[maxn] , Cnt;

void Ins( int x , int y ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
}

void Dfs( int x ){
	Dfn[x] = ++Cnt;Back[Cnt] = x;
	Rep( i , H[x] , Nt[i] )Dfs( To[i] );
	End[x] = Cnt;
}

int root[maxn];
int Ch[maxx][2] , Sz[maxx];
LL sum[maxx];
void modify( int pt , int &rt , int l , int r , int x , LL y ){
	sum[ rt = ++Cnt ] = sum[pt] + y;
	Sz[rt] = Sz[pt] + 1;
	if( l == r )return;
	int mid = l + r >> 1;
	if( x <= mid )Ch[rt][1] = Ch[pt][1] , modify( Ch[pt][0] , Ch[rt][0] , l , mid , x , y );
	else Ch[rt][0] = Ch[pt][0] , modify( Ch[pt][1] , Ch[rt][1] , mid + 1 , r , x , y );
}

int Query( int rt , int pt , LL limit ){
	int l = 1 , r = Ct , Res = 0;
	while( l < r ){
		int mid = l + r >> 1;
		if( sum[ Ch[rt][0] ] - sum[ Ch[pt][0] ] <= limit )
			limit -= sum[ Ch[rt][0] ] - sum[ Ch[pt][0] ] , Res += Sz[ Ch[rt][0] ] - Sz[ Ch[pt][0] ] , pt = Ch[pt][1] , rt = Ch[rt][1] , l = mid + 1;
		else r = mid - 1 , rt = Ch[rt][0] , pt = Ch[pt][0];
	}
	return Res + min( limit / (LL)D[l] , ( LL )( Sz[rt] - Sz[pt] ) );
}

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n ){
		int x;
		Read( x );Read( B[i] );Read( C[i] );D[i] = B[i];
		Ins( x , i );
	}
	Dfs( 1 );
	Cnt = 0;
	sort( 1 + D , 1 + n + D );
	Ct = unique( 1 + D , 1 + n + D ) - D - 1;
	For( i , 1 , n )modify( root[i - 1] , root[i] , 1 , Ct , lower_bound( 1 + D , 1 + Ct + D , B[ Back[i] ] ) - D , B[ Back[i] ] );
	
	LL ans = 0;
	For( i , 1 , n )ans = max( ans , (LL)C[i] * Query( root[End[i]] , root[Dfn[i] - 1] , m ) );
	
	printf("%lld\n",ans);
	
	return 0;
}
