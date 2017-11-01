#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e6 +1;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
#define Lc p<<1
#define Rc Lc|1
#define Lson Lc,l,Mid
#define Rson Rc,Mid+1,r

int n,m,d,s,t;bool Flag;
int Min[MAXN<<2],Lazy[MAXN<<2];

void Up( int p ){ Min[p] = min( Min[Lc],Min[Rc] ); }
void Build( int p,int l,int r ){
	if( l==r ){
		Read( Min[p] );
		return;
	}
	int Mid = l+r >>1;
	Build( Lson );Build( Rson );
	Up( p );
}
void Pd( int p ){
	if( !Lazy[p] )return;
	Lazy[Lc] += Lazy[p];
	Lazy[Rc] += Lazy[p];
	Min[Lc] -= Lazy[p];
	Min[Rc] -= Lazy[p];
	Lazy[p] = 0;
}
void Mf( int p,int l,int r,int L,int R,int k ){
	if( l> R||r< L )return;
	if( l>=L&&r<=R ){
		Lazy[p] += k;
		Min[p] -= k;
		if( Min[p]<0 )Flag = 1;
		return;
	}
	Pd( p );
	int Mid = l+r >>1;
	Mf( Lson , L , R , k );Mf( Rson , L , R , k );
	Up( p );
}

int main(){
	
	Read( n );Read( m );
	Build( 1 , 1 , n );
	For( i , 1 , m ){
		Read( d ),Read( s ),Read( t );
		Mf( 1 , 1 , n , s , t , d );
		if( Flag )
			return printf("-1\n%d\n",i) , 0;
	}
	puts("0");
	return 0;
}
