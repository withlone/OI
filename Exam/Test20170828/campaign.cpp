#include<cmath>
#include<cstdio>

using namespace std;

#define For( i , _begin , _end ) for( LL i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )
#define Rep( i , _begin , _add ) for( LL i = (_begin) ; i ; i = (_add) )

template< typename type >inline void scanf( type &in ){
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ; ch > '9' || ch < '0' ; ch = getchar() )if( ch == '-' )f = -1 ;
	for( ; ch >='0' && ch <='9' ; ch = getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

typedef long long LL;
typedef double DB;

LL S;
LL A;
LL W;
LL P;
LL B;
DB CC;
LL C;
LL K;
LL ans_a;
LL ans_b;
LL ans_c;
LL ans;

void read_in(){
	scanf( S ) ; scanf( A ) ; scanf( W ) ; scanf( P ) ;
	scanf( B ) ; scanf( "%lf" , &CC ) ; scanf( K ) ; C = 100 * CC ;
}

LL calc( LL xa , LL xb , LL xc ){
	return 1LL * ( W + xa * P ) * ( xb + 1 ) * ( 1e4 + C * xc * ( K - 1 ) );
}

LL Get( LL x ){ return abs( x - A ) ; }

void work1( LL xa , LL xb ){
	if( xb < 0 )return;
	LL xc = S - xa - xb * B ;
	if( Get( calc( xa , xb , xc ) ) < Get( ans ) ){
		ans = calc( xa , xb , xc ) ;
		ans_a = xa ; ans_b = xb ; ans_c = xc ;
	}
}

void work2( LL xb , LL xa ){
	if( xa < 0 )return;
	LL xc = S - xa - xb * B ;
	if( Get( calc( xa , xb , xc ) ) < Get( ans ) ){
		ans = calc( xa , xb , xc ) ;
		ans_a = xa ; ans_b = xb ; ans_c = xc ;
	}
}

void Enum(){
	For( xa , 0 , 1e7 ){
		DB A0 , C0 , a , b , c , x1 , x2 ;
		LL t1 , t2 , t3 , t4;
		First :
			if( A % ( W + xa * P ) )goto Second ;
			A0 = A / ( W + xa * P ) ;
			C0 = 1e4 + C * ( K - 1 ) * ( S - xa ) ;
			a = C * ( K - 1 ) * B;
			b = C * ( K - 1 ) * B - C0;
			c = A0 - C0;
			x1 = ( -b + sqrt( b * b - 4 * a * c ) ) / ( 2 * a );
			x2 = ( -b - sqrt( b * b - 4 * a * c ) ) / ( 2 * a );
			t1 = floor( x1 ) , t2 = ceil( x1 ) , t3 = floor( x2 ) , t4 = ceil( x2 ) ;
			work1( xa , t1 );work1( xa , t2 );
			work1( xa , t3 );work1( xa , t4 );
		Second :
			LL xb = xa ;
			if( A % ( xb + 1 ) )goto end ;
			A0 = A / ( xb + 1 );
			C0 = 1e4 + C * ( K - 1 ) * ( S - B * xb );
			a = P * C * ( K - 1 );
			b = W * C * ( K - 1 ) - C0 * P;
			c = A0 - W * C0;
			x1 = ( -b + sqrt( b * b - 4 * a * c ) ) / ( 2 * a );
			x2 = ( -b - sqrt( b * b - 4 * a * c ) ) / ( 2 * a );
			t1 = floor( x1 ) , t2 = ceil( x1 ) , t3 = floor( x2 ) , t4 = ceil( x2 ) ;
			work2( xb , t1 );work2( xb , t2 );
			work2( xb , t3 );work2( xb , t4 );
		end :
		if( ans == A )return;
	}
}

void display(){
	printf("%lld %lld %lld\n" , ans_a , ans_b , ans_c ) ;
}

int main(){
	
	freopen("campaign.in","r",stdin);
	freopen("campaign.out","w",stdout);
	
	read_in();
	
	Enum();
	
	display();
	
	return 0;
}
