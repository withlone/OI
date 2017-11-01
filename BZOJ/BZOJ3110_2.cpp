#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 5e4 +1;
static const int maxx = maxn << 2;

int n , m , Cnt;
int ans[maxn];

struct data{ int f , l , r , id;LL v; }Q[maxn] , Q1[maxn] , Q2[maxn];

namespace Segment_tree{
	
	bool emp[maxx];
	int tag[maxx];LL sum[maxx];
	
	#define Lson rt << 1 , l , mid
	#define Rson rt << 1 | 1 , mid + 1 , r
	
	void clear(){ emp[1] = true;tag[1] = sum[1] = 0; }
	
	void Pd( int rt , int L , int R ){
		int l = rt << 1 , r = rt << 1 | 1;
		if( emp[rt] ){
			emp[rt] = false;emp[l] = emp[r] = true;
			sum[l] = sum[r] = tag[l] = tag[r] = 0;
		}
		if( tag[rt] ){
			tag[l] += tag[rt];tag[r] += tag[rt];
			sum[l] += 1LL * tag[rt] * L;sum[r] += 1LL * tag[rt] * R;
			tag[rt] = 0;
		}
	}
	
	void modify( int rt , int l , int r , int L , int R ){
		if( l > R || r < L )return;
		if( l >= L && r <= R )return sum[rt] += r - l + 1 , ++tag[rt] , void();
		int mid = l + r >> 1;
		Pd( rt , mid - l + 1 , r - mid );
		modify( Lson , L , R );modify( Rson , L , R );
		sum[rt] = sum[ rt << 1 ] + sum[ rt << 1 | 1 ];
	}
	
	LL Query( int rt , int l , int r , int L , int R ){
		if( l > R || r < L )return 0;
		if( l >= L && r <= R )return sum[rt];
		int mid = l + r >> 1;
		Pd( rt , mid - l + 1 , r - mid );
		return Query( Lson , L , R ) + Query( Rson , L , R );
	}
	
}using namespace Segment_tree;

void div( int l , int r , int L , int R ){
	if( L > R )return;
	if( l == r ){
		For( i , L , R )ans[ Q[i].id ] = l;
		return;
	}
	int mid = l + r >> 1 , q1 = 0 , q2 = 0;
	clear();
	For( i , L , R )
		if( Q[i].f == 1 ){
			if( Q[i].v <= mid )Q1[ ++q1 ] = Q[i];
			else{
				Q2[ ++q2 ] = Q[i];
				modify( 1 , 1 , n , Q[i].l , Q[i].r );
			}
		}
		else{
			LL t = Query( 1 , 1 , n , Q[i].l , Q[i].r );
			if( t >= Q[i].v )Q2[ ++q2 ] = Q[i];
			else Q[i].v -= t , Q1[ ++q1 ] = Q[i];
		}
	For( i , L , L + q1 - 1 )Q[i] = Q1[ i - L + 1 ];
	For( i , L + q1 , R )Q[i] = Q2[ i - L - q1 + 1 ];
	div( l , mid , L , L + q1 - 1 );
	div( mid + 1 , r , L + q1 , R );
}

int main(){
	
	Read( n );Read( m );
	For( i , 1 , m )Read( Q[i].f ) , Read( Q[i].l ) , Read( Q[i].r ) , Read( Q[i].v ) , Q[i].id = ( Q[i].f == 2 ? ++Cnt : 0 );
	
	div( -n , n , 1 , m );
	
	For( i , 1 , Cnt )printf("%d\n",ans[i]);
	
	return 0;
}
