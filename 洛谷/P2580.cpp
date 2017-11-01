#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )

static const int MAXN = 1e4 +1;
static const int MAXM = 1e5 +1;
static const int MAXL = 51;

int n , m;
char Nm[MAXN][MAXL] , Qry[MAXL];

namespace Trie{
	static const int maxx = 26;
	int Ct;
	struct Node{
		char Wd;int Ct;
		int Ch[26];
		Node(){ Wd = Ct = 0;For( i , 0 , 25 )Ch[i] = 0; }
	}Tr[MAXN*MAXL];
	void Insert( char *x ){
		char *p = x;
		int Nd = 1;
		while( *p ){
			int tmp = *p - 'a';
			if( !Tr[Nd].Ch[ tmp ] )Tr[Nd].Ch[ tmp ] = ++Ct;
			Nd = Tr[Nd].Ch[ tmp ];
			p++;
		}
	}
	int Find( char *x ){
		char *p = x;
		int Nd = 1;
		while( *p ){
			int tmp = *p - 'a';
			if( !Tr[Nd].Ch[ tmp ] )return 0;
			Nd = Tr[Nd].Ch[ tmp ];
			p++;
		}
		return ++Tr[Nd].Ct;
	}
}using namespace Trie;

int main(){
	
	scanf("%d",&n);
	For( i , 1 , n ){
		scanf("%s",Nm[i]);
		Insert( Nm[i] );
	}
	scanf("%d",&m);
	while( m-- ){
		scanf("%s",Qry);
		int tmp = Find( Qry );
		if( !tmp )puts("WRONG");
		else if( tmp == 1 )puts("OK");
		else puts("REPEAT");
	}
	return 0;
}
