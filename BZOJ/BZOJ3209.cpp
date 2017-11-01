#include<cstdio>

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )
#define Rep( i , _Begin , _End ) for( int i=(_Begin);i>=(_End);i-- )

typedef long long LL;
static const int MAXN = 60;
static const int Mod = 10000007;

LL n;
int Len , A[MAXN];
LL C[MAXN+1][MAXN+1];

void Init();
LL Solve( int );
LL pow( LL , LL );

int main(){
	
	Init();
	
	LL Ans = 1;
	For( i , 2 , Len )Ans = Ans * pow( i , Solve( i ) ) % Mod;
	printf("%lld\n",Ans);
	
	return 0;
}

void Init(){
	scanf("%lld",&n);n++;
	For( i , 0 , MAXN ){
		C[i][0] = 1;
		For( j , 1 , i )
			C[i][j] = C[i-1][j-1] + C[i-1][j];
	}
	for( ;n;n>>=1 )A[++Len] = n&1;
}
LL Solve( int x ){
	LL Res = 0;
	Rep( i , Len , 1 ){
		if( A[i] ){
			Res += C[i-1][x];
			x--;
		}
		if( x < 0 )return Res;
	}
	return Res;
}
LL pow( LL x , LL y ){
	LL Res = 1;
	for( ;y;y >>= 1 , x = x * x % Mod )
		if( y & 1 )Res = Res * x % Mod;
	return Res;
}
