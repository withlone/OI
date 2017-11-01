#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;

template <typename Type> inline void Read( Type &in ){
	in=0;char ch=getchar();Type f=1;
	for(;ch> '9'||ch< '0';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())in=in*10+ch-'0';in*=f;
}
template <typename Type> inline Type MAX( Type A,Type B ){return A>B?A:B;}

static const int MAXN = 1e5 +1;
static const int MAXM = MAXN<<1;

int n,m,Num,Ct,u,v,Opt,k,Ans;
int Nt[MAXM],H[MAXN],To[MAXM];
int Qu[MAXM],Qv[MAXM],Qw[MAXM];
int Size[MAXN],Top[MAXN],Son[MAXN],Rank[MAXN],Fa[MAXN],Dep[MAXN];

inline void Ins( int From,int _To ){
	Nt[++Num] = H[From];
	H[From] = Num;
	To[Num] = _To;
}

inline void Dfs1( int A ){
	Size[A] = 1;
	for( int i=H[A];i;i=Nt[i] ){
		int B = To[i];if( Fa[A]==B )continue;
		Fa[B] = A;Dep[B] = Dep[A] +1;
		Dfs1( B );
		Size[A] += Size[B];
		if( Size[B]>=Size[Son[A]] ) Son[A] = B;
	}
}

inline void Dfs2( int A,int Chain ){
	Rank[A] = ++Ct;
	Top [A] = Chain;
	if( Son[A] ) Dfs2( Son[A],Chain );
	for( int i=H[A];i;i=Nt[i] )
		if( To[i]!=Fa[A]&&To[i]!=Son[A] )
			Dfs2( To[i],To[i] );
}

struct Segment_Tree{
	priority_queue< int > Ext[2];
	inline int Get(){
		for( ;!Ext[0].empty()&&!Ext[1].empty()&&Ext[0].top()==Ext[1].top();Ext[0].pop(),Ext[1].pop());
		if( Ext[0].empty() ) return -1;
		return Ext[0].top();
	}
}Max[MAXN<<2];

inline void MF( int Nd,int l,int r,int s,int t,int w ){
	if( l>=s&&r<=t ){
		Max[Nd].Ext[Opt].push( w );
		return;
	}
	int Mid = ( l+r )>>1;
	if( Mid>=s )MF( Nd<<1,l,Mid,s,t,w );if( Mid<t )MF( Nd<<1|1,Mid+1,r,s,t,w );
}

inline void Query( int Nd,int l,int r,int s ){
	Ans = MAX( Ans,Max[Nd].Get() );
	if( l==r )return;
	int Mid = ( l+r )>>1;
	if( Mid>=s ) Query( Nd<<1,l,Mid,s );
	else Query( Nd<<1|1,Mid+1,r,s );
}

struct QUE{
	int l,r;
	inline bool operator < (QUE T)const{return l<T.l;}
}Que[MAXN];

inline void Solve( int A,int B,int C ){
	int Cnt = 0;
	while( Top[A]!=Top[B] ){
		if( Dep[Top[A]]<Dep[Top[B]] )A^=B^=A^=B;
		Que[++Cnt].l=Rank[Top[A]];Que[Cnt].r=Rank[A];
		A = Fa[Top[A]];
	}
	if( Rank[A]>Rank[B] )A^=B^=A^=B;
	Que[++Cnt].l=Rank[A];Que[Cnt].r=Rank[B];
	sort( Que+1,Que+1+Cnt );
	for( int i=1;i<=Cnt;i++ )if( Que[i-1].r+1<=Que[i].l-1 ) MF( 1,1,n,Que[i-1].r+1,Que[i].l-1,C );
	if( Que[Cnt].r+1<=n ) MF( 1,1,n,Que[Cnt].r+1,n,C );
}

int main(){
	
	Read( n );Read( m );
	for( int i=1;i< n;i++ )Read( u ),Read( v ),Ins( u,v ),Ins( v,u );
	Dfs1( 1 );Dfs2( 1,1 );
	for( int i=1;i<=m;i++ ){
		Read( Opt );Read( u );
		switch( Opt ){
			case 0:Qu[i] = u;Read( Qv[i] );Read( Qw[i] );Solve( Qu[i],Qv[i],Qw[i] );break;
			case 1:Solve( Qu[u],Qv[u],Qw[u] );break;
			case 2:Ans=-1;Query( 1,1,n,Rank[u] );printf("%d\n",Ans);break;
		}
	}
	return 0;
}
