#include<cstdio>

template <typename Type> inline void Read( Type& in ){
	in = 0;char ch=getchar();
	for(;ch> '9'||ch< '0';ch=getchar());
	for(;ch>='0'&&ch<='9';ch=getchar())in=in*10+ch-'0';
}

const int MAXN = 5e5 +1;

int n,m,Ct,u,v,In;
int Root[MAXN],Lc[MAXN*20],Rc[MAXN*20],Sum[MAXN*20];
void Build( int& Nd,int Pt,int l,int r,int p ){
	Nd = ++Ct;
	Sum[Nd] = Sum[Pt]+1;
	if( l==r )return;
	Lc[Nd] = Lc[Pt];Rc[Nd] = Rc[Pt];
	int Mid = l+r >>1;
	if( p<=Mid )Build( Lc[Nd],Lc[Pt],l,Mid,p );
	else Build( Rc[Nd],Rc[Pt],Mid+1,r,p );
}
int Query( int Nd,int Pt,int l,int r,int k ){
	if( l==r )return l;
	int Mid = l+r >>1;
	if( Sum[Lc[Nd]]-Sum[Lc[Pt]]>k ) return Query( Lc[Nd],Lc[Pt],l,Mid,k );
	else if( Sum[Rc[Nd]]-Sum[Rc[Pt]]>k ) return Query( Rc[Nd],Rc[Pt],Mid+1,r,k );
	return 0;
}

int main(){
	
	Read( n );Read( m );
	for( int i=1;i<=n;i++ )Read( In ),Build( Root[i],Root[i-1],1,n,In );
	while( m-- ){
		Read( u );Read( v );
		printf("%d\n",Query( Root[v],Root[u-1],1,n,v-u+1>>1 ));
	}
	return 0;
}
