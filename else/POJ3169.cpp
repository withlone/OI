#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

const int MAXN = 1e4 +1;

int n,ml,md,u,v,w,Ct;
int Nt[MAXN],H[MAXN],Dt[MAXN],To[MAXN];

void Ins( int F,int T,int D ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
	Dt[Ct] = D;
}

int Dis[MAXN],Idg[MAXN];bool Vis[MAXN];
int Spfa(){
	queue< int >Que;
	memset( Dis,30,sizeof Dis );
	Que.push( 1 );Dis[1] = 0;Idg[1]++;
	while( !Que.empty() ){
		int p = Que.front();Que.pop();Vis[p] = false;
		for( int i=H[p];i;i=Nt[i] )
			if( Dis[To[i]] > Dis[p] + Dt[i] ){
				Dis[To[i]] = Dis[p] + Dt[i];
				if( !Vis[To[i]] ){
					Vis[To[i]] = true;
					if( ++Idg[To[i]]>n )return -1;
					Que.push( To[i] );
				}
			}
	}
	return Dis[n]==Dis[0]?-2:Dis[n];
}

int main(){
	
	Read( n );Read( ml );Read( md );
	while( ml-- )Read( u ),Read( v ),Read( w ),Ins( u,v, w );
	while( md-- )Read( u ),Read( v ),Read( w ),Ins( v,u,-w );
	printf("%d\n",Spfa());
	return 0;
}
