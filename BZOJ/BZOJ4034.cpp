#include<cstdio>

template <typename Type> inline void Read( Type &in ){
	in=0;char ch=getchar();Type f=1;
	for(;ch> '9'||ch< '0';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())in=in*10+ch-'0';in*=f;
}

const int MAXN = 2e5 +1;
typedef long long LL;

int n,m,u,v,Num,Ct,Opt;
int Va[MAXN];
int Nt[MAXN<<1],To[MAXN<<1],H[MAXN<<1];
int Size[MAXN],Dep[MAXN],Fa[MAXN],Top[MAXN],Rank[MAXN],Son[MAXN],End[MAXN];
LL Sum[MAXN<<2],Add[MAXN<<2],k;

void Ins ( int ,int );
void Dfs1( int );
void Dfs2( int ,int );
void PD( int,int,int );
void Swap( int&,int& );
void Solve( int,int );

void MF( int,int,int,int,int,LL );
LL Query( int,int,int,int,int );

int main(){
	
	Read( n );Read( m );
	for( int i=1;i<=n;i++ )Read( Va[i] );
	for( int i=1;i< n;i++ )Read( u ),Read( v ),Ins( u,v ),Ins( v,u );
	Dfs1( 1 );Dfs2( 1,1 );
	for( int i=1;i<=n;i++ )MF( 1,1,n,Rank[i],Rank[i],Va[i] );
	while( m-- ){
		Read( Opt );Read( u );
		switch( Opt ){
			case 1:Read( k );MF( 1,1,n,Rank[u],Rank[u],k );break;
			case 2:Read( k );MF( 1,1,n,Rank[u],End[u] ,k );break;
			case 3:Solve( 1,u );break;
		}
	}
	return 0;
}

void Ins( int From,int _To ){
	Nt[++Num] = H[From];
	H[From] = Num;
	To[Num] = _To;
}

void Dfs1( int A ){
	Size[A] = 1;
	for( int i=H[A];i;i=Nt[i] ){
		int B = To[i];if( Fa[A]==B )continue;
		Dep[B] = Dep[A] +1;Fa[B] = A;
		Dfs1( B );
		Size[A] += Size[B];
		if( Size[Son[A]]<Size[B] ) Son[A] = B;
	}
}

void Dfs2( int A,int Chain ){
	Rank[A] = ++Ct;
	Top[A] = Chain;
	if( Son[A] ) Dfs2( Son[A],Chain );
	for( int i=H[A];i;i=Nt[i] )
		if( To[i]!=Son[A]&&Dep[To[i]]>Dep[A] )
			Dfs2( To[i],To[i] );
	End[A] = Ct;
}

void PD( int Nd,int L,int R ){
	int Lc = Nd<<1,Rc = Nd<<1|1;
	Add[Lc] += Add[Nd];
	Add[Rc] += Add[Nd];
	Sum[Lc] += Add[Nd]*L;
	Sum[Rc] += Add[Nd]*R;
	Add[Nd] = 0;
}

void Swap( int& A,int& B){A^=B^=A^=B;}

void Solve( int l,int r ){
	LL Ans = 0;
	while( Top[l]!=Top[r] ){
		if( Dep[Top[l]]<Dep[Top[r]] ) Swap( l,r );
		Ans += Query( 1,1,n,Rank[Top[l]],Rank[l] ) ;
		l = Fa[Top[l]];
	}
	if( Rank[l]>Rank[r] ) Swap( l,r );
	Ans += Query( 1,1,n,Rank[l],Rank[r] );
	printf("%lld\n",Ans);
}

void MF( int Nd,int l,int r,int s,int t,LL k ){
	if( l> t||r< s ) return;
	if( l>=s&&r<=t ){
		Sum[Nd] += k*( r-l+1 );
		Add[Nd] += k;
		return;
	}
	int Mid = ( l+r )>>1;
	if( Add[Nd] ) PD( Nd,Mid-l+1,r-Mid );
	MF( Nd<<1,l,Mid,s,t,k );MF( Nd<<1|1,Mid+1,r,s,t,k );
	Sum[Nd] = Sum[Nd<<1] + Sum[Nd<<1|1];
}

LL Query( int Nd,int l,int r,int s,int t ){
	if( l> t||r< s ) return 0;
	if( l>=s&&r<=t ) return Sum[Nd];
	int Mid = ( l+r )>>1;
	if( Add[Nd] ) PD( Nd,Mid-l+1,r-Mid );
	return Query( Nd<<1,l,Mid,s,t ) + Query( Nd<<1|1,Mid+1,r,s,t );
}
