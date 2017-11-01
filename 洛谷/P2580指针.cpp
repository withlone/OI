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
	struct Node{
		char Wd;int Ct;bool Flag;
		Node *Ch[26];
		Node(){ Flag = Wd = Ct = 0;For( i , 0 , 25 )Ch[i] = NULL; }
	} *Rt;
	void Insert( char *x ){
		char *p = x;
		Node *Nd = Rt;
		while( *p ){
			int tmp = *p - 'a';
			if( Nd -> Ch[ tmp ] == NULL )Nd -> Ch[ tmp ] = new Node;
			Nd = Nd -> Ch[ tmp ];
			p++;
		}
		Nd -> Flag = 1;
	}
	int Find( char *x ){
		char *p = x;
		Node *Nd = Rt;
		while( *p ){
			int tmp = *p - 'a';
			if( Nd -> Ch[ tmp ] == NULL )return 0;
			Nd = Nd -> Ch[ tmp ];
			p++;
		}
		if( Nd -> Flag )return ++( Nd -> Ct );
		return -1;
	}
}using namespace Trie;

int main(){
	
	Rt = new Node;
	
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
