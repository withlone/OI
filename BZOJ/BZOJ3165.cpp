#include<cmath>
#include<cstdio>
#include<algorithm>

using namespace std;

#define Lson rt << 1 , l , mid
#define Rson rt << 1 | 1 , mid + 1 , r
#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int maxn = 1e5 +1;
static const int maxm = 4e4;
static const int mod1 = 39989;
static const int mod2 = 1e9;
static double eps = 1e-10;

int m , ans , cnt;
int x0[maxn] , Y0[maxn] , x1[maxn] , Y1[maxn];

int Seg[maxm << 2];

double calc( int num , int k ){
	return x1[num] == x0[num] ? Y0[num] : ( 1.0 * ( k - x0[num] ) * Y1[num] + 1.0 * ( x1[num] - k ) * Y0[num] ) / ( x1[num] - x0[num] );
}

int Cmp( double x , double y ){
	return fabs( x - y ) < eps ? 0 : x > y ? 1 : -1;
}

int cmp( int x , int y , int k ){
	if( !( x * y ) )return x + y;
	double tmp_x = calc( x , k );
	double tmp_y = calc( y , k );
	int p = Cmp( tmp_x , tmp_y );
	return !p ? min( x , y ) : p == 1 ? x : y;
}

void modify( int rt , int l , int r , int L , int R , int k ){
	if( l > R || r < L )return;
	int mid = l + r >> 1;
	if( l >= L && r <= R ){
		if( !Seg[rt] )Seg[rt] = k;
		else{
			bool t1 = Cmp( calc( k , l ) , calc( Seg[rt] , l ) ) > 0;
			bool t2 = Cmp( calc( k , r ) , calc( Seg[rt] , r ) ) > 0;
			if( t1 & t2 )Seg[rt] = k;
			else if( t1 + t2 ){
				bool t3 = Cmp( calc( k , mid ) , calc( Seg[rt] , mid ) ) > 0;
				if( t1 & t3 )modify( Rson , mid + 1 , r , Seg[rt] ) , Seg[rt] = k;
				else if( t2 & t3 )modify( Lson , l , mid , Seg[rt] ) , Seg[rt] = k;
				else if( t1 )modify( Lson , l , mid , k );
				else modify( Rson , mid + 1 , r , k );
			}
		}
		return;
	}
	modify( Lson , L , R , k );modify( Rson , L , R , k );
}

int Query( int rt , int l , int r , int k ){
	if( l == r )return Seg[rt];
	int mid = l + r >> 1 , p;
	if( k <= mid )return cmp( Query( Lson , k ) , Seg[rt] , k );
	return cmp( Query( Rson , k ) , Seg[rt] , k );
}

int main(){
	
	Read( m );
	
	For( i , 1 , m ){
		int opt , x;
		Read( opt );
		if( !opt ){
			Read( x );x = ( x + ans - 1 ) % mod1 + 1;
			printf("%d\n",ans = Query( 1 , 1 , mod1 , x ));
		}
		else{
			cnt++;
			Read( x0[cnt] );Read( Y0[cnt] );Read( x1[cnt] );Read( Y1[cnt] );
			x0[cnt] = ( x0[cnt] + ans - 1 ) % mod1 + 1;Y0[cnt] = ( Y0[cnt] + ans - 1 ) % mod2 + 1;
			x1[cnt] = ( x1[cnt] + ans - 1 ) % mod1 + 1;Y1[cnt] = ( Y1[cnt] + ans - 1 ) % mod2 + 1;
			if( x0[cnt] > x1[cnt] )swap( x0[cnt] , x1[cnt] ) , swap( Y0[cnt] , Y1[cnt] );
			modify( 1 , 1 , mod1 , x0[cnt] , x1[cnt] , cnt  );
		}
	}
	
	return 0;
}
