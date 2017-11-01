#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

static const int maxn = 20 ;

char mp[maxn][maxn] ;

int John ;
int cow ;

bool V1[maxn][maxn][4] ;
bool V2[maxn][maxn][4] ;

int mx[] = { -1 , 0 , 1 , 0 } ;
int my[] = { 0 , 1 , 0 , -1 } ;

bool chk(){
	For( i , 1 , 10 )For( j , 1 , 10 ){
		bool f1 = 0 , f2 = 0 ;
		For( k , 0 , 3 )f1 |= V1[i][j][k] , f2 |= V2[i][j][k] ;
		if( f1 == f2 && f1 )return true ;
	}
	return false ;
}

int main(){
	
	freopen( "ttwo.in" , "r" , stdin ) ;
	freopen( "ttwo.out" , "w" , stdout ) ;
	
	For( i , 1 , 10 )
		scanf( "%s" , mp[i] + 1 ) ;
	
	For( i , 1 , 10 )
		mp[0][i] = mp[i][0] = mp[11][i] = mp[i][11] = '*' ;
	
	int x1 , y1 , z1 ;
	int x2 , y2 , z2 ;
	For( i , 1 , 10 )For( j , 1 , 10 )
		if( mp[i][j] == 'F' )
			x1 = i , y1 = j , z1 = 0 ;
		else if( mp[i][j] == 'C' )
			x2 = i , y2 = j , z2 = 0 ;
	
	int step = 0 ;
	while( true ){
		V1[x1][y1][z1] = V2[x2][y2][z2] = true ;
		if( x1 == x2 && y1 == y2 )return printf("%d\n" , step ) , 0 ;
		if( mp[ x1 + mx[z1] ][ y1 + my[z1] ] == '*' )
			z1 = ( z1 + 1 ) % 4 ;
		else
			x1 += mx[z1] , y1 += my[z1] ;
		if( mp[ x2 + mx[z2] ][ y2 + my[z2] ] == '*' )
			z2 = ( z2 + 1 ) % 4 ;
		else
			x2 += mx[z2] , y2 += my[z2] ;
		if( !John && V1[x1][y1][z1] )John = step ;
		if( !cow && V2[x2][y2][z2] )cow = step ;
		step++ ;
		if( John && cow )break ;
	}
	
	if( !( John % cow ) || !( cow % John ) || !chk() )return puts("0") , 0 ;
	
	while( true ){
		if( x1 == x2 && y1 == y2 )return printf("%d\n" , step ) , 0 ;
		if( mp[ x1 + mx[z1] ][ y1 + my[z1] ] == '*' )
			z1 = ( z1 + 1 ) % 4 ;
		else
			x1 += mx[z1] , y1 += my[z1] ;
		if( mp[ x2 + mx[z2] ][ y2 + my[z2] ] == '*' )
			z2 = ( z2 + 1 ) % 4 ;
		else
			x2 += mx[z2] , y2 += my[z2] ;
		step++ ;
		if( step == 9000900 )return puts("0") , 0 ;
	}
	
	return 0 ;
}
