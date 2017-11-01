#include<cmath>
#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

static const int maxn = 1e4 +1;

int n , m , Qct , Mct , sum , Fac;
int Col[maxn] , Lst[maxn];
int num[maxn * 100] , ans[maxn];

struct Query{
	int l , r , id , x;
	bool operator < ( Query tmp ) const {
		return l/Fac < tmp.l/Fac || l/Fac == tmp.l/Fac && r/Fac < tmp.r/Fac || l/Fac == tmp.l/Fac && r/Fac == tmp.r/Fac && x < tmp.x;
	}
}Q[maxn];

struct Modify{ int x , col1 , col2; }M[maxn];

int main(){
	
	Read( n );Read( m );Fac = pow( n , 2.0 / 3 );
	For( i , 1 , n )Read( Col[i] ) , Lst[i] = Col[i];
	For( i , 1 , m ){
		char ch;scanf("%s",&ch);
		int x , y;Read( x );Read( y );
		if( ch == 'Q' )Q[ ++Qct ] = (Query){ x , y , Qct , Mct };
		else M[ ++Mct ] = (Modify){ x , Lst[x] , y } , Lst[x] = y;
	}
	sort( 1 + Q , 1 + Qct + Q );
	
	int l = 1 , r = 0 , x = 0;
	For( i , 1 , Qct ){
		while( x < Q[i].x ){
			x++;
			if( l <= M[x].x && M[x].x <= r )
				sum += ( 1 == ++num[ M[x].col2 ] ) ,
				sum -= !--num[ Col[ M[x].x ] ];
			Col[ M[x].x ] = M[x].col2;
		}
		while( x > Q[i].x ){
			if( l <= M[x].x && M[x].x <= r )
				sum += ( 1 == ++num[ M[x].col1 ] ) ,
				sum -= !--num[ Col[ M[x].x ] ];
			Col[ M[x].x ] = M[x].col1;
			x--;
		}
		while( r < Q[i].r )r++ , sum += ( 1 == ++num[ Col[r] ] );
		while( l > Q[i].l )l-- , sum += ( 1 == ++num[ Col[l] ] );
		while( r > Q[i].r )sum -= !--num[ Col[r] ] , r--;
		while( l < Q[i].l )sum -= !--num[ Col[l] ] , l++;
		ans[ Q[i].id ] = sum;
	}
	
	For( i , 1 , Qct )printf("%d\n",ans[i]);
	
	return 0;
}
