#include<cstdio>
#include<cstring>
#include<cstdlib>

const int MAXN = 27;

int n,V,Cmp;int Ans[MAXN],Sum[MAXN];
char s[4][MAXN];

struct map{
	static const int Mod = 314159;
	int Hash[ Mod+1 ];
	void Insert( int i,int Val ){
		Hash[i%Mod] = Val;
	}
	int Get( int i ){
		return Hash[i%Mod];
	}
}f;

void Work( int,int );
void Dfs( int );
bool Check( int );

int main(){
	
	freopen( "alpha.in" , "r" , stdin ) ;
	freopen( "alpha.out" , "w" , stdout ) ;
	
	memset( Ans,-1,sizeof Ans );
	scanf("%d",&n);
	for( int i=1,j=0;j<n;j++,i<<=1 )f.Insert( i,n-j-1 );
	Cmp = (1<<n)-1;
	for( int i=1;i<=3;i++ )scanf("%s",s[i]);
	for( int j=0;j<n;j++ )s[1][j] -= 'A',s[2][j] -= 'A',s[3][j] -= 'A';
	Dfs( n-1 );
	return 0;
}

void Work( int Dep,int Num ){
	int t = V^Cmp;
	while( t ){
		int p = t&-t;
		t ^= p;
		V |= p;
		Ans[Num] = f.Get( p );
		Dfs( Dep );
		Ans[Num] = -1;
		V ^= p;
	}
}

bool Check( int Dep ){
	while( Dep-- ){
		if( -1!=Ans[s[1][Dep]]&&-1!=Ans[s[2][Dep]]&&-1!=Ans[s[3][Dep]] ){
			int k = Ans[s[1][Dep]]+Ans[s[2][Dep]],x = Ans[s[3][Dep]];
			if( (k+1)%n==x||k%n==x/*||(k+n-1)%n==x*/ )continue;
			return true;
		}
	}
	return false;
}

void Dfs( int Dep ){
	if( Dep==-1 ){
		for( int i=0;i<n;i++ )printf("%d ",Ans[i]);
		exit(0);
	}
	if( Check( Dep ) )return;
	if( -1==Ans[s[1][Dep]] )Work( Dep,s[1][Dep] );
	if( -1==Ans[s[2][Dep]] )Work( Dep,s[2][Dep] );
	int t = 0;
	for( int i=n-1;i>Dep;i-- )
		t = (t+Ans[s[1][i]]+Ans[s[2][i]])/n;
	if( -1==Ans[s[3][Dep]] ){
		int T = ( t+Ans[s[1][Dep]]+Ans[s[2][Dep]] )%n;
		int p = 1<<(n-1-T);
		if( p&V||f.Get( p )!=T )return;
		V |= p;
		Ans[s[3][Dep]] = T;
		Dfs( Dep-1 );
		Ans[s[3][Dep]] = -1;
		V ^= p;return;
	}
	if( ((t+Ans[s[1][Dep]]+Ans[s[2][Dep]])%n)!=Ans[s[3][Dep]]
	||-1==Ans[s[1][Dep]]||-1==Ans[s[2][Dep]]||-1==Ans[s[3][Dep]] )return;
	Dfs( Dep-1 );
}
