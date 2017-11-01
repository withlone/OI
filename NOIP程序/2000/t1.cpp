#include<cstdio>
int a[50];char ch[]={'A','B','C','D','E','F','G','H'};
int main()
{
	
	freopen( "t1.in" , "r" , stdin ) ;
	freopen( "t1.out" , "w" , stdout ) ;
	
	int n,r;
	scanf("%d%d",&n,&r);
	printf("%d=",n);
	int k=0;int l;
	while(n)
	{
		l=n%r;
		n/=r;
		if(l<0)
			l=l-r,n++;
		a[++k]=l;
	}
	for(int i=k;i>=1;i--)
		if(a[i]>=10)
			printf("%c",ch[a[i]-10]);
		else
			printf("%d",a[i]);
	printf("(base%d)",r);
	return 0;
}
