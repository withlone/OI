#include<cstdio>
#include<cstring>

int k,Ct;

void inv( int &x ){
	(++x) %= k<<1;
	if( !x ) x = k<<1;
}

bool Check( int m ){
	Ct = 0;
	for( int T=k<<1;T!=k;T-- ){
		(Ct += m%T)%=T;
		if( Ct<k )return false;
	}
	return true;
}

int main(){
	
	scanf("%d",&k);
	for( int i=1;;i++ )if( Check(i) )return printf("%d\n",i+1),0;
}
