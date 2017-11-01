#include<cstdio>

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}
template< typename Type >inline void swap( Type &x,Type &y ){ x^=y^=x^=y; }
template< typename Type >inline Type max ( Type x,Type y ){ return x>y?x:y; }

static const int MAXN = 3e5 +5;

int n,q,Opt,Tp,w;int u[MAXN],v[MAXN],St[MAXN];
int Fa[MAXN],Ch[MAXN][2],Max[MAXN],Lazy[MAXN],Key[MAXN];bool Flag[MAXN];

int GS( int p ){ return p==Ch[Fa[p]][1]; }
bool Is_Rot( int p ){ return p!=Ch[Fa[p]][0]&&p!=Ch[Fa[p]][1]; }
void UP( int p ){ Max[p] = max( Key[p],max( Max[Ch[p][0]],Max[Ch[p][1]] ) ); }
void Flip( int p ){
	int l = Ch[p][0],r = Ch[p][1];
	if( Flag[p] ){
		if( l )Flag[l] ^= 1;
		if( r )Flag[r] ^= 1;
		swap( Ch[p][0],Ch[p][1] );
		Flag[p] = 0;
	}
	if( Lazy[p] ){
		if( l ){ Lazy[l] += Lazy[p];Key[l] += Lazy[p];Max[l] += Lazy[p]; }
		if( r ){ Lazy[r] += Lazy[p];Key[r] += Lazy[p];Max[r] += Lazy[p]; }
		Lazy[p] = 0;
	}
}
void Rotate( int p ){
	int fa = Fa[p],Gfa = Fa[fa],t=GS(p);
	if( !Is_Rot( fa ) )Ch[Gfa][GS(fa)] = p;
	Fa[p] = Gfa;
	Ch[fa][t] = Ch[p][t^1];
	if( Ch[p][t^1] )Fa[Ch[p][t^1]] = fa;
	Fa[fa] = p;
	Ch[p][t^1] = fa;
	UP( fa );UP( p );
}
void Splay( int p ){
	St[Tp=1] = p;
	for( int i=p;!Is_Rot(i);i=Fa[i] )St[++Tp] = Fa[i];
	while( Tp )Flip( St[Tp--] );
	for( int fa;!Is_Rot(p);Rotate(p) )
		if( !Is_Rot(fa=Fa[p]) )
			Rotate( GS(fa)==GS(p)?fa:p );
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
	Splay( x );
}
void Cut( int x,int y ){
	MRot( x );
	Access( y );Splay( y );
	Ch[y][0] = Fa[Ch[y][0]] = 0;UP( y );
}
int Find( int p ){
	Access( p );
	Splay( p );
	while( Ch[p][0] )p = Ch[p][0];
	return p;
}

int main(){
	
	while( ~scanf("%d",&n) ){
		for( int i=0;i<=n;i++ )Fa[i] = Ch[i][0] = Ch[i][1] = Flag[i] = Lazy[i] = 0;
		for( int i=1;i< n;i++ )Read( u[i] ),Read( v[i] );
		for( int i=1;i<=n;i++ )Read( Key[i] ),Max[i] = Key[i];
		for( int i=1;i< n;i++ )Link( u[i],v[i] );
		Read( q );
		while( q-- ){
			Read( Opt );Read( u[0] );Read( v[0] );
			switch( Opt ){
				case 1:
					if( Find(u[0])==Find(v[0]) )puts("-1");
					else Link( u[0],v[0] );
					break;
				case 2:
					if( u[0]==v[0]||Find(u[0])!=Find(v[0]) )puts("-1");
					else Cut( u[0],v[0] );
					break;
				case 3:
					w = u[0];u[0] = v[0];Read( v[0] );
					if( Find(u[0])!=Find(v[0]) )puts("-1");
					else{
						MRot( u[0] );Access( v[0] );Splay( v[0] );
						Key[v[0]] += w;Max[v[0]] += w;Lazy[v[0]] += w;
					}
					break;
				case 4:
					if( Find(u[0])!=Find(v[0]) )puts("-1");
					else{
						MRot( u[0] );Access( v[0] );Splay( v[0] );
						printf("%d\n",Max[v[0]]);
					}
					break;
			}
		}
		puts("");
	}
	return 0;
}
