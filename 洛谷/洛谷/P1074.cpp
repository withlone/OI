#include<cstdio>
#include<algorithm>
using namespace std;

#define For(i) for( int i=0;i<9;i++ )

int At[9][9]={
{0,0,0,1,1,1,2,2,2},
{0,0,0,1,1,1,2,2,2},
{0,0,0,1,1,1,2,2,2},
{3,3,3,4,4,4,5,5,5},
{3,3,3,4,4,4,5,5,5},
{3,3,3,4,4,4,5,5,5},
{6,6,6,7,7,7,8,8,8},
{6,6,6,7,7,7,8,8,8},
{6,6,6,7,7,7,8,8,8}
};
int Poi[9][9]={
{6,6,6,6,6,6,6,6,6},
{6,7,7,7,7,7,7,7,6},
{6,7,8,8,8,8,8,7,6},
{6,7,8,9,9,9,8,7,6},
{6,7,8,9,10,9,8,7,6},
{6,7,8,9,9,9,8,7,6},
{6,7,8,8,8,8,8,7,6},
{6,7,7,7,7,7,7,7,6},
{6,6,6,6,6,6,6,6,6}
};
int A[9][9],Num,Ans=-1,Cmp=(1<<9)-1;
int l[9],r[9],s[9],Row[9],Line[1<<10|1],Cnt[9],Rank[9];

void Get(){
	int Sum = 0;
	For(i)For(j)Sum += A[i][j]*Poi[i][j];
	Ans = max( Ans,Sum );
}

void Dfs( int Deep ){
	if( Deep==9 ){Get();return;}
	if( !Cnt[Rank[Deep]] ){Dfs( Deep+1 );return;}
	int D = Rank[Deep];
	int p = Cmp ^ Row[D];
	int t = p&-p;
	int k = Cmp ^ (l[D]|r[Line[t]]|s[At[D][Line[t]]]);
	Row[D] |= t;
	Cnt[D]--;
	while( k ){
		int n = k&-k;
		k ^= n;
		l[D] |= n;
		r[Line[t]] |= n;
		s[At[D][Line[t]]] |= n;
		A[D][Line[t]] = Line[n]+1;
		Dfs( Deep );
		l[D] ^= n;
		r[Line[t]] ^= n;
		s[At[D][Line[t]]] ^= n;
	}
	Row[D] ^= t;
	Cnt[D]++;
}

int main(){

	for( int i=1,j=0;j<=9;j++,i<<=1 )Line[i] = j;
	For(i)For(j){
		scanf("%d",&A[i][j]);
		if( A[i][j] ){
			int p = 1<<j,t = 1<<A[i][j]-1,k = At[i][j];
			if( l[i]&t||r[j]&t||s[k]&t )return printf("-1\n"),0;
			Row[i] |= p;
			l[i] |= t;
			r[j] |= t;
			s[k] |= t;
		}
		else Cnt[i]++;
	}
	for( int i=0;i<9;i++ )Rank[i] = i;
	for( int i=0;i<9;i++ )for( int j=i+1;j<9;j++ )if( Cnt[Rank[i]]>Cnt[Rank[j]] )swap( Rank[i],Rank[j] );
	Dfs( 0 );
	printf("%d\n",Ans);
	return 0;
}
