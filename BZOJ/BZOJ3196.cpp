#include<cstdio>

#define For( i , _Begin , _End ) for( int i=(_Begin) , i##END = (_End);i<=(i##END);i++ )
#define Rep( i , _Begin , _End ) for( int i=(_Begin) , i##END = (_End);i>=(i##END);i-- )

template< typename Type >inline Type max( Type x , Type y ){ return x > y ? x : y ; }
template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void swap( Type &x , Type &y ){ x ^= y ^= x ^= y ; }
namespace read{
	const int LEN = 1 << 17;
	char buffer[LEN] , *MS , *MT;
	inline char Getchar(){
		if( MS == MT ){
			MT = ( MS = buffer ) + fread( buffer , 1 , LEN , stdin );
			if( MS == MT )return EOF;
		}
		return *MS++;
	}
	template< typename Type >inline void Read( Type &In ){
		In=0;char ch=Getchar();Type f = 1;
		for( ;ch> '9'||ch< '0';ch=Getchar() )if( ch == '-' )f = -1;
		for( ;ch>='0'&&ch<='9';ch=Getchar() )In = In*10 + ch-'0';In *= f;
	}
}

using namespace read;

static const int Inf  = 0x7fffffff;
static const int MAXN = 5e4 +1;
static const int MAXM = 4e6 +1;

int n , m;
int A[MAXN];

int Stk[MAXM] , Tp , Num;
int Fa[MAXM] , Ch[MAXM][2];
int Sz[MAXM] , Sm[MAXM] , Key[MAXM];

int New( int val ){
	int p = ++Num;
	if( Tp )p = Stk[Tp--];else p = ++Num;
	Fa[p] = Ch[p][0] = Ch[p][1] = 0;
	Sz[p] = Sm[p] = 1;Key[p] = val;
	return p;
}

struct Splay_tree{
	
	int Rt;
	
	int GS( int x ){ return x == Ch[Fa[x]][1]; }
	
	void Up( int x ){ Sz[x] = Sz[Ch[x][0]] + Sz[Ch[x][1]] + Sm[x]; }
	
	void Rotate( int x ){
		int p = GS( x ) , fa = Fa[x] , gfa = Fa[fa];
		Ch[fa][p] = Ch[x][p^1];
		if( Ch[x][p^1] )Fa[ Ch[x][p^1] ] = fa;
		Ch[x][p^1] = fa;
		Fa[fa] = x;
		Fa[x] = gfa;
		if( gfa )Ch[gfa][ Ch[gfa][1] == fa ] = x;
		Up( fa );Up( x );
	}
	
	void Splay( int x , int y ){
		for( int fa;( fa = Fa[x] ) != y;Rotate( x ) )
			if( Fa[fa] != y )Rotate( GS( fa ) == GS( x ) ? fa : x );
		if( !y )Rt = x;
	}
	
	int Find( int x ){
		int p = Rt;
		while( 1 )
			if( x < Key[p] )p = Ch[p][0];
			el	se{
				if( x == Key[p] ){ Splay( p , 0 );return p; }
				p = Ch[p][1];
			}
	}
	
	int Qrank( int x ){
		int p = Rt , Res = 0;
		while( 1 )
			if( x < Key[p] )p = Ch[p][0];
			else{
				Res += Sz[Ch[p][0]];
				if( x == Key[p] || !p ){ if( p )Splay( p , 0 );return Res; }
				Res += Sm[p];
				p = Ch[p][1];
			}
	}
	
	int Pre( int x ){
		Insert( x );
		int p = Ch[Rt][0];
		if( !p ){Del( x );return -Inf;}
		while( Ch[p][1] )p = Ch[p][1];
		Del( x );
		return Key[p];
	}
	
	int Next( int x ){
		Insert( x );
		int p = Ch[Rt][1];
		if( !p ){ Del( x );return Inf; }
		while( Ch[p][0] )p = Ch[p][0];
		Del( x );
		return Key[p];
	}
	
	void Insert( int x ){
		if( !Rt ){ Rt = New( x );return; }
		int p = Rt , fa = 0;
		while( 1 ){
			if( Key[p] == x ){
				Sm[p]++;Sz[p]++;
				return Splay( p , 0 );
			}
			fa = p;p = Ch[p][ x > Key[p] ];
			if( !p ){
				p = New( x );
				Fa[p] = fa;
				Ch[fa][ x > Key[fa] ] = p;
				return Splay( p , 0 );
			}
		}
	}
	
