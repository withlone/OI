#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <=(i##END) ; i++ )

template< typename Type >inline void swap( Type &x , Type &y ){ x ^= y ^= x ^= y; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

static const int maxn = 2e4 +1;
static const int maxm = 6e5 +1;

int n , m;

namespace Sust{
	
	int Cnt;
	int root[maxm] , Ch[maxm][2];
	int Uset[maxm] , Dep[maxm];
	
	#define Lson Ch[rt][0] , l , mid
	#define Rson Ch[rt][1] , mid + 1 , r
	
	void Build( int &rt , int l , int r ){
		rt = ++Cnt;
		if( l == r )return Uset[rt] = l , void();
		int mid = l + r >> 1;
		Build( Lson );Build( Rson );
	}
	
	void modify( int pt , int &rt , int l , int r , int x , int y , int f ){
		rt = ++Cnt;
		if( l == r )return Dep[rt] = Dep[pt] + f , Uset[rt] = y , void();
		int mid = l + r >> 1;
		if( x <= mid )Ch[rt][1] = Ch[pt][1] , modify( Ch[pt][0] , Lson , x , y , f );
		else Ch[rt][0] = Ch[pt][0] , modify( Ch[pt][1] , Rson , x , y , f );
	}
	
	int Query( int rt , int l , int r , int x ){
		int mid = l + r >> 1;
		return l == r ? rt : x <= mid ?
			Query( Lson , x ) : Query( Rson , x );
	}
	
	int Find( int rt , int x ){
		int t = Query( rt , 1 , n , x );
		return Uset[t] == x ? t : Find( rt , Uset[t] );
	}
	
}using namespace Sust;

int main(){
	
	Read( n );Read( m );
	
	Build( root[0] , 1 , n );
	
	For( i , 1 , m ){
		int opt , x , y;
		Read( opt );
		root[i] = root[i - 1];
		if( opt == 1 ){
			Read( x );Read( y );
			int fx = Find( root[i] , x ) , fy = Find( root[i] , y );
			if( Uset[fx] == Uset[fy] )continue;
			if( Dep[fx] < Dep[fy] )swap( fx , fy );
			modify( root[i - 1] , root[i] , 1 , n , Uset[fx] , Uset[fy] , 0 );
			if( Dep[fx] == Dep[fy] )modify( root[i - 1] , root[i] , 1 , n , Uset[fx] , Uset[fy] , 1 );
		}
		else if( opt == 2 )Read( x ) , root[i] = root[x];
		else{
			Read( x );Read( y );
			int fx = Find( root[i] , x ) , fy = Find( root[i] , y );
			puts( Uset[fx] == Uset[fy] ? "1" : "0" );
		}
	}
	
	return 0;
}
