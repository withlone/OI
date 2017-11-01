#include<cstdio>
#include<cstring>

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}
template< typename Type >inline void swap( Type& x,Type& y ){ x^=y^=x^=y; }

const int MAXN = 1e4 +1;
const int MAX  = 20;
#define Mem( p ) memset( p,0,sizeof p )

int n,T,u,v,w,Ct,Tmp;char Opt[10];
int Nt[MAXN<<1],To[MAXN<<1],Dt[MAXN<<1],H[MAXN];
int Fa[MAXN][MAX+1],Dis[MAXN];
int Dep[MAXN];

void Ins( int F,int T,int D ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
	Dt[Ct] = D;
}
void Dfs( int p ){
	for( int i=H[p];i;i=Nt[i] ){
		if( Fa[p][0]==To[i] )continue;
		Dep[To[i]] = Dep[p] +1;Fa[To[i]][0] = p;Dis[To[i]] = Dt[i] + Dis[p];
		Dfs( To[i] );
	}
}
int Lca( int x,int y ){
	if( Dep[x]<Dep[y] )swap( x,y );
	int D = Dep[x] - Dep[y];
	for( int i=MAX;i>=0;i-- )
		if( D&(1<<i) )x = Fa[x][i];
	if( x==y )return x;
	for( int i=MAX;i>=0;i-- )
		if( Fa[x][i]!=Fa[y][i] )x = Fa[x][i],y = Fa[y][i];
	return Fa[x][0];
}
int Work(){
	Read( w );int lca = Lca( u,v );
	if( Dep[u]-Dep[lca]+1 >= w ){
		w--;
		for( int i=MAX;i>=0;i-- )
			if( w&(1<<i) )u = Fa[u][i];
		return u;
	}
	w = Dep[u]+Dep[v]-(Dep[lca]<<1)+1 - w;
	for( int i=MAX;i>=0;i-- )
		if( w&(1<<i) )v = Fa[v][i];
	return v;
}

int main(){
	
	Read( T );
	while( T-- ){
		Read( n );
		Ct = 0;Mem( Fa );Mem( Dis );Mem( H );Mem( Dep );
		for( int i=1;i< n;i++ )Read( u ),Read( v ),Read( w ),Ins( u,v,w );
		Dfs( 1 );
		for( int j=1;j<=MAX;j++ )for( int i=1;i<=n;i++ )Fa[i][j]  = Fa[Fa[i][j-1]][j-1];
		scanf("%s",Opt);
		while( Opt[0]!='D'||Opt[1]!='O' ){
			Read( u );Read( v );
			if( Opt[0]=='D' )printf("%d\n",Dis[u]+Dis[v]-(Dis[Lca(u,v)]<<1));
			else printf("%d\n",Work());
			scanf("%s",Opt);
		}
	}
	return 0;
}
