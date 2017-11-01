#include<cstdio>
#include<algorithm>
using namespace std;

static const int MAXN = 1e5 +1;
#define Lc Nd<<1
#define Rc Nd<<1|1
#define Lson Lc,l,Mid
#define Rson Rc,Mid+1,r

int n,m,T,x,y,C;char Opt[4];
int Col[MAXN<<2],Lazy[MAXN<<2];

void PD( int Nd ){
	if( !Lazy[Nd] )return;
	Lazy[Lc] = Lazy[Rc] = Lazy[Nd];
	Col[Lc] = Col[Rc] = 1<<Lazy[Nd]-1;
	Lazy[Nd] = 0;
}
void MF( int Nd,int l,int r,int L,int R,int c ){
	if( l> R||r< L )return;
	if( l>=L&&r<=R ){
		Lazy[Nd] = c;
		Col[Nd] = 1<<c-1;
		return;
	}
	PD( Nd );
	int Mid = l+r >>1;
	MF( Lson,L,R,c );MF( Rson,L,R,c );
	Col[Nd] = Col[Nd<<1] | Col[Nd<<1|1];
}
int Query( int Nd,int l,int r,int L,int R ){
	if( l> R||r< L )return 0;
	if( l>=L&&r<=R )return Col[Nd];
	PD( Nd );
	int Mid = l+r >>1;
	return Query( Lson,L,R ) | Query( Rson,L,R );
}

int main(){
	
	scanf("%d%d%d",&n,&T,&m);
	MF( 1,1,n,1,n,1 );
	while( m-- ){
		scanf("%s%d%d",Opt,&x,&y);
		if( x>y )swap( x,y );
		if( Opt[0]=='C' ){
			scanf("%d",&C);
			MF( 1,1,n,x,y,C );
		}
		else{
			int t = Query( 1,1,n,x,y ),Ans=0;
			for( ;t;t &= t-1 )Ans++;
			printf("%d\n",Ans);
		}
	}
	return 0;
}