	void Del( int x ){
		int p = Find( x );
		if( Sm[Rt] > 1 )Sm[Rt]-- , Sz[Rt]--;
		else{
			Stk[++Tp] = Rt;
			if( !( Ch[Rt][0] + Ch[Rt][1] ) )Rt = 0;
			else if( !Ch[Rt][0] )Fa[ Rt = Ch[Rt][1] ] = 0;
			else if( !Ch[Rt][1] )Fa[ Rt = Ch[Rt][0] ] = 0;
			else{
				int tmp = Ch[p][0];
				while( Ch[tmp][1] )tmp = Ch[tmp][1];
				Splay( tmp , 0 );
				Ch[Rt][1] = Ch[p][1];
				Fa[Ch[p][1]] = Rt;
				Up( Rt );
			}
		}
	}
	
}root[MAXN<<2];
/*
namespace Segment_tree{
	
	#define Lson rt<<1 , l , mid
	#define Rson rt<<1|1 , mid+1 , r
	
	void Build( int rt , int l , int r ){
		For( i , l , r )root[rt].Insert( A[i] );
		if( l == r )return;
		int mid = l + r >> 1;
		Build( Lson );Build( Rson );
	}
	
	int Get_Rank( int rt , int l , int r , int L , int R , int k ){
		if( l > R || r < L )return 0;
		if( l >= L && r <= R )return root[rt].Qrank( k );
		int mid = l + r >> 1;
		return Get_Rank( Lson , L , R , k ) + Get_Rank( Rson , L , R , k );
	}
	
	int Get_Num( int L , int R , int k ){
		int l = 0 , r = Inf , Res;
		while( l <= r ){
			int mid = l + r >> 1;
			if( Get_Rank( 1 , 1 , n , L , R , mid ) + 1 <= k )Res = mid , l = mid + 1;
			else r = mid - 1;
		}
		return Res;
	}
	
	void Modify( int rt , int l , int r , int x , int y ){
		root[rt].Del( A[x] );
		root[rt].Insert( y );
		if( l == r )return;
		int mid = l + r >> 1;
		if( x <= mid )Modify( Lson , x , y );
		else Modify( Rson , x , y );
	}
	
	int Query( int rt , int l , int r , int L , int R , int k , int Flag ){
		if( l > R || r < L )return Flag * Inf;
		if( l >= L && r <= R )return Flag == -1 ? root[rt].Pre( k ) : root[rt].Next( k );
		int mid = l + r >> 1;
		return Flag == -1 ?
			max( Query( Lson , L , R , k , Flag ) , Query( Rson , L , R , k , Flag ) ) : 
			min( Query( Lson , L , R , k , Flag ) , Query( Rson , L , R , k , Flag ) ) ;
	}
	
}

//using namespace Segment_tree;
*/
namespace Zkw_segment_tree{
	int M;
	int Lp[MAXN<<2] , Rp[MAXN<<2];
	
	void Build( int x , int y , int z ){
		for( M = 1;M < n + 2;M <<= 1 );
		For( i , M + 1 , M << 1 )Lp[i] = Rp[i] = i - M;
		Rep( i , M - 1 , 1 )Lp[i] = Lp[i<<1] , Rp[i] = Rp[i<<1|1];
		For( i , 1 , M << 1 )
			For( j , Lp[i] , Rp[i] )root[i].Insert( A[j] );
	}
	
	int Get_Rank( int rt , int l , int r , int s , int t , int k ){
		int Res = 0;
		for( s += M - 1 , t += M + 1;s ^ t ^ 1;s >>= 1 , t >>= 1 ){
			if( ~s & 1 )Res += root[ s ^ 1 ].Qrank( k );
			if(  t & 1 )Res += root[ t ^ 1 ].Qrank( k );
		}
		return Res;
	}
	
	int Get_Num( int L , int R , int k ){
		int l = 0 , r = Inf , Res;
		while( l <= r ){
			int mid = l + r >> 1;
			if( Get_Rank( 1 , 1 , n , L , R , mid ) + 1 <= k )Res = mid , l = mid + 1;
			else r = mid - 1;
		}
		return Res;
	}
	
	void Modify( int rt , int l , int r , int x , int y ){
		int tmp = x;
		for( x += M;x;x >>= 1 )
			root[x].Del( A[tmp] ) , root[x].Insert( y );
	}
	
	int Query( int rt , int l , int r , int s , int t , int k , int Flag ){
		int Res = Flag * Inf;
		for( s += M - 1 , t += M + 1;s ^ t ^ 1;s >>= 1 , t >>= 1 ){
			if( ~s & 1 )Res = (( Flag == -1 ) ? max( root[ s ^ 1 ].Pre( k ) , Res ) : min( root[ s ^ 1 ].Next( k ) , Res ));
			if(  t & 1 )Res = (( Flag == -1 ) ? max( root[ t ^ 1 ].Pre( k ) , Res ) : min( root[ t ^ 1 ].Next( k ) , Res ));
		}
		return Res;
	}
}

using namespace Zkw_segment_tree;

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n ) Read( A[i] ) ;
	
	Build( 1 , 1 , n );
	
	while( m-- ){
		int Opt , x , y , z;
		Read( Opt );Read( x );Read( y );
		if( Opt == 3 )Modify( 1 , 1 , n , x , y ) , A[x] = y;
		else{
			Read( z );
			if( Opt == 1 )printf("%d\n",Get_Rank( 1 , 1 , n , x , y , z ) + 1);
			else if( Opt == 2 )printf("%d\n",Get_Num( x , y , z ));
			else if( Opt == 4 )printf("%d\n",Query( 1 , 1 , n , x , y , z , -1 ));
			else printf("%d\n",Query( 1 , 1 , n , x , y , z , 1 ));
		}
	}
	
	return 0;
}
