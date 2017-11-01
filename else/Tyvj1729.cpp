#include<cstdio>
#include<algorithm>
using namespace std;

int n,m;

struct SPLAY{
	static const int MAXN = 1e5 +1;
	int Rot;
	struct Node{
		int Son[2],Ct,Key,Fa;
		bool Flag;
	}T[MAXN];
	int GS( int p ){return p==T[T[p].Fa].Son[1];}
	void UP( int p ){T[p].Ct = T[T[p].Son[0]].Ct + T[T[p].Son[1]].Ct +1;}
	int Build( int l,int r ){
		if( l==r )return l;
		if( l+1==r ){
			T[l].Fa = r;T[r].Son[0] = l;
			UP(r);return r;
		}
		int Mid = l+r >>1;
		T[T[Mid].Son[0]=Build( l,Mid-1 )].Fa = 
		T[T[Mid].Son[1]=Build( Mid+1,r )].Fa = Mid;
		UP( Mid );return Mid;
	}
	void Build(){
		for( int i=1;i<=n;i++ ){
			T[i].Ct = 1;T[i].Key = i;
		}
		Rot = Build( 1,n );
	}
	void PD( int p ){
		if( !T[p].Flag )return;
		T[p].Flag = 0;
		if( T[p].Son[0] )T[T[p].Son[0]].Flag ^= 1;
		if( T[p].Son[1] )T[T[p].Son[1]].Flag ^= 1;
		swap( T[p].Son[0],T[p].Son[1] );
	}
	void Rotate( int p ){
		int Fa = T[p].Fa,GFa = T[Fa].Fa,t = GS(p);if( !Fa )return;
		T[Fa].Son[t] = T[p].Son[t^1];
		if( T[p].Son[t^1] )T[T[p].Son[t^1]].Fa = Fa;
		T[p].Son[t^1] = Fa;
		T[Fa].Fa = p;
		T[p].Fa = GFa;
		if( GFa )T[GFa].Son[T[GFa].Son[1]==Fa] = p;
		UP( Fa );UP( p );
	}
	void MT( int p,int To ){
		PD( p );
		for( int Fa;(Fa=T[p].Fa)!=To;Rotate(p) )
			if( T[Fa].Fa!=To )
				Rotate( GS(Fa)==GS(p)?Fa:p );
		if( !To )Rot = p;
	}
	int FN( int t ){
		int p = Rot;
		while(1){
			PD( p );
			if( T[p].Son[0]&&t<=T[T[p].Son[0]].Ct )p = T[p].Son[0];
			else{
				t -= T[T[p].Son[0]].Ct + 1;
				if( !t )return p;
				p = T[p].Son[1];
			}
		}
	}
	void Flip( int l,int r ){
		if( l==1&&r==n ){
			T[Rot].Flag ^= 1;
			return;
		}
		if( l==1 ){
			MT( FN( r+1 ),0 );
			T[T[Rot].Son[0]].Flag ^= 1;
			return;
		}
		if( r==n ){
			MT( FN( l-1 ),0 );
			T[T[Rot].Son[1]].Flag ^= 1;
			return;
		}
		MT( FN(l-1),0 );MT( FN(r+1),Rot );
		T[T[T[Rot].Son[1]].Son[0]].Flag ^= 1;
	}
	void Display( int p ){
		if( !p )return;
		PD( p );
		Display( T[p].Son[0] );
		printf("%d ",T[p].Key);
		Display( T[p].Son[1] );
	}
}Splay;

int main(){
	
	scanf("%d%d",&n,&m);
	Splay.Build();
	while( m-- ){
		int l,r;
		scanf("%d%d",&l,&r);
		Splay.Flip( l,r );
	}
	Splay.Display( Splay.Rot );
	return 0;
}
