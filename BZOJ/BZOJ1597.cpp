#include<cstdio>
#include<algorithm>

using std :: sort;

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

typedef long long LL;
static const int MAXN = 5e4 +1;

struct Sort{
	int A , B;
	bool operator < ( Sort x )const{ return A < x.A || A == x.A && B < x.B; }
}Data[MAXN];

int n , Ct;
LL f[MAXN];
int A[MAXN] , B[MAXN];
int Que[MAXN] , H , T;

LL Dp();
LL Up( int , int );
LL Down( int , int );
void Init();

int main(){
	
	Init();
	
	printf("%lld\n",Dp());
	
	return 0;
}

void Init(){
	Read( n );
	For( i , 1 , n )Read( Data[i].A ) , Read( Data[i].B );
	sort( 1 + Data , 1 + n + Data );
	For( i , 1 , n ){
		while( Ct && Data[i].B >= B[Ct] )Ct--;
		Ct++;A[Ct] = Data[i].A;B[Ct] = Data[i].B;
	}
	n = Ct;
}
LL Up( int x , int y ){ return f[x] - f[y]; }
LL Down( int x , int y ){ return B[y+1] - B[x+1]; }
LL Dp(){
	For( i , 1 , n ){
		while( H < T && Up( Que[H+1] , Que[H] ) <= A[i] * Down( Que[H+1] , Que[H] ) )H++;
		f[i] = f[Que[H]] + 1LL*A[i]*B[Que[H]+1];
		while( H < T && Up( i , Que[T] ) * Down( Que[T] , Que[T-1] ) <= Up( Que[T] , Que[T-1] ) * Down( i , Que[T] ) )T--;
		Que[++T] = i;
	}
	return f[n];
}
