#include<cstdio>
#include<algorithm>
using namespace std;

static const int MAXN = 5e4 +1;
static const int MAXM = 2e5 +1;
static const int MAX  = 1e6 +1;

int N,M,Cs,L,R;
int A[MAXN],H[MAX],Next[MAX];
int TC[MAX],Lc[MAX],Rc[MAX],Sum[MAX];

void Build( int Pt,int &Nt,int Add,int l,int r ){
	Sum[Nt=++Cs] = Sum[Pt] + 1;
	if(l==r) return;
	Lc[Nt] = Lc[Pt] ; Rc[Nt] = Rc[Pt];
	int Mid = ( l+r )>>1;
	if( Add<=Mid ) Build( Lc[Pt],Lc[Nt],Add,l,Mid );
	else Build( Rc[Pt],Rc[Nt],Add,Mid+1,r );
}

int Query( int Pt,int Nt,int l,int r,int k ){
	if( l==r ) return Sum[Nt]-Sum[Pt];
	int Mid = ( l+r )>>1;
	if( Mid>k ) return Query( Lc[Pt],Lc[Nt],l,Mid,k )+Sum[Rc[Nt]]-Sum[Rc[Pt]];
	else return Query( Rc[Pt],Rc[Nt],Mid+1,r,k );
}

int main(){
	
	scanf("%d",&N);
	for(int i=1;i<=N;i++)scanf("%d",&A[i]);
	
	for(int i=1;i<=N;i++){
		if(H[A[i]]) Next[H[A[i]]] = i;
		H[A[i]] = i;
	}
	for(int i=1;i<=N;i++)if(!Next[i])Next[i]=N+1;
	for(int i=1;i<=N;i++)Build( TC[i-1],TC[i],Next[i],1,N+1 );
	
	scanf("%d",&M);
	while( M-- ){
		scanf("%d%d",&L,&R);
		printf("%d\n",Query( TC[L-1],TC[R],1,N+1,R ));
	}
	
	return 0;
}
