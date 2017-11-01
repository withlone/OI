#include<cstdio>
#include<cstring>

template <typename Type> inline void Read( Type& in ){
	in = 0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )in=in*10+ch-'0';
}

const int MAXN = 1e5 +1;

char Opt;
int n,m,In,Num,Ct;
int Nt[MAXN],H[MAXN],To[MAXN];
void Ins( int From,int _To ){
	Nt[++Num] = H[From];
	H[From] = Num;
	To[Num] = _To;
}

int Size[MAXN],Fa[MAXN],Top[MAXN],Rank[MAXN],Dep[MAXN],Son[MAXN],End[MAXN];
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
	if( Son[A] )Dfs2( Son[A],Chain );
	for( int i=H[A];i;i=Nt[i] )
		if( To[i]!=Fa[A]&&To[i]!=Son[A] )
			Dfs2( To[i],To[i] );
	End[A] = Ct;
}

int Sum[MAXN<<2],Add[MAXN<<2];
void PD( int Nd,int L,int R ){
	int Lc = Nd<<1,Rc = Nd<<1|1;
	Add[Lc] = Add[Rc] = Add[Nd];
	Sum[Lc] = Add[Nd]*L;
	Sum[Rc] = Add[Nd]*R;
	Add[Nd] = -1;
}
void MF( int Nd,int l,int r,int s,int t,int w ){
	if( l> t||r< s )return;
	if( l>=s&&r<=t ){
		Sum[Nd] = w*(r-l+1);
		Add[Nd] = w;
		return;
	}
	int Mid = ( l+r )>>1;
	if( Add[Nd]!=-1 ) PD( Nd,Mid-l+1,r-Mid );
	MF( Nd<<1,l,Mid,s,t,w );MF( Nd<<1|1,Mid+1,r,s,t,w );
	Sum[Nd] = Sum[Nd<<1] + Sum[Nd<<1|1];
}
int Query( int Nd,int l,int r,int s,int t ){
	if( l> t||r< s ) return 0;
	if( l>=s&&r<=t ) return Sum[Nd];
	int Mid = ( l+r )>>1;
	if( Add[Nd]!=-1 ) PD( Nd,Mid-l+1,r-Mid );
	return Query( Nd<<1,l,Mid,s,t ) + Query( Nd<<1|1,Mid+1,r,s,t );
}
void Solve( int l,int r ){
	int Ans = 0;
	while( Top[l]!=Top[r] ){
		if( Dep[Top[l]]<Dep[Top[r]] ) l^=r^=l^=r;
		Ans += Query( 1,1,n,Rank[Top[l]],Rank[l] );
		MF( 1,1,n,Rank[Top[l]],Rank[l],1 );
		l = Fa[Top[l]];
	}
	if( Rank[l]>Rank[r] ) l^=r^=l^=r;
	Ans += Query( 1,1,n,Rank[l],Rank[r] );
	MF( 1,1,n,Rank[l],Rank[r],1 );
	printf("%d\n",Dep[In]-Ans+1);
}

int main(){
	
	memset( Add,-1,sizeof Add );
	Read( n );
	for( int i=2;i<=n;i++ )Read( In ),Ins( 1+In,i );
	Dfs1( 1 );Dfs2( 1,1 );
	Read( m );
	while( m-- ){
		Opt = '0';while( Opt!='i'&&Opt!='u' )Opt=getchar();
		Read( In );++In;
		if( Opt=='i' )Solve( 1,In );
		else{
			printf("%d\n",Query( 1,1,n,Rank[In],End[In] ));
			MF( 1,1,n,Rank[In],End[In],0 );
		}
	}
	return 0;
}
