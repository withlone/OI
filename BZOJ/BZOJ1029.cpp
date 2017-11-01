#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 2e5 +1;
typedef pair< int , int > Pair;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
#define x first
#define y second

int n,Ans,R;
Pair A[MAXN];
priority_queue< Pair >H;

int main(){
	
	Read( n );
	For( i , 1 , n )Read( A[i].y ),Read( A[i].x );
	sort( 1+A,1+n+A );
	For( i , 1 , n )swap( A[i].x,A[i].y );
	For( i , 1 , n )
		if( R + A[i].x<=A[i].y ){
			R += A[i].x;
			Ans++;
			H.push( A[i] );
		}
		else if( !H.empty()&&H.top().x>A[i].x ){
			R = R - H.top().x + A[i].x;
			H.pop();H.push( A[i] );
		}
	printf("%d\n",Ans);
	return 0;
}
