#include<bits/stdc++.h>
using namespace std;
char a[101];char b[101];char c[101];bool bo[26];char s[101];
void put()
{
	printf("Failed");
	exit(0);
}
int main()
{

	freopen( "spy.in" , "r" , stdin ) ;
	freopen( "spy.out" , "w" , stdout ) ;
	
	cin>>a>>b>>c;
	int la=strlen(a);int lb=strlen(b);int lc=strlen(c);
	for(int i=0;i<la;i++)
		bo[b[i]-'A']=1;
	if(la!=lb)
		put();
	for(int i=0;i<=25;i++)
		if(!bo[i])
			put();
	for(int i=0;i<la;i++)
		for(int j=0;j<lb;j++)
			if(a[i]!=a[j]&&b[i]==b[j]||a[i]==a[j]&&b[i]!=b[j])
				put();
	for(int i=0;i<lc;i++)
		for(int j=0;j<la;j++)
			if(c[i]==a[j])
			{
				putchar(b[j]);
				break;
			}
	return 0;
}
