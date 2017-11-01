#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

template <typename Type> inline void Read( Type& in ){
	in=0;char ch=getchar();
	for(;ch> '9'||ch< '0';ch=getchar());
	for(;ch>='0'&&ch<='9';ch=getchar())in=in*10+ch-'0';
}

const int MAXN = 1e5 +1;
const int MAXP = 1e7;
typedef long long LL;

int n,m,u,v,w,Ct,Mn=MAXP,Mx,X,A,B,C;
LL Ans = 1;
struct Node{
	int Lc,Rc,Ct;LL Val;
}T[MAXN*80];

vector<int> L[MAXN],R[MAXN];
int Rot[MAXN],Flag[MAXN*80],F;
void New( int &Nd,int Pt ){
	T[Nd=++Ct] = T[Pt];
	Flag[Nd] = F;
}
void Build( int &Nd,int Pt,int l,int r,int p,int Num ){
	if( Flag[Nd]!=F )New( Nd,Pt );//保证Rot只开一次
	T[Nd].Ct += Num;T[Nd].Val += Num*p;
	if( l==r )return;
	int Mid = l+r >>1;
	if( p<=Mid )Build( T[Nd].Lc,T[Pt].Lc,l,Mid,p,Num );
	else Build( T[Nd].Rc,T[Pt].Rc,Mid+1,r,p,Num );
}
LL Query( int Nd,int l,int r,int k ){
	if( l==r )return 1LL*l*k;//保证将优先级大小相同的算入答案
	int Mid = l+r >>1;
	if( T[T[Nd].Lc].Ct>=k ) return Query( T[Nd].Lc,l,Mid,k );
	return Query( T[Nd].Rc,Mid+1,r,k-T[T[Nd].Lc].Ct ) + T[T[Nd].Lc].Val;
}

int main(){
	
	Read( n );Read( m );
	for( int i=1;i<=n;i++ ){
		Read( u );Read( v );Read( w );
		L[u].push_back( w );
		R[v].push_back( w );
		Mn = min( Mn,u );Mx = max( Mx,v );
	}
	for( int i=Mn;i<=Mx;i++ ){
		New( Rot[i],Rot[i-1] );F++;
		for( int j=0;j<L[i].size();j++ )Build( Rot[i],Rot[i-1],1,MAXP,L[i][j],1 );
		for( int j=0;j<R[i-1].size();j++ )Build( Rot[i],Rot[i-1],1,MAXP,R[i-1][j],-1 );
	}
	while( m-- ){
		Read( X );Read( A );Read( B );Read( C );
		int K = 1 + ( A*Ans + B ) %C;
		if( K>=T[Rot[X]].Ct ) Ans=T[Rot[X]].Val;
		else Ans = Query( Rot[X],1,MAXP,K );
		printf("%lld\n",Ans);
	}
	return 0;
}
