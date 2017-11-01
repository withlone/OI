#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;

const int MAXN = 1e5 +1;
typedef long long LL;
#define Lson Nd<<1,l,Mid
#define Rson Nd<<1|1,Mid+1,r

int n;LL Ans;
LL A[MAXN<<1],Sum[MAXN<<1],Min[MAXN<<1],p[MAXN<<1],d[MAXN<<4];

void Build( int Nd,int l,int r ){
	if( l==r ){
		d[Nd] = Sum[l];
		return;
	}
	int Mid = l+r >>1;
	Build( Lson );Build( Rson );
	d[Nd] = min( d[Nd<<1],d[Nd<<1|1] );
}

LL Query( int Nd,int l,int r,int L,int R ){
	if( l>R||r<L )return LONG_LONG_MAX;
	if( l>=L&&r<=R )return d[Nd];
	int Mid = l+r >>1;
	return min( Query( Lson,L,R ),Query( Rson,L,R ) );
}

int main(){
	
	freopen("bomb.in","r",stdin);
	freopen("bomb.out","w",stdout);
	scanf("%d",&n);
	for( int i=1;i<=n;i++ )scanf("%lld",&A[i]),A[i+n]=A[i];
	for( int i=1;i<=(n<<1);i++ )Sum[i] = Sum[i-1] + A[i];
	Build( 1,1,n<<1 );
	for( int i=1;i<=(n<<1);i++ )
		Ans = max( Ans,Sum[i]-Query( 1,1,n<<1,max( 1,i-n ),i ) );
	printf("%lld\n",Ans);
	return 0;
}
