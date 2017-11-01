#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
typedef unsigned int UI;
static const UI mod = 1 << 31;
static const int maxn = 1e5 + 10;
static const int maxm = 2e4 + 10;

int n;
int top;

struct query{
	int n;
	int m;
	int A;
	int id;
	bool operator < ( query t ) const { return A < t.A; }
}Q[maxm];

bool V[maxn];
int mu[maxn];
int cnt;
int pri[maxn];
int ans[maxm];
LL sm[maxn];
pair< LL , int >d[maxn];

void Init(){
	
	sm[1] = mu[1] = 1;
	For( i , 2 , top ){
		if( !V[i] )pri[ ++cnt ] = i , mu[i] = -1 , sm[i] = i + 1;
		For( j , 1 , cnt ){
			int t = pri[j] * i;
			if( t > top )break;
			V[t] = true;
			if( !( i % pri[j] ) ){
				sm[t] = sm[i] + ( sm[i] - sm[ i / pri[j] ] ) * pri[j];
				break;
			}
			mu[t] = -mu[i];
			sm[t] = sm[i] * ( pri[j] + 1 );
		}
	}
	
}

namespace BIT{
	
	LL T[maxn];
	
	int Lowbit( int x ){ return x & -x ; }
	
	void Add( int x , LL y ){
		for( int i = x ; i <= top ; i += Lowbit( i ) )
			T[i] += y;
	}
	
	LL Query( int x ){
		LL Res = 0;
		for( int i = x ; i ; i -= Lowbit( i ) )Res += T[i];
		return Res;
	}
	
}using namespace BIT;

UI Solve( int n , int m ){
	if( n > m )n ^= m ^= n ^= m;
	int Nxt;UI Res = 0;
	for( int i = 1 ; i <= n ; i = Nxt + 1 ){
		Nxt = min( min( n / ( n / i ) , m / ( m / i ) ) , n );
		Res += ( Query( Nxt ) - Query( i - 1 ) ) * ( n / i ) * ( m / i );
	}
	return Res;
}

int main(){
	
	Read( n );
	
	For( i , 1 , n )Read( Q[i].n ) , Read( Q[i].m ) , Read( Q[i].A ) , Q[i].id = i , top = max( top , max( Q[i].n , Q[i].m ) );
	
	sort( 1 + Q , 1 + n + Q );
	
	Init();
	
	For( i , 1 , top )d[i] = make_pair( sm[i] , i );
	
	sort( 1 + d , 1 + top + d );
	
	int pos = 1;
	For( i , 1 , n ){
		while( pos <= top && d[pos].first <= Q[i].A ){
			For( j , 1 , top / d[pos].second )
				Add( d[pos].second * j , sm[ d[pos].second ] * mu[j]  );
			++pos;
		}
		ans[ Q[i].id ] = Solve( Q[i].n , Q[i].m ) & ( mod - 1 );
	}
	
	For( i , 1 , n )printf("%d\n",ans[i]);
	
	return 0;
}
