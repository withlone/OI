#include<set>
#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

typedef set< int > :: iterator IT;
static const int maxn = 1e5 +1;

int m , Cnt;
int opt[maxn] , A[maxn] , Fd[maxn];
set< int >Set;
int Rt;
int Fa[maxn] , Ch[maxn][2];

namespace Segment_tree{
	
	#define Lson rt << 1 , l , mid
	#define Rson rt << 1 | 1 , mid + 1 , r
	
	int T[maxn << 2];
	
	void modify( int rt , int l , int r , int L , int R , int f ){
		if( l > R || r < L )return;
		if( l >= L && r <= R )return T[rt] += f , void();
		if( T[rt] )T[ rt << 1 ] += T[rt] , T[ rt << 1 | 1 ] += T[rt] , T[rt] = 0;
		int mid = l + r >> 1;
		modify( Lson , L , R , f );modify( Rson , L , R , f );
	}
	void modify( int L , int R , int f ){ modify( 1 , 1 , Cnt , L , R , f ) ; }
	
	void modify( int rt , int l , int r , int x , int f ){
		if( l == r )return T[rt] = f , void();
		if( T[rt] )T[ rt << 1 ] += T[rt] , T[ rt << 1 | 1 ] += T[rt] , T[rt] = 0;
		int mid = l + r >> 1;
		return x <= mid ? modify( Lson , x , f ) : modify( Rson , x , f );
	}
	void modify( int x , int f ){ modify( 1 , 1 , Cnt , x , f ) ; }
	
	int Query( int rt , int l , int r , int x ){
		if( l == r )return T[rt];
		if( T[rt] )T[ rt << 1 ] += T[rt] , T[ rt << 1 | 1 ] += T[rt] , T[rt] = 0;
		int mid = l + r >> 1;
		return x <= mid ? Query( Lson , x ) : Query( Rson , x );
	}
	int Query( int x ){ return Query( 1 , 1 , Cnt , x ) ; }
	
}using namespace Segment_tree;

void Splay_min(){
	IT t = Set.begin();
	printf("%d\n",Query( *t ));
	if( Rt == *t )return;
	if( Fa[*t] )Ch[ Fa[*t] ][0] = Ch[*t][1];
	if( Ch[*t][1] )Fa[ Ch[*t][1] ] = Fa[*t];
	modify( Fa[*t] , Cnt , 1 );modify( *t , 1 );
	Fa[Rt] = *t;
	Fa[*t] = 0;Ch[*t][1] = Rt;Rt = *t;
}

void Splay_max(){
	IT t = Set.end();t--;
	printf("%d\n",Query( *t ));
	if( Rt == *t )return;
	if( Fa[*t] )Ch[ Fa[*t] ][1] = Ch[*t][0];
	if( Ch[*t][0] )Fa[ Ch[*t][0] ] = Fa[*t];
	modify( 1 , Fa[*t] , 1 );modify( *t , 1 );
	Fa[Rt] = *t;
	Fa[*t] = 0;Ch[*t][0] = Rt;Rt = *t;
}

int main(){
	
	Read( m );
	For( i , 1 , m ){
		Read( opt[i] );
		if( opt[i] == 1 )Read( A[i] ) , Fd[ ++Cnt ] = A[i];
	}
	
	sort( 1 + Fd , 1 + Cnt + Fd );
	For( i , 1 , m )if( opt[i] == 1 )A[i] = lower_bound( 1 + Fd , 1 + Cnt + Fd , A[i] ) - Fd;
	
	For( i , 1 , m )
		if( opt[i] == 1 ){
			int d = 1;
			if( Set.empty() )Rt = A[i] , modify( A[i] , 1 );
			else{
				IT t = Set.lower_bound( A[i] );
				if( Ch[*t][0] || t == Set.end() )t-- , Ch[*t][1] = A[i] , Fa[ A[i] ] = *t;
				else Ch[*t][0] = A[i] , Fa[ A[i] ] = *t;
				d += Query( *t );
				modify( A[i] , d );
			}
			Set.insert( A[i] );
			printf("%d\n",d);
		}
		else if( opt[i] == 2 )Splay_min();
		else if( opt[i] == 3 )Splay_max();
		else if( opt[i] == 4 ){
			Splay_min();
			IT t = Set.begin();
			Set.erase( *t );Rt = Ch[*t][1];Fa[Rt] = 0;
			modify( 1 , Cnt , -1 );
		}
		else{
			Splay_max();
			IT t = Set.end();t--;
			Set.erase( *t );Rt = Ch[*t][0];Fa[Rt] = 0;
			modify( 1 , Cnt , -1 );
		}
	
	return 0;
}
