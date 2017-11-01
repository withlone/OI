#include<cstring>
#include<cstdio>
#include<queue>

using std :: queue;

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )
#define Rep( i , _Begin , _Add ) for( int i=(_Begin);i; i = (_Add) )

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline Type max( Type x , Type y ){ return x > y ? x : y ; }
template< typename Type >inline Type abs( Type x ){ return x < 0 ? -x : x ; }
template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int Inf = 0x7fffffff;
static const int MAXN = 21;
static const int MAXM = 16e4;

int n , m , d , Num , s , t , tot;
int Mp[MAXN][MAXN] , Sort[MAXN][MAXN];
char mp[MAXN][MAXN];

int Dep[MAXM];
int H[MAXM] , Cur[MAXM] , Nt[MAXM] , To[MAXM] , Dt[MAXM] , Sam[MAXM] , Ct;

bool Bfs();
int Dfs( int , int );
void Dinic();

int Sqr( int );
void Ins( int , int , int );

char Getchar();

int main(){
	
	Read( n );Read( m );Read( d );
	For( i , 1 , n )For( j , 1 , m )scanf("%1d",&Mp[i][j]);
	For( i , 1 , n )For( j , 1 , m )mp[i][j] = Getchar();
	
	For( i , 1 , n )For( j , 1 , m )if( Mp[i][j] )Sort[i][j] = ++Num;
	
	s = Num<<1|1;t = s + 1;
	
	For( i , 1 , n )For( j , 1 , m )if( Mp[i][j] ){
		if( i <= d || j <= d || n - i < d || m - j < d )Ins( Sort[i][j] + Num , t , Inf );
		Ins( Sort[i][j] , Sort[i][j] + Num , Mp[i][j] );
		For( x , 1 , n )For( y , 1 , m )if( Sqr( i - x ) + Sqr( j - y ) <= Sqr( d ) && Mp[x][y] )
			Ins( Sort[i][j] + Num , Sort[x][y] , Inf );
	}
	
	For( i , 1 , n )For( j , 1 , m )if( mp[i][j] == 'L' )Ins( s , Sort[i][j] , 1 ) , tot++;
	
	Dinic();
	
	return 0;
}

void Ins( int F , int T , int D ){
	Nt[++Ct] = H[F];H[F] = Ct;To[Ct] = T;Dt[Ct] = D;
	Nt[++Ct] = H[T];H[T] = Ct;To[Ct] = F;Dt[Ct] = 0;
	Sam[Ct-1] = Ct;Sam[Ct] = Ct-1;
}

int Sqr( int x ){ return x * x; }
char Getchar(){
	char ch = getchar();
	while( ch != '.' && ch != 'L' )ch = getchar();
	return ch;
}

bool Bfs(){
	queue< int >Que;
	Que.push( s );
	memset( Dep , 0 , sizeof Dep );
	Dep[s] = 1;
	while( !Que.empty() ){
		int x = Que.front();Que.pop();
		Rep( i , H[x] , Nt[i] ){
			int y = To[i];
			if( !Dt[i] || Dep[y] )continue;
			Dep[y] = Dep[x] + 1;
			Que.push( y );
			if( y == t )return true;
		}
	}
	return false;
}
int Dfs( int x , int Flow ){
	if( x == t )return Flow;
	for( int &i = Cur[x];i;i=Nt[i] ){
		int y = To[i] , tmp;
		if( !Dt[i] || Dep[y] != Dep[x] + 1 || !( tmp = Dfs( y , min( Flow , Dt[i] ) ) ) )continue;
		Dt[i] -= tmp;
		Dt[Sam[i]] += tmp;
		return tmp;
	}
	return 0;
}
void Dinic(){
	int tmp;
	while( Bfs() ){
		memcpy( Cur , H , sizeof H );
		while( tmp = Dfs( s , Inf ) )tot -= tmp;
	}
	printf("%d\n",max( 0 , tot ));
}
