#include<cstdio>
#include<cstring>
char m[1001];
char c[1001];
char k[101];
int main()
{
	
	freopen( "vigenere.in" , "r" , stdin ) ;
	freopen( "vigenere.out" , "w" , stdout ) ;
	
	int j=0;
	gets(k);
	gets(c);
	int lk=strlen(k);
	int lc=strlen(c);
	for(int i=0;i<lk;i++)
	{
		if(k[i]>='A'&&k[i]<='Z')
		k[i]+=32;
	}
	for(int i=0;i<lc;i++)
	{
		m[i]=c[i]-k[j]+97;
		if(m[i]<'a'&&c[i]>='a'&&c[i]<='z'||m[i]<'A'&&c[i]>='A'&&c[i]<='Z')
		m[i]=26+m[i];
		if(m[i]>'z'&&c[i]>='a'&&c[i]<='z'||m[i]>'Z'&&c[i]>='A'&&c[i]<='Z')
		m[i]=m[i]-26;
		j++;
		if(j==lk)
		j=0;
	}
	puts(m);
	return 0;
}
