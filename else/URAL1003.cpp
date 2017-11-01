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

static const int maxn = 5e3 + 10;
static const int maxm = maxn << 1;

int m , ans;
int d[maxm] , dct;
int A[maxn] , B[maxn];
char opt[maxn][10];
int Fa[maxm << 1];

int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int main(){
	
	while( 1 ){
		Read( m );if( m == -1 )break;
		Read( m );dct = 0;
		For( i , 1 , m )
			Read( A[i] ) , Read( B[i] ) , scanf( "%s" , opt[i] ) ,
			d[ ++dct ] = A[i] , d[ ++dct ] = B[i];
		
		sort( 1 + d , 1 + dct + d );
		dct = unique( 1 + d , 1 + dct + d ) - d - 1;
		For( i , 1 , m )
			A[i] = lower_bound( 1 + d , 1 + dct + d , A[i] ) - d - 1,
			B[i] = lower_bound( 1 + d , 1 + dct + d , B[i] ) - d ;
		
		For( i , 0 , ( dct << 1 ) + 10 )Fa[i] = i;
		
		ans = m;
		For( i , 1 , m )
			if( !strcmp( "odd" , opt[i] ) ){
				if( Find( A[i] ) == Find( B[i] ) ){ ans = i - 1;break; }
				Fa[ Find( A[i] ) ] = Find( B[i] + dct + 1 );
				Fa[ Find( B[i] ) ] = Find( A[i] + dct + 1 );
			}
			else{
				if( Find( A[i] ) == Find( B[i] + dct + 1 ) ){ ans = i - 1;break; }
				Fa[ Find( A[i] ) ] = Find( B[i] );
				Fa[ Find( A[i] + dct + 1 ) ] = Find( B[i] + dct + 1 );
			}
		printf("%d\n",ans);
	}
	
	return 0;
}
