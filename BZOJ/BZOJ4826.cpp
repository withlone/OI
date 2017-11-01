#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

typedef long long LL;
typedef pair< int , int > par;
static const int maxn = 2e5 +1;

int n , m , p1 , p2;
int A[maxn];
int L[maxn] , R[maxn];
int Stk[maxn] , tp;
LL ans[maxn];

vector< int >P[maxn];
vector< par >HL[maxn] , HR[maxn] , TL[maxn] , TR[maxn];

namespace BIT{
	
	LL T1[maxn] , T2[maxn];
	
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
	
}using namespace BIT;

void Init(){
	Read( n );Read( m );Read( p1 );Read( p2 );
	For( i , 1 , n )Read( A[i] );
	
	For( i , 1 , n ){
		while( tp && A[i] > A[ Stk[tp] ] )tp--;
		L[i] = Stk[tp];
		Stk[ ++tp ] = i;
	}
	Stk[ tp = 0 ] = n + 1;
	Rep( i , n , 1 ){
		while( tp && A[i] > A[ Stk[tp] ] )tp--;
		R[i] = Stk[tp];
		Stk[ ++tp ] = i;
	}
}

void calc(){
	
	Rep( i , n , 1 ){
		For( j , 0 , P[i].size() - 1 )
			Add( P[i][j] , p1 ) , Add( P[i][j] + 1 , -p1 );
		For( j , 0 , HL[i].size() - 1 )
			Add( HL[i][j].first , p2 ) , Add( HL[i][j].second + 1 , -p2 );
		For( j , 0 , TL[i].size() - 1 )
			ans[ TL[i][j].second ] += Query( TL[i][j].first );
	}
	
	memset( T1 , 0 , sizeof T1 );
	memset( T2 , 0 , sizeof T2 );
	
	For( i , 1 , n ){
		For( j , 0 , HR[i].size() - 1 )
			Add( HR[i][j].first , p2 ) , Add( HR[i][j].second + 1 , -p2 );
		For( j , 0 , TR[i].size() - 1 )
			ans[ TR[i][j].second ] += Query( n ) - Query( TR[i][j].first - 1 );
	}
	
}

int main(){
	
	Init();
	
	For( i , 1 , n ){
		if( L[i] && R[i] <= n ) P[L[i]].push_back( R[i] );
		if( i + 1 <= R[i] - 1 )HL[L[i]].push_back( make_pair( i + 1 , R[i] - 1 ) );
		if( L[i] + 1 <= i - 1 )HR[R[i]].push_back( make_pair( L[i] + 1 , i - 1 ) );
	}
	
	For( i , 1 , m ){
		int x , y;
		Read( x );Read( y );
		ans[i] += ( y - x ) * p1;
		TL[x].push_back( make_pair( y , i ) );
		TR[y].push_back( make_pair( x , i ) );
	}
	
	calc();
	
	For( i , 1 , m )printf("%lld\n",ans[i]);
	
	return 0;
}
