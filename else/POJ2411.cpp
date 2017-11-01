#include<cstdio>
#include<cstring>

const int MAXN = 12;
typedef long long LL;

int n,m,Tmp;LL f[MAXN][1<<MAXN];
bool Able[1<<MAXN];

bool Ok( int A ){
	int B=0;
	for( ;A;A>>=1 ){
		if( A&1 ) B++;
		else{
			if( B&1 )return false;
			B = 0;
		}
	}
	return !(B&1);
}

void Init(){
	for( int i=0;i<(1<<MAXN);i++ )
		Able[i] = Ok(i);
}

int main(){
	
	Init();
	Start:
	scanf("%d%d",&n,&m);
	if( !(n+m) )goto End;
	Tmp = (1<<m)-1;
	memset( f,0,sizeof f );
	for( int i=0;i<=Tmp;i++ )f[1][i] = Able[i];
	for( int i=2;i<=n;i++ )
		for( int Ts=0;Ts<=Tmp;Ts++ )
			for( int Ls=0;Ls<=Tmp;Ls++ )
				if( Able[Ts&Ls]&&(Ts|Ls)==Tmp )
					f[i][Ts] += f[i-1][Ls];
	printf("%lld\n",f[n][Tmp]);
	goto Start;
	End:
	return 0;
}
