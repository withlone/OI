#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ;i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

typedef unsigned long long ULL;
static const int maxn = 1e5 +1;
static const int maxx = 8e6;
static const ULL hash1 = 233;

int n , m , k , Cnt;
ULL A[maxn] , B[maxn][21];
int QL[maxn] , QR[maxn];
ULL hash[maxn << 1] , Hash[maxn << 1];

namespace president_tree{
	
	int root[maxn];
	int Ch[maxx][2] , Sz[maxx] , cnt;
	
	void modify( int pt , int &rt , int l , int r , int val ){
		Sz[ rt = ++cnt ] = Sz[pt] + 1;
		if( l == r )return;
		int mid = l + r >> 1;
		if( val <= mid )Ch[rt][1] = Ch[pt][1] , modify( Ch[pt][0] , Ch[rt][0] , l , mid , val );
		else Ch[rt][0] = Ch[pt][0] , modify( Ch[pt][1] , Ch[rt][1] , mid + 1 , r , val );
	}
	
	bool Query( int x , int y , int quq ){
		int l = 1 , r = Cnt;
		while( l < r ){
			int mid = l + r >> 1;
			if( quq <= mid )x = Ch[x][0] , y = Ch[y][0] , r = mid;
			else x = Ch[x][1] , y = Ch[y][1] , l = mid + 1;
		}
		return Sz[x] - Sz[y];
	}
	
}using namespace president_tree;

int main(){
	
	
	Read( n );Read( m );Read( k );
	For( i , 1 , n )Read( A[i] );
	For( i , 1 , m ){
		Read( QL[i] );Read( QR[i] );
		For( j , 1 , k )Read( B[i][j] );
	}
	
	For( i , k , n )
		For( j , i - k + 1 , i )
			hash[i - k + 1] = hash1 * hash[i - k + 1] + A[j];
	For( i , 1 , m )
		For( j , 1 , k )
			hash[n - k + i + 1] = hash1 * hash[n - k + i + 1] + B[i][j];
	
	Cnt = n - k + m + 1;
	For( i , 1 , Cnt )Hash[i] = hash[i];
	
	sort( 1 + hash , 1 + Cnt + hash );
	Cnt = unique( 1 + hash , 1 + Cnt + hash ) - hash - 1;
	For( i , k , n )modify( root[i-1] , root[i] , 1 , Cnt , lower_bound( 1 + hash , 1 + Cnt + hash , Hash[i - k + 1] ) - hash );
	
	For( i , 1 , m )
		puts( Query( root[ QR[i] ] , root[ QL[i] + k - 2 ] , lower_bound( 1 + hash , 1 + Cnt + hash , Hash[n - k + i + 1] ) - hash ) ? "No" : "Yes" );
	
	return 0;
}
