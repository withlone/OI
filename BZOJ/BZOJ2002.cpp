#include<cstdio>

template< typename Type >inline void Read( Type& In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}
template< typename Type >inline void swap( Type& x,Type& y ){ x^=y^=x^=y; }
template< typename Type >inline Type min( Type x,Type y ){ return x<y?x:y; }

const int MAXN = 2e5 +2;

int n,m,Opt,u,v;
int k[MAXN];bool Flag[MAXN];
int Fa[MAXN],Ch[MAXN][2],Size[MAXN];

int GS( int p ){ return p==Ch[Fa[p]][1]; }
bool Is_Rot( int p ){ return p!=Ch[Fa[p]][0]&&p!=Ch[Fa[p]][1]; }
void UP( int p ){ Size[p] = Size[Ch[p][0]] + Size[Ch[p][1]] + 1; }
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
	if( Ch[p][0] )Flag[Ch[p][0]] ^= 1;
	if( Ch[p][1] )Flag[Ch[p][1]] ^= 1;
	swap( Ch[p][0],Ch[p][1] );
	Flag[p] = 0;
}
void Push( int p ){
	if( !Is_Rot(p) )Push( Fa[p] );
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
	Access( y );Splay( y );
	Fa[x] = Ch[y][0] = 0;
}

int main(){
	
	Read( n );
	for( int i=1;i<=n;i++ ){
		Read( k[i] );
		if( k[i]+i>n+1 )k[i] = n+1-i;
		Link( i,i+k[i] );
	}
	Read( m );
	while( m-- ){
		Read( Opt );Read( u );u++;
		if( Opt==1 ){
			MRot( n+1 );
			Access( u );Splay( u );
			printf("%d\n",Size[Ch[u][0]]);
		}
		else{
			Read( v );if( u+v>n+1 )v = n+1-u;
			Cut( u,u+k[u] );Link( u,u+(k[u]=v) );
		}
	}
	return 0;
}
