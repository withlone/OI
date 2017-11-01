#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int MAXN=200;
struct BIGNUM {
	int len,s[MAXN];
	BIGNUM(){len=1;memset(s,0,sizeof s);}
	BIGNUM operator =(char *num){
		len=strlen(num);
		for(int i=0;i<len;i++)
			s[len-i]=num[i]-'0';
		return *this;
	}
	BIGNUM operator =(int num){
		char a[MAXN];
		sprintf(a,"%d",num);
		*this=a;
		return *this;
	}
	BIGNUM (char *num){*this=num;}
	BIGNUM (int num){*this=num;}
	BIGNUM operator +(BIGNUM a){
		BIGNUM c;
		c.len=max(a.len,len)+1;
		for(int i=1;i<=c.len;i++)
		{
			c.s[i]=c.s[i]+s[i]+a.s[i];
			c.s[i+1]+=c.s[i]/10;
			c.s[i]%=10;
		}
		while(c.s[c.len]==0&&c.len>1) c.len--;
		return c;
	}
	BIGNUM operator +=(BIGNUM a){
		*this=*this+a;
		return *this;
	}
	BIGNUM operator *(BIGNUM a){
		BIGNUM c;
		c.len=a.len+len;
		for(int i=1;i<=len;i++)
			for(int j=1;j<=a.len;j++)
			{
				c.s[i+j-1]+=s[i]*a.s[j];
				c.s[i+j]+=c.s[i+j-1]/10;
				c.s[i+j-1]%=10;
			}
		while(c.s[c.len]==0&&c.len>1) c.len--;
		return c;
	}
	bool operator > (BIGNUM a) const {
		if(a.len!=len)
			return len>a.len;
		for(int i=len;i>=1;i--)
			if(a.s[i]!=s[i])
				return s[i]>a.s[i];
		return false;
	}
	bool operator < (BIGNUM a) const {return a>*this;}
};
istream& operator >>(istream &in,BIGNUM &a)
{
	char num[MAXN];
	in>>num;
	a=num;
	return in;
}
ostream& operator <<(ostream &out,BIGNUM a)
{
	for(int i=a.len;i>=1;i--)
		cout<<a.s[i];
	return out;
}
BIGNUM ch[81];
BIGNUM f[81][81];
BIGNUM a[81];
BIGNUM max(BIGNUM a,BIGNUM b)
{
	return a>b?a:b;
}
int main()
{
	
	freopen( "game.in" , "r" , stdin ) ;
	freopen( "game.out" , "w" , stdout ) ;
	
	int n,m;
	scanf("%d%d",&n,&m);
	ch[1]=2;
	for(int i=2;i<=m;i++)
		ch[i]=ch[i-1]*2;
	BIGNUM ans=0;
	for(int I=1;I<=n;I++)
	{
		for(int i=1;i<=m;i++)
			cin>>a[i];
		for(int i=1;i<=m;i++)
		{
			f[0][i]=a[i];
			f[i][m+1]=a[m];
		}
		for(int i=0;i<=m;i++)
			for(int j=m+1;j>i;j--)
			{
				f[i][j]=0;
				if(i) f[i][j]=f[i-1][j]+a[i]*ch[i+m-j+1];
				if(j!=m+1) f[i][j]=max(f[i][j],f[i][j+1]+a[j]*ch[i+m-j+1]);
			}
		BIGNUM Ans=0;
		for(int i=0;i<=m;i++)
			Ans=max(Ans,f[i][i+1]);
		ans+=Ans;
	}
	cout<<ans<<endl;
	return 0;
}
