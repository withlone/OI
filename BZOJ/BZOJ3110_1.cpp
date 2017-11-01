#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i=(_Begin),i##END=(_End);i<=(i##END);i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int MAXN = 5e4 +1;
static const int MAXM = 13e6;

int n , m , Ct , num;
int opt[MAXN]  , x[MAXN] , y[MAXN];LL z[MAXN] , A[MAXN];

int Ch[MAXM][2];LL Lz[MAXM] , Sum[MAXM];
struct Segment_tree{
	
	int Rt;
	
	void modify( int &rt , int l , int r , int L , int R ){
		if( l > R || r < L )return;
		if( !rt )rt = ++Ct;
		if( l >= L && r <= R ){
			Lz[rt]++;
			Sum[rt] += r - l + 1;
			return;
		}
		int mid = l + r >> 1;
		modify( Ch[rt][0] , l , mid , L , R );modify( Ch[rt][1] , mid+1 , r , L , R );
		Sum[rt] = Sum[ Ch[rt][0] ] + Sum[ Ch[rt][1] ] + Lz[rt] * ( r - l + 1 );
	}
	
	LL query( int rt , int l , int r , int L , int R ){
		if( l > R || r < L )return 0;
		if( l >= L && r <= R )return Sum[rt];
		int mid = l + r >> 1;
		return query( Ch[rt][0] , l , mid , L , R ) + query( Ch[rt][1] , mid+1 , r , L , R ) + Lz[rt] * ( 1 + min( r , R ) - max( l , L ) );
	}
	
}T[MAXN << 2];

namespace out_Segment_tree{
	
	void Insert( int rt , int l , int r , int L , int R , int k ){
		T[rt].modify( T[rt].Rt , 1 , n , L , R );
		if( l == r )return;
		int mid = l + r >> 1;
		if( k <= mid )Insert( rt<<1 , l , mid , L , R , k );
		else Insert( rt<<1|1 , mid+1 , r , L , R , k );
	}
	
	int Query( int rt , int l , int r , int L , int R , LL k ){
		if( l == r )return l;
		int mid = l + r >> 1;LL tmp = T[rt<<1].query( T[rt<<1].Rt , 1 , n , L , R );
		if( tmp >= k )return Query( rt<<1 , l , mid , L , R , k );
		return Query( rt<<1|1 , mid+1 , r , L , R , k - tmp );
	}
	
}using namespace out_Segment_tree;

int main(){
	
	Read( n );Read( m );
	
	For( i , 1 , m ){
		Read( opt[i] ) , Read( x[i] ) , Read( y[i] ) , Read( z[i] );
		if( opt[i] == 1 )A[ ++num ] = z[i];
	}
	sort( 1 + A , 1 + num + A );
	num = unique( 1 + A , 1 + num + A ) - A - 1;
	For( i , 1 , m )if( opt[i] == 1 )z[i] = lower_bound( 1 + A , 1 + num + A , z[i] ) - A;
	
	For( i , 1 , m )
		if( opt[i] == 1 )Insert( 1 , 1 , num , x[i] , y[i] , num - z[i] + 1 );
		else printf("%lld\n",A[num - Query( 1 , 1 , num , x[i] , y[i] , z[i] ) + 1]);
	
	return 0;
}
