#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

static const int Inf = 1e8;
static const int maxn = 1e5 +1;
static const int maxm = maxn << 1;
static const int maxx = maxn * 3 << 2;

int n , m , u , v , Cnt , num;
int A[maxx] , At[maxn];bool Lt[maxn];
int H[maxn] , Nt[maxm] , To[maxm];

void Ins( int x , int y ){
	Nt[ ++Cnt ] = H[x];
	H[x] = Cnt;
	To[Cnt] = y;
}

void Dfs( int x , int fa ){
	A[ ++Cnt ] = -1;
	A[ ++Cnt ] = x;At[x] = Cnt;
	Rep( i , H[x] , Nt[i] )
		if( To[i] != fa )Dfs( To[i] , x );
	A[ ++Cnt ] = -2;
}

namespace Segment{
	
	#define Lson rt << 1 , l , mid
	#define Rson rt << 1 | 1 , mid + 1 , r
	
	int C1[maxx] , C2[maxx] , Dis[maxx];
	int Lp[maxx] , Lm[maxx] , Rp[maxx] , Rm[maxx];
	
	void Up( int rt ){
		int l = rt << 1 , r = rt << 1 | 1;
		
		if( C2[l] >= C1[r] )C1[rt] = C1[l] , C2[rt] = C2[l] - C1[r] + C2[r];
		else C1[rt] = C1[l] + C1[r] - C2[l] , C2[rt] = C2[r];
		
		Dis[rt] = max( max( Dis[l] , Dis[r] ) , max( Rp[l] + Lm[r] , Rm[l] + Lp[r] ) );
		
		Lp[rt] = max( Lp[l] , max( Lp[r] - C2[l] + C1[l] , Lm[r] + C2[l] + C1[l] ) );
		Lm[rt] = max( Lm[l] , Lm[r] + C2[l] - C1[l] );
		Rp[rt] = max( Rp[r] , max( Rp[l] - C1[r] + C2[r] , Rm[l] + C1[r] + C2[r] ) );
		Rm[rt] = max( Rm[r] , Rm[l] + C1[r] - C2[r] );
	}
	
	void Build( int rt , int l , int r ){
		if( l == r ){
			Lp[rt] = Rp[rt] = Lm[rt] = Rm[rt] = Dis[rt] = -Inf;
			if( A[l] > 0 )Lp[rt] = Rp[rt] = Lm[rt] = Rm[rt] = 0;
			else if( A[l] == -1 )C2[rt] = 1;
			else C1[rt] = 1;
			return;
		}
		int mid = l + r >> 1;
		Build( Lson );Build( Rson );
		Up( rt );
	}
	
	void modify( int rt , int l , int r , int k ){
		if( l == r ){
			if( Lt[k] )Lp[rt] = Rp[rt] = Lm[rt] = Rm[rt] = -Inf;
			else Lp[rt] = Rp[rt] = Lm[rt] = Rm[rt] = 0;
			return;
		}
		int mid = l + r >> 1;
		if( At[k] <= mid )modify( Lson , k );else modify( Rson , k );
		Up( rt );
	}
	
}using namespace Segment;

int main(){
	
	Read( n );num = n;
	For( i , 1 , n - 1 )Read( u ) , Read( v ) , Ins( u , v ) , Ins( v , u );
	Cnt = 0;
	
	Dfs( 1 , 0 );
	
	Build( 1 , 1 , Cnt );
	
	Read( m );
	
	while( m-- ){
		char opt = getchar();
		while( opt != 'G' && opt != 'C' )opt = getchar();
		if( opt == 'C' ){
			int x;Read( x );
			if( Lt[x] )num++;else num--;
			Lt[x] ^= 1;
			modify( 1 , 1 , Cnt , x );
		}
		else if( !num )puts("-1");
		else if( num == 1 )puts("0");
		else printf("%d\n",Dis[1]);
	}
	
	return 0;
}
