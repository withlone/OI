#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _begin , _end ) for( int i = (_begin) , i##end = _end ; i <= (i##end) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 101;
static const int MAXM = MAXN << 1;

struct data{
	double x1 , x2 , y;int f;
	bool operator < ( data tmp ) const { return y < tmp.y; }
}d[MAXM];

int T , n , m , Ct;
double x1 , y1 , x2 , y2;
double pos[MAXM];

double Sum[MAXM << 2] , Lz[MAXM << 2];

void modify( int rt , int l , int r , int L , int R , int f ){
	if( l > R || r < L )return;
	if( l >= L && r <= R ){
		Lz[rt] += f;
		Sum[rt] = ( Lz[rt] <= 0 && l != r ) * ( Sum[ rt<<1 ] + Sum[ rt<<1|1 ] ) + ( Lz[rt] > 0 ) * ( pos[r+1] - pos[l] );
		return ;
	}
	int mid = l + r >> 1;
	modify( rt<<1 , l , mid , L , R , f );modify( rt<<1|1 , mid + 1 , r , L , R , f );
	Sum[rt] = ( Lz[rt] <= 0 && l != r ) * ( Sum[ rt<<1 ] + Sum[ rt<<1|1 ] ) + ( Lz[rt] > 0 ) * ( pos[r+1] - pos[l] );
}

int main(){
	
	while( scanf("%d",&n) , ++T , n ){
		double ans = Ct = 0;m = 1;
		For( i , 1 , n ){
			scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
			d[ ++Ct ] = (data){ x1 , x2 , y1 , 1 };
			d[ ++Ct ] = (data){ x1 , x2 , y2 , -1 };
			pos[ Ct-1 ] = x1;pos[ Ct ] = x2;
		}
		sort( 1 + d , 1 + Ct + d );
		sort( 1 + pos , 1 + Ct + pos );
		For( i , 2 , Ct )
			if( pos[i] != pos[i-1] )pos[ ++m ] = pos[i];
		For( i , 1 , Ct ){
			int l = lower_bound( 1 + pos , 1 + m + pos , d[i].x1 ) - pos;
			int r = lower_bound( 1 + pos , 1 + m + pos , d[i].x2 ) - pos - 1;
			if( i != 1 )ans += Sum[1] * ( d[i].y - d[i-1].y );
			modify( 1 , 1 , m , l , r , d[i].f );
		}
		printf("Test case #%d\nTotal explored area: %.2lf\n\n",T,ans);
	}
	
	return 0;
}
