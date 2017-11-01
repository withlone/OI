#include<cstdio>
#include<algorithm>
using namespace std;

static const int MAXN = 30000+1;
static const int MAXC = 5000 +1;

int n,m,c,Ans;
int Tp[3];

struct Data{
	int x,y;
	bool operator < ( Data T )const{ return x<T.x; }
}d[MAXN];

int main(){
	
	scanf("%d%d%d",&n,&m,&c);
	c += 4;
	d[2].x = n;d[3].y = m;
	d[4].x = n;d[4].y = m;
	for( int i=5;i<=c;i++ )scanf("%d%d",&d[i].x,&d[i].y);
	sort( 1+d,1+c+d );
	for( int i=1;i<=c;i++ ){
		Tp[1] = 0;Tp[2] = m;
		for( int j=i+1;j<=c;j++ ){
			Ans = max( Ans,( d[j].x-d[i].x )*( Tp[2]-Tp[1] ) );
			if( d[j].y<=d[i].y )Tp[1] = max( Tp[1],d[j].y );
			if( d[j].y>=d[i].y )Tp[2] = min( Tp[2],d[j].y );
			if( Tp[1]>=Tp[2] )break;
		}
	}
	printf("%d\n",Ans);
	return 0;
}
