#include<cstdio>

template <typename Type> inline void Read( Type &in ){
	in=0;char ch=getchar();Type f=1;
	for( ;ch> '9'||ch< '0';ch=getchar() ) if( ch=='-' ) f=-1;
	for( ;ch>='0'&&ch<='9';ch=getchar() ) in=in*10+ch-'0';in*=f;
}

const int MAXN = 1e5 +1;
typedef long long LL;

int n,m,Root,Mod,u,v,w,Num,Ct,Opt;
int Va[MAXN];
int H[MAXN<<1],Nt[MAXN<<1],To[MAXN<<1];

void Ins( int From,int _To ){
	Nt[++Num] = H[From];
	H[From] = Num;
	To[Num] = _To;
}

int Size[MAXN],Rank[MAXN],Son[MAXN],End[MAXN],Fa[MAXN],Dep[MAXN],Top[MAXN];
void Dfs1( int A ){
	Size[A] = 1;
	for( int i=H[A];i;i=Nt[i] ){
		int B = To[i];if( Fa[A]==B ) continue;
		Fa[B] = A;Dep[B] = Dep[A] +1;
		Dfs1( B );
		Size[A] += Size[B];
		if( Size[B]>Size[Son[A]] ) Son[A] = B;
	}
}

void Dfs2( int A,int Chain ){
	Rank[A] = ++Ct;
	Top [A] = Chain;
	if( Son[A] ) Dfs2( Son[A],Chain );
	for( int i=H[A];i;i=Nt[i] )
		if( Dep[To[i]]>Dep[A]&&To[i]!=Son[A] )
			Dfs2( To[i],To[i] );
	End[A] = Ct;
}

LL Sum[MAXN<<2],Add[MAXN<<2];
void PD( int Nd,int L,int R ){
	int Lc = Nd<<1,Rc = Nd<<1|1;
	Sum[Lc] = ( Sum[Lc] + L*Add[Nd]%Mod ) %Mod;
	Sum[Rc] = ( Sum[Rc] + R*Add[Nd]%Mod ) %Mod;
	Add[Lc] = ( Add[Lc] + Add[Nd] ) %Mod;
	Add[Rc] = ( Add[Rc] + Add[Nd] ) %Mod;
	Add[Nd] = 0;
}
void MD( int Nd,int l,int r,int s,int t,int k ){
	if( l> t||r< s ) return;
	if( l>=s&&r<=t ){
		Sum[Nd] = ( Sum[Nd] + k*( r-l+1 ) ) %Mod;
		Add[Nd] = ( Add[Nd] + k ) %Mod;
		return;
	}
	int Mid = ( l+r )>>1;
	if( Add[Nd] ) PD( Nd,Mid-l+1,r-Mid );
	MD( Nd<<1,l,Mid,s,t,k );MD( Nd<<1|1,Mid+1,r,s,t,k );
	Sum[Nd] = (Sum[Nd<<1] + Sum[Nd<<1|1]) %Mod;
}

LL Query( int Nd,int l,int r,int s,int t ){
	if( l> t||r< s ) return 0;
	if( l>=s&&r<=t ) return Sum[Nd];
	int Mid = ( l+r )>>1;
	if( Add[Nd] ) PD( Nd,Mid-l+1,r-Mid );
	return ( Query( Nd<<1,l,Mid,s,t ) + Query( Nd<<1|1,Mid+1,r,s,t ) )%Mod;
}

void Solve( int A,int B ){
	LL Ans=0;
	while( Top[A]!=Top[B] ){
		if( Dep[Top[A]]<Dep[Top[B]] ) A^=B^=A^=B;
		Ans = ( Ans + Query( 1,1,n,Rank[Top[A]],Rank[A] ) ) %Mod;
		A = Fa[Top[A]];
	}
	if( Rank[A] > Rank[B] ) A^=B^=A^=B;
	Ans = ( Ans + Query( 1,1,n,Rank[A],Rank[B] ) ) %Mod;
	printf("%lld\n",Ans);
}

void UP( int A,int B,int k ){
	while( Top[A]!=Top[B] ){
		if( Dep[Top[A]]<Dep[Top[B]] ) A^=B^=A^=B;
		MD( 1,1,n,Rank[Top[A]],Rank[A],k );
		A = Fa[Top[A]];
	}
	if( Rank[A] > Rank[B] ) A^=B^=A^=B;
	MD( 1,1,n,Rank[A],Rank[B],k );
}

int main(){
	
	Read( n );Read( m );Read( Root );Read( Mod );
	for( int i=1;i<=n;i++ ) Read( Va[i] );
	for( int i=1;i< n;i++ ) Read( u ),Read( v ),Ins( u,v ),Ins( v,u );
	Dfs1( Root );Dfs2( Root,Root );
	for( int i=1;i<=n;i++ ) MD( 1,1,n,Rank[i],Rank[i],Va[i] );
	while( m-- ){
		Read( Opt );
		switch( Opt ){
			case 1:Read( u );Read( v );Read( w );UP( u,v,w );break;
			case 2:Read( u );Read( v );Solve( u,v );break;
			case 3:Read( u );Read( w );MD( 1,1,n,Rank[u],End[u],w );break;
			case 4:Read( u );printf("%lld\n",Query( 1,1,n,Rank[u],End[u] ) );break;
		}
	}
	return 0;
}
