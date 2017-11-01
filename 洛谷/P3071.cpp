#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 5e5 +1;
static const int MAXM = MAXN<<2;
#define Lc p<<1
#define Rc p<<1|1
#define Lson Lc,l,Mid
#define Rson Rc,Mid+1,r

int n,m,x,y,Ans;
char Opt;
int Sum[MAXM],Lsum[MAXM],Rsum[MAXM],Lazy[MAXM];

void Build( int p,int l,int r ){
	Sum[p] = Lsum[p] = Rsum[p] = r-l+1;
	Lazy[p] = -1;
	if( l==r )return;
	int Mid = l+r >>1;
	Build( Lson );Build( Rson );
}
void PD( int p,int L,int R ){
	if( Lazy[p]==-1 )return;
	Lazy[Lc] = Lazy[Rc] = Lazy[p];
	Sum[Lc] = Lsum[Lc] = Rsum[Lc] = Lazy[p]?0:L;
	Sum[Rc] = Lsum[Rc] = Rsum[Rc] = Lazy[p]?0:R;
	Lazy[p] = -1;
}
void UP( int p,int L,int R ){
	Lsum[p] = Lsum[Lc];Rsum[p] = Rsum[Rc];
	if( Lsum[p]==L )Lsum[p] += Lsum[Rc];
	if( Rsum[p]==R )Rsum[p] += Rsum[Lc];
	Sum[p] = max( max( Sum[Lc],Sum[Rc] ),Rsum[Lc]+Lsum[Rc] );
}
void MF( int p,int l,int r,int L,int R,int k ){
	if( l> R||r< L )return;
	if( l>=L&&r<=R ){
		Lazy[p] = k;
		Sum[p] = Lsum[p] = Rsum[p] = k?0:r-l+1;
		return;
	}
	int Mid = l+r >>1;
	PD( p,Mid-l+1,r-Mid );
	MF( Lson,L,R,k );MF( Rson,L,R,k );
	UP( p,Mid-l+1,r-Mid );
}
int Query( int p,int l,int r,int k ){
	if( l==r )return l;
	int Mid = l+r >>1;
	PD( p,Mid-l+1,r-Mid );
	if( Sum[Lc]>=k )return Query( Lson,k );
	if( Rsum[Lc]+Lsum[Rc]>=k )return Mid-Rsum[Lc]+1;
	return Query( Rson,k );
}

int main(){
	
	Read( n );Read( m );
	Build( 1,1,n );
	while( m-- ){
		scanf("%s",&Opt);Read( x );
		if( Opt=='A' ){
			if( Sum[1]<x )Ans++;
			else{
				y = Query( 1,1,n,x );
				MF( 1,1,n,y,y+x-1,1 );
			}
		}
		else{
			Read( y );
			MF( 1,1,n,x,y,0 );
		}
	}
	printf("%d\n",Ans);
	return 0;
}
