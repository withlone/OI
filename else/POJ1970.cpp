#include<cstdio>

const int MAXN = 20;

int T,Wier,X,Y;
int Map[MAXN][MAXN];
int Mx[]={1,1,0,-1};
int My[]={1,0,1,1};

bool Dfs( int x,int y,int Dir,int A ){
	if( Map[x-Mx[Dir]][y-My[Dir]]==A )return false;
	int Cnt = 0;
	for( ;A==Map[x][y];Cnt++,x+=Mx[Dir],y+=My[Dir] );
	return Cnt==5;
}

void Work( int A ){
	for( int i=1;i<MAXN;i++ )
		for( int j=1;j<MAXN;j++ )
			if( Map[i][j]==A )
				for( int k=0;k<4;k++ ){
					if( Dfs( i,j,k,Map[i][j] ) ){
						Wier = A;
						X = i;Y = j;
						return;
					}
				}
}

int main(){
	
	scanf("%d",&T);
	while( T-- ){
		Wier = 0;
		for( int i=1;i<MAXN;i++ )for( int j=1;j<MAXN;j++ )scanf("%d",&Map[i][j]);
		Work( 1 );if( !Wier )Work( 2 );
		printf("%d\n",Wier);
		if( Wier )printf("%d %d\n",X,Y);
	}
	return 0;
}
