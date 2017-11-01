#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 2e5 +1;
typedef long long LL;

int m,x,Tp,n,Mod,Ans;

LL A[MAXN];
pair< int,int > St[MAXN];

int main(){
	
	Read( m );Read( Mod );
	while( m-- ){
		char Opt = '0';
		while( Opt>'Z'||Opt<'A' )Opt = getchar();
		Read( x );
		if( Opt=='A' ){
			x = 1LL*( x+Ans )%Mod;
			A[++n] = x;
			while( Tp&&St[Tp].second<=x )Tp--;
			St[++Tp] = make_pair( n,x );
		}
		else{
			int p = upper_bound( 1+St,1+Tp+St,make_pair( n-x+1,0 ) )-St;
			printf("%d\n",Ans=St[p].second);
		}
	}
	return 0;
}
