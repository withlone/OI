#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 4e4 +1;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

int n,m,k,x;
int A[MAXN],f[MAXN];
int b[MAXN],Pre[MAXN],Cnt[MAXN];

int main(){
	
	memset( f,0x3f,sizeof f );
	Read( n );Read( m );
	For( i , 1 , n ){
		Read( x );
		if( A[A[0]]!=x )A[++A[0]] = x;
	}
	n = A[0];
	f[0] = 0;k = (int)sqrt( n+0.5 );
	For( i , 1 , n ){
		For( j , 1 , k )
			if( Pre[A[i]]<=b[j] )Cnt[j]++;
		Pre[A[i]] = i;
		For( j , 1 , k )
			if( Cnt[j]>j ){
				int t = b[j]+1;
				while( Pre[A[t]]>t )t++;
				b[j] = t;Cnt[j]--;
			}
		For( j , 1 , k )
			f[i] = min( f[i] , f[b[j]] + j*j );
	}
	
	printf("%d\n",f[n]);
	return 0;
}
