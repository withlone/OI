#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int maxn = 1e4 + 1;
static const int maxm = maxn << 1;
static const int maxx = 38e5 + 1;

int n , m , cnt , Ct;
char opt[maxn];
int A[maxn] , _A[maxn] , _B[maxn] , _C[maxn];
int mine[maxm] , work[2][maxn] , size[2];

namespace President_tree{
	
	int Ch[maxx][2] , Sz[maxx] , Rt[maxn];
	
	void modify( int pt , int &rt , int l , int r , int x , int y ){
		Sz[ rt = ++Ct ] = Sz[pt] + y;
		if( l == r )return;
		Ch[rt][0] = Ch[pt][0];Ch[rt][1] = Ch[pt][1];
		int mid = l + r >> 1;
		if( x <= mid )modify( Ch[pt][0] , Ch[rt][0] , l , mid , x , y );
		else modify( Ch[pt][1] , Ch[rt][1] , mid + 1 , r , x , y );
	}
	
	int Query( int l , int r , int k ){
		while( l < r ){
			if( l == r )return mine[l];
			int suml = 0 , sumr = 0;
			For( i , 1 , size[0] )suml += Sz[ Ch[work[0][i]][0] ];
			For( i , 1 , size[1] )sumr += Sz[ Ch[work[1][i]][0] ];
			int mid = l + r >> 1 , p = ( sumr - suml < k );
			For( i , 0 , 1 )For( j , 1 , size[i] )
				work[i][j] = Ch[work[i][j]][p];
			if( !p )r = mid;
			else l = mid + 1 , k -= sumr - suml;
		}
		return mine[l];
	}
	
}using namespace President_tree;

namespace BIT{
	
	int Lowbit( int x ){ return x & -x ; }
	
	void Add( int x , int y , int f ){
		for( ; x <= n ; x += Lowbit( x ) )
			modify( Rt[x] , Rt[x] , 1 , cnt , y , f );
	}
	
	void Get( int x , int num ){
		for( size[num] = 0; x ; x -= Lowbit( x ) )
			work[num][ ++size[num] ] = Rt[x];
	}
	
}using namespace BIT;

void Init(){
	Read( n );Read( m );
	For( i , 1 , n )Read( A[i] ) , mine[ ++cnt ] = A[i];
	For( i , 1 , m ){
		scanf("%s",&opt[i]);
		Read( _A[i] );Read( _B[i] );
		if( opt[i] == 'Q' )Read( _C[i] );
		else mine[ ++cnt ] = _B[i];
	}
	sort( 1 + mine , 1 + cnt + mine );
	cnt = unique( 1 + mine , 1 + cnt + mine ) - mine - 1;
	
	For( i , 1 , n ){
		int t = lower_bound( 1 + mine , 1 + cnt + mine , A[i] ) - mine;
		Add( i , t , 1 );
	}
}

int main(){
	
	Init();
	
	For( i , 1 , m )
		if( opt[i] == 'Q' ){
			Get( _A[i] - 1 , 0 );Get( _B[i] , 1 );
			printf("%d\n",Query( 1 , cnt , _C[i] ));
		}
		else{
			int p = lower_bound( 1 + mine , 1 + cnt + mine , A[ _A[i] ] ) - mine;
			int t = lower_bound( 1 + mine , 1 + cnt + mine , A[ _A[i] ] = _B[i] ) - mine;
			Add( _A[i] , p , -1 );
			Add( _A[i] , t , 1 );
		}
	
	return 0;
}
