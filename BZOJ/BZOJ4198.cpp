#include<queue>
#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
typedef pair< LL , LL > par;

priority_queue< par , vector< par > , greater< par > >que;

int n;
int k;

void read_in(){
	scanf( n ) ; scanf( k ) ;
	For( i , 1 , n ){
		LL x ; scanf( x ) ;
		que.push( make_pair( x , 1 ) );
	}
}

void Run(){
	int ext = 0;
	if( ( n - 1 ) % ( k - 1 ) )
		ext = k - 1 - ( n - 1 ) % ( k - 1 ) ;
	For( i , 1 , ext )
		que.push( make_pair( 0 , 1 ) ) ;
	LL ans = 0 , len = 0;
	while( true ){
		LL res = 0 ;
		For( i , 1 , k ){
			res += que.top().first;
			len = max( len , que.top().second );
			que.pop();
		}
		ans += res;
		if( que.empty() )break;
		que.push( make_pair( res , len + 1 ) ) ;
	}
	printf("%lld\n%lld\n" , ans , len );
}

int main(){
	
	read_in();
	
	Run();
	
	return 0;
}
