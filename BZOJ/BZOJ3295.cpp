#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Dnt( i , _Begin , _End , _Add ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i = (_Add) )
#define Lop( i , _Begin , _End , _Add ) for( int i = (_Begin) , i##END = (_End) ; i >  (i##END) ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

typedef long long LL;
static const int maxn = 1e5 +1;
static const int maxx = 1e7 +1;

int n , m;LL ans;
int A[maxn];

namespace president_tree{
	
	int root[maxn] , Cnt;
	int Sz[maxx] , Ch[maxx][2];
	
	void modify( int &rt , int l , int r , int x , int f ){
		if( !rt )rt = ++Cnt;
		Sz[rt] += f;
		if( l == r )return;
		int mid = l + r >> 1;
		if( x <= mid )modify( Ch[rt][0] , l , mid , x , f );
		else modify( Ch[rt][1] , mid + 1 , r , x , f );
	}
	
}using namespace president_tree;

namespace BIT{
	
	int Tr[maxn];
	int work[2][maxn] , size[2];
	
	int Lowbit( int x ){ return x & -x ; }
	
	void Add( int x , int y , int f ){
		Dnt( i , x , n , i + Lowbit( i ) )
			modify( root[i] , 1 , n , y , f );
	}
	
	void Get( int x , int num ){
		Lop( i , x , 0 , i - Lowbit( i ) )
			work[num][ ++size[num] ] = root[i];
	}
	
	LL Query( int x ){
		LL Res = 0;
		size[0] = 0;
		Get( A[x] - 1 , 0 );
		int l = 1 , r = n;
		while( l < r ){
			int mid = l + r >> 1;
			if( x <= mid ){
				For( i , 1 , size[0] )Res += Sz[ Ch[ work[0][i] ][1] ];
				r = mid;
				For( i , 1 , size[0] )work[0][i] = Ch[ work[0][i] ][0];
			}
			else{
				For( i , 1 , size[0] )work[0][i] = Ch[ work[0][i] ][1];
				l = mid + 1;
			}
		}
		l = 1; r = n;
		size[0] = size[1] = 0;
		Get( n , 0 );Get( A[x] , 1 );
		while( l < r ){
			int mid = l + r >> 1;
			if( x <= mid ){
				For( i , 0 , 1 )For( j , 1 , size[i] )work[i][j] = Ch[ work[i][j] ][0];
				r = mid;
			}
			else{
				For( i , 1 , size[0] )Res += Sz[ Ch[ work[0][i] ][0] ];
				For( i , 1 , size[1] )Res -= Sz[ Ch[ work[1][i] ][0] ];
				For( i , 0 , 1 )For( j , 1 , size[i] )work[i][j] = Ch[ work[i][j] ][1];
				l = mid + 1;
			}
		}
		return Res;
	}
	
	void _Add( int x ){	Dnt( i , x , n , i + Lowbit( i ) )Tr[i]++; }
	
	LL _Query( int x ){
		LL Res = 0;
		Lop( i , x , 0 , i - Lowbit( i ) )Res += Tr[i];
		return Res;
	}
	
}using namespace BIT;

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n ){
		int x;
		Read( x );A[x] = i;
		_Add( x );
		Add( i , x , 1 );
		ans += _Query( n ) - _Query( x );
	}
	
	while( m-- ){
		int x;
		Read( x );
		printf("%lld\n",ans);
		Add( A[x] , x , -1 );
		ans -= Query( x );
	}
	
	return 0;
}
