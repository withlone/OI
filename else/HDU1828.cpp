#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i=(_Begin),i##END=(_End);i<=(i##END);i++ )

static const int MAXN = 5e3 +1;
static const int MAXM = MAXN << 1;

int n;
int pos[MAXM];

struct data{
	int x1 , x2 , y , f;
	bool operator < ( data tmp ) const { return y < tmp.y ; }
}d[MAXM];

int Sum[MAXM<<2] , Lz[MAXM<<2] , Num[MAXM<<2];bool left[MAXM<<2] , right[MAXM<<2];
void Up( int rt , int l , int r ){
	Sum[rt] = ( Lz[rt] <= 0 && l != r ) * ( Sum[ rt<<1 ] + Sum[ rt<<1|1 ] ) + ( Lz[rt] > 0 ) * ( pos[r+1] - pos[l] );
	if( Lz[rt] )left[rt] = right[rt] = Num[rt] = 1;
	else if( l == r )left[rt] = right[rt] = Num[rt] = 0;
	else{
		left[rt] = left[ rt<<1 ];
		right[rt] = right[ rt<<1|1 ];
		Num[rt] = Num[ rt<<1 ] + Num[ rt<<1|1 ] - ( left[ rt<<1|1 ] == right[ rt<<1 ] && left[ rt<<1|1 ] == 1 );
	}
}
void modify( int rt , int l , int r , int L , int R , int f ){
	if( l > R || r < L )return;
	if( l >= L && r <= R ){
		Lz[rt] += f;
		Up( rt , l , r );
		return;
	}
	int mid = l + r >> 1;
	modify( rt<<1 , l , mid , L , R , f );modify( rt<<1|1 , mid+1 , r , L , R , f );
	Up( rt , l , r );
}

int main(){
	
	while( scanf("%d",&n) == 1 ){
		For( i , 1 , n ){
			int x1 , x2 , y1 , y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			d[i] = ( data ){ x1 , x2 , y1 , 1 };
			d[i + n] = ( data ){ x1 , x2 , y2 , -1 };
			pos[i] = x1;pos[i + n] = x2;
		}
		n <<= 1;
	
		sort( 1 + d , 1 + n + d );
		sort( 1 + pos , 1 + n + pos );
	
		int m = unique( 1 + pos , 1 + n + pos ) - pos - 1;
		int ans = 0 , last = 0;
		For( i , 1 , n ){
			int l = lower_bound( 1 + pos , 1 + m + pos , d[i].x1 ) - pos;
			int r = lower_bound( 1 + pos , 1 + m + pos , d[i].x2 ) - pos - 1;
			modify( 1 , 1 , m , l , r , d[i].f );
			ans += abs( Sum[1] - last );last = Sum[1];
			if( i != n )ans += 2 * Num[1] * ( d[i+1].y - d[i].y );
		}
		printf("%d\n",ans);
	}
	return 0;
}
