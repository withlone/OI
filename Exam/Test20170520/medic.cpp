#include<cstdio>

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

template< typename Type >inline Type max ( Type x , Type y ){ return x > y ? x : y ; }
template< typename Type >inline Type min ( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e5 +1;

int n , q , t , v , x , c , M , tmp;
int Que[MAXN][2] , H , T;
int m[MAXN] , Sz[11][11];
int f[MAXN];

void Pack_with_queue(){
	For( I , 1 , 10 )For( J , 1 , 10 )
		if( Sz[I][J] ){
			t = I;v = J;x = M / t;
			c = min( x , Sz[I][J] );
			For( j , 0 , t-1 ){
				H = T = 0;
				Que[0][1] = f[j] + x*v;
				For( k , 1 , x ){
					int tmp = j + k*t;
					if( tmp > M )break;
					while( H <= T && k - Que[H][0] > c )H++;
					while( H <= T && Que[T][1] <= f[ tmp ] + ( x-k )*v )T--;
					T++;
					Que[T][0] = k;Que[T][1] = f[ tmp ] + ( x-k )*v;
					f[ tmp ] = max( f[ tmp ] , Que[H][1] - ( x-k )*v );
				}
			}
		}
}

#define Judge

int main(){
	
	#ifdef Judge
		freopen("medic.in","r",stdin);
		freopen("medic.out","w",stdout);
	#endif
	
	Read( n );Read( q );
	For( i , 1 , n )Read( t ) , Read( v ) , Sz[t][v]++;
	For( i , 1 , q )Read( m[i] ) , M = max( M , m[i] );
	
	Pack_with_queue();
	
	For( i , 1 , q )
		printf("%d\n",f[m[i]]);
	return 0;
}
