#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch=='-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}

static const int MAXN = 1e6 +1;
static const int M    = 1048576;
typedef long long LL;

int Opt,W,C,Ct;LL T_c,T_w;
int d[3][MAXN<<2];

void Mf( int x,int k ){
	x += M;if( d[2][x] )return;Ct++;
	d[0][x] = d[1][x] = x;d[2][x] = k;
	for( x>>=1;x;x>>=1 )
		d[0][x] = min( d[0][x<<1],d[0][x<<1|1] ),
		d[1][x] = max( d[1][x<<1],d[1][x<<1|1] );
}
int Qm(){
	int Res = 0;
	for( int s=M,t=M<<1;s^t^1;s>>=1,t>>=1 ){
		if( ~s&1 )Res = max( Res,d[1][s^1] );
		if(  t&1 )Res = max( Res,d[1][t^1] );
	}
	return Res;
}
int Qn(){
	int Res = 0x7fffffff;
	for( int s=M,t=M<<1;s^t^1;s>>=1,t>>=1 ){
		if( ~s&1 )Res = min( Res,d[0][s^1] );
		if(  t&1 )Res = min( Res,d[0][t^1] );
	}
	return Res;
}
void Del( int x ){
	d[0][x] = 0x7fffffff;
	d[1][x] = d[2][x] = 0;
	for( x>>=1;x;x>>=1 )
		d[0][x] = min( d[0][x<<1],d[0][x<<1|1] ),
		d[1][x] = max( d[1][x<<1],d[1][x<<1|1] );
}

int main(){
	
	memset( d[0],0x3f,sizeof d[0] );
	while( Opt!=-1 ){
		Read( Opt );
		switch( Opt ){
			case 1:Read( W );Read( C );Mf( C,W );break;
			case 2:if( Ct )Del( Qm() ),Ct--;break;
			case 3:if( Ct )Del( Qn() ),Ct--;break;
		}
	}
	for( int x=M+1;x<=M<<1;x++ )
		if( d[2][x] )T_w += d[2][x],T_c += x-M;
	
	printf("%lld %lld\n",T_w,T_c);
	return 0;
}
