#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 3e5 + 10;

int n , S;
int sumT[maxn] , sumF[maxn];
int que1[maxn] , qt[maxn] , que2[maxn];
LL F[maxn];

LL Up( int x , int y ){ return F[x] - F[y] ; }
LL Down( int x , int y ){ return sumT[x] - sumT[y] ; }
LL Dp( int x , int y ){ return 1LL * ( sumT[x] - sumT[y] + S ) * sumF[x] + F[y] ; }

bool chk1( int x , int y , int z ){
	LL x1 = Down( y , x ) , x2 = Down( z , y );
	LL y1 = Up( y , x ) , y2 = Up( z , y );
	return x1 * y2 <= x2 * y1;
}

bool chk2( int x , int y , int z ){
	LL x0 = Down( y , x ) , y0 = Up( y , x );
	return y0 < x0 * z;
}

void merge( int *que , int l , int r ){
	int mid = l + r >> 1;
	int ql = l , qr = mid + 1;
	For( i , l , r )
		que[i] <= mid ? qt[ ql++ ] = que[i] : qt[ qr++ ] = que[i];
	
	For( i , l , r )que[i] = qt[i];
}

void sort( int *que , int l , int r , int f ){
	int mid = l + r >> 1;
	int ql = l , qr = mid + 1;
	For( i , l , r )
		if( ql > mid )qt[i] = que[ qr++ ];
		else if( qr > r )qt[i] = que[ ql++ ];
		else if( !f )qt[i] = sumT[ que[ql] ] < sumT[ que[qr] ] ? que[ ql++ ] : que[ qr++ ];
		else qt[i] = sumF[ que[ql] ] < sumF[ que[qr] ] ? que[ ql++ ] : que[ qr++ ];
	
	For( i , l , r )que[i] = qt[i];
}

void CDQ( int l , int r ){
	if( l == r )return;
	int mid = l + r >> 1;
	
	merge( que1 , l , r );
	merge( que2 , l , r );
	
	CDQ( mid + 1 , r );
	
	int ql = 1 , qr = 0;
	For( i , mid + 1 , r ){
		while( ql < qr && chk1( qt[qr - 1] , qt[qr] , que1[i] ) )--qr;
		qt[ ++qr ] = que1[i];
	}
	
	For( i , l , mid ){
		while( ql < qr && chk2( qt[ql] , qt[ql + 1] , sumF[ que2[i] ] ) )++ql;
		F[ que2[i] ] = min( F[ que2[i] ] , Dp( que2[i] , qt[ql] ) );
	}
	
	CDQ( l , mid );
	
	sort( que1 , l , r , 0 );
	sort( que2 , l , r , 1 );
	
}

int main(){
	
	Read( n );Read( S );
	For( i , 1 , n )Read( sumT[i] ) , Read( sumF[i] ) , que2[i] = que1[i] = n - i + 1;
	Lop( i , n - 1 , 1 )sumT[i] += sumT[i + 1] , sumF[i] += sumF[i + 1];
	
	For( i , 1 , n )F[i] = Dp( i , n + 1 );
	
	CDQ( 1 , n );
	
	printf("%lld\n",F[1]);
	
	return 0;
}
