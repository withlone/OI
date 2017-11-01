#include<cstdio>
#include<cstring>

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}
template< typename Type >inline Type max( Type x,Type y ){ return x>y?x:y; }
template< typename Type >inline Type min( Type x,Type y ){ return x<y?x:y; }


static const int MAXN = 6e3 +1;
static const int MAXM = 3e4 +1;
static const int Inf  = 1e9 ;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
#define Lop( i , _Begin , _End ) for( int i=_Begin;i>=_End;i-- )

int n,Sum;
int A[MAXN],B[MAXN],C[MAXN];
int f[MAXM];

int main(){
	
	For( i , 1 , MAXM-1 )f[i] = Inf;
	
	Read( n );
	For( i , 1 , n )Read( A[i] ),Read( B[i] ),Read( C[i] ),Sum += max( A[i],max( B[i],C[i] ) );
	
	For( i , 1 , n )
		Lop( j , Sum , 0 ){
			int tmp = f[j];
			f[j] = Inf;
			if( B[i] )f[j] = min( f[j] , tmp + B[i] );
			if( A[i]&&j>=A[i] )f[j] = min( f[j] , f[j-A[i]] );
			if( C[i]&&j>=C[i] )f[j] = min( f[j] , f[j-C[i]] + C[i] );
		}
	
	int Ans = Inf;
	For( i , 0 , Sum )Ans = min( Ans , max( f[i] , i ) );
	printf("%d\n",Ans);
	return 0;
}
