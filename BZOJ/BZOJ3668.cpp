#include<cstdio>
#include<algorithm>
using namespace std;

static const int MAXN = 1e5 +1;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
#define Rep( i , _End , _Begin ) for( int i=_End;i>=_Begin;i-- )

int n,m,In,Len,Sum;
int d[MAXN];
char Ch[MAXN][10];

void Opt( int &To ){
	For( i , 1 , n )
		if( Ch[i][0]=='A' )To &= d[i];
		else if( Ch[i][0]=='O' )To |= d[i];
		else To ^= d[i];
}

int main(){
	
	scanf("%d%d",&n,&m);
	For( i , 1 , n )scanf("%s%d",Ch[i],&d[i]);
	Rep( i , 30 , 0 ){
		if( Sum + ( 1<<i )>m )continue;
		int t1 = Sum,t2 = Sum + ( 1<<i );
		Opt( t1 );Opt( t2 );
		if( t2>t1 )Sum += 1<<i;
	}
	
	Opt( Sum );
	printf("%d\n",Sum);
	return 0;
}
