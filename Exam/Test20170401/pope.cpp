#include<cstdio>
#include<cstring>

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}
template< typename Type >inline Type min( Type x,Type y ){ return x<y?x:y; }

const int MAXN = 16  +1;
const int MAXM = 120 +1<<1;
const int MAXC = 1e8 +1;
typedef long long LL;

int n,m,Ct,u,v,w;
int Nt[MAXM],H[MAXM],To[MAXM],Dt[MAXM];LL f[MAXN][1<<MAXN];

void Ins( int F,int T,int D ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
	Dt[Ct] = D;
}

int main(){
	
	freopen("pope.in","r",stdin);
	freopen("pope.out","w",stdout);
	for( int i=0;i<MAXN;i++ )for( int j=0;j<(1<<MAXN);j++ )f[i][j] = 0x7fffffff;
	Read( n );Read( m );
	while( m-- )Read( u ),Read( v ),Read( w ),Ins( u,v,w ),Ins( v,u,w );
	f[1][1] = 0;
	for( int St=0;St<(1<<n);St++ )
		for( int i=1;i<=n;i++ )
			if( St&(1<<i-1) )
				for( int j=H[i];j;j=Nt[j] )
					if( !( St&(1<<To[j]-1) ) )
						f[To[j]][St|(1<<To[j]-1)] = min( f[To[j]][St|(1<<To[j]-1)],f[i][St]+Dt[j] );
	LL Ans = 0x7fffffff;
	for( int i=1;i<=n;i++ )Ans = min( Ans,f[i][(1<<n)-1] );
	printf("%lld\n",Ans==0x7fffffff?-1:Ans);
	return 0;
}
