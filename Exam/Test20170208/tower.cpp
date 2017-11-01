#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN = 11;
#define T_At(i) make_pair( Tow[i][1],Tow[i][2] )

int n,m,q,Sx,Sy,Ex,Ey,Tsize;
int Ag[MAXN],R[MAXN],Hp[MAXN],S[MAXN],Die[MAXN],Life[MAXN];
int Tow[MAXN*MAXN][3],Pt[MAXN*MAXN];
pair<int,int> Nt[MAXN][MAXN],At[MAXN],St,En;
int Mx[] = {0,1,0,-1};
int My[] = {1,0,-1,0};
char Map[MAXN][MAXN];
bool Vis[MAXN][MAXN];

int Dis( pair<int,int> A,pair<int,int> B ){
	return abs( A.first-B.first ) + abs( A.second-B.second );
}
int Get_Near( int Num ){
	for( int i=1;i<=q;i++ )
		if( !Die[i] )
			if( Dis( T_At(Num),At[i] )<=R[Tow[Num][0]] )return i;
	return 0;
}
bool Check(){
	for( int i=1;i<=q;i++ )
		if( !Die[i]||Die[i]==-1 )return false;
	return true;
}

void Life_Recovery(){
	for( int i=1;i<=q;i++ )
		if( !Die[i] )Life[i] = min( Hp[i],S[i]+Life[i] );
}
void Mov(){
	for( int i=1;i<=q;i++ )
		if( !Die[i] )
			At[i] = Nt[At[i].first][At[i].second];
}
void New_Life( int Rd ){
	if( Rd<=q ){
		Die[Rd] = 0;
		At[Rd] = St;
	}
}
void Lock(){
	for( int i=1;i<=Tsize;i++ )
		if( !Pt[i]||Dis( T_At(i),At[Pt[i]])>R[Tow[i][0]]||Die[Pt[i]] )Pt[i] = Get_Near( i );
}
void Hurt_Calc(){
	for( int i=1;i<=Tsize;i++ ){
		if( !Pt[i] )continue;
		Life[Pt[i]] -= Ag[Tow[i][0]];
	}
}
void Dying( int Rd ){
	for( int i=1;i<=q;i++ )
		if( !Die[i] )
			if( Life[i]<=0 )Die[i] = Rd;
}
void Arrive(){
	for( int i=1;i<=q;i++ )
		if( !Die[i] )
			if( At[i]==En )Die[i] = -2;
}

void Game_Start(){
	Vis[Sx][Sy] = true;Map[Ex][Ey] = '0';
	int x = Sx,y = Sy;
	while( x!=Ex||y!=Ey ){
		for( int i=0;i<4;i++ ){
			int X = x + Mx[i],Y = y + My[i];
			if( Map[X][Y]!='0'||Vis[X][Y] )continue;
			Nt[x][y] = make_pair( X,Y );
			x = X;y = Y;
			Vis[x][y] = true;
		}
	}
	Map[Ex][Ey] = 'T';
	memset( Die,-1,sizeof Die );
	for( int i=1;i<=q;i++ )Life[i] = Hp[i];
	St.first = Sx;St.second = Sy;
	En.first = Ex;En.second = Ey;
}
void Game_Ing(){
	for( int Rd=1;!Check();Rd++ ){
		First:  Life_Recovery();
		Second: Mov();
		Third:  New_Life(Rd);
		Fourth: Lock();
		Fifth:  Hurt_Calc();
		Sixth:  Dying(Rd);
		Seventh:Arrive();
	}
}
void Game_End(){
	for( int i=1;i<=q;i++ )
		if( Die[i]==-2 )printf("Never!\n");
		else printf("%d\n",Die[i]);
}

void Game(){
	Game_Start();
	Game_Ing();
	Game_End();
}

int main(){
	
	freopen("tower.in","r",stdin);
	freopen("tower.out","w",stdout);
	scanf("%d%d",&n,&m);
	for( int i=1;i<=n;i++ ){
		scanf("%s",Map[i]);
		for( int j=m;j>=1;j-- )Map[i][j] = Map[i][j-1];
		Map[i][0] = ' ';
		for( int j=1;j<=m;j++ ){
			if( Map[i][j]=='S' )Sx = i,Sy = j;
			if( Map[i][j]=='T' )Ex = i,Ey = j;
			if( Map[i][j]>='1'&&Map[i][j]<='9' ){
				Tow[++Tsize][0] = Map[i][j]-'0';Tow[Tsize][1] = i;Tow[Tsize][2] = j;
			}
		}
	}
	for( int i=1;i<=9;i++ )scanf("%d%d",&Ag[i],&R[i]);
	scanf("%d",&q);
	for( int i=1;i<=q;i++ )scanf("%d%d",&Hp[i],&S[i]);
	Game();
	return 0;
}
