#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

const int MAXN = 5e5 +1;

int Ct,n,Rot,u,v,w;long long Ans;
int Fa[MAXN],G[MAXN],F[MAXN];
int Nt[MAXN<<1],H[MAXN],To[MAXN<<1],Dis[MAXN<<1];

void Ins( int F,int T,int D ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
	Dis[Ct] = D;
}

void Dfs( int p,int Num ){
	for( int i=H[p];i;i=Nt[i] ){
		if( Fa[p]==To[i] )continue;
		Fa[To[i]] = p;
		Dfs( To[i],i );
		G[p] = max( G[p],G[To[i]]+Dis[i] );
	}
}
void Dp( int p ){
	for( int i=H[p];i;i=Nt[i] ){
		if( Fa[p]==To[i] )continue;
		Dp( To[i] );
		Ans += F[To[i]] + G[p] - G[To[i]] - Dis[i];
		//F[p] += F[To[i]] + G[p] - G[To[i]] - Dis[i];
	}
}

int main(){
	
	Read( n );Read( Rot );
	for( int i=1;i<n;i++ )Read( u ),Read( v ),Read( w ),Ins( u,v,w ),Ins( v,u,w );
	Dfs( Rot,0 );
	Dp( Rot );
	printf("%lld\n",Ans);
	return 0;
}
