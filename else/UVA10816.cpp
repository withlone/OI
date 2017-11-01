#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

typedef double DB;
typedef pair< DB , int > par;
static const int maxn = 100 + 10;
static const int maxm = 1e4 + 10;
static const int maxx = maxm << 1;
static const DB eps = 1e-10;

int cmp( DB x , DB y ){ return abs( x - y ) < eps ? 0 : x - y > 0 ? 1 : -1 ; }

int n;
int m;
int S;
int T;

int mp[maxn][maxn];

struct edge{
	int x , y;DB tp , len;
	bool operator < ( edge t ) const { return cmp( tp , t.tp ) == -1 ; }
}e[maxm];

int Fa[maxn];

int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int Ct;
int Ht[maxn];
int Nt[maxx];
int To[maxx];
int Cm[maxx];
DB Dt[maxx];

void Ins( int x , int y , DB z ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Cm[Ct] = x;Dt[Ct] = z;
}


bool operator < ( par x , par y ){ return cmp( x.first , y.first ) == -1 ; }
bool operator > ( par x , par y ){ return cmp( x.first , y.first ) ==  1 ; }

struct heap{
	
	int size;
	par T[maxx];
	
	void clear(){ size = 0; }
	
	void push( par t ){
		T[ ++size ] = t;
		int p = size;
		while( p != 1 && T[p] < T[p >> 1] ){
			swap( T[p] , T[p >> 1] );
			p >>= 1;
		}
	}
	
	void pop(){
		T[1] = T[ size-- ];
		int p = 1;
		while( ( p << 1 ) <= size && T[p] > min( T[p << 1] , T[p << 1 | 1] ) ){
			int t = T[p << 1] < T[p << 1 | 1] ? p << 1 : p << 1 | 1;
			swap( T[p] , T[t] );
			p = t;
		}
	}
	
	int top(){ return T[1].second ; }
	
	bool empty(){ return !size ; }
	
}Hp;

int main(){
	
	while( scanf("%d%d%d%d" , &n , &m , &S , &T ) != EOF ){
		
		init : {
			
			For( i , 1 , m )scanf("%d%d%lf%lf", &e[i].x , &e[i].y , &e[i].tp , &e[i].len );
			
			For( i , 1 , n )Fa[i] = i;
			
		}
		DB limit = 0;
		
		MST : {
		
			sort( 1 + e , 1 + m + e );
			
			For( i , 1 , m )
				if( Find( e[i].x ) != Find( e[i].y ) ){
					Fa[ Find( e[i].x ) ] = Find( e[i].y );
					if( Find( S ) == Find( T ) ){
						limit = e[i].tp;
						break;
					}
				}
			
		}
		
		Ct = 0;
		For( i , 1 , n )Ht[i] = 0;
		
		For( i , 1 , m )
			if( cmp( e[i].tp , limit ) <= 0 )
				Ins( e[i].x , e[i].y , e[i].len ) ,
				Ins( e[i].y , e[i].x , e[i].len ) ,
				mp[ e[i].x ][ e[i].y ] = mp[ e[i].y ][ e[i].x ] = i;
		
		dijkstra : {
			
			DB dis[maxn];
			bool V[maxn];
			int pre[maxn];
			
			For( i , 1 , n )dis[i] = 1e9 , V[i] = false;
	
			Hp.clear();
	
			dis[S] = 0;
	
			Hp.push( make_pair( 0 , S ) );
	
			while( !Hp.empty() ){
				int x = Hp.top();Hp.pop();
				if( V[x] )continue;
				V[x] = true;
				Rep( i , Ht[x] , Nt[i] ){
					int y = To[i];
					if( cmp( dis[y] , dis[x] + Dt[i] ) == 1 && !V[y] ){
						dis[y] = dis[x] + Dt[i];
						pre[y] = i;
						Hp.push( make_pair( dis[y] , y ) );
					}
				}
			}
	
			int ans[maxn] , cnt = 0;
	
			int s = S , t = T;
			while( s != t ){
				ans[ ++cnt ] = t;
				t = Cm[ pre[t] ];
			}
	
			printf("%d", s );
	
			Lop( i , cnt , 1 )printf(" %d" , ans[i] );
	
			putchar( '\n' );
	
			printf("%.1lf %.1lf\n" , dis[T] , limit );
			
		}
	}
	
	return 0;
}
