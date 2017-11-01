#include<cstdio>
#include<algorithm>
using namespace std;

static const int MAXN = 5e4 +1;

int n;
struct Sec{
	int x,y;
	bool operator < ( Sec T )const{ return x<T.x||x==T.x&&y<T.y; }
}s[MAXN];

int main(){
	
	scanf("%d",&n);
	for( int i=1;i<=n;i++ )scanf("%d%d",&s[i].x,&s[i].y);
	sort( 1+s,1+n+s );
	int L = s[1].x,R = s[1].y;
	for( int i=2;i<=n;i++ )
		if( s[i].x>R )printf("%d %d\n",L,R),L=s[i].x,R=s[i].y;
		else if( s[i].y>R )R = s[i].y;
	printf("%d %d\n",L,R);
	return 0;
}
