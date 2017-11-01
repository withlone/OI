#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )

template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef pair< int , int > par ;
static const int maxn = 1e5 + 10;

bool operator < ( par x , par y ) { return x.first < y.first ; }
bool operator > ( par x , par y ) { return x.first > y.first ; }

int n;

int A[maxn];

void read_in(){
	scanf( n ) ;
	For( i , 1 , n )
		scanf( A[i] ) ;
}

int dct;

struct data{
	int val , x ;
	data(){ val = x = 0 ; }
	data( int a , int b ){ val = a ; x = b ; }
	bool operator < ( data t ) const { return val == t.val ? x < t.x : val < t.val ; }
}d[maxn];

int len ;
par C[maxn];

int div( par x ){
	int l = 1 , r = len ;
	while( l <= r ){
		int mid = l + r >> 1;
		if( x > C[mid] )l = mid + 1 ;
		else r = mid - 1;
	}
	return l ;
}

void preparation(){
	For( i , 1 , n )
		if( i - A[i] >= 0 )d[ ++dct ] = data( i - A[i] , i );
	sort( 1 + d , 1 + dct + d ) ;
}

int F[maxn];
int pre[maxn];

void LIS(){
	int ans = 0 ;
	For( i , 1 , n )C[i] = make_pair( 1e7 , 0 ) ;
	For( i , 1 , dct ){
		int t = div( make_pair( A[ d[i].x ] , d[i].x ) );
		F[ d[i].x ] = t ;
		pre[ d[i].x ] = C[t - 1].second;
		len = max( len , t ) ;
		C[t] = min( C[t] , make_pair( A[ d[i].x ] , d[i].x ) ) ;
	}
}

int size;
int ans[maxn];
bool V[maxn];

vector < int > vec;

void display(){
	int pos = 0 ;
	For( i , 1 , n )
		if( F[i] == len ){ pos = i ; break ; }
	while( pos ){
		ans[ ++size ] = pos;
		pos = pre[pos];
	}
	For( i , 1 , size )V[ ans[i] ] = true;
	int last = 0 ;
	Lop( i , size , 1 ){
		int t = ans[i] - 1 ;
		For( j , 1 , ans[i] - A[ ans[i] ] - last )vec.push_back( t-- );
		last = max( last , ans[i] - A[ ans[i] ] ) ;
	}
	printf("%d\n" , vec.size() );
	For( i , 0 , vec.size() - 1 )printf("%d " , vec[i] ) ;
	putchar( '\n' );
}

int main(){
	
	freopen("klo.in","r",stdin);
	freopen("klo.out","w",stdout);
	
	read_in();
	
	preparation();
	
	LIS();
	
	display();
	
	return 0;
}
