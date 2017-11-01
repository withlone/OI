#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline Type max ( Type x , Type y ){ return x > y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

typedef long long LL;
#define Lson rt << 1 , l , mid
#define Rson rt << 1 | 1 , mid + 1 , r
static const int maxn = 3e5 +1;
static const int maxm = maxn << 2;

int n , m;
int A[maxn];
LL Lm[maxm] , Rm[maxm];
int mx[maxm] , Lmax[maxm] , Rmax[maxm] , tot[maxm];

int Get( LL x ){ return x ? x > 0 ? 1 : -1 : 0 ; }

void Up( int rt ){
	int l = rt << 1 , r = rt << 1 | 1;
	mx[rt] = max( mx[l] , mx[r] );
	Lm[rt] = Lm[l];Rm[rt] = Rm[r];
	if( !Rm[l] || !Lm[r] || Get( Rm[l] ) < Get( Lm[r] ) )
		Lmax[rt] = Lmax[l] , Rmax[rt] = Rmax[r];
	else{
		Lmax[rt] = Lmax[l] + ( tot[l] == Lmax[l] ) * Lmax[r];
		Rmax[rt] = Rmax[r] + ( tot[r] == Rmax[r] ) * Rmax[l];
		mx[rt] = max( mx[rt] , Rmax[l] + Lmax[r] );
	}
}

void modify( int rt , int l , int r , int x , LL y ){
	if( l == r )return Lm[rt] += y , Rm[rt] += y , mx[rt] = Lmax[rt] = Rmax[rt] = ( Lm[rt] != 0 ) , void();
	int mid = l + r >> 1;
	if( x <= mid )modify( Lson , x , y );
	else modify( Rson , x , y );
	Up( rt );
}

void Build( int rt , int l , int r ){
	if( l == r )return Lm[rt] = Rm[rt] = A[l] , tot[rt] = 1 , mx[rt] = Lmax[rt] = Rmax[rt] = ( A[l] != 0 ) , void();
	int mid = l + r >> 1;
	Build( Lson );Build( Rson );
	tot[rt] = r - l + 1;
	Up( rt );
}

int main(){
	
	Read( n );
	For( i , 1 , n )Read( A[i] ) , A[i - 1] = A[i] - A[i - 1];
	
	n--;
	if( n )Build( 1 , 1 , n );
	
	Read( m );
	while( m-- ){
		int x , y , z;
		Read( x );Read( y );Read( z );
		if( x >= 2 )modify( 1 , 1 , n , x - 1 , z );
		if( y <= n )modify( 1 , 1 , n , y , -z );
		printf("%d\n",mx[1] + 1);
	}
	
	return 0;
}
