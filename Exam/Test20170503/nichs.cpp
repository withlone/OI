#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e6 +1;

int m , n , Ct , H , T , Num , Ans;
int A[MAXN] , Que[MAXN];
char s[MAXN];

#define Judge

int main(){
	
	#ifdef Judge
		freopen("nichs.in","r",stdin);
		freopen("nichs.out","w",stdout);
	#endif
	
	Read( m );
	scanf("%s",s);
	n = strlen( s );
	For( i , 1 , n )A[i] = s[i-1] - '0';
	
	H = 1;
	
	For( i , 1 , n ){
		Que[ ++T ] = i;
		Ct += A[i];
		Num += !Ct;
		if( Ct > m ){
			while( Ct > m ){
				Ct -= A[Que[H]];
				H++;
			}
			Num = 0;
			int p = H;
			while( p <= T && !A[Que[p]] )Num++ , p++;
		}
		if( Ct == m )Ans += Num + 1 - !m;
	}
	
	printf("%d\n",Ans);
	return 0;
}
