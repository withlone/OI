#include<cmath>
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
static const int maxn = 5e4 +1;

int n , m , Cft;
int A[maxn] , B[maxn];
LL ans[maxn] , sum;

struct data{
	int l , r , id;
	bool operator < ( data tmp ) const { return l/Cft < tmp.l/Cft || l/Cft == tmp.l/Cft && r < tmp.r ; }
}Q[maxn];

namespace BIT{
	
	int T[maxn];
	
	int Lowbit( int x ){ return x & -x ; }
	
	void Add( int x , int f ){
		for( int i = x ; i <= n ; i += Lowbit( i ) )
			T[i] += f;
	}
	
	LL Query( int x ){
		LL Res = 0;
		for( int i = x ; i ; i -= Lowbit( i ) )
			Res += T[i];
		return Res;
	}
	
}using namespace BIT;

int main(){
	
	Read( n );Cft = ( int )sqrt( n + 0.5 );
	For( i , 1 , n )Read( A[i] ) , B[i] = A[i];
	Read( m );
	For( i , 1 , m )Read( Q[i].l ) , Read( Q[i].r ) , Q[i].id = i;
	
	sort( 1 + B , 1 + n + B );
	sort( 1 + Q , 1 + m + Q );
	int Ct = unique( 1 + B , 1 + n + B ) - B - 1;
	For( i , 1 , n )A[i] = lower_bound( 1 + B , 1 + Ct + B , A[i] ) - B;
	
	int l = 1 , r = 0;
	For( i , 1 , m ){
		while( r < Q[i].r ){
			r++;
			sum += Query( n ) - Query( A[r] );
			Add( A[r] , 1 );
		}
		while( l > Q[i].l ){
			l--;
			sum += Query( A[l] - 1 );
			Add( A[l] , 1 );
		}
		while( r > Q[i].r ){
			sum -= Query( n ) - Query( A[r] );
			Add( A[r] , -1 );
			r--;
		}
		while( l < Q[i].l ){
			sum -= Query( A[l] - 1 );
			Add( A[l] , -1 );
			l++;
		}
		ans[ Q[i].id ] = sum;
	}
	
	For( i , 1 , m )printf("%lld\n",ans[i]);
	
	return 0;
}
