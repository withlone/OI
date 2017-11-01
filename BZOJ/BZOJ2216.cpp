#include<cstdio>
#include<cmath>

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )

template< typename Type >inline Type max ( Type x , Type y ){ return x > y ? x : y; }
template< typename Type >inline Type min ( Type x , Type y ){ return x < y ? x : y; }
template< typename Type >inline void swap( Type&x , Type&y ){ x ^= y ^= x ^= y; }
template< typename Type >inline Type abs ( Type x ){ return x < 0 ? -x : x; }
template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 5e5 +1;

int n;
int A[MAXN];double F[MAXN] , G[MAXN];
struct queue{ int l , r , p; }Que[MAXN];int H , T;

double Calc( int x , int y ){ return A[x] + sqrt( abs( x - y ) ) - A[y]; }
int Find( queue x , int y ){
	int l = x.l , r = x.r;
	while( l <= r ){
		int Mid = l + r >>1;
		if( Calc( y , Mid ) < Calc( x.p , Mid ) )l = Mid + 1;
		else r = Mid - 1;
	}
	return l;
}
void Work( double *f ){
	H = 1;T = 0;
	For( i , 1 , n ){
		Que[H].l++;
		while( H <= T && Que[H].l > Que[H].r )H++;
		if( H > T || Calc( i , n ) > Calc( Que[H].p , n ) ){
			while( H <= T && Calc( i , Que[T].l ) > Calc( Que[T].p , Que[T].l ) )T--;
			if( H > T )Que[++T] = (queue){ i , n , i };
			else{
				int tmp = Find( Que[T] , i );
				Que[T].r = tmp - 1;
				Que[++T] = (queue){ tmp , n , i };
			}
		}
		f[i] = Calc( Que[H].p , i );
	}
}

int main(){
	
	Read( n );
	For( i , 1 , n )Read( A[i] );
	Work( F );
	For( i , 1 , n>>1 )swap( A[i] , A[n-i+1] );
	Work( G );
	For( i , 1 , n )printf("%.0lf\n",ceil(max( F[i], G[n-i+1] )));
	return 0;
}
