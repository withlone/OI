#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

typedef long long LL;
typedef pair< int , int > par;
#define Lson rt << 1 , l , mid
#define Rson rt << 1 | 1 , mid + 1 , r
static const int maxn = 1e5 +1;
static const int maxm = maxn << 2;

int n , m , up , down;
par A[maxn];
char opt[maxn];int opter[maxn];
LL ans[maxn];

LL mx[maxm] , mn[maxm] , add[maxm] , mul[maxm] , tag[maxm];

void Up( int rt ){ mx[rt] = mx[ rt << 1 | 1 ];mn[rt] = mn[ rt << 1 ]; }

void Change( int rt , int l , int r , LL Add , LL Mul , LL Tag ){
	mx[rt] = mx[rt] * Mul + Add + Tag * A[r].first;
	mn[rt] = mn[rt] * Mul + Add + Tag * A[l].first;
	mul[rt] *= Mul;tag[rt] = tag[rt] * Mul + Tag;add[rt] = add[rt] * Mul + Add;
}

void Pd( int rt , int l , int r ){
	if( mul[rt] == 1 && !add[rt] && !tag[rt] )return;
	int mid = l + r >> 1;
	Change( rt << 1 , l , mid , add[rt] , mul[rt] , tag[rt] );
	Change( rt << 1 | 1 , mid + 1 , r , add[rt] , mul[rt] , tag[rt] );
	add[rt] = tag[rt] = 0;mul[rt] = 1;
}

LL Query( int rt , int l , int r , int x ){
	if( l == r )return mx[rt];
	int mid = l + r >> 1;
	Pd( rt , l , r );Up( rt );
	if( x <= mid )return Query( Lson , x );
	return Query( Rson , x );
}

LL Query( int rt , int l , int r , LL x , int f ){
	if( l == r )return  !f ? mx[rt] > x ? 0 : l : mx[rt] < x ? n + 1 : l;
	int mid = l + r >> 1;
	Pd( rt , l , r );Up( rt );
	if( !f && mn[rt << 1 | 1] <= x || f && mx[rt << 1] < x )return Query( Rson , x , f );
	return Query( Lson , x , f );
}

void modify( int rt , int l , int r , int L , int R , LL x ){
	if( l > R || r < L )return;
	if( l >= L && r <= R )return Change( rt , l , r , x , 0 , 0 ) , void();
	int mid = l + r >> 1;
	Pd( rt , l , r );
	modify( Lson , L , R , x );modify( Rson , L , R , x );
	Up( rt );
}

void Build( int rt , int l , int r ){
	mul[rt] = 1;
	if( l == r )return mx[rt] = mn[rt] = A[l].first , void();
	int mid = l + r >> 1;
	Build( Lson );Build( Rson );
	Up( rt );
}

int main(){
	
	Read( m );Read( down );Read( up );
	For( i , 1 , m ){
		opt[i] = getchar();
		while( opt[i] != '+' && opt[i] != '-' && opt[i] != '*' && opt[i] != '@' )opt[i] = getchar();
		Read( opter[i] );
	}
	Read( n );
	For( i , 1 , n )Read( A[i].first ) , A[i].second = i;
	sort( 1 + A , 1 + n + A );
	
	Build( 1 , 1 , n );
	For( i , 1 , m ){
		if( opt[i] == '+' )Change( 1 , 1 , n , opter[i] , 1 , 0 );
		else if( opt[i] == '-' )Change( 1 , 1 , n , -opter[i] , 1 , 0 );
		else if( opt[i] == '*' )Change( 1 , 1 , n , 0 , opter[i] , 0 );
		else Change( 1 , 1 , n , 0 , 1 , opter[i] );
		int y = Query( 1 , 1 , n , up , 1 );
		if( y <= n )modify( 1 , 1 , n , y , n , up );
		int x = Query( 1 , 1 , n , down , 0 );
		if( x >= 1 )modify( 1 , 1 , n , 1 , x , down );
	}
	
	For( j , 1 , n )ans[ A[j].second ] = Query( 1 , 1 , n , j );
	
	For( j , 1 , n )printf("%lld\n",ans[j]);
	
	return 0;
}
