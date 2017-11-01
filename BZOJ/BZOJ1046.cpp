#include<bits/stdc++.h>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e4 +1;
static const int MAXM = 1e3 +1;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
#define Lop( i , _Begin , _End ) for( int i=_Begin;i>=_End;i-- )

int n,m,L,Len;
int A[MAXN],f[MAXN],Bt[MAXN];

int Find( int x ){
	int l = 1,r = n,Res = 0;
	while( l<=r ){
		int Mid = l+r >>1;
		if( Bt[Mid]>x )Res = Mid,l = Mid+1;
		else r = Mid-1;
	}
	return Res;
}

int main(){
	
	Read( n );
	For( i , 1 , n )Read( A[i] );
	
	Lop( i , n , 1 ){
		int p = Find( A[i] );
		f[i] = p + 1;
		Bt[f[i]] = max( Bt[f[i]] , A[i] );
	}
	
	For( i , 1 , n )
		if( Bt[i] )Len = i;
	
	Read( m );
	while( m-- ){
		Read( L );
		if( L > Len )puts("Impossible");
		else{
			int Last = 0;
			For( i , 1 , n )
				if( f[i]>=L&&L&&A[i]>Last ){
					Last = A[i];L--;
					printf("%d",A[i]);
					if( L )printf(" ");
				}
			puts("");
		}
	}
	return 0;
}
