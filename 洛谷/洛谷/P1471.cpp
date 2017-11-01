#include<cstdio>

double P(double k){return k*k;}

const int MAXN = 1e5*4 + 1;

int n,m;double R,Var,Tot;
double A[MAXN],V[MAXN],Add[MAXN];

void Up(int k){
	A[k] = A[k<<1] + A[k<<1|1];
	V[k] = V[k<<1] + V[k<<1|1];
}

void Build(int Nd,int l,int r){
	if(l==r){
		scanf("%lf",&A[Nd]);
		V[Nd] = P(A[Nd]);
		return ;
	}
	int Mid = (l+r)>>1;
	Build(Nd<<1  ,l    ,Mid);
	Build(Nd<<1|1,Mid+1,r);
	Up(Nd);
}

void UD(int Nd,int L,int R,int l,int r){
	if(!Add[Nd])return;
	V[Nd<<1]     += l*P(Add[Nd])+2*Add[Nd]*A[Nd<<1];
	V[Nd<<1|1]   += r*P(Add[Nd])+2*Add[Nd]*A[Nd<<1|1];
	A[Nd<<1]     += Add[Nd]*l;
	A[Nd<<1|1]   += Add[Nd]*r;
	Add[Nd<<1]   += Add[Nd];
	Add[Nd<<1|1] += Add[Nd];
	Add[Nd]=0;
}

void Modify(int Nd,int L,int R,int l,int r,double k){
	if(L>r||R<l) return;
	if(L>=l&&R<=r){
		Add[Nd] += k;
		V[Nd]   += (R-L+1)*P(k)+2*k*A[Nd];
		A[Nd]   += k*(R-L+1);
		return ;
	}
	int Mid = (L+R)>>1;
	UD(Nd,L,R,Mid-L+1,R-Mid);
	Modify(Nd<<1  ,L    ,Mid,l,r,k);
	Modify(Nd<<1|1,Mid+1,R  ,l,r,k);
	Up(Nd);
}

void Query(int Nd,int L,int R,int l,int r){
	if(L>r||R<l) return ;
	if(L>=l&&R<=r){
		Var += V[Nd];
		Tot += A[Nd];
		return;
	}
	int Mid = (L+R)>>1;
	UD(Nd,L,R,Mid-L+1,R-Mid);
	Query(Nd<<1  ,L    ,Mid,l,r);
	Query(Nd<<1|1,Mid+1,R  ,l,r);
}

int main(){
	
	scanf("%d%d",&n,&m);
	
	Build(1,1,n);
	
	while( m-- ){
		int Opt,x,y;double k;
		Tot=0;Var=0;
		scanf("%d%d%d",&Opt,&x,&y);
		switch( Opt ){
			case 1:scanf("%lf",&k);Modify(1,1,n,x,y,k);break;
			case 2:Query(1,1,n,x,y);printf("%.4lf\n",Tot*1.0/(y-x+1));break;
			case 3:Query(1,1,n,x,y);printf("%.4lf\n",(Var-(y-x+1)*P(Tot*1.0/(y-x+1)))*1.0/(y-x+1));break;
		}
	}
	
	return 0;
}
