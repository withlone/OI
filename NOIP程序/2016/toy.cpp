#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

static const int maxn = 1e5 +1;

int n , m;
int face[maxn];
char Job[maxn][11];

int main(){
	
	freopen( "toy.in" , "r" , stdin ) ;
	freopen( "toy.out" , "w" , stdout ) ;
	
	scanf("%d%d",&n,&m);
	For( i , 0 , n - 1 )scanf("%d%s",&face[i],Job[i]);
	
	int pos = 0;
	while( m-- ){
		int x , y;
		scanf("%d%d",&x,&y);
		if( x == face[pos] )pos = ( pos - y + n ) % n;
		else pos = ( pos + y ) % n;
	}
	
	puts( Job[pos] );
	
	return 0;
}
