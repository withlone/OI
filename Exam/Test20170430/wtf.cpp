#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch=='-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}

static const int MAXN = 1e4 +10;
static const int MAXM = 1e2 +10;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
#define C first
#define D second

int T,s,n,Am,Ans;
int M[MAXN],L[MAXN],A[MAXN];
int f[MAXN][MAXM];

pair<int,int> Wtf[MAXN];

int Min[MAXN<<2];
#define Lc p<<1
#define Rc Lc|1
#define Lson Lc,l,Mid
#define Rson Rc,Mid+1,r
void Build( int p,int l,int r ){
	if( l==r ){
		Min[p] = Wtf[l].D;
		return;
	}
	int Mid = l+r >>1;
	Build( Lson );Build( Rson );
	Min[p] = min( Min[Lc],Min[Rc] );
}
int Query( int p,int l,int r,int L,int R ){
	if( l> R||r< L )return 0x7fffffff;
	if( l>=L&&r<=R )return Min[p];
	int Mid = l+r >>1;
	return min( Query( Lson,L,R ),Query( Rson,L,R ) );
}
int At[MAXN];
int Find( int x ){ return Query( 1,1,n,1,At[x] ); }

int Nt[MAXN],H[MAXN],To[MAXN],Ct;
void Ins( int F,int t ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = t;
}

int main(){
	
	freopen("wtf.in","r",stdin);
	freopen("wtf.out","w",stdout);
	memset( f,-1,sizeof f );
	Read( T );Read( s );Read( n );
	For( i , 1 , s )Read( M[i] ),Read( L[i] ),Read( A[i] ),Am = max( Am,A[i] ),Ins( M[i],i ),f[min(M[i]+L[i],T+1)][A[i]]=0;
	For( i , 1 , n )Read( Wtf[i].C ),Read( Wtf[i].D );
	sort( 1+Wtf , 1+n+Wtf );
	For( i , 1 , n )At[Wtf[i].C] = max( At[Wtf[i].C],i );
	For( i , 1 ,Am )if( !At[i] )At[i] = At[i-1];
	Build( 1,1,n );
	f[0][1] = 0;A[0] = 1;
	For( i , 0 , T ){
		int Max = -1;
		For( k , 0 , s ){
			int j = A[k];
			int t = Find( j );
			if( i )f[i][j] = max( f[i][j] , f[i-1][j] );
			if( i-t<0||f[i-t][j]==-1 )continue;
			f[i][j] = max( f[i][j] , f[i-t][j] + 1 );
			Max = max( Max,f[i][j] );
		}
		for( int j=H[i];j;j=Nt[j] )
			f[min(i+L[To[j]],T+1)][A[To[j]]] = max( Max,f[min(T+1,i+L[To[j]])][A[To[j]]] );
		Ans = max ( Ans , Max );
	}
	printf("%d\n",Ans);
	return 0;
}
