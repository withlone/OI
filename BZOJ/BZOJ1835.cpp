#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type > inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 2e4 +2;
static const int Inf  = 1e9 +1;
#define Lc p<<1
#define Rc Lc|1
#define Lson Lc,l,Mid
#define Rson Rc,Mid+1,r

int N,K;
int D[MAXN],C[MAXN],S[MAXN],W[MAXN],L[MAXN],R[MAXN];
int Nt[MAXN],To[MAXN],H[MAXN],Ct;
int f[MAXN];

void Ins( int F,int T ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
}

void Init(){
	Read( N );Read( K );
	for( int i=2;i<=N;i++ )Read( D[i] );
	for( int i=1;i<=N;i++ )Read( C[i] );
	for( int i=1;i<=N;i++ )Read( S[i] );
	for( int i=1;i<=N;i++ )Read( W[i] );
	N++;K++;D[N] = S[N] = Inf;
	for( int i=1;i<=N;i++ ){
		L[i] = lower_bound( 1+D,1+N+D,D[i]-S[i] )-D;
		R[i] = lower_bound( 1+D,1+N+D,D[i]+S[i] )-D;
		if( D[R[i]]>D[i]+S[i] )R[i]--;
		Ins( R[i],i );
	}
}

int Min[MAXN<<2],Add[MAXN<<2];
void Up( int p ){ Min[p] = min( Min[Lc],Min[Rc] ); }
void Build( int p,int l,int r ){
	Add[p] = 0;
	if( l==r ){
		Min[p] = f[l];
		return;
	}
	int Mid = l+r >>1;
	Build( Lson );Build( Rson );
	Up( p );
}
void Pd( int p ){
	if( !Add[p] )return;
	Add[Lc] += Add[p];Add[Rc] += Add[p];
	Min[Lc] += Add[p];Min[Rc] += Add[p];
	Add[p] = 0;
}
void Mf( int p,int l,int r,int L,int R,int k ){
	if( l> R||r< L )return;
	if( l>=L&&r<=R ){
		Add[p] += k;
		Min[p] += k;
		return;
	}
	int Mid = l+r >>1;
	Pd( p );
	Mf( Lson,L,R,k );Mf( Rson,L,R,k );
	Up( p );
}
int Query( int p,int l,int r,int L,int R ){
	if( l> R||r< L )return 0x7fffffff;
	if( l>=L&&r<=R )return Min[p];
	int Mid = l+r >>1;
	Pd( p );
	return min( Query( Lson,L,R ),Query( Rson,L,R ) );
}

int Dp(){
	int t = 0;
	for( int i=1;i<=N;i++ ){
		f[i] = t + C[i];
		for( int j=H[i];j;j=Nt[j] )t += W[To[j]];
	}
	int Res = f[N];
	for( int j=2;j<=K;j++ ){
		Build( 1,1,N );
		f[1] = C[1];
		for( int i=2;i<=N;i++ ){
			f[i] = Query( 1,1,N,1,i-1 ) + C[i];
			for( int k=H[i];k;k=Nt[k] )
				if( L[To[k]]-1>=1 )
					Mf( 1,1,N,1,L[To[k]]-1,W[To[k]] );
		}
		Res = min( Res,f[N] );
	}
	return Res;
}

int main(){
	
	Init();
	printf("%d\n",Dp());
	return 0;
}
