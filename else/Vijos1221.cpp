#include<cstdio>
#include<cstring>
#include<cstdlib>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 200 + 10;
static const int maxm = 1e4 + 10;

int n , m;
int A[maxm] , B[maxm] , ansA[maxm] , ansB[maxm];
int St[2][maxn] , tp[2];
bool V[maxn];

int Fa[maxm << 2];
int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int H[maxn] , Nt[maxm << 1] , To[maxm << 1] , Ct;
void Ins( int x , int y ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
}

void error(){ puts("No Answer");exit( 0 ); }

struct BIGNUM{
	int s[4000] , len;
	
	BIGNUM(){ memset( s , 0 , sizeof s );len = 1; }
	
	BIGNUM operator * ( BIGNUM x ){
		BIGNUM y;
		y.len = len + x.len;
		For( i , 1 , len )
			For( j , 1 , x.len ){
				y.s[i + j - 1] += s[i] * x.s[j];
				y.s[i + j] += y.s[i + j - 1] / 10;
				y.s[i + j - 1] %= 10;
			}
		while( y.len > 1 && !y.s[y.len] )--y.len;
		return y;
	}
	
	BIGNUM calc( int m ){
		BIGNUM x , res;
		x.s[1] = 2;
		res.s[1] = 1;
		for( ; m ; m >>= 1 , x = x * x )
			if( m & 1 )res = res * x;
		return res;
	}
	
	void display(){
		Lop( i , len , 1 )printf("%d",s[i]);
	}
	
}ans;

int main(){
	
	Read( n );Read( m );
	For( i , 1 , m << 1 )Fa[i] = i;
	For( i , 1 , m ){
		Read( A[i] ) , Read( ansA[i] ) , Read( B[i] ) , Read( ansB[i] ) , 
		Ins( A[i] , i ) , Ins( B[i] , i );
		V[ A[i] ] = V[ B[i] ] = true;
		if( A[i] == B[i] && ansA[i] != ansB[i] )error();
	}
	
	For( i , 1 , n ){
		tp[0] = tp[1] = 0;
		Rep( j , H[i] , Nt[j] ){
			int y = To[j];
			if( A[y] == i )St[ ansA[y] ][ ++tp[ ansA[y] ] ] = y;
			else St[ ansB[y] ][ ++tp[ ansB[y] ] ] = y;
		}
		For( k , 0 , 1 ){
			int x = St[k][1];
			For( j , 2 , tp[k] ){
				int y = St[k][j];
				if( Find( x ) == Find( y + m ) )error();
				Fa[ Find( x ) ] = Find( y );
				Fa[ Find( x + m ) ] = Find( y + m );
			}
			if( !tp[k ^ 1] )continue;
			x = St[k ^ 1][1];
			For( j , 1 , tp[k] ){
				int y = St[k][j];
				if( Find( x ) == Find( y ) )error();
				Fa[ Find( x ) ] = Find( y + m );
				Fa[ Find( y ) ] = Find( x + m );
			}
		}
	}
	
	int tot = 0;
	
	For( i , 1 , m << 1 )if( Find( i ) == i )++tot;
	tot >>= 1;
	
	For( i , 1 , n )tot += !V[i];
	
	ans = ans.calc( tot );
	
	ans.display();
	
	return 0;
}
