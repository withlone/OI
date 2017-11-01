#include<cstdio>

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e5 +1;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

int n,u,v,P;
int Nt[MAXN<<1],H[MAXN],To[MAXN<<1],Ct;

namespace BIT{
	int Sum[MAXN];
	int Lowbit( int k ){ return k&-k; }
	void Add( int x,int k ){
		for( ;x<=n;x += Lowbit( x ) )Sum[x] += k;
	}
	int Get( int x ){
		int Res = 0;
		for( ;x;x -= Lowbit( x ) )Res += Sum[x];
		return Res;
	}
}

void Ins( int F,int T ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
}

int Rank[MAXN],Last[MAXN];
void Dfs( int p ){
	Rank[p] = ++Ct;
	for( int i=H[p];i;i=Nt[i] )
		if( !Rank[To[i]] )Dfs( To[i] );
	Last[p] = Ct;
}

using namespace BIT;
int main(){
	
	Read( n );
	For( i , 1 , n-1 )Read( u ),Read( v ),Ins( u,v ),Ins( v,u );
	
	Ct = 0;
	Dfs( 1 );
	
	For( i , 1 , n ){
		Read( P );
		printf("%d\n",Get( Rank[P] ));
		Add( Rank[P],1 );Add( Last[P]+1,-1 );
	}
	return 0;
}
