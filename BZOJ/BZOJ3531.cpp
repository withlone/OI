#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 1e5 +1;

char Opt[2];
int n,q,Num,Ct,Tot,u,v;
int W[MAXN],C[MAXN];
int Nt[MAXN<<1],H[MAXN<<1],To[MAXN<<1];
void Ins( int From,int _To ){
	Nt[++Num] = H[From];
	H[From] = Num;
	To[Num] = _To; 
}

int Size[MAXN],Fa[MAXN],Dep[MAXN],Son[MAXN],Root[MAXN],Rank[MAXN],Top[MAXN];
void Dfs1( int A ){
	Size[A] = 1;
	for( int i=H[A];i;i=Nt[i] ){
		int B = To[i];if( Fa[A]==B )continue;
		Fa[B] = A;Dep[B] = Dep[A] +1;
		Dfs1( B );
		Size[A] += Size[B];
		if( Size[B]>Size[Son[A]] )Son[A] = B;
	}
}
void Dfs2( int A,int Chain ){
	Rank[A] = ++Ct;
	Top[A] = Chain;
	if( Son[A] ) Dfs2( Son[A],Chain );
	for( int i=H[A];i;i=Nt[i] )
		if( To[i]!=Fa[A]&&To[i]!=Son[A] )
			Dfs2( To[i],To[i] );
}

int Sum[MAXN<<6],Max[MAXN<<6],Lc[MAXN<<6],Rc[MAXN<<6];
int Ch( int A,int B ){
	if( Opt[1] == 'S' ) return A+B;
	return max( A,B );
}
void MF( int& Nd,int l,int r,int p,int w ){
	if( !Nd ) Nd = ++Tot;
	if( l==r ){Sum[Nd] = Max[Nd] = w;return;}
	int Mid = ( l+r )>>1;
	if( p<=Mid ) MF( Lc[Nd],l,Mid,p,w );
	else MF( Rc[Nd],Mid+1,r,p,w );
	Sum[Nd] = Sum[Lc[Nd]] + Sum[Rc[Nd]];
	Max[Nd] = max( Max[Lc[Nd]],Max[Rc[Nd]] );
}
int Query( int Nd,int l,int r,int s,int t ){
	if( !Nd||l>t||r<s )return 0;
	if( l>=s&&r<=t ) return (Opt[1]=='S')?Sum[Nd]:Max[Nd];
	int Mid = ( l+r )>>1;
	return Ch( Query( Lc[Nd],l,Mid,s,t ),Query( Rc[Nd],Mid+1,r,s,t ) );
}
void Solve(){
	int Ans = 0,Be = C[u];
	while( Top[u]!=Top[v] ){
		if( Dep[Top[u]]<Dep[Top[v]] )swap( u,v );
		Ans = Ch( Ans,Query( Root[Be],1,n,Rank[Top[u]],Rank[u] ) );
		u = Fa[Top[u]];
	}
	if( Rank[u]>Rank[v] )swap( u,v );
	Ans = Ch( Ans,Query( Root[Be],1,n,Rank[u],Rank[v] ));
	printf("%d\n",Ans);
}

int main(){
	
	scanf("%d%d",&n,&q);
	for( int i=1;i<=n;i++ )scanf("%d%d",&W[i],&C[i]);
	for( int i=1;i< n;i++ )scanf("%d%d",&u,&v),Ins( u,v ),Ins( v,u );
	Dfs1( 1 );Dfs2( 1,1 );
	for( int i=1;i<=n;i++ )MF( Root[C[i]],1,n,Rank[i],W[i] );
	while( q-- ){
		Opt[0] = '0';while( Opt[0]!='C'&&Opt[0]!='Q' )Opt[0] = getchar();Opt[1] = getchar();
		scanf("%d%d",&u,&v);
		switch( Opt[1] ){
			case 'C':MF( Root[C[u]],1,n,Rank[u],0 );MF( Root[C[u]=v],1,n,Rank[u],W[u] );break;
			case 'W':MF( Root[C[u]],1,n,Rank[u],W[u]=v );break;
			default:Solve();
		}
	}
	return 0;
}
