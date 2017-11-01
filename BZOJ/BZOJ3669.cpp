#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

const int MAXN = 5e4 +1e5 +1;
const int MAXM = 2e5 +1;

int n,m,Ans=0x7fffffff;
struct Edge{
	int x,y,z,A,B;
	bool operator < ( Edge T )const{ return A<T.A; }
}E[MAXM];

int Father[MAXM];
int Find( int p ){ return p==Father[p]?p:Father[p]=Find(Father[p]); }

int Tp,St[MAXN];
int Fa[MAXN],Ch[MAXN][2],Max[MAXN],At[MAXN],Key[MAXN];bool Flag[MAXN];
int GS( int p ){ return p==Ch[Fa[p]][1]; }
bool Is_Rot( int p ){ return p!=Ch[Fa[p]][0]&&p!=Ch[Fa[p]][1]; }
void UP( int p ){
	int l = Ch[p][0],r = Ch[p][1];
	Max[p] = Key[p];At[p] = p;
	if( Max[l]>Max[p] ){
		Max[p] = Max[l];
		At[p] = At[l];
	}
	if( Max[r]>Max[p] ){
		Max[p] = Max[r];
		At[p] = At[r];
	}
}
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
	UP( x );
	Splay( x );
}
void Cut( int x,int y ){
	MRot( x );
	Access( y );Splay( y );
	Fa[x] = Ch[y][0] = 0;UP( y );
}

int main(){
	
	Read( n );Read( m );
	for( int i=1;i<=n;i++ )Father[i] = i;
	for( int i=1;i<=m;i++ )Read( E[i].x ),Read( E[i].y ),Read( E[i].A ),Read( E[i].B ),Key[E[i].z = i+n]=E[i].B;
	sort( 1+E,1+m+E );
	for( int i=1;i<=m;i++ ){
		int x = E[i].x,y = E[i].y,z = E[i].z;
		if( Find( x )!=Find( y ) ){
			Link( x,z );Link( y,z );
			Father[Find( x )] = Find( y );
		}
		else{
			MRot( x );
			Access( y );Splay( y );
			if( Max[y]>E[i].B ){
				int T = At[y];
				Cut( x,T );Cut( y,T );
				Link( x,z );Link( y,z );
			}
		}
		if( Find( 1 )==Find( n ) ){
			MRot( 1 );
			Access( n );Splay( n );
			Ans = min( Ans,E[i].A + Max[n] );
		}
	}
	printf("%d\n",Ans==0x7fffffff?-1:Ans);
	return 0;
}
