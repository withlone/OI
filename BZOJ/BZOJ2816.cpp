#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

const int MAXN = 1e4 +1;

int N,M,C,K,u,v,w,Opt,Tp;
int Val[MAXN],Col[MAXN][11],St[MAXN];
map < int,int > Mp[MAXN];

struct Link_Cut_Tree{
	int Fa[MAXN],Ch[MAXN][2],Max[MAXN];bool Flag[MAXN];
	int GS( int p ){ return p==Ch[Fa[p]][1]; }
	bool Is_Rot( int p ){ return p!=Ch[Fa[p]][0]&&p!=Ch[Fa[p]][1]; }
	void UP( int p ){ Max[p] = max( Val[p],max( Max[Ch[p][0]],Max[Ch[p][1]] ) ); }
	void Rotate( int p ){
		int fa = Fa[p],Gfa = Fa[fa],t=GS(p);
		if( !Is_Rot(fa) )Ch[Gfa][GS(fa)] = p;
		Fa[p] = Gfa;
		Ch[fa][t] = Ch[p][t^1];
		if( Ch[p][t^1] )Fa[Ch[p][t^1]] = fa;
		Fa[fa] = p;
		Ch[p][t^1] = fa;
		UP( fa );UP( p );
	}
	void Flip( int p ){
		if( !Flag[p] )return;
		int l = Ch[p][0],r = Ch[p][1];
		if( l )Flag[l] ^= 1;
		if( r )Flag[r] ^= 1;
		swap( Ch[p][0],Ch[p][1] );
		Flag[p] = 0;
	}
	void Push( int p ){
		St[Tp=1] = p;
		for( ;!Is_Rot(p);p=Fa[p] )St[++Tp] = Fa[p];
		while( Tp )Flip( St[Tp--] );
	}
	void Splay( int p ){
		Push( p );
		for( int fa;!Is_Rot(p);Rotate(p) )
			if( !Is_Rot(fa=Fa[p]) )
				Rotate( GS( fa )==GS( p )?fa:p );
	}
	void Access( int p ){
		int t = 0;
		while( p ){
			Splay( p );
			Ch[p][1] = t;
			UP( p );
			t = p;p = Fa[p];
		}
	}
	void MRot( int p ){
		Access( p );
		Splay( p );
		Flag[p] ^= 1;
	}
	void Link( int x,int y ){
		MRot( x );
		Fa[x] = y;
		UP( y );
		Splay( x );
	}
	void Cut( int x,int y ){
		MRot( x );
		Access( y );Splay( y );
		Fa[x] = Ch[y][0] = 0;UP( y );
	}
	int Find( int p ){
		Access( p );
		Splay( p );
		while( Ch[p][0] )p = Ch[p][0];
		return p;
	}
}Lct[11];

int main(){
	
	Read( N );Read( M );Read( C );Read( K );
	for( int i=1;i<=N;i++ )Read( Val[i] );
	for( int i=1;i<=M;i++ ){
		Read( u );Read( v );Read( w );w++;
		Col[u][w]++;Col[v][w]++;
		Lct[w].Link( u,v );
		Mp[u][v] = Mp[v][u] = w;
	}
	while( K-- ){
		Read( Opt );Read( u );Read( v );
		switch( Opt ){
			case 0:
				Val[u] = v;
				for( int i=1;i<=C;i++ )Lct[i].Splay( u );
				break;
			case 1:
				Read( w );w++;
				if( !Mp[u][v] )puts("No such edge.");
				else if( Mp[u][v]==w )puts("Success.");
				else if( Col[u][w]==2||Col[v][w]==2 )puts("Error 1.");
				else if( Lct[w].Find( u )==Lct[w].Find( v ) )puts("Error 2.");
				else{
					puts("Success.");
					int c = Mp[u][v];Mp[u][v] = w;
					Col[u][w]++;Col[v][w]++;Col[u][c]--;Col[v][c]--;
					Lct[c].Cut( u,v );
					Lct[w].Link( u,v );
				}
				break;
			case 2:
				w = u+1;u = v;Read( v );
				if( Lct[w].Find(u)!=Lct[w].Find(v) )puts("-1");
				else{
					Lct[w].MRot( u );Lct[w].Access( v );Lct[w].Splay( v );
					printf("%d\n",Lct[w].Max[v]);
				}
				break;
		}
	}
	return 0;
}
