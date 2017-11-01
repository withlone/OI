#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

const int MAXN = 1e6 +1;

int n,m,l,B;
int A[MAXN];
vector<int> Seq[MAXN];

int main(){
	
	Read( n );
	for( int i=1;i<=n;i++ ){
		Read( A[i] );
		Seq[A[i]].push_back( i );
	}
	Read( m );
	while( m-- ){
		Read( l );
		bool Flag = 1;
		for( int i=1,Last=1;i<=l;i++ ){
			Read( B );
			int t = lower_bound( Seq[B].begin(),Seq[B].end(),Last ) - Seq[B].begin();
			if( Seq[B].end()-Seq[B].begin()==t )Flag = 0;
			else Last = Seq[B][t]+1;
		}
		puts( Flag?"TAK":"NIE" );
	}
	return 0;
}
