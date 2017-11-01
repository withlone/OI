#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}
static const int maxn = 5e4 +1;
static const int maxm = 1e4 +1;
static const int maxq = maxn + ( maxm << 1 );

int n , m , Cnt , Case;
int ans[maxm];
int A[maxq] , B[maxn];

struct data{ int x , y , k , id , type; }Q[maxq] , Q1[maxq] , Q2[maxq];

namespace BIT{
	
	int T[maxq];
	
	int Lowbit( int x ){ return x & -x ; }
	
	void Add( int x , int f ){
		for( ; x <= n ; x += Lowbit( x ) )T[x] += f;
	}
	
	int Query( int x ){
		int Res = 0;
		for( ; x ; x -= Lowbit( x ) )Res += T[x];
		return Res;
	}
	
}using namespace BIT;

void div( int l , int r , int L , int R ){
	if( L > R )return;
	if( l == r ){
		For( i , L , R )ans[ Q[i].id ] = A[l];
		return;
	}
	int mid = l + r >> 1 , q1 = 0 , q2 = 0;
	For( i , L , R )
		if( Q[i].type != 2 ){
			if( Q[i].y <= mid )Add( Q[i].x , Q[i].type ) , Q1[ ++q1 ] = Q[i];
			else Q2[ ++q2 ] = Q[i];
		}
		else{
			int tmp = Query( Q[i].y ) - Query( Q[i].x - 1 );
			if( tmp >= Q[i].k )Q1[ ++q1 ] = Q[i];
			else Q[i].k -= tmp , Q2[ ++q2 ] = Q[i];
		}
	For( i , L , R )
		if( Q[i].type != 2 && Q[i].y <= mid )Add( Q[i].x , -Q[i].type );
	
	For( i , L , L + q1 - 1 )Q[i] = Q1[ i - L + 1 ];
	For( i , L + q1 , R )Q[i] = Q2[ i - L - q1 + 1 ];
	div( l , mid , L , L + q1 - 1 );
	div( mid + 1 , r , L + q1 , R );
}

int main(){
	
	Read( Case );
	
	while( Case-- ){
		
		int Qct = Cnt = 0 , Ct = 0;
		
		Read( n );Read( m );
		For( i , 1 , n ){
			Read( Q[i].y );
			B[i] = A[ ++Cnt ] = Q[i].y;
			Q[i] = (data){ i , Q[i].y , 0 , 0 , 1 };
		}
		Qct = n;
		For( i , 1 , m ){
			char ch = getchar();
			while( ch > 'Z' || ch < 'A' )ch = getchar();
			int x , y , z;
			Read( x );Read( y );
			if( ch == 'Q' )Read( z ) , Q[ ++Qct ] = (data){ x , y , z , ++Ct , 2 };
			else{
				A[ ++Cnt ] = y;
				Q[ ++Qct ] = (data){ x , B[x] , 0 , 0 , -1 };
				Q[ ++Qct ] = (data){ x , B[x] = y , 0 , 0 , 1 };
			}
		}
		
		sort( 1 + A , 1 + Cnt + A );
		Cnt = unique( 1 + A , 1 + Cnt + A ) - A - 1;
		For( i , 1 , Qct )if( Q[i].type != 2 )Q[i].y = lower_bound( 1 + A , 1 + Cnt + A , Q[i].y ) - A;
		
		div( 1 , Cnt , 1 , Qct );
		
		For( i , 1 , Ct )printf("%d\n",ans[i]);
		
	}
	
	return 0;
}
