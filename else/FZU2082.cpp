#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

template <typename Type >inline void Read( Type &in ){
	in  = 0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )in=in*10+ch-'0';
}

const int MAXN  = 5e4 +1;
typedef long long LL;
#define Clear(i) memset(i,0,sizeof i)

int n,m,Ct,Num,Opt,u,v;LL w;
int Nt[MAXN<<1],H[MAXN<<1],To[MAXN<<1];
struct NODE{
	int u,v;LL w;
}Node[MAXN];

void Ins( int From,int _To ){
	Nt[++Num] = H[From];
	H[From]   = Num;
	To[Num]   = _To;
}

int Size[MAXN],Top[MAXN],Rank[MAXN],Fa[MAXN],Dep[MAXN],Son[MAXN];
void Dfs1( int A ){
	Size[A] = 1;
	for( int i=H[A];i;i=Nt[i] ){
		int B = To[i];if( Fa[A]==B )continue;
		Fa[B] = A;Dep[B] = Dep[A] +1;
		Dfs1( B );
		Size[A] += Size[B];
		if( Size[B]>Size[Son[A]] ) Son[A] = B;
	}
}
void Dfs2( int A,int Chain ){
	Rank[A] = ++Ct;
	Top[A]  = Chain;
	if( Son[A] ) Dfs2( Son[A],Chain );
	for( int i=H[A];i;i=Nt[i] )
		if( To[i]!=Fa[A]&&To[i]!=Son[A] )
			Dfs2( To[i],To[i] );
}

LL Sum[MAXN<<2];
void MF( int Nd,int l,int r,int p,LL W ){
	if( l==r ){Sum[Nd] = W;return;}
	int Mid = ( l+r )>>1;
	if( p<=Mid )MF( Nd<<1,l,Mid,p,W );
	else MF( Nd<<1|1,Mid+1,r,p,W );
	Sum[Nd] = Sum[Nd<<1] + Sum[Nd<<1|1];
}
LL Query( int Nd,int l,int r,int s,int t ){
	if( l> t||r< s )return 0;
	if( l>=s&&r<=t )return Sum[Nd];
	int Mid = ( l+r )>>1;
	return Query( Nd<<1,l,Mid,s,t ) + Query( Nd<<1|1,Mid+1,r,s,t );
}
void Solve( int l,int r ){
	LL Ans = 0;
	while( Top[l]!=Top[r] ){
		if( Dep[Top[l]]<Dep[Top[r]] )swap( l,r );
		Ans += Query( 1,1,n,Rank[Top[l]],Rank[l] );
		l = Fa[Top[l]];
	}
	if( Rank[l]>Rank[r] )swap( l,r );
	Ans += Query( 1,1,n,Rank[l]+1,Rank[r] );
	printf("%lld\n",Ans);
}

int main(){
	
	while(scanf("%d%d",&n,&m)==2){
		Num = Ct = 0;
		Clear( Nt );Clear( To );Clear( Sum );Clear( H );
		Clear(Size);Clear(Top) ;Clear(Rank)  ;Clear(Fa)	  ;Clear(Dep);  Clear(Son);
		for( int i=1;i< n;i++ ){
			Read( Node[i].u );Read( Node[i].v );Read( Node[i].w );
			Ins( Node[i].u,Node[i].v );Ins( Node[i].v,Node[i].u );
		}
		Dfs1( 1 );Dfs2( 1,1 );
		for( int i=1;i< n;i++ ){
			if( Dep[Node[i].u]<Dep[Node[i].v] )swap( Node[i].u,Node[i].v );
			MF( 1,1,n,Rank[Node[i].u],Node[i].w );
		}
		while( m-- ){
			Read( Opt );Read( u );
			if( !Opt ) Read( w ),MF( 1,1,n,Rank[Node[u].u],w );
			else Read( v ),Solve( u,v );
		}
	}
	return 0;
}
