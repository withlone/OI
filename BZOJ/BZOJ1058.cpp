#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<set>

using namespace std;

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}

static const int Inf  = 0x7fffffff;
static const int MAXN = 5e5 +1;

int n , m;
int Mn;
int A[MAXN] , B[MAXN];
char Opt[100];

multiset< int >set1 , set2;
multiset< int > :: iterator it , bk;

int main(){
	
	Mn = Inf;
	
	Read( n );Read( m );
	
	For( i , 1 , n ){
		Read( A[i] );
		B[i] = A[i];
		set1.insert( A[i] );
		if( i != 1 )set2.insert( abs( A[i] - A[i-1] ) );
	}
	
	it = set1.begin();bk = set1.begin();bk++;
	for( ;bk != set1.end();it++,bk++ )
		Mn = min( Mn , abs( *bk - *it ) );
	
	while( m-- ){
		scanf("%s",Opt);
		if( !strcmp( Opt , "INSERT" ) ){
			int x , y;
			Read( x );Read( y );
			if( x != n )set2.erase( set2.find( abs( A[x] - B[x+1] ) ) ) , set2.insert( abs( B[x+1] - y ) );
			set2.insert( abs( A[x] - y ) );
			A[x] = y;
			it = set1.insert( y );
			it--;Mn = min( Mn , abs( *it - y ) );
			it++;
			if( x != n )it++ , Mn = min( Mn , abs( *it - y ) );
		}
		if( !strcmp( Opt , "MIN_GAP" ) )printf("%d\n",*set2.begin());
		if( !strcmp( Opt , "MIN_SORT_GAP" ) )printf("%d\n",Mn);
	}
	
	return 0;
}
