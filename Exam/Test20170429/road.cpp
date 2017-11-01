#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e6 +1;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
#define Rep( i , _End , _Begin ) for( int i=_End;i>=_Begin;i-- )
typedef long long LL;

int n,A[MAXN],B[MAXN],Ct;LL C[MAXN];
int Nt[MAXN<<1],To[MAXN<<1],H[MAXN];LL Dis[MAXN<<1];

void Ins( int F,int T,LL D ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
	Dis[Ct] = D;
}

int Size[MAXN],Fa[MAXN],Que[MAXN+1],h,T;LL w[MAXN];
LL Bfs(){
	Que[++T] = 1;
	while( h!=T ){
		int p = Que[++h];
		for( int i=H[p];i;i=Nt[i] )
			if( To[i]!=Fa[p] ){
				Que[++T] = To[i];
				Fa[To[i]] = p;
				w[To[i]] = Dis[i];
			}
	}
	LL Res = 0;
	Rep( i , n , 1 )Size[Fa[Que[i]]] += (++Size[Que[i]]);
	For( i , 1 , n )Res += abs( n-Size[i]*2 )*w[i];
	return Res;
}

#define OnlineJudge
int main(){
	
	#ifdef OnlineJudge
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	#endif
	
	Read( n );
	For( i , 1 , n-1 ){
		Read( A[i] );Read( B[i] );Read( C[i] );
		Ins( A[i],B[i],C[i] );Ins( B[i],A[i],C[i] );
	}
	printf("%lld\n",Bfs());
	return 0;
}
