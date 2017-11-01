#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int cmark[101];
int pjmark[101];
char worker[101];
char west[101];
int m[101];
string name[101];
int art[101];
int main()
{
	
	freopen( "scholar.in" , "r" , stdin ) ;
	freopen( "scholar.out" , "w" , stdout ) ;
	
	int n,max=0,total=0;
	memset(m,0,sizeof(m));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		cin>>name[i]>>pjmark[i]>>cmark[i]>>worker[i]>>west[i]>>art[i];
		if((pjmark[i]>80)&&(art[i]>=1))
		m[i]=m[i]+8000;
		if((pjmark[i]>85)&&(cmark[i]>80))
		m[i]=m[i]+4000;
		if(pjmark[i]>90)
		m[i]=m[i]+2000;
		if((pjmark[i]>85)&&(west[i]=='Y'))
		m[i]=m[i]+1000;
		if((cmark[i]>80)&&(worker[i]=='Y'))
		m[i]=m[i]+850;
		if(m[i]>max)
		max=m[i];
		total+=m[i];
	}
	for(int i=1;i<=n;i++)
	{
		if(m[i]==max)
		{
			cout<<name[i]<<endl<<max<<endl<<total;
			return 0;
		}
	}
}
