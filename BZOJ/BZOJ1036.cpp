#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 3e4 +1;
const int Inf  = (unsigned)(-1)>>1;

int n,Q,Ct,Num,u,v;
int H[MAXN<<1],Nt[MAXN<<1],To[MAXN<<1],Va[MAXN];
int Sum[MAXN<<2],Max[MAXN<<2];
char s[10];

void Ins( int From,int to ){
	Nt[++Num] = H[From];
	H[From] = Num;
	To[Num] = to;
}

int Size[MAXN],Top[MAXN],Son[MAXN],Rank[MAXN],Fa[MAXN],Dep[MAXN];
void Dfs1( int A ){
	Size[A] = 1;
	for( int i=H[A];i;i=Nt[i] ){
		int B = To[i];
		if( Fa[A]==B ) continue;Fa[B] = A;Dep[B] = Dep[A] +1;
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
		if( Dep[To[i]]>Dep[A]&&To[i]!=Son[A] )
			Dfs2( To[i],To[i] );
}

int Check( int Flag,int A,int B ){
	if( Flag ) return A+B;
	return max( A,B );
}

void Modify( int Nd,int l,int r,int At,int Val ){
	if( l>At||r<At ) return;
	if( l==r&&l==At ){Max[Nd]=Sum[Nd]=Val;return;}
	int Mid = ( l+r ) >>1;
	Modify( Nd<<1,l,Mid,At,Val );Modify( Nd<<1|1,Mid+1,r,At,Val );
	Max[Nd] = max( Max[Nd<<1],Max[Nd<<1|1] );
	Sum[Nd] = Sum[Nd<<1] + Sum[Nd<<1|1];
}

int Query( int Flag,int Nd,int l,int r,int s,int t ){
	if( l> t||r< s ) return Flag?0:-Inf;
	if( l>=s&&r<=t ) return Flag?Sum[Nd]:Max[Nd];
	int Mid = ( l+r ) >>1;
	return Check( Flag,Query( Flag,Nd<<1,l,Mid,s,t ),Query( Flag,Nd<<1|1,Mid+1,r,s,t ) );
}

void Solve( int Flag,int l,int r ){
	int Ans = Flag?0:-Inf;
	while( Top[l]!=Top[r] ){
		if( Dep[Top[l]]<Dep[Top[r]] ) swap( l,r );
		Ans = Check( Flag,Ans,Query( Flag,1,1,n,Rank[Top[l]],Rank[l] ) );
		l = Fa[Top[l]];
	}
	if( Rank[l]>Rank[r] ) swap( l,r );
	Ans = Check( Flag,Ans,Query( Flag,1,1,n,Rank[l],Rank[r] ) );
	printf("%d\n",Ans);
}

int main(){
	
	scanf("%d",&n);
	for( int i=1;i< n;i++ )scanf("%d%d",&u,&v),Ins( u,v ),Ins( v,u );
	for( int i=1;i<=n;i++ )scanf("%d",&Va[i]);Dfs1( 1 );Dfs2( 1,1 );
	for( int i=1;i<=n;i++ )Modify( 1,1,n,Rank[i],Va[i] );
	scanf("%d",&Q);
	while( Q-- ){
		scanf("%s%d%d",s,&u,&v);
		if( s[1] == 'H' ) Modify( 1,1,n,Rank[u],v );
		if( s[1] == 'M' ) Solve ( 0,u,v );
		if( s[1] == 'S' ) Solve ( 1,u,v );
	}
	return 0;
}
