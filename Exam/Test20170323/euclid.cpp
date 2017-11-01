#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long LL;
const LL MAXN = 12000 +1;
const int Ten = 1e8;

struct BIGNUM{
	int len,s[MAXN/7];
	BIGNUM (){len = 1;memset( s,0,sizeof s );}
	BIGNUM operator =( char *A ){
		len = 0;int n = strlen( A );
		char T[MAXN];
		for( int i=0;i<n;i++ )T[i] = A[n-i-1];for( int i=0;i<n;i++ )A[i] = T[i];
		for( int i=0;i<n;i+=8 ){
			len++;
			for( int j=min( i+7,n-1 );j>=i;j-- )
				s[len] = s[len]*10 + A[j]-'0';
		}
		return *this;
	}
	BIGNUM operator =( LL A ){
		memset( s,0,sizeof s );len = 1;
		char Num[MAXN];sprintf( Num,"%lld",A );
		*this = Num;
		return *this;
	}
	BIGNUM ( char  *A ){*this = A;}
	BIGNUM ( LL     A ){*this = A;}
	BIGNUM operator +( BIGNUM A ){
		BIGNUM C;
		C.len = max( A.len,len ) +1;
		for( int i=1;i<=C.len;i++ ){
			C.s[i] += A.s[i] + s[i];
			C.s[i+1] += C.s[i]/Ten;
			C.s[i] %= Ten;
		}
		while( !C.s[C.len]&&C.len>1 )C.len--;
		return C;
	}
	bool operator <=( BIGNUM A ){
		if( A.len!=len )return len<A.len;
		for( int i=len;i>=1;i-- )if( A.s[i]!=s[i] )return s[i]<A.s[i];
		return true;
	}
	void print(){
		printf("%d",s[len]);
		for( int i=len-1;i>=1;i-- )printf("%08d",s[i]);printf("\n");
	}
}F0,F1,F2,N;
char Num[MAXN];

int main(){
	freopen("euclid.in","r",stdin);
	freopen("euclid.out","w",stdout);
	scanf("%s",Num);N = Num;
	F0 = 0LL;F1 = 1LL;
	while( (F2=F1+F0)<=N ){
		F0 = F1;
		F1 = F2;
	}
	F0.print();F1.print();
	return 0;
}
