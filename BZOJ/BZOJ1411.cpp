#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e5 +1;
typedef long long LL;

int n;LL m;
int A[MAXN] , B[MAXN];

int main(){
	
	Read( n );Read( m );
	For( i , 0 , n-1 )Read( A[i] ) , A[i]--;
	A[n] = A[0];
	
	LL T = m;
	
	if( T & 1 )For( i , 0 , n-1 )A[i] ^= A[i+1];
	T>>=1;
	while( T ){
		LL tmp = T & -T;
		For( i , 0 , n-1 )
			B[i] = A[((i-tmp)%n+n)%n] ^ A[(i+tmp)%n];
		memcpy( A , B , sizeof A );
		T -= tmp;
	}
	
	if( m & 1 )printf("0 %d",A[0]+1);
	else printf("%d 0",A[0]+1);
	For( i , 1 , n-1 )
		if( m & 1 )printf(" 0 %d",A[i]+1);
		else printf(" %d 0",A[i]+1);
	
	return 0;
}
