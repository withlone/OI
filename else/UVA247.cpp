#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

static const int maxn = 30;

int n;
int m;
int cases;

char name[maxn][maxn];
map< string , int >mp;

bool dis[maxn][maxn];

void read_in(){
	int Ct = 0;
	mp.clear();
	memset( dis , 0 , sizeof dis );
	For( i , 1 , m ){
		char x[maxn] , y[maxn];
		scanf( "%s%s" , x , y );
		if( !mp[x] )strcpy( name[ mp[x] = ++Ct ] , x );
		if( !mp[y] )strcpy( name[ mp[y] = ++Ct ] , y );
		dis[ mp[x] ][ mp[y] ] = true;
	}
}

void Floyd(){
	For( i , 1 , n )dis[i][i] = true;
	For( k , 1 , n )
		For( i , 1 , n )
			For( j , 1 , n )
				dis[i][j] |= dis[i][k] & dis[k][j];
}

void display(){
	bool V[maxn];
	memset( V , 0 , sizeof V );
	printf("Calling circles for data set %d:\n" , ++cases );
	For( i , 1 , n )if( !V[i] ){
		int set[maxn] , cnt = 0;
		For( j , 1 , n )
			if( dis[i][j] & dis[j][i] )set[ ++cnt ] = j , V[j] = true;
		printf("%s" , name[ set[1] ] );
		For( j , 2 , cnt )printf(", %s" , name[ set[j] ] );
		putchar( '\n' );
	}
}

int main(){
	
	bool f = 0;
	
	while( scanf( "%d%d" , &n , &m ) != EOF && n + m ){
		
		if( f )putchar( '\n' ) ; else f = true;
		
		read_in();
		
		Floyd();
		
		display();
		
	}
	
	return 0;
}
