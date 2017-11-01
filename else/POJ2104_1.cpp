#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN = 1e5*20;
int T,N,M,L,R,K;
int A[MAXN];

struct DEAL{
	int Val,Num;
	bool operator < (DEAL T)const{return Val<T.Val;}
}Deal[MAXN];

int TC[MAXN],Cs;
int Lc[MAXN],Rc[MAXN];
int Sum[MAXN];

void Build( int Pt,int &Nt,int Add,int l,int r ){
	Nt = ++Cs;
	Sum[Nt] = Sum[Pt]+1;
	if( l==r )return;
	Lc[Nt] = Lc[Pt] ; Rc[Nt] = Rc[Pt];
	int Mid = ( l+r )>>1;
	if( Add<=Mid ) Build( Lc[Pt],Lc[Nt],Add,l,Mid );
	else Build( Rc[Pt],Rc[Nt],Add,Mid+1,r );
}

int Query( int Pt,int Nt,int k,int l,int r ){
	if( l==r ) return l;
	int Mid = ( l+r )>>1;
	if( Sum[Lc[Nt]]-Sum[Lc[Pt]]>=k ) return Query( Lc[Pt],Lc[Nt],k,l,Mid );
	else Query( Rc[Pt],Rc[Nt],k-(Sum[Lc[Nt]]-Sum[Lc[Pt]]),Mid+1,r );
}

void Init(){
	memset(TC,0,sizeof TC);memset(Lc,0,sizeof Lc);memset(Rc,0,sizeof Rc);memset(Sum,0,sizeof Sum);Cs=0;
}

int main(){
	
	scanf("%d",&T);
	while( T-- ){
		Init();
		scanf("%d%d",&N,&M);
	
		for(int i=1;i<=N;i++)scanf("%d",&Deal[i].Val),Deal[i].Num=i;
		sort(1+Deal,1+N+Deal);
		for(int i=1;i<=N;i++)A[Deal[i].Num]=i;
	
		for(int i=1;i<=N;i++)Build( TC[i-1],TC[i],A[i],1,N );
		while( M-- ){
			scanf("%d%d%d",&L,&R,&K);
			printf("%d\n",Deal[Query( TC[L-1],TC[R],K,1,N )].Val);
		}
	}
	return 0;
}
