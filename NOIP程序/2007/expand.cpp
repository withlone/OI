#include<cstdio>
#include<cstring>
char a[101];
int main()
{
	
	freopen( "expand.in" , "r" , stdin ) ;
	freopen( "expand.out" , "w" , stdout ) ;
	
	int p1,p2,p3;
	scanf("%d%d%d\n",&p1,&p2,&p3);
	gets(a);
	int l=strlen(a);
	for(int i=0;i<l;i++)
	{
		if(i==0&&a[i]=='-')
		{
			while(a[i]=='-')
			{
				putchar('-');
				i++;
			}
		}
		if(a[i]!='-')
			putchar(a[i]);
		else
		{
			if(a[i+1]>='0'&&a[i+1]<='9'&&a[i-1]>='a'&&a[i-1]<='z'
			||a[i+1]>='a'&&a[i+1]<='z'&&a[i-1]>='0'&&a[i-1]<='9'
			||a[i-1]>=a[i+1])
			{
				putchar('-');
				putchar(a[i+1]);
				i++;
			}
			else if(a[i-1]==a[i+1]-1)
			{
				putchar(a[i+1]);
				i++;
			}
			else
			{
				bool pd=0;
				if(a[i-1]>='a'&&a[i-1]<='z')
					pd=1;
				if(p3==1)
					for(char j=a[i-1]+1;j<=a[i+1]-1;j++)
					{
						for(int k=1;k<=p2;k++)
						{
							if(p1==2&&pd)
								putchar(j-32);
							else if(p1==3)
								putchar('*');
							else
								putchar(j);
						}
					}
				else
					for(char j=a[i+1]-1;j>=a[i-1]+1;j--)
					{
						for(int k=1;k<=p2;k++)
						{
							if(p1==2&&pd)
								putchar(j-32);
							else if(p1==3)
								putchar('*');
							else
								putchar(j);
						}
					}
				putchar(a[i+1]);
				i++;
			}
		}
	}
	return 0;
}
