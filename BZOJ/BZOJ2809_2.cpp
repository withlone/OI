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

int n , m , Cnt;LL ans;
int B[maxn] , C[maxn] , D[maxn];

int H[maxn] , Nt[maxm] , To[maxm] , Ct;

int Stk[maxx] , tp;

void Ins( int x , int y ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
}

int root[maxn];
int Ch[maxx][2] , Sz[maxx];LL sum[maxx];

void Del( int &rt ){ Stk[ ++tp ] = rt;sum[rt] = Ch[rt][0] = Ch[rt][1] = Sz[rt] = 0;rt = 0; }

int merge( int x , int y ){
	if( !( x * y ) )return x ^ y;
	Sz[x] += Sz[y];sum[x] += sum[y];
	Ch[x][0] = merge( Ch[x][0] , Ch[y][0] );
	Ch[x][1] = merge( Ch[x][1] , Ch[y][1] );
	Del( y );
	return x;
}

void Insert( int &rt , int l , int r , int x , LL y ){
	if( !rt )rt = ( tp ? Stk[ tp-- ] : ++Cnt );
	Sz[rt]++;sum[rt] += y;
	if( l == r )return;
	int mid = l + r >> 1;
	if( x <= mid )Insert( Ch[rt][0] , l , mid , x , y );
	else Insert( Ch[rt][1] , mid + 1 , r , x , y );
}

int Query( int rt , LL Limit ){
	int l = 1 , r = n , Res = 0;
	while( l < r ){
		int mid = l + r >> 1;
		if( sum[ Ch[rt][0] ] <= Limit )
			Limit -= sum[ Ch[rt][0] ] , Res += Sz[ Ch[rt][0] ] , l = mid + 1 , rt = Ch[rt][1];
		else r = mid , rt = Ch[rt][0];
	}
	return Res + min( Limit / (LL)D[l] , (LL)Sz[rt] );
}

void Dfs( int x ){
	Rep( i , H[x] , Nt[i] ){
		Dfs( To[i] );
		root[x] = merge( root[x] , root[To[i]] );
	}
	Insert( root[x] , 1 , n , lower_bound( 1 + D , 1 + n + D , B[x] ) - D , B[x] );
	ans = max( ans , ( LL ) C[x] * Query( root[x] , m ) );
}

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n ){
		int x;
		Read( x );Read( B[i] );Read( C[i] );D[i] = B[i];
		Ins( x , i );
	}
	
	sort( 1 + D , 1 + n + D );
	n = unique( 1 + D , 1 + n + D ) - D - 1;
	
	Dfs( 0 );
	
	printf("%lld\n",ans);
	
	return 0;
}
