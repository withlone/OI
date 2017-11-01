#include<cstdio>

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

static const int maxn = 2e5 +1;
static const int maxx = 55e5;

int n , m , ans;

namespace Sust{
	
	int Cnt;
	int root[maxn] , Ch[maxx][2];
	int Uset[maxx] , Dep[maxx];
	
	#define Lson Ch[rt][0] , l , mid
	#define Rson Ch[rt][1] , mid + 1 , r
	
	void Build( int &rt , int l , int r ){
		rt = ++Cnt;
		if( l == r )return Uset[rt] = l , void();
		int mid = l + r >> 1;
		Build( Lson );Build( Rson );
	}
	
	void modify( int pt , int &rt , int l , int r , int x , int y ){
		rt = ++Cnt;
		if( l == r )return Dep[rt] = Dep[pt] , Uset[rt] = y , void();
		int mid = l + r >> 1;
		if( x <= mid )Ch[rt][1] = Ch[pt][1] , modify( Ch[pt][0] , Lson , x , y );
		else Ch[rt][0] = Ch[pt][0] , modify( Ch[pt][1] , Rson , x , y );
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
	
	for( int i = 1 ; i <= m ; i++ ){
		int x , y , opt;
		Read( opt );
		root[i] = root[i - 1];
		if( opt == 1 ){
			Read( x );Read( y );
			x ^= ans;y ^= ans;
			int fx = Find( root[i] , x ) , fy = Find( root[i] , y );
			if( Uset[fx] == Uset[fy] )continue;
			if( Dep[fx] > Dep[fy] )fx ^= fy ^= fx ^= fy;
			modify( root[i - 1] , root[i] , 1 , n , Uset[fx] , Uset[fy] );
			if( Dep[fx] == Dep[fy] )Dep[ Query( root[i] , 1 , n , Uset[fy] ) ]++;
		}
		else if( opt == 2 ){
			Read( x );x ^= ans;
			root[i] = root[x];
		}
		else{
			Read( x );Read( y );
			x ^= ans;y ^= ans;
			int fx = Find( root[i] , x ) , fy = Find( root[i] ,  y );
			printf("%d\n",ans = ( Uset[fx] == Uset[fy] ));
		}
	}
	
	return 0;
}
