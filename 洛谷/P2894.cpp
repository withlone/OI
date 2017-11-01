#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 5e4 +1;
static const int MAXM = MAXN<<2;
#define Lc Nd<<1
#define Rc Nd<<1|1
#define Lson Lc,l,Mid
#define Rson Rc,Mid+1,r

int n,m,Opt,x,y;
int Sum[MAXM],Lsum[MAXM],Rsum[MAXM],Lazy[MAXM];

void UP( int Nd,int L,int R ){
	Lsum[Nd] = Lsum[Lc];Rsum[Nd] = Rsum[Rc];
	if( Lsum[Nd]==L )Lsum[Nd] += Lsum[Rc];
	if( Rsum[Nd]==R )Rsum[Nd] += Rsum[Lc];
	Sum[Nd] = max( max( Sum[Lc],Sum[Rc] ),Rsum[Lc]+Lsum[Rc] );
}
void Build( int Nd,int l,int r ){
	Sum[Nd] = Lsum[Nd] = Rsum[Nd] = r-l+1;
	Lazy[Nd] = -1;
	if( l==r )return;
	int Mid = l+r >>1;
	Build( Lson );Build( Rson );
}
void PD( int Nd,int L,int R ){
	if( Lazy[Nd]==-1 )return;
	Lazy[Lc] = Lazy[Rc] = Lazy[Nd];
	Sum[Lc] = Lsum[Lc] = Rsum[Lc] = Lazy[Nd]?0:L;
	Sum[Rc] = Lsum[Rc] = Rsum[Rc] = Lazy[Nd]?0:R;
	Lazy[Nd] = -1;
}
void MF( int Nd,int l,int r,int L,int R,int k ){
	if( l> R||r< L )return;
	if( l>=L&&r<=R ){
		Lazy[Nd] = k;
		Sum[Nd] = Lsum[Nd] = Rsum[Nd] = k?0:r-l+1;
		return;
	}
	int Mid = l+r >>1;
	PD( Nd,Mid-l+1,r-Mid );
	MF( Lson,L,R,k );MF( Rson,L,R,k );
	UP( Nd,Mid-l+1,r-Mid );
}
int Query( int Nd,int l,int r,int k ){
	if( l==r )return l;
	int Mid = l+r >>1;
	PD( Nd,Mid-l+1,r-Mid );
	if( Sum[Lc]>=k )return Query( Lson,k );
	if( Rsum[Lc]+Lsum[Rc]>=k )return Mid-Rsum[Lc]+1;
	return Query( Rson,k );
}

int main(){
	
	Read( n );Read( m );
	Build( 1,1,n );
	while( m-- ){
		Read( Opt );Read( x );
		if( Opt==1 ){
			if( Sum[1]<x )puts("0");
			else{
				printf("%d\n",y=Query( 1,1,n,x ));
				MF( 1,1,n,y,y+x-1,1 );
			}
		}
		else{
			Read( y );
			MF( 1,1,n,x,x+y-1,0 );
		}
	}
	return 0;
}
