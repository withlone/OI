#include<cstdio>
#include<algorithm>

using namespace std;

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

#define Lson rt<<1 , l , mid
#define Rson rt<<1|1 , mid+1 , r
static const int MAXN = 1e5 +1;

int n , m;

int Sum[MAXN << 2];double H[MAXN << 2];

int query( int rt , int l , int r , double h ){
	if( l == r )return H[rt] > h;
	int mid = l + r >> 1;
	if( H[rt<<1] <= h )return query( Rson , h );
	return query( Lson , h ) + Sum[rt] - Sum[rt<<1];
}

void modify( int rt , int l , int r , int k , double h ){
	if( l == r ){
		Sum[rt] = 1;
		H[rt] = h;
		return;
	}
	int mid = l + r >> 1;
	if( k <= mid )modify( Lson , k , h );
	else modify( Rson , k , h );
	H[rt] = max( H[rt<<1] , H[rt<<1|1] );
	Sum[rt] = Sum[rt<<1] + query( rt<<1|1 , mid+1 , r , H[rt<<1] );
}

int main(){
	
	Read( n );Read( m );
	
	while( m-- ){
		int x , y;
		Read( x );Read( y );
		modify( 1 , 1 , n , x , y * 1.0 / x );
		printf("%d\n",Sum[1]);
	}
	
	return 0;
}
