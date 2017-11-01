#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

const int MAXN = 1e4 +1;
const int MAXM = 5e4 +1;

int n,m,Ct;

struct Edge{
	int x,y,c,d;double Dis;
	bool operator < ( Edge T )const{ return Dis>T.Dis; }
}E[MAXM],Tmp[MAXM];
int Fa[MAXM];
int Find( int t ){ return t==Fa[t]?t:Fa[t] = Find( Fa[t] ); }
bool Ch( double Eval ){
	double Sum = 0;
	for( int i=1;i<=m;i++ )Tmp[i] = E[i],Tmp[i].Dis = E[i].c - E[i].d*Eval,Fa[i] = i;
	sort( 1+Tmp,1+m+Tmp );
	for( int i=1;i<=m;i++ ){
		int x = Find( Tmp[i].x ),y = Find( Tmp[i].y );
		if( x!=y ){
			Fa[x] = y;
			Sum += Tmp[i].Dis;
		}
	}
	return Sum>=0;
}

double Div(){
	double l = 0,r = 1e9;
	while( r-l>0.0000001 ){
		double Mid = (l+r)/2.0;
		if( Ch( Mid ) )l = Mid;
		else r = Mid;
	}
	return l;
}

int main(){
	
	freopen("emperor.in","r",stdin);
	freopen("emperor.out","w",stdout);
	Read( n );Read( m );
	for( int i=1;i<=m;i++ ){
		Read( E[i].x );Read( E[i].y );Read( E[i].c );Read( E[i].d );
	}
	printf("%.6lf\n",Div());
	return 0;
}
