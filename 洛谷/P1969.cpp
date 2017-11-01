#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

const int MAXN = 1e5 +1;
#define Pair pair<int,int>

int n;
int H[MAXN];

struct SegmentTree{
	#define Lson Nd<<1,l,Mid
	#define Rson Nd<<1|1,Mid+1,r
	Pair Min[MAXN<<2];
	void Build( int Nd,int l,int r ){
		if( l==r ){
			Min[Nd] = make_pair( H[l],l );
			return;
		}
		int Mid = l+r>>1;
		Build( Lson );Build( Rson );
		Min[Nd] = min( Min[Nd<<1],Min[Nd<<1|1] );
	}
	Pair Query( int Nd,int l,int r,int L,int R ){
		if( l> R||r< L )return make_pair( 0x7fffffff,0 );
		if( l>=L&&r<=R )return Min[Nd];
		int Mid = l+r >>1;
		return min( Query( Lson,L,R ),Query( Rson,L,R ) );
	}
	void Build_Tree(){Build( 1,1,n );}
	Pair Find( int l,int r ){return Query( 1,1,n,l,r );}
}ST;

int Div( int l,int r,int h ){
	if( l==r )return H[l]-h;
	if( l==r+1 )return 0;
	int Mid = ST.Find( l,r ).second;
	int p = H[Mid] - h;
	return p + Div( l,Mid-1,H[Mid] ) + Div( Mid+1,r,H[Mid] );
}

int main(){
	
	Read( n );
	for( int i=1;i<=n;i++ )Read( H[i] );
	ST.Build_Tree();
	printf("%d\n",Div( 1,n,0 ));
	return 0;
}
