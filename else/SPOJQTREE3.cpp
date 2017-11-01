#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 1e5 +1;

int n,Ct,u,v,m,Ad;
int Val[MAXN],Rank[MAXN],End[MAXN];
int Nt[MAXN<<1],To[MAXN<<1],H[MAXN];
int Mp[MAXN];

int Rot[MAXN*20],Sum[MAXN*20],Lc[MAXN*20],Rc[MAXN*20];
void Build( int &Nd,int Pt,int l,int r,int w ){
	Nd = ++Ad;Sum[Nd] = Sum[Pt] +1;
	if( l==r )return;
	Lc[Nd] = Lc[Pt];Rc[Nd] = Rc[Pt];
	int Mid = l+r >>1;
	if( w<=Mid )Build( Lc[Nd],Lc[Pt],l,Mid,w );
	else Build( Rc[Nd],Rc[Pt],Mid+1,r,w );
}
int Query( int Nd,int Pt,int l,int r,int k ){
	if( l==r )return l;
	int Mid = l+r >>1;
	if( Sum[Lc[Nd]]-Sum[Lc[Pt]]>=k )return Query( Lc[Nd],Lc[Pt],l,Mid,k );
	return Query( Rc[Nd],Rc[Pt],Mid+1,r,k-(Sum[Lc[Nd]]-Sum[Lc[Pt]]) );
}

void Ins( int F,int T ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
}
void Dfs( int p,int Fa ){
	Rank[p] = ++Ct;
	Build( Rot[Ct],Rot[Ct-1],1,n,Val[p] );
	for( int i=H[p];i;i=Nt[i] ){
		if( To[i]==Fa )continue;
		Dfs( To[i],p );
	}
	End[p] = Ct;
}

struct Deal{
	int Val,Num;
	bool operator < ( Deal B )const { return Val<B.Val; }
}A[MAXN];

int main(){
	
	scanf("%d",&n);
	for( int i=1;i<=n;i++ )scanf("%d",&Val[i]),A[i].Val = Val[i],A[i].Num = i;
	sort( 1+A,1+n+A );
	for( int i=1;i<=n;i++ )Val[A[i].Num] = i,Mp[i] = A[i].Num;
	for( int i=1;i< n;i++ )scanf("%d%d",&u,&v),Ins( u,v ),Ins( v,u );
	Ct = 0;Dfs( 1,0 );
	scanf("%d",&m);
	while( m-- ){
		scanf("%d%d",&u,&v);
		printf("%d\n",Mp[Query( Rot[End[u]],Rot[Rank[u]-1],1,n,v )]);
	}
	return 0;
}
