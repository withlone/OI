#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 1e3 + 10;

int n , son , rt;
int num[maxn];bool mp[maxn][maxn];
int A[maxn] , B[maxn] , d[maxn] , cnt;

int H[maxn] , Nt[maxn] , To[maxn] , Ct;

void Ins( int x , int y ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
}

int dfn[maxn] , Low[maxn] , sum[maxn];bool V[maxn];
void tarjan( int x , int f ){
	dfn[x] = Low[x] = ++Ct;
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( y == f )continue;
		if( !dfn[y] ){
			tarjan( y , x );
			Low[x] = min( Low[x] , Low[y] );
			if( rt == x )++son;
			if( Low[y] >= dfn[x] )
				V[x] = true;
		}
		else Low[x] = min( Low[x] , dfn[y] );
	}
}

int Fa[maxn];
int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int main(){
	
	int T = 0;
	
	while( Read( n ) , ++T , n ){
		
		int cutp = Ct = cnt = 0;
		
		For( i , 1 , n )
			Read( A[i] ) , Read( B[i] ) ,
			d[ ++cnt ] = A[i] , d[ ++cnt ] = B[i];
		
		sort( 1 + d , 1 + cnt + d );
		cnt = unique( 1 + d , 1 + cnt + d ) - d - 1;
		
		For( i , 1 , cnt )num[i] = sum[i] = dfn[i] = Low[i] = V[i] = H[i] = 0 , Fa[i] = i;
		
		For( i , 1 , n ){
			A[i] = lower_bound( 1 + d , 1 + cnt + d , A[i] ) - d;
			B[i] = lower_bound( 1 + d , 1 + cnt + d , B[i] ) - d;
			Ins( A[i] , B[i] );Ins( B[i] , A[i] );
		}
		
		Ct = 0;
		For( i , 1 , cnt )if( !dfn[i] ){
			rt = i;son = 0;
			tarjan( i , 0 );
			V[i] = ( son > 1 );
		}
		
		For( i , 1 , cnt )if( V[i] )++cutp;
		
		if( !cutp ){
			printf("Case %d: 2 %lld\n",T , 1LL * cnt * ( cnt - 1 ) >> 1);
			continue;
		}
		
		For( i , 1 , n )
			if( !V[ A[i] ] && !V[ B[i] ] )Fa[ Find( A[i] ) ] = Find( B[i] );
		
		memset( mp , 0 , sizeof mp );
		
		For( i , 1 , n ){
			int fx = Find( A[i] ) , fy = Find( B[i] );
			if( V[fx] ^ V[fy] && !mp[fx][fy] ){
				mp[fx][fy] = mp[fy][fx] = true;
				if( !V[fx] )num[fx]++;
				else num[fy]++;
			}
		}
		
		Ct = 0;
		For( i , 1 , cnt ){
			sum[ Find( i ) ]++;
			if( Find( i ) == i && !V[i] && num[i] == 1 )++Ct;
		}
		LL ans = 1;
		
		For( i , 1 , cnt )if( Find( i ) == i && !V[i] && num[i] == 1 )ans *= sum[i];
		
		printf("Case %d: %d %lld\n",T , Ct , ans);
	}
	
	return 0;
}
