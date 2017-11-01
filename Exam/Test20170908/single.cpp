#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

static const int maxn = 1e4 + 10  ;

int n ;
int ans ;
int len ;

int money[4] = { 0 , 91 , 29 , 8 } ;

char s[maxn] ;
char chk_s[] = "shang" ;
char chk_z[] = "zhong" ;
char chk_x[] = "xia" ;

int getline( char *x ){
	For( i , 1 , maxn - 1 ){
		x[i] = getchar() ;
		if( x[i] == '\n' )return i - 1 ;
	}
	throw ;
}

void match(){
	if( s[len - 5] != ' ' )return ;
	For( i , len - 4 , len )
		if( s[i] != chk_s[ i - len + 4 ] )return ;
	len -= 6 ;
	int f = 0 ;
	if( s[len - 3] == ' ' ){
		For( i , len - 2 , len )
			if( s[i] != chk_x[ i - len + 2 ] )return ;
		f = 3 ;
	}
	else if( s[len - 5] == ' ' ){
		if( s[len - 4] == 's' ){
			For( i , len - 3 , len )
				if( s[i] != chk_s[ i - len + 4 ] )return ;
			f = 1 ;
		}
		else if( s[len - 4] == 'z' ){
			For( i , len - 3 , len )
				if( s[i] != chk_z[ i - len + 4 ] )return ;
			f = 2 ;
		}
	}
	ans += money[f] ;
}

int main(){
	
	freopen( "single.in" , "r" , stdin ) ;
	freopen( "single.out" , "w" , stdout ) ;
	
	scanf( "%d\n" , &n ) ;
	
	while( n-- ){
		len = getline( s ) ;
		while( len > 1 && s[len] == ' ' )--len ;
		int blank = 0 ;
		For( i , 1 , len )blank += ( s[i] == ' ' ) ;
		if( blank >= 7 )continue ;
		match() ;
	}
	
	printf("%d\n" , ans ) ;
	
	return 0 ;
}
