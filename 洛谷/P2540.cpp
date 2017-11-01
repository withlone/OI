#include<cstdio>
#include<cstring>
#include<algorithm>

using std :: pair ;
using std :: make_pair ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )
#define FOR( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define LOP( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define REP( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type max( const type& x , const type& y ) { return x > y ? x : y ; }
template < typename type >
inline type min( const type& x , const type& y ) { return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , const type& y ) {
	return x >= y ? false : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x <= y ? false : ( x = y , true ) ;
}

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 29 ;
static const int maxm = 17 ;

int cases ;
int n ;
int ans ;
int able1 ;
int able2 ;

pair < int , int > emp ;

int ai[maxn] ;
int bi[maxn] ;

int cd[maxm] ;

inline bool chk_rocket( int *card ) {
	return card[0] & card[1] ;
}

inline bool chk_bomb( int *card , const int& x ) {
	return card[x] == 4 ;
}

inline bool chk_single( int *card , const int& x ) {
	return card[x] ;
}

inline bool chk_couple( int *card , const int& x ) {
	return card[x] >= 2 ;
}

inline bool chk_three( int *card , const int& x ) {
	return card[x] >= 3 ;
}

inline bool chk_empty( int *card ) {
	static int cder[maxm] ;
	memcpy( cder , card , sizeof cder ) ;
	int tot = 0 , t1 = able1 , t2 = able2 ;
	FOR( i , 2 , 14 ) {
		if( !t2 )break ;
		if( cder[i] == 4 )cder[i] -= 4 , t2-- ;
		else if( chk_couple( cder , i ) ) {
			if( !tot )tot = i ;
			else {
				cder[tot] -= 2 ;
				cder[i] -= 2 ;
				t2-- ;
				tot = 0 ;
			}
		}
	}
	FOR( i , 2 , 14 ) {
		if( !t1 )break ;
		if( chk_couple( cder , i ) ) {
			t1-- ;
			cder[i] -= 2 ;
		}
	}
	tot = 0 ;
	FOR( i , 0 , 14 ) tot += cder[i] ;
	tot -= ( t2 << 1 ) ;
	if( tot < 0 )tot += 2 ;
	if( tot <= t1 ) return true ;
	return false ;
}

inline int find_single( int *card , int start = 0 ) {
	FOR( i , start , 14 )
		if( card[i] == 1 ) return i ;
	FOR( i , 2 , 14 )
		if( card[i] ) return i ;
	FOR( i , 0 , 1 )
		if( card[i] ) return i ;
	return -1 ;
}

inline int find_couple( int *card , int start = 2 ) {
	FOR( i , start , 14 )
		if( card[i] >= 2 ) return i ;
	return 0 ;
}

inline int find_three( int *card , int start = 2 ) {
	FOR( i , start , 14 )
		if( card[i] >= 3 ) return i ;
	return 0 ;
}

inline int find_bomb( int *card , int start = 2 ) {
	FOR( i , start , 14 )
		if( card[i] == 4 ) return i ;
	return 0 ;
}

inline pair < int , int > find_one_line( int *card , int start = 3 ) {
	int stt = start ;
	FOR( i , start , 15 )
		if( !chk_single( card , i ) ) {
			if( i - stt >= 5 ) return make_pair( stt , i - 1 ) ;
			else stt = i + 1 ;
			if( 14 - stt + 1 < 5 ) return emp ;
		}
	return emp ;
}

inline pair < int , int > find_two_line( int *card , int start = 3 ) {
	int stt = start ;
	FOR( i , start , 15 )
		if( !chk_couple( card , i ) ) {
			if( i - stt >= 3 ) return make_pair( stt , i - 1 ) ;
			else stt = i + 1 ;
		}
	return emp ;
}

inline pair < int , int > find_three_line( int *card  , int start = 3 ) {
	int stt = start ;
	FOR( i , start , 15 )
		if( !chk_three( card , i ) ) {
			if( i != stt ) return make_pair( stt , i - 1 ) ;
			else stt = i + 1 ;
		}
	return emp ;
}

inline void dfs( int dep ) {
	if( dep >= ans )return ;
	if( chk_empty( cd ) )return ans = dep , void() ;
	pair < int , int > t = find_one_line( cd ) ;
	while( t != emp ) {
		FOR( i , t.first , t.second )cd[i]-- ;
		dfs( dep + 1 ) ;
		FOR( i , t.first , t.second )cd[i]++ ;
		if( t.second - t.first + 1 > 5 )t.second-- ;
		else t = emp ;
	}
	t = find_two_line( cd ) ;
	while( t != emp ) {
		FOR( i , t.first , t.second )cd[i] -= 2 ;
		dfs( dep + 1 ) ;
		FOR( i , t.first , t.second )cd[i] += 2 ;
		if( t.second - t.first + 1 > 3 )t.second-- ;
		else t = emp ;
	} 
	t = find_three_line( cd ) ;
	while( t != emp ) {
		FOR( i , t.first , t.second )cd[i] -= 3 ;
		dfs( dep + 1 ) ;
		FOR( i , t.first , t.second )cd[i] += 3 ;
		if( t.second - t.first + 1 > 2 )t.second-- ;
		else t = emp ;
	}
	int x = find_three( cd ) ;
	if( x ) {
		cd[x] -= 3 ;
		able1++ ;
		dfs( dep + 1 ) ;
		able1-- ;
		cd[x] += 3 ;
	}
	x = find_couple( cd ) ;
	if( x )
		cd[x] -= 2 , dfs( dep + 1 ) , cd[x] += 2 ;
	x = find_bomb( cd ) ;
	if( x ) {
		cd[x] -= 4 ;
		++able2 ;
		dfs( dep + 1 ) ;
		--able2 ;
		cd[x] += 4 ;
	}
	if( chk_rocket( cd ) )
		cd[0]-- , cd[1]-- , dfs( dep + 1 ) , cd[0]++ , cd[1]++ ;
	x = find_single( cd ) ;
	if( x != -1 )
		cd[x]-- , dfs( dep + 1 ) , cd[x]++ ;
}

int main() {
	
	emp = make_pair( 0 , 0 ) ;
	
	scanf( cases ) ; scanf( n ) ;
	
	while( cases-- ) {
		memset( cd , 0 , sizeof cd ) ;
		able1 = able2 = 0 ;
		FOR( i , 1 , n ) {
			scanf( ai[i] ) , scanf( bi[i] ) ;
			if( ai[i] == 1 )cd[14]++ ;
			else if( ai[i] )cd[ ai[i] ]++ ;
			else cd[ bi[i] - 1 ]++ ;
		}
		ans = n ;
		dfs( 0 ) ;
		printf( "%d\n" , ans ) ;
	}
	
	return 0 ;
}
