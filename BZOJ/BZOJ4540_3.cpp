#include<cmath>
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

typedef long long LL;
static const int maxn = 1e5 +1;

int n , m , Fac;
int A[maxn] , BL[maxn];
int Bin[18] , Log[maxn];
int L[maxn] , R[maxn];
int Stk[maxn] , tp;
int ST[maxn][18];
LL suml[maxn] , sumr[maxn] , ans[maxn] , sum;

struct Query{
	int l , r , id;
	bool operator < ( Query t ) const { return BL[l] < BL[t.l] || BL[l] == BL[t.l] && r < t.r ; }
}Q[maxn];

void Init(){
	Bin[0] = 1;
	For( i , 1 , 17 )Bin[i] = Bin[i - 1] << 1;
	For( i , 2 , n )Log[i] = Log[i >> 1] + 1;
	For( i , 1 , n )ST[i][0] = i;
	
	Lop( i , n , 1 )
		For( j , 1 , 17 ){
			int t = i + Bin[j - 1];
			if( i + Bin[j] - 1 > n )break;
			else if( A[ ST[i][j - 1] ] <= A[ ST[t][j - 1] ] )
				ST[i][j] = ST[i][j - 1];
			else ST[i][j] = ST[t][j - 1];
		}
	
	For( i , 1 , n ){
		while( tp && A[ Stk[tp] ] >= A[i] )tp--;
		L[i] = Stk[tp];Stk[ ++tp ] = i;
	}
	Stk[ tp = 0 ] = n + 1;
	Lop( i , n , 1 ){
		while( tp && A[ Stk[tp] ] > A[i] )tp--;
		R[i] = Stk[tp];Stk[ ++tp ] = i;
	}
	
	For( i , 1 , n )suml[i] = suml[L[i]] + (LL)( i - L[i] ) * A[i];
	Lop( i , n , 1 )sumr[i] = sumr[R[i]] + (LL)( R[i] - i ) * A[i];
	
}

int Rmq( int l , int r ){
	int k = Log[ r - l + 1 ] , t = r - Bin[k] + 1;
	return A[ ST[l][k] ] <= A[ ST[t][k] ] ?
		ST[l][k] : ST[t][k];
}

void modify_L( int l , int r , LL f ){
	int y = Rmq( l , r );
	sum += f * ( (LL) A[y] * ( r - y + 1 ) + sumr[l] - sumr[y] );
}

void modify_R( int l , int r , LL f ){
	int y = Rmq( l , r );
	sum += f * ( (LL) A[y] * ( y - l + 1 ) + suml[r] - suml[y] );
}

int main(){
	
	Read( n );Read( m );Fac = sqrt( n );
	For( i , 1 , n )Read( A[i] ) , BL[i] = i / Fac + 1;
	For( i , 1 , m )Read( Q[i].l ) , Read( Q[i].r ) , Q[i].id = i;
	
	sort( 1 + Q , 1 + m + Q );
	
	Init();
	
	int l = 1 , r = 0;
	For( i , 1 , m ){
		while( r < Q[i].r )modify_R( l , ++r , 1 );
		while( l > Q[i].l )modify_L( --l , r , 1 );
		while( r > Q[i].r )modify_R( l , r-- , -1 );
		while( l < Q[i].l )modify_L( l++ , r , -1 );
		ans[ Q[i].id ] = sum;
	}
	
	For( i , 1 , m )printf("%lld\n",ans[i]);

	return 0;
}
