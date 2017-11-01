#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
#define Lson rt << 1 , l , mid
#define Rson rt << 1 | 1 , mid + 1 , r
static const LL Inf = 9223372036854775807LL;
static const int maxn = 1e5 +1;
static const int maxm = maxn << 2;

int n , m;
LL A[maxn];

bool flag[maxm];
LL sum[maxm] , tag1[maxm] , tag2[maxm] , mx[maxm] , mn[maxm];

void Up( int rt ){
	sum[rt] = sum[ rt << 1] + sum[ rt << 1 | 1 ];
	mx[rt] = max( mx[ rt << 1 ] , mx[ rt << 1 | 1 ] );
	mn[rt] = min( mn[ rt << 1 ] , mn[ rt << 1 | 1 ] );
}

void Pd( int rt , int L , int R ){
	int l = rt << 1 , r = rt << 1 | 1;
	if( flag[rt] ){
		sum[l] = tag2[rt] * L;
		sum[r] = tag2[rt] * R;
		mx[l] = mn[l] = mx[r] = mn[r] = tag2[rt];
		tag1[l] = tag1[r] = 0;
		tag2[l] = tag2[r] = tag2[rt];
		flag[l] = flag[r] = true;
		tag2[rt] = flag[rt] = 0;
	}
	if( tag1[rt] ){
		sum[l] += tag1[rt] * L;
		sum[r] += tag1[rt] * R;
		mx[l] += tag1[rt];mn[l] += tag1[rt];
		mx[r] += tag1[rt];mn[r] += tag1[rt];
		tag1[l] += tag1[rt];
		tag1[r] += tag1[rt];
		tag1[rt] = 0;
	}
}

void Build( int rt , int l , int r ){
	if( l == r )return sum[rt] = mx[rt] = mn[rt] = A[l] , void();
	int mid = l + r >> 1;
	Build( Lson );Build( Rson );
	Up( rt );
}

void modify( int rt , int l , int r , int L , int R , LL val , int f ){
	if( l > R || r < L )return;
	if( l >= L && r <= R ){
		if( !f ){
			tag1[rt] += val;
			mx[rt] += val;
			mn[rt] += val;
			sum[rt] += val * ( r - l + 1 );
		}
		else{
			tag1[rt] = 0;
			tag2[rt] = val;
			flag[rt] = true;
			mx[rt] = mn[rt] = val;
			sum[rt] = val * ( r - l + 1 );
		}
		return;
	}
	int mid = l + r >> 1;
	Pd( rt , mid - l + 1 , r - mid );
	modify( Lson , L , R , val , f );modify( Rson , L , R , val , f );
	Up( rt );
}

LL Query( int rt , int l , int r , int L , int R , int f ){
	if( l > R || r < L )return !f ? 0 : (f == 1 ? -Inf : Inf);
	if( l >= L && r <= R )return !f ? sum[rt] : (f == 1 ? mx[rt] : mn[rt]);
	int mid = l + r >> 1;
	Pd( rt , mid - l + 1 , r - mid );
	LL x = Query( Lson , L , R , f ) , y = Query( Rson , L , R , f );
	return !f ? x + y : (f == 1 ? max( x , y ) : min( x , y ));
}

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n )Read( A[i] );
	
	Build( 1 , 1 , n );
	
	while( m-- ){
		char s[10];
		LL x , y , z;
		scanf("%s",s);Read( x );Read( y );
		if( !strcmp( s , "add" ) )Read( z ) , modify( 1 , 1 , n , x , y , z , 0 );
		else if( !strcmp( s , "set" ) )Read( z ) , modify( 1 , 1 , n , x , y , z , 1 );
		else if( !strcmp( s , "sum" ) )printf("%lld\n",Query( 1 , 1 , n , x , y , 0 ));
		else if( !strcmp( s , "max" ) )printf("%lld\n",Query( 1 , 1 , n , x , y , 1 ));
		else printf("%lld\n",Query( 1 , 1 , n , x , y , 2 ));
	}
	
	return 0;
}
