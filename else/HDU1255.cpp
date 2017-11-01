#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _begin , _end ) for( int i = (_begin) , i##end = _end ; i <= (i##end) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e3 + 1;
static const int MAXM = MAXN << 1;

struct data{
	double x1 , x2 , y;int f;
	bool operator < ( data tmp ) const { return y < tmp.y; }
}d[MAXM];

int T , n , m;
double x1 , y1 , x2 , y2;
double pos[MAXM];

double Sum[MAXM << 2] , Lz[MAXM << 2] , Tot[MAXM << 2];

void Up( int rt , int l , int r ){
	if( Lz[rt] >= 2 )Sum[rt] = Tot[rt] = pos[r+1] - pos[l];
	else if( Lz[rt] == 1 )Tot[rt] = pos[r+1] - pos[l] , Sum[rt] = ( l != r ) * ( Tot[ rt<<1 ] + Tot[ rt<<1|1 ] );
	else Tot[rt] = ( l != r ) * ( Tot[ rt<<1 ] + Tot[ rt<<1|1 ] )
		,Sum[rt] = ( l != r ) * ( Sum[ rt<<1 ] + Sum[ rt<<1|1 ] );
}

void modify( int rt , int l , int r , int L , int R , int f ){
	if( l > R || r < L )return;
	if( l >= L && r <= R ){
		Lz[rt] += f;
		Up( rt , l , r );
		return ;
	}
	int mid = l + r >> 1;
	modify( rt<<1 , l , mid , L , R , f );modify( rt<<1|1 , mid + 1 , r , L , R , f );
	Up( rt , l , r );
}

int main(){
	
	scanf("%d",&T);
	
	while( T-- ){
		scanf("%d",&n);
		double ans = 0;
		For( i , 1 , n ){
			scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
			d[ i ] = (data){ x1 , x2 , y1 , 1 };
			d[ i + n ] = (data){ x1 , x2 , y2 , -1 };
			pos[ i ] = x1;pos[ i + n ] = x2;
		}
		n <<= 1;
		sort( 1 + d , 1 + n + d );
		sort( 1 + pos , 1 + n + pos );
		m = unique( 1 + pos , 1 + n + pos ) - pos - 1;
		For( i , 1 , n ){
			int l = lower_bound( 1 + pos , 1 + m + pos , d[i].x1 ) - pos;
			int r = lower_bound( 1 + pos , 1 + m + pos , d[i].x2 ) - pos - 1;
			if( i != 1 )ans += Sum[1] * ( d[i].y - d[i-1].y );
			modify( 1 , 1 , m , l , r , d[i].f );
		}
		printf("%.2lf\n",ans);
	}
	
	return 0;
}
