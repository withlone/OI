#include<cstdio>

const int MAXN = 1e5 +1;

int n,m,u,v,Num,Ct;char Opt;
int Nt[MAXN<<1],H[MAXN<<1],To[MAXN<<1];

void Ins( int From,int _To ){
	Nt[++Num] = H[From];
	H[From] = Num;
	To[Num] = _To;
}

int Size[MAXN],Fa[MAXN],Top[MAXN],Rank[MAXN],Son[MAXN],Dep[MAXN],Road[MAXN<<1];
int Sum[MAXN<<2],Add[MAXN<<2];
void Dfs1( int A ){
	Size[A] = 1;
	for( int i=H[A];i;i=Nt[i] ){
		int B = To[i];if( Fa[A]==B )continue;
		Road[i] = B;
		Dep[B] = Dep[A] +1;Fa[B] = A;
		Dfs1( B );
		Size[A] += Size[B];
		if( Size[B]>Size[Son[A]] ) Son[A] = B;
	}
}

void Dfs2( int A,int Chain ){
	Rank[A] = ++Ct;
	Top[A] = Chain;
	if( Son[A] ) Dfs2( Son[A],Chain );
	for( int i=H[A];i;i=Nt[i] )
		if( Son[A]!=To[i]&&To[i]!=Fa[A] )
			Dfs2( To[i],To[i] );
}

void PD( int Nd,int L,int R ){
	int Lc = Nd<<1,Rc = Nd<<1|1;
	Add[Lc] += Add[Nd];
	Add[Rc] += Add[Nd];
	Sum[Lc] += Add[Nd]*L;
	Sum[Rc] += Add[Nd]*R;
	Add[Nd] = 0;
}

void MF( int Nd,int l,int r,int s,int t ){
	if( l> t||r< s ) return;
	if( l>=s&&r<=t ){
		Sum[Nd] += r-l+1;
		Add[Nd]++;
		return;
	}
	int Mid = ( l+r )>>1;
	if( Add[Nd] ) PD( Nd,Mid-l+1,r-Mid );
	MF( Nd<<1,l,Mid,s,t );MF( Nd<<1|1,Mid+1,r,s,t );
	Sum[Nd] = Sum[Nd<<1] + Sum[Nd<<1|1];
}

int Query( int Nd,int l,int r,int s,int t ){
	if( l> t||r< s )return 0;
	if( l>=s&&r<=t )return Sum[Nd];
	int Mid = ( l+r )>>1;
	if( Add[Nd] ) PD( Nd,Mid-l+1,r-Mid );
	return Query( Nd<<1,l,Mid,s,t ) + Query( Nd<<1|1,Mid+1,r,s,t );
}

void Solve( int A,int B ){
	int Ans = 0;
	while( Top[A]!=Top[B] ){
		if( Dep[Top[A]]<Dep[Top[B]] )A^=B^=A^=B;
		if( Opt=='P' )MF( 1,1,n,Rank[Top[A]],Rank[A] );
		else Ans += Query( 1,1,n,Rank[Top[A]],Rank[A] );
		A = Fa[Top[A]];
	}
	if( Rank[A]>Rank[B] ) A^=B^=A^=B;
	if( Opt=='P' )MF( 1,1,n,Rank[A]+1,Rank[B] );
	else Ans += Query( 1,1,n,Rank[A]+1,Rank[B] );
	if( Opt=='Q' ) printf("%d\n",Ans);
}

int main(){
	
	scanf("%d%d",&n,&m);
	for(int i=1;i< n;i++)scanf("%d%d",&u,&v),Ins( u,v ),Ins( v,u );
	Dfs1( 1 );Dfs2( 1,1 );
	while( m-- ){
		Opt = '0';
		while( Opt!='P'&&Opt!='Q' ) scanf("%c",&Opt);
		scanf("%d%d",&u,&v);
		Solve( u,v );
	}
	return 0;
}
