#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 5e3 +1;

int n,None,Kep,Begin,Max;
struct Water{
	int x,y;
	bool operator < ( Water T )const { return x<T.x||x==T.x&&y<T.y; }
}Seq[MAXN];

int main(){
	
	Read( n );
	for( int i=1;i<=n;i++ )Read( Seq[i].x ),Read( Seq[i].y );
	sort( 1+Seq,1+n+Seq );
	Begin = 1;Max = Seq[1].y;
	for( int i=2;i<=n;i++ )
		if( Seq[i].x>Max ){
			Kep  = max( Kep,Max- Seq[Begin].x );
			None = max( None,Seq[i].x-Max );
			Begin= i;
			Max = Seq[i].y;
		}
		else Max = max( Max,Seq[i].y );
	Kep = max( Kep,Max - Seq[Begin].x );
	printf("%d %d\n",Kep,None);
	return 0;
}
