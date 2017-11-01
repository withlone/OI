#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline Type max ( Type x , Type y ){ return x > y ? x : y ; }
template< typename Type >inline void swap( Type &x , Type &y ){ x ^= y ^= x ^= y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e5 + 10;

int T , n , m;
int Idg[maxn];

struct heap{
	
	int T[maxn] , size;
	
	bool empty(){ return !size ; }
	
	void clear(){ T[0] = size = 0 ; }
	
	void push( int x ){
		T[ ++size ] = x;
		int p = size;
		while( p != 1 && T[p] > T[p >> 1] ){
			swap( T[p] , T[p >> 1] );
			p >>= 1;
		}
	}
	
	int top(){ return T[1] ; }
	
	void pop(){
		T[1] = T[ size-- ];
		int p = 1;
		while( ( p << 1 ) <= size && T[p] < max( T[p << 1] , T[p << 1 | 1] ) ){
			int t = ( T[p << 1] > T[p << 1 | 1] ? p << 1 : p << 1 | 1 );
			swap( T[p] , T[t] );
			p = t;
		}
	}
	
}Hp;

int H[maxn] , Nt[maxn] , To[maxn] , Ct;
void Ins( int x , int y ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
}

int seq[maxn] , cnt;

int main(){
	
	Read( T );
	
	while( T-- ){
		
		cnt = Ct = 0;
		
		Read( n );Read( m );
		
		For( i , 1 , n )Idg[i] = H[i] = 0;
		
		For( i , 1 , m ){
			int x , y;
			Read( x );Read( y );
			Ins( y , x );
			++Idg[x];
		}
		
		For( i , 1 , n )
			if( !Idg[i] )Hp.push( i );
		
		cnt = n;
		while( !Hp.empty() ){
			int x = Hp.top();Hp.pop();
			seq[ cnt-- ] = x;
			Rep( i , H[x] , Nt[i] )
				if( !--Idg[ To[i] ] )Hp.push( To[i] );
		}
		
		if( cnt )puts("Impossible!");
		else { For( i , 1 , n )printf("%d ",seq[i]);puts(""); }
		
	}
	
	return 0;
}
