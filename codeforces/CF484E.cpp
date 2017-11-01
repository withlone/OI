#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

#define Lson Ch[rt][0] , l , mid
#define Rson Ch[rt][1] , mid + 1 , r
static const int maxn = 1e5 + 10;
static const int maxm = 2e6;

int n , m , Ct;
int A[maxn];
int Ch[maxm][2] , root[maxn];
int mx[maxm] , Lmax[maxm] , Rmax[maxm] , tot[maxm];
pair< int , int >Srt[maxn];

int Up( int rt , int l , int r ){
	if( !( l * r ) )return l ^ r;
	Lmax[rt] = Lmax[l] + ( Lmax[l] == tot[l] ) * Lmax[r];
	Rmax[rt] = Rmax[r] + ( Rmax[r] == tot[r] ) * Rmax[l];
	mx[rt] = max( max( mx[l] , mx[r] ) , Lmax[r] + Rmax[l] );
	return rt;
}

void Build( int &rt , int l , int r ){
	if( !rt )rt = ++Ct;
	if( l == r )return tot[rt] = 1 , void();
	int mid = l + r >> 1;
	Build( Lson );Build( Rson );
	tot[rt] = tot[ Ch[rt][0] ] + tot[ Ch[rt][1] ];
	Up( rt , Ch[rt][0] , Ch[rt][1] );
}

void modify( int pt , int &rt , int l , int r , int x ){
	if( !rt )rt = ++Ct;tot[rt] = tot[pt];
	if( l == r )return mx[rt] = Lmax[rt] = Rmax[rt] = 1 , void();
	int mid = l + r >> 1;
	if( x <= mid )Ch[rt][1] = Ch[pt][1] , modify( Ch[pt][0] , Lson , x );
	else Ch[rt][0] = Ch[pt][0] , modify( Ch[pt][1] , Rson , x );
	Up( rt , Ch[rt][0] , Ch[rt][1] );
}

int Query( int rt , int l , int r , int L , int R ){
	if( l > R || r < L || !rt )return 0;
	if( l >= L && r <= R )return rt;
	int mid = l + r >> 1;
	return Up( ++Ct , Query( Lson , L , R ) , Query( Rson , L , R )  );
}

int main(){
	
	Read( n );
	For( i , 1 , n )Read( A[i] );
	
	For( i , 1 , n )Srt[i] = make_pair( A[i] , i );
	
	sort( 1 + Srt , 1 + n + Srt );
	
	Build( root[n + 1] , 1 , n );
	Lop( i , n , 1 )modify( root[i + 1] , root[i] , 1 , n , Srt[i].second );
	
	Read( m );
	
	while( m-- ){
		int x , y , z;
		Read( x );Read( y );Read( z );
		int l = 1 , r = n , ans;
		while( l <= r ){
			int mid = l + r >> 1;
			int tmp = Ct;
			if( mx[ Query( root[mid] , 1 , n , x , y ) ] >= z )ans = mid , l = mid + 1;
			else r = mid - 1;
			Ct = tmp;
		}
		printf("%d\n",Srt[ans].first);
	}
	
	return 0;
}
