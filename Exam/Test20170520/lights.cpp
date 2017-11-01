#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
#define Rep( i , _Begin , _End ) for( int i=_Begin;i>=_End;i-- )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

typedef long long LL;
static const int MAXN = 101;

struct BIGNUM{
	static const int Mod = 1e7;
	static const int MAXL = 1e3;
	int s[MAXL] , len;
	void Clear(){ memset( s , 0 , sizeof s ) ; len = 1 ; }
	BIGNUM (){ Clear(); }
	BIGNUM ( int x ){ Clear(); *this = x; }
	BIGNUM operator = ( int x ){
		char A[MAXL];
		sprintf( A , "%d" , x );
		len = 0;
		for( int i=strlen( A )-1;i>=0;i-=7 ){
			++len;
			For( j , max( 0 , i-6 ) , i )
				s[len] = s[len]*10 + A[j]-'0';
		}
		return *this;
	}
	
	BIGNUM operator + ( BIGNUM x ){
		BIGNUM y;
		y.len = max( x.len , len ) +1;
		For( i , 1 , y.len ){
			y.s[i] += s[i] + x.s[i];
			if( y.s[i] < 0 )y.s[i] += Mod , y.s[i+1]--;
			y.s[i+1] += y.s[i] / Mod;
			y.s[i] %= Mod;
		}
		while( !y.s[y.len] && y.len > 1 )y.len--;
		return y;
	}
	
	BIGNUM operator - ( BIGNUM x ){
		BIGNUM y;
		y.len = max( x.len , len ) +1;
		For( i , 1 , y.len ){
			y.s[i] += s[i] - x.s[i];
			if( y.s[i] < 0 )y.s[i] += Mod , y.s[i+1]-- ;
		}
		while( !y.s[y.len] && y.len > 1 )y.len--;
		return y;
	}
	
	BIGNUM operator * ( BIGNUM x ){
		BIGNUM y;
		y.len = x.len + len + 1;
		For( i , 1 , len )
			For( j , 1 , x.len ){
				y.s[i+j-1] += s[i]*x.s[j];
				y.s[i+j] += y.s[i+j-1] / Mod;
				y.s[i+j-1] %= Mod;
			}
		while( !y.s[y.len] && y.len > 1 )y.len--;
		return y;
	}
	
	void print(){
		printf("%d",s[len]);
		Rep( i , len-1 , 1 )printf("%07d",s[i]);
		puts("");
	}
}f[MAXN][MAXN];

int n,m;

void Dp(){
	For( i , 1 , m )f[1][i] = i , f[2][i] = i*(i-1);
	For( i , 3 , n )
		For( j , 2 , m ){
			f[i][j] = f[i-1][j] * (j-1);
			if( i&1 )f[i][j] = f[i][j] - j*(j-1);
			else f[i][j] = f[i][j] + j*(j-1);
		}
	f[n][m].print();
}

#define Judge

int main(){
	
	#ifdef Judge
		freopen("lights.in","r",stdin);
		freopen("lights.out","w",stdout);
	#endif
	Read( n );Read( m );
	
	Dp();
	
	return 0;
}
