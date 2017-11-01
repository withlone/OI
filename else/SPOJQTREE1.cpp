#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();Type f=1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch=='-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}

static const int MAXN = 1e4 +5;
#define Lson p<<1,l,Mid
#define Rson p<<1|1,Mid+1,r

int T,n,u[MAXN],v[MAXN],w[MAXN],Ct;char Opt[10];
int H[MAXN],Nt[MAXN<<1],To[MAXN<<1],Dis[MAXN<<1],Road[MAXN<<1];

void Ins( int F,int T,int D ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
	Dis[Ct] = D;
}

int Size[MAXN],Rank[MAXN],Dep[MAXN],Son[MAXN],Top[MAXN],Fa[MAXN],Wa[MAXN];
int Max[MAXN<<2];
void Dfs1( int p ){
	Size[p] = 1;
	for( int i=H[p];i;i=Nt[i] ){
		if( Fa[p]==To[i] )continue;
		Dep[To[i]] = Dep[p] +1;Fa[To[i]] = p;Wa[To[i]] = Dis[i];
		Dfs1( To[i] );
		Size[p] += Size[To[i]];
		if( Size[To[i]]>Size[Son[p]] )Son[p] = To[i];
	}
}
void Dfs2( int p,int Chain ){
	Rank[p] = ++Ct;
	Top[p] = Chain;
	if( Son[p] )Dfs2( Son[p],Chain );
	for( int i=H[p];i;i=Nt[i] )
		if( To[i]!=Fa[p]&&To[i]!=Son[p] )
			Dfs2( To[i],To[i] );
}
void Modify( int p,int l,int r,int k,int w ){
	if( l> k||r< k )return;
	if( l==r&&l==k ){
		Max[p] = w;
		return;
	}
	int Mid = l+r >>1;
	Modify( Lson,k,w );Modify( Rson,k,w );
	Max[p] = max( Max[p<<1],Max[p<<1|1] );
}
int Query( int p,int l,int r,int L,int R ){
	if( l> R||r< L )return 0;
	if( l>=L&&r<=R )return Max[p];
	int Mid = l+r >>1;
	return max( Query( Lson,L,R ),Query( Rson,L,R ) );
}
void Solve( int x,int y ){
	int Ans = 0;
	while( Top[x]!=Top[y] ){
		if( Dep[Top[x]]<Dep[Top[y]] )swap( x,y );
		Ans = max( Ans,Query( 1,1,n,Rank[Top[x]],Rank[x] ) );
		x = Fa[Top[x]];
	}
	if( Dep[x]>Dep[y] )swap( x,y );
	Ans = max( Ans,Query( 1,1,n,Rank[Son[x]],Rank[y] ) );
	printf("%d\n",Ans);
}

int main(){
	
	Read( T );
	while( T-- ){
		Read( n );
		Ct=0;memset( Road,0,sizeof Road );
		memset( Rank,0,sizeof Rank );memset( H,0,sizeof H );memset( Max,0,sizeof Max );memset( Fa,0,sizeof Fa );
		memset( Dep,0,sizeof Dep );memset( Wa,0,sizeof Wa );memset( Size,0,sizeof Size );memset( Nt,0,sizeof Nt );
		memset( Dis,0,sizeof Dis );memset( Son,0,sizeof Son );memset( Top,0,sizeof Top );memset( To,0,sizeof To );
		for( int i=1;i< n;i++ )Read( u[i] ),Read( v[i] ),Read( w[i] ),Ins( u[i],v[i],w[i] ),Ins( v[i],u[i],w[i] );
		Ct = 0;
		Dfs1( 1 );Dfs2( 1,1 );
		for( int i=1;i< n;i++ )u[i] = Dep[u[i]]>Dep[v[i]]?u[i]:v[i];
		for( int i=1;i<=n;i++ )Modify( 1,1,n,Rank[i],Wa[i] );
		while( 1 ){
			scanf("%s",Opt);
			if( Opt[0]=='D' )break;
			Read( u[0] );Read( v[0] );
			if( Opt[0]=='C' )Modify( 1,1,n,Rank[u[u[0]]],v[0] );
			if( Opt[0]=='Q' )Solve( u[0],v[0] );
		}
	}
	return 0;
}
