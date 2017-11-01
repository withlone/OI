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

static const int maxn = 2e4 +1;
static const int maxq = 25e3 +1;
static const int maxx = 38e4;

int n , m , ans , Cnt , Ct;
pair< int , int >A[maxn];
int B[maxn] , poi[maxn];
int q[4];

int root[maxn] , Ch[maxx][2];
int Lmax[maxx] , Rmax[maxx] , sum[maxx];

int Up( int rt , int l , int r ){
	if( !( l * r ) )return l ^ r;
	sum[rt] = sum[l] + sum[r];
	Lmax[rt] = max( Lmax[l] , sum[l] + Lmax[r] );
	Rmax[rt] = max( Rmax[r] , sum[r] + Rmax[l] );
	return rt;
}

void Build( int &rt , int l , int r ){
	rt = ++Cnt;
	if( l == r )return sum[rt] = Lmax[rt] = Rmax[rt] = 1 , void();
	int mid = l + r >> 1;
	Build( Ch[rt][0] , l , mid );Build( Ch[rt][1] , mid + 1 , r );
	Up( rt , Ch[rt][0] , Ch[rt][1] );
}

void modify( int pt , int &rt , int l , int r , int pos ){
	rt = ++Cnt;
	if( l == r )return sum[rt] = Lmax[rt] = Rmax[rt] = -1 , void();
	int mid = l + r >> 1;
	if( pos <= mid )Ch[rt][1] = Ch[pt][1] , modify( Ch[pt][0] , Ch[rt][0] , l , mid ,  pos );
	else Ch[rt][0] = Ch[pt][0] , modify( Ch[pt][1] , Ch[rt][1] , mid + 1 , r , pos );
	Up( rt , Ch[rt][0] , Ch[rt][1] );
}

int Query( int rt , int l , int r , int L , int R ){
	if( l > R || r < L || L > R || !rt )return 0;
	if( l >= L && r <= R )return rt;
	int mid = l + r >> 1;
	return Up( ++Cnt ,Query( Ch[rt][0] , l , mid , L , R ) , Query( Ch[rt][1] , mid + 1 , r , L , R ) );
}

int Div(){
	int l = 0 , r = n - 1 , Res;
	while( l <= r ){
		int mid = l + r >> 1;
		int tmp = Cnt;
		int x = sum[ Query( root[mid] , 0 , n - 1 , q[1] + 1 , q[2] - 1 ) ];
		int y = Rmax[ Query( root[mid] , 0 , n - 1 , q[0] , q[1] ) ];
		int z = Lmax[ Query( root[mid] , 0 , n - 1 , q[2] , q[3] ) ];
		if( x + y + z >= 0 )
			Res = mid , l = mid + 1;
		else r = mid - 1;
		Cnt = tmp;
	}
	return A[Res].first;
}

int main(){
	
	Read( n );
	For( i , 0 , n - 1 )Read( A[i].first ) , A[i].second = i;
	sort( A , A + n );
	For( i , 0 , n - 1 )poi[ B[ A[i].second ] = i ] = A[i].second;
	
	Build( root[0] , 0 , n - 1 );
	For( i , 1 , n - 1 )modify( root[i - 1] , root[i] , 0 , n - 1 , poi[i - 1] );
	
	Read( m );
	
	while( m-- ){
		For( i , 0 , 3 )Read( q[i] ) , q[i] = ( q[i] + ans ) % n;
		sort( q , q + 4 );
		printf("%d\n",ans = Div());
	}
	
	return 0;
}
