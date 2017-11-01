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

static const int maxn = 1e5 +1;

int n , Dct , Cnt1 , Cnt2;
int D[maxn] , A[maxn] , ans[maxn] , B[maxn];

struct data{ int x , y , id , sum , f ; }Q[maxn] , Qt[maxn];

namespace BIT{
	
	int T[maxn];
	
	int Lowbit( int x ){ return x & -x ; }
	
	void Add( int x , int f ){
		for( int i = x ; i <= Cnt2 ; i += Lowbit( i ) )T[i] += f;
	}
	
	int Query( int x ){
		int Res = 0;
		for( int i = x ; i ; i -= Lowbit( i ) )Res += T[i];
		return Res;
	}
	
}using namespace BIT;

void CDQ( int l , int r ){
	if( l == r )return;
	int mid = l + r >> 1;
	CDQ( l , mid );CDQ( mid + 1 , r );
	int pos = l , qt = l - 1;
	For( i , mid + 1 , r ){
		while( pos <= mid && Q[pos].x <= Q[i].x ){
			if( Q[pos].f )Add( Q[pos].y , Q[pos].f );
			Qt[ ++qt ] = Q[ pos++ ];
		}
		if( !Q[i].f )Q[i].sum += Query( Cnt2 ) - Query( Q[i].y - 1 );
		Qt[ ++qt ] = Q[i];
	}
	For( i , l , pos - 1 )if( Q[i].f )Add( Q[i].y , -Q[i].f );
	while( pos <= mid )Qt[ ++qt ] = Q[ pos++ ];
	For( i , l , r )Q[i] = Qt[i];
}

int main(){
	
	while( scanf("%d",&n) != EOF ){
		
		int Ct = Cnt1 = Cnt2 = Dct = 0;
		
		For( i , 1 , n ){
			Q[i].id = Q[i].sum = Q[i].f = 0;
			char ch = getchar();
			while( ch > 'Z' || ch < 'A' )ch = getchar();
			if( ch == 'D' ){
				Read( Q[i].x );Read( Q[i].y );Q[i].f = 1;
				D[ ++Dct ] = i;A[ ++Cnt1 ] = Q[i].x;B[ ++Cnt2 ] = Q[i].y;
			}
			else if( ch == 'C' ){
				int x;Read( x );
				Q[i] = Q[ D[x] ];Q[i].f = -1;
			}
			else{
				Read( Q[i].x );Read( Q[i].y );Q[i].id = ++Ct;
				A[ ++Cnt1 ] = Q[i].x;B[ ++Cnt2 ] = Q[i].y;
			}
		}
		
		sort( 1 + A , 1 + Cnt1 + A );sort( 1 + B , 1 + Cnt2 + B );
		Cnt1 = unique( 1 + A , 1 + Cnt1 + A ) - A - 1;
		Cnt2 = unique( 1 + B , 1 + Cnt2 + B ) - B - 1;
		For( i , 1 , n )
			Q[i].x = lower_bound( 1 + A , 1 + Cnt1 + A , Q[i].x ) - A ,
			Q[i].y = lower_bound( 1 + B , 1 + Cnt2 + B , Q[i].y ) - B ;
		
		CDQ( 1 , n );
		
		For( i , 1 , n )ans[ Q[i].id ] = Q[i].sum;
		
		For( i , 1 , Ct )printf("%d\n",ans[i]);
		
	}
	
	return 0;
}
