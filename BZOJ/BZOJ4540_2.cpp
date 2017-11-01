#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( LL i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _End ) for( LL i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 1e5 +1;

int n , m , Cnt;
LL A[maxn] , Y[maxn];
LL L[maxn] , R[maxn];
int Stk[maxn] , tp;
LL ans[maxn];

struct Line{
	LL x1 , x2 , y , f , id;
	bool operator < ( Line tmp ) const { return y < tmp.y || y == tmp.y && f > tmp.f ; }
}d[maxn << 3];

void Init(){
	Read( n );Read( m );
	For( i , 1 , n )Read( A[i] );
	For( i , 1 , Cnt = m )Read( d[i].x1 ) , Read( d[i].y ) , d[i].f = 0 , d[i].id = i;
	
	For( i , 1 , n ){
		while( tp && A[ Stk[tp] ] >= A[i] )tp--;
		L[i] = Stk[tp];
		Stk[ ++tp ] = i;
	}
	Stk[ tp = 0 ] = n + 1;
	Rep( i , n , 1 ){
		while( tp && A[ Stk[tp] ] > A[i] )tp--;
		R[i] = Stk[tp];
		Stk[ ++tp ] = i;
	}
}

struct BIT{
	
	LL T1[maxn] , T2[maxn];
	
	BIT(){ memset( T1 , 0 , sizeof T1 ) ; memset( T2 , 0 , sizeof T2 ) ; }
	
	int Lowbit( int x ){ return x & -x ; }
	
	void Add( LL x , LL y ){
		for( int i = x ; i <= n ; i += Lowbit( i ) )
			T1[i] += y , T2[i] += x * y;
	}
	
	LL Query( LL x ){
		LL Res = 0;
		for( int i = x ; i ; i -= Lowbit( i ) )
			Res += ( x + 1 ) * T1[i] - T2[i];
		return Res;
	}
	
	LL Get( LL x , LL y ){ return Query( y ) - Query( x - 1 ); }
	
	void modify( LL x , LL y , LL z ){ Add( x , z ) ; Add( y + 1 , -z ); }
	
}_K , _B;

int main(){
	
	Init();
	
	For( i , 1 , n ){
		LL x1 = min( i , L[i] + 1 ) , x2 = max( i , L[i] + 1 ) , y1 = min( i , R[i] - 1 ) , y2 = max( i , R[i] - 1 );
		Y[i] = y1;
		d[ ++Cnt ] = ( Line ){ x1 , x2 , y1 , 1 , i };
		d[ ++Cnt ] = ( Line ){ x1 , x2 , y2 , -1 , i };
	}
	sort( 1 + d , 1 + Cnt + d );
	
	For( i , 1 , Cnt )
		if( !d[i].f )ans[ d[i].id ] = _K.Get( d[i].x1 , n ) * d[i].y + _B.Get( d[i].x1 , n );
		else{
			LL l = d[i].x1 , r = d[i].x2 , f = d[i].f , y = d[i].y , k = A[ d[i].id ] * f , b = ( 1 - Y[ d[i].id ] ) * A[ d[i].id ] * f;
			_K.modify( l , r , k );
			_B.modify( l , r , b );
			if( f == -1 )_B.modify( l , r , A[ d[i].id ] * ( d[i].y - Y[ d[i].id ] + 1 ));
		}
	
	For( i , 1 , m )printf("%lld\n",ans[i]);
	
	return 0;
}
