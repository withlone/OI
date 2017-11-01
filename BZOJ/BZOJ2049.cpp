#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 1e4 +1;
const int MAXM = 2e5 +1;

int n,m,u,v;
char Opt[10];

int Fa[MAXN],Ch[MAXN][2];bool Flag[MAXN];

int GS( int p ){ return p==Ch[Fa[p]][1]; }
bool Is_Rot( int p ){ return p!=Ch[Fa[p]][0]&&p!=Ch[Fa[p]][1]; }
void Rotate( int p ){
	int fa = Fa[p],Gfa = Fa[fa],t=GS(p);
	if( !Is_Rot( fa ) )Ch[Gfa][Ch[Gfa][1]==fa] = p;
	Fa[p] = Gfa;
	Ch[fa][t] = Ch[p][t^1];
	if( Ch[p][t^1] )Fa[Ch[p][t^1]] = fa;
	Fa[fa] = p;
	Ch[p][t^1] = fa;
}
void Flip( int p ){
	if( !Flag[p] )return;
	if( Ch[p][0] )Flag[Ch[p][0]] ^= 1;
	if( Ch[p][1] )Flag[Ch[p][1]] ^= 1;
	swap( Ch[p][0],Ch[p][1] );
	Flag[p] = 0;
}
void Push( int p ){
	if( !Is_Rot( p ) )Push( Fa[p] );
	Flip( p );
}
void Splay( int p ){
	Push( p );
	for( int fa;!Is_Rot(p);Rotate(p) )
		if( !Is_Rot(fa=Fa[p]) )
			Rotate( GS(fa)==GS(p)?fa:p );
}
void Access( int p ){
	int t = 0;
	while( p ){
		Splay( p );
		Ch[p][1] = t;
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
	Splay( x );
}
void Cut( int x,int y ){
	MRot( x );
	Access( y );
	Splay( y );
	Fa[x] = Ch[y][0] = 0;
}
int Find( int p ){
	Access( p );
	Splay( p );
	while( Ch[p][0] )p = Ch[p][0];
	return p;
}

int main(){
	
	scanf("%d%d",&n,&m);
	while( m-- ){
		scanf("%s%d%d",Opt,&u,&v);
		if( Opt[0]=='Q' )puts( Find(u)==Find(v)?"Yes":"No" );
		if( Opt[0]=='C' )Link( u,v );
		if( Opt[0]=='D' )Cut( u,v );
	}
	return 0;
}
