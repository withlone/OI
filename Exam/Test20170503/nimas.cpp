#include<cstdio>

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

typedef long long LL;
static const LL Inf = 1e18;
static const int MAXN = 1e6 +1;

int n,L,R,H,T;
int Que[MAXN],s[MAXN];
LL f[MAXN];

#define Judge

int main(){
	
	#ifdef Judge
		freopen("nimas.in","r",stdin);
		freopen("nimas.out","w",stdout);
	#endif
	
	Read( n );Read( L );Read( R );
	For( i , 1 , n ){
		Read( s[i] );
		f[i] = Inf;
	}
	f[1] = s[1];
	Que[ H = T = 1 ] = 1;
	For( i , L+1 , n ){
		while( H<=T && Que[H]<i-R )H++;
		f[i] = f[Que[H]] + s[i];
		while( H<=T && f[Que[T]] > f[i-L+1] )T--;
		Que[++T] = i-L+1;
	}
	printf("%lld\n",f[n]==Inf?-1:f[n]);
	return 0;
}
