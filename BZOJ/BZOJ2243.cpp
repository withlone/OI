#include<cstdio>
template <typename Type>inline void Read( Type &in ){
	in = 0;char ch=getchar();Type f=1;
	for(;ch> '9'||ch< '0';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())in=in*10+ch-'0';in*=f;
}

const int MAXN = 2e5 +1;

char Opt;
int n,m,Num,Ct,u,v,w;
int Col[MAXN];
int Nt[MAXN<<1],H[MAXN<<1],To[MAXN<<1];
void Ins( int From,int _To ){
	Nt[++Num] = H[From];
	H[From] = Num;
	To[Num] = _To;
}

int Size[MAXN],Fa[MAXN],Dep[MAXN],Son[MAXN],Top[MAXN],Rank[MAXN];
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
	Top[A]  = Chain;
	if( Son[A] ) Dfs2( Son[A],Chain );
	for( int i=H[A];i;i=Nt[i])
		if( To[i]!=Son[A]&&To[i]!=Fa[A] )
			Dfs2( To[i],To[i] );
}

int Sum[MAXN<<2],Lco[MAXN<<2],Rco[MAXN<<2],Add[MAXN<<2];
void PD( int Nd ){
	int Lc = Nd<<1,Rc = Nd<<1|1;
	Lco[Lc] = Lco[Rc] = Rco[Lc] = Rco[Rc] = Add[Lc] = Add[Rc] = Add[Nd];
	Sum[Lc] = Sum[Rc] = 1;
	Add[Nd] = 0;
}
void MF( int Nd,int l,int r,int s,int t,int Col ){
	if( l> t||r< s )return;
	if( l>=s&&r<=t ){
		Lco[Nd] = Rco[Nd] = Add[Nd] = Col;
		Sum[Nd] = 1;
		return;
	}
	if( Add[Nd] )PD( Nd );
	int Mid = ( l+r )>>1;
	MF( Nd<<1,l,Mid,s,t,Col );MF( Nd<<1|1,Mid+1,r,s,t,Col );
	Lco[Nd] = Lco[Nd<<1];Rco[Nd] = Rco[Nd<<1|1];
	Sum[Nd] = Sum[Nd<<1] + Sum[Nd<<1|1] - (Rco[Nd<<1]==Lco[Nd<<1|1]);
}
int Query( int Nd,int l,int r,int s,int t ){
	if( l>=s&&r<=t )return Sum[Nd];
	if( Add[Nd] )PD( Nd );
	int Mid = ( l+r )>>1,A=0,Flag=0;
	if( !(s<=Mid) ) Flag=1;else A += Query( Nd<<1,l,Mid,s,t );
	if( !(Mid<t) ) Flag=1;else A += Query( Nd	<<1|1,Mid+1,r,s,t );
	if( !Flag && Rco[Nd<<1] == Lco[Nd<<1|1] ) A--;
	return A;
}
int Color( int Nd,int l,int r,int s ){
	if( l==r ) return Lco[Nd];
	if( Add[Nd] ) PD( Nd );
	int Mid = ( l+r )>>1;
	if( Mid>=s ) return Color( Nd<<1,l,Mid,s );
	return Color( Nd<<1|1,Mid+1,r,s );
}
void Solve(){
	int Ans = 0;
	while( Top[u]!=Top[v] ){
		if( Dep[Top[u]]<Dep[Top[v]] ) u^=v^=u^=v;
		if( Opt=='C' ) MF( 1,1,n,Rank[Top[u]],Rank[u],w );
		else Ans += Query( 1,1,n,Rank[Top[u]],Rank[u] ) - ( Color( 1,1,n,Rank[Top[u]] )==Color( 1,1,n,Rank[Fa[Top[u]]] ) );
		u = Fa[Top[u]];
	}
	if( Rank[u]>Rank[v] ) u^=v^=u^=v;
	if( Opt=='C' ) MF( 1,1,n,Rank[u],Rank[v],w );
	else Ans += Query( 1,1,n,Rank[u],Rank[v] );
	if( Opt=='Q' ) printf("%d\n",Ans);
}

int main(){
	
	scanf("%d%d",&n,&m);
	for( int i=1;i<=n;i++ )Read( Col[i] ),Col[i]++;
	for( int i=1;i< n;i++ )Read( u ),Read( v ),Ins( u,v ),Ins( v,u );
	Dfs1( 1 );Dfs2( 1,1 );
	for( int i=1;i<=n;i++ )MF( 1,1,n,Rank[i],Rank[i],Col[i] );
	while( m-- ){
		Opt = '0';
		while( Opt!='C'&&Opt!='Q' )	Opt=getchar();
		Read( u );Read( v );
		if( Opt=='C' )Read( w ),w++;
		Solve();
	}
	return 0;
}
