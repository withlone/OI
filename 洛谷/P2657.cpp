#include<cstdio>
#include<algorithm>
using namespace std;

static const int MAXN = 1e5 +1;
static const int MAXX = 2e4 +1;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
#define v first
#define x second
typedef pair< int,int > Pair;
typedef long long LL;

int n,Top;LL Ans,t;
Pair d[MAXN];

namespace BIT{
	LL Sum[MAXX],Tot[MAXX];
	int Lowbit( int k ){ return k&-k; }
	void Add( int x ){
		for( int i=x;i<=Top;i += Lowbit(i) )
			Sum[i] += x,Tot[i]++;
	}
	LL Get_T( int x ){
		LL Res = 0;
		for( ;x;x -= Lowbit(x) )Res += Tot[x];
		return Res;
	}
	LL Get_S( int x ){
		LL Res = 0;
		for( ;x;x -= Lowbit(x) )Res += Sum[x];
		return Res;
	}
}
using namespace BIT;

int main(){
	
	scanf("%d",&n);
	For( i , 1 , n )scanf("%d%d",&d[i].v,&d[i].x),Top = max( Top , d[i].x );
	sort( 1+d , 1+n+d );
	For( i , 1 , n ){
		Add( d[i].x );
		LL Num1 = Get_T( d[i].x-1 ),Sum1 = Get_S( d[i].x-1 );
		LL Num2 = i - 1 - Num1,Sum2 = t - Sum1;
		Ans += d[i].v * ( ( Num1 - Num2 )*d[i].x - Sum1 + Sum2 );
		t += d[i].x;
	}
	printf("%lld\n",Ans);
	return 0;
}
