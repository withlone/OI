#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

static const int MAXN = 101;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
#define Rep( i , _End , _Begin ) for( int i=_End;i>=_Begin;i-- )

struct BIGNUM{
	int s[MAXN],len;
	BIGNUM(){ memset( s , 0 , sizeof s );len = 1; }
	BIGNUM operator = ( char *A ){
		len = strlen( A );
		For( i , 1 , len )s[i] = A[len-i] - '0';
		return *this;
	}
	BIGNUM operator = ( int A ){
		char B[MAXN];
		sprintf( B,"%d",A );
		*this = B;
		return *this;
	}
	BIGNUM ( char *A ){ *this = A; }
	BIGNUM ( int A ){ *this = A; }
	BIGNUM operator + ( BIGNUM A ){
		BIGNUM C;
		C.len = max( len,A.len )+1;
		For( i , 1 , C.len ){
			C.s[i] += s[i] + A.s[i];
			C.s[i+1] = C.s[i]/10;
			C.s[i] %= 10;
		}
		while( C.len>1&&!C.s[C.len] )C.len--;
		return C;
	}
	BIGNUM operator * ( BIGNUM A ){
		BIGNUM C;
		C.len = len+A.len+1;
		For( i , 1 , len )
			For( j , 1 , A.len ){
				C.s[i+j-1] += s[i]*A.s[j];
				C.s[i+j] += C.s[i+j-1]/10;
				C.s[i+j-1] %= 10;
			}
		while( C.len>1&&!C.s[C.len] )C.len--;
		return C;
	}
	void print(){
		Rep( i , len , 1 )printf("%d",s[i]);puts("");
	}
}f[MAXN][2],Ans;

int n;

int main(){
	
	scanf("%d",&n);
	f[0][1] = f[1][0] = f[1][1] = 1;
	For( i , 2 , n ){
		f[i][0] = f[i-1][0] + f[i-1][1];
		f[i][1] = f[i-1][0] + f[i-1][1]*2;
	}
	For( i , 1 , n )Ans = Ans + f[n-i][1]*i*i;
	Ans.print();
	return 0;
}
