#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define For( i , _Begin , _End ) for( int i = _Begin ; i <= _End ; i++ )

int Res,n;
char Type;char Mp[100];
int Ans[25];
int f[6][6][6][6][6];

bool Ch( int x,int A ){ return !Ans[x]||Ans[x]==A; }

int Dfs( int A,int B,int C,int D,int E,int Alp ){
	if( Alp==25 )return 1;
	if( f[A][B][C][D][E] )return f[A][B][C][D][E];
	if( A<5&&Ch( A   ,Alp+1 ) )f[A][B][C][D][E] += Dfs( A+1,B,C,D,E,Alp+1 );
	if( B<A&&Ch( B+5 ,Alp+1 ) )f[A][B][C][D][E] += Dfs( A,B+1,C,D,E,Alp+1 );
	if( C<B&&Ch( C+10,Alp+1 ) )f[A][B][C][D][E] += Dfs( A,B,C+1,D,E,Alp+1 );
	if( D<C&&Ch( D+15,Alp+1 ) )f[A][B][C][D][E] += Dfs( A,B,C,D+1,E,Alp+1 );
	if( E<D&&Ch( E+20,Alp+1 ) )f[A][B][C][D][E] += Dfs( A,B,C,D,E+1,Alp+1 );
	return f[A][B][C][D][E];
}
#define OnlineJudge
int main(){
	
	#ifdef OnlineJudge
	freopen("twofive.in","r",stdin);
	freopen("twofive.out","w",stdout);
	#endif
	
	Type = getchar();
	while( Type>'Z'||Type<'A' )Type = getchar();
	if( Type=='W' ){
		scanf("%s",Mp);
		For( i , 0 , strlen( Mp ) )
			for( Ans[i]=1;Ans[i]<=Mp[i]-'A';Ans[i]++ ){
				memset( f,0,sizeof f );
				n += Dfs( 0,0,0,0,0,0 );
			}
		printf("%d\n",n+1);
	}
	else{
		scanf("%d",&n);
		For( i , 0 , 24 )
			for( Ans[i]=1;Ans[i]<=25;Ans[i]++ ){
				memset( f,0,sizeof f );
				int p = Dfs( 0,0,0,0,0,0 );
				if( p>=n )break;
				n -= p;
			}
		For( i , 0 , 24 )putchar( Ans[i]+'A'-1 );
	}
	return 0;
}
