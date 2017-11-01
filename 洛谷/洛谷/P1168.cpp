#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e6;

int n;
int A[MAXN];
pair< int , int >pt[MAXN];

namespace Zkw{
	
	int M;
	int Sz[MAXN];
	
	void Insert( int x ){ for( x += M ; x ; x >>= 1 )Sz[x]++; }
	
	int Query( int x ){
		int rt = 1;
		while( rt < M )
			if( x <= Sz[ rt<<1 ] )rt <<= 1;
			else x -= Sz[ rt<<1 ] , rt = rt<<1|1;
		return pt[ rt - M ].first;
	}
	
}using namespace Zkw;

int main(){
	
	Read( n );
	For( i , 1 , n )Read( pt[i].first ) , pt[i].second = i;
	
	for( M = 1 ; M < n + 2 ; M <<= 1 );
	sort( 1 + pt , 1 + n + pt );
	For( i , 1 , n )A[ pt[i].second ] = i;
	
	For( i , 1 , n ){
		Insert( A[i] );
		if( i & 1 )printf("%d\n",Query( ( i >> 1 ) + 1 ));
	}
	
	return 0;
}
