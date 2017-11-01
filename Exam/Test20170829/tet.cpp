#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename type >inline void swap( type &x , type &y ){ type t = x ; x = y ; y = t ; }
template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 5e4 + 10;
static const int maxm = 1e6 + 10;

int n;

int size;
int ans[maxm];

int pos[maxn];

int tp;
int stk[maxm];

int main(){
	
	freopen("tet.in","r",stdin);
	freopen("tet.out","w",stdout);
	
	scanf( n ) ;
	
	For( i , 1 , n << 1 ){
		int x ;
		scanf( x ) ;
		stk[ ++tp ] = x;
		if( pos[x] ){
			if( pos[x] == tp - 1 ){ tp -= 2 ; continue ; }
			int t = pos[x] ;
			while( t != tp - 1 ){
				swap( stk[t] , stk[t + 1] );
				pos[ stk[t] ]--;
				ans[ ++size ] = t++;
			}
			tp -= 2 ;
			pos[x] = 0 ;
		}
		else pos[x] = tp ;
	}
	
	printf("%d\n" , size );
	
	For( i , 1 , size )printf("%d\n" , ans[i] );
	
	return 0;
}
