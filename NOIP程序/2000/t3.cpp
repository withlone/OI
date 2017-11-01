#include<bits/stdc++.h>
using namespace std;
char s[21][50];int n;int b[21];int ans=0;int maxn=0;
int check(int x,int y)
{
	int l1=strlen(s[x]);
	int l2=strlen(s[y]);
	bool pd;
	for(int i=l1-1;i>=1;i--)
	{
		pd=0;
		for(int j=0;j<l2;j++)
		{
			if(j==l2-1&&i+j<l1)
			{
				pd=1;break;
			}
			if(i+j>=l1)
				break;
			if(s[x][i+j]!=s[y][j])
			{
				pd=1;break;
			}
		}	
		if(!pd)	return l2-l1+i;
	}
	return 0;
}
int search(int t)
{
	if(ans>maxn)
		maxn=ans;
	for(int i=1;i<=n;i++)
	{
		int xx=check(t,i);
		if(b[i]<2&&xx>0)
		{
			b[i]++;
			ans=ans+xx;
			search(i);
			b[i]--;
			ans=ans-xx;
		}
	}		
}
int main()
{
	
	freopen( "t3.in" , "r" , stdin ) ;
	freopen( "t3.out" , "w" , stdout ) ;
	
	scanf("%d\n",&n);
	for(int i=1;i<=n;i++)
		scanf("%s\n",s[i]);
	char ch=getchar();
	for(int i=1;i<=n;i++)
		if(ch==s[i][0])
		{
			b[i]++;
			ans=strlen(s[i]);
			search(i);
			b[i]--;
		}
	printf("%d",maxn);
	return 0;
}
