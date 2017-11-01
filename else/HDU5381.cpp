#include<cmath>
#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 1e4 +1;

int Case , n , m , Fac;
int A[maxn] , BL[maxn];
int v[maxn] , w[maxn];
int size1[maxn] , size2[maxn];
int LG[maxn][15] , RG[maxn][15] , Lp[maxn][15] , Rp[maxn][15];
LL ans[maxn] , sum;

struct Query{
	int l , r , id;
	bool operator < ( Query t ) const { return BL[l] < BL[t.l] || BL[l] == BL[t.l] && r < t.r; }
}Q[maxn];

int Gcd( int x , int y ){ return !y ? x : Gcd( y , x % y ) ; }

void unique( int &Cnt ){
	int t = 0;
	For( i , 1 , Cnt )
		if( v[i] != v[t] )
			v[ ++t ] = v[i] , w[t] = w[i];
	Cnt = t;
}

void Init(){
	int Cnt = 0;
	For( i , 1 , n ){
		For( j , 1 , Cnt )v[j] = Gcd( A[i] , v[j] );
		v[ ++Cnt ] = A[i];w[ Cnt ] = i;
		unique( Cnt );
		For( j , 1 , size1[i] = Cnt ){
			LG[i][j] = v[ Cnt - j + 1 ];
			Lp[i][j] = w[ Cnt - j + 1 ];
		}
	}
	Cnt = 0;
	Lop( i , n , 1 ){
		For( j , 1 , Cnt )v[j] = Gcd( A[i] , v[j] );
		v[ ++Cnt ] = A[i];w[ Cnt ] = i;
		unique( Cnt );
		For( j , 1 , size2[i] = Cnt ){
			RG[i][j] = v[ Cnt - j + 1 ];
			Rp[i][j] = w[ Cnt - j + 1 ];
		}
	}
}

int main(){
	
	Read( Case );
	
	while( Case-- ){
		Read( n );Fac = sqrt( n + 0.5 );
		For( i , 1 , n )Read( A[i] ) , BL[i] = i / Fac;
		Read( m );
		For( i , 1 , m )Read( Q[i].l ) , Read( Q[i].r ) , Q[i].id = i;
		
		sort( 1 + Q , 1 + m + Q );
		
		Init();
		
		int l = 1 , r = 0;sum = 0;
		For( i , 1 , m ){
			while( r < Q[i].r ){
				++r;
				int last = r + 1;
				For( j , 1 , size1[r] )
					if( l > Lp[r][j] ){ sum += 1LL * ( Lp[r][j - 1] - l ) * LG[r][j];break; }
					else sum += 1LL * ( last - Lp[r][j] ) * LG[r][j] , last = Lp[r][j];
			}
			while( l > Q[i].l ){
				--l;
				int last = l - 1;
				For( j , 1 , size2[l] )
					if( r < Rp[l][j] ){ sum += 1LL * ( r - Rp[l][j - 1] ) * RG[l][j];break; }
					else sum += 1LL * ( Rp[l][j] - last ) * RG[l][j] , last = Rp[l][j];
			}
			while( r > Q[i].r ){
				int last = r + 1;
				For( j , 1 , size1[r] )
					if( l > Lp[r][j] ){ sum -= 1LL * ( Lp[r][j - 1] - l ) * LG[r][j];break; }
					else sum -= 1LL * ( last - Lp[r][j] ) * LG[r][j] , last = Lp[r][j];
				--r;
			}
			while( l < Q[i].l ){
				int last = l - 1;
				For( j , 1 , size2[l] )
					if( r < Rp[l][j] ){ sum -= 1LL * ( r - Rp[l][j - 1] ) * RG[l][j];break; }
					else sum -= 1LL * ( Rp[l][j] - last ) * RG[l][j] , last = Rp[l][j];
				++l;
			}
			ans[ Q[i].id ] = sum;
		}
		
		For( i , 1 , m )printf("%lld\n",ans[i]);
		
	}
	
	return 0;
}
