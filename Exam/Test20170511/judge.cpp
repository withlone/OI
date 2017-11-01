#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 2e5 +1;
typedef long long LL;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

int n;LL m,Sum,Tmp,Ans;
LL A[MAXN];

bool Cmp( int x , int y ){return x>y;}

#define Judge

int main(){
	
	#ifdef Judge
		freopen("judge.in","r",stdin);
		freopen("judge.out","w",stdout);
	#endif
	
	Read( m );Read( n );
	For( i , 1 , n )Read( A[i] );
	sort( 1+A , 1+n+A , Cmp );
	
	For( i , 2 , n )
		if( Tmp +  1LL*(i-1)*( A[i-1]-A[i] )<=m )
			Tmp += 1LL*(i-1)*( A[i-1]-A[i] );
		else{
			LL t = m - Tmp;
			For( j , 1 , i-1 )A[j] = A[i-1] - t/(i-1);
			t %= i-1;
			sort( 1+A , 1+A+n , Cmp );
			For( j , 1 , t )A[j]--;
			m = 0;
			break;
		}
	if( m ){
		m -= Tmp;
		For( i , 1 , n-1 )A[i] = A[n];
		For( i , 1 , n )A[i] -= m/n;
		m %= n;
		sort( 1+A , 1+A+n , Cmp );
		For( i , 1 , m )A[i]--;
	}
	For( i , 1 , n )Ans += A[i]*A[i];
	printf("%lld\n",Ans);
	return 0;
}
