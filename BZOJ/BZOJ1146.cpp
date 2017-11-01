#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int maxn = 8e4 +1;
static const int maxm = maxn << 1;
static const int maxx = 1e7;

int n , m , u , v , Cnt , Ct;
int work[2][maxn] , Size[2];
int A[maxn] , mine[maxm];
int opt[maxn] , _A[maxn] , _B[maxn];

int H[maxn] , Nt[maxm] , To[maxm];
void Ins( int x , int y ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
}

namespace tree_subdivision{
	
	int size[maxn] , Fa[maxn] , Dep[maxn] , Son[maxn];
	int Top[maxn] , Begin[maxn] , End[maxn] , rank;
	
	void Dfs( int x ){
		size[x] = 1;
		Rep( i , H[x] , Nt[i] ){
			int y = To[i];
			if( y == Fa[x] )continue;
			Dep[y] = Dep[x] + 1;
			Fa[y] = x;
			Dfs( y );
			size[x] += size[y];
			if( size[y] > size[Son[x]] )Son[x] = y;
		}
	}
	
	void Dfs( int x , int chain ){
		Top[x] = chain;
		Begin[x] = ++rank;
		if( Son[x] )Dfs( Son[x] , chain );
		Rep( i , H[x] , Nt[i] )
			if( To[i] != Son[x] && To[i] != Fa[x] )
				Dfs( To[i] , To[i] );
		End[x] = rank;
	}
	
	int Lca( int x , int y ){
		while( Top[x] != Top[y] ){
			if( Dep[Top[x]] < Dep[Top[y]] )swap( x , y );
			x = Fa[Top[x]];
		}
		return Dep[x] < Dep[y] ? x : y ;
	}
	
}using namespace tree_subdivision;


namespace President_tree{
	
	int Rt[maxn] , Sz[maxx] , Ch[maxx][2];
	
	void modify( int pt , int &rt , int l , int r , int x , int y ){
		Sz[ rt = ++Ct ] = Sz[pt] + y;
		if( l == r )return;
		int mid = l + r >> 1;
		if( x <= mid )Ch[rt][1] = Ch[pt][1] , modify( Ch[pt][0] , Ch[rt][0] , l , mid , x , y );
		else Ch[rt][0] = Ch[pt][0] , modify( Ch[pt][1] , Ch[rt][1] , mid + 1 , r , x , y );
	}
	
}using namespace President_tree;

namespace BIT{
	
	int Lowbit( int x ){ return x & -x ; }
	
	void Add( int x , int y , int f ){
		for( ; x <= n ; x += Lowbit( x ) )
			modify( Rt[x] , Rt[x] , 1 , Cnt , y , f );
	}
	
	void Get( int x , int num ){
		for( ; x ; x -= Lowbit( x ) )
			work[num][++Size[num]] = Rt[x];
	}
	
}using namespace BIT;

int root[maxn];
void Build( int x ){
	int t = lower_bound( 1 + mine , 1 + Cnt + mine , A[x] ) - mine;
	modify( root[Fa[x]] , root[x] , 1 , Cnt , t , 1 );
	if( Son[x] )Build( Son[x] );
	Rep( i , H[x] , Nt[i] )
		if( To[i] != Son[x] && To[i] != Fa[x] )
			Build( To[i] );
}

void Init(){
	Read( n );Read( m );
	For( i , 1 , n )Read( A[i] ) , mine[ ++Cnt ] = A[i];
	For( i , 1 , n - 1 )Read( u ) , Read( v ) , Ins( u , v ) , Ins( v , u );
	For( i , 1 , m ){
		Read( opt[i] ) ; Read( _A[i] ) ; Read( _B[i] );
		if( !opt[i] )mine[ ++Cnt ] = _B[i];
	}
	sort( 1 + mine , 1 + Cnt + mine );
	Cnt = unique( 1 + mine , 1 + Cnt + mine ) - mine - 1;
	
	Dep[1] = 1;
	Dfs( 1 );
	Dfs( 1 , 1 );
	Ct = 0;
	
	Build( 1 );
}

int Query( int l , int r , int k ){
	while( l < r ){
		int suml = 0 , sumr = 0;
		For( i , 1 , Size[0] )sumr += Sz[ Ch[work[0][i]][0] ];
		For( i , 1 , Size[1] )suml += Sz[ Ch[work[1][i]][0] ];
		int mid = l + r >> 1 , p = ( sumr - suml < k );
		For( i , 0 , 1 )For( j , 1 , Size[i] )
			work[i][j] = Ch[work[i][j]][p];
		if( !p )r = mid;
		else l = mid + 1 , k -= sumr - suml;
	}
	return mine[l];
}

int main(){
	
	Init();
	
	For( i , 1 , m )
		if( !opt[i] ){
			int t = lower_bound( 1 + mine , 1 + Cnt + mine , A[ _A[i] ] ) - mine;
			int p = lower_bound( 1 + mine , 1 + Cnt + mine , A[ _A[i] ] = _B[i] ) - mine;
			Add( Begin[_A[i]] , t , -1 );
			Add( End[_A[i]] + 1 , t , 1 );
			Add( Begin[_A[i]] , p , 1 );
			Add( End[_A[i]] + 1 , p , -1 );
		}
		else{
			int lca = Lca( _A[i] , _B[i] ) , tmp = Dep[ _A[i] ] + Dep[ _B[i] ] - Dep[ lca ] - Dep[ Fa[lca] ];
			if( tmp < opt[i] ){ puts("invalid request!") ; continue ; }
			Size[0] = Size[1] = 2;
			work[0][1] = root[ _A[i] ];work[0][2] = root[ _B[i] ];
			work[1][1] = root[ lca ];work[1][2] = root[ Fa[lca] ];
			Get( Begin[ _A[i] ] , 0 );Get( Begin[ _B[i] ] , 0 );
			Get( Begin[ lca ] , 1 );Get( Begin[ Fa[ lca ] ] , 1 );
			printf("%d\n",Query( 1 , Cnt , tmp - opt[i] + 1 ));
		}
	return 0;
}
