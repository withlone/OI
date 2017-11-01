#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN = 10001;
const int Ten  = 1e8;

struct BIGNUM{
	int s[1300],len;
	BIGNUM(){memset(s,0,sizeof s);len=1;}
	BIGNUM operator =(char *T){
		len=0;int n=strlen(T);
		char C[MAXN];
		for(int i=0;i<n;i++) C[i]=T[n-i-1];
		for(int i=0;i<n;i++) T[i]=C[i];
		for(int i=0;i<n;i+=8){
			++len;
			for(int j=min(i+7,n-1);j>=i;j--)
				s[len]=s[len]*10+T[j]-'0';
		}
		return *this;
	}
	BIGNUM operator =(int T){
		char C[MAXN];sprintf(C,"%d",T);
		*this=C;
		return *this;
	}
	BIGNUM (char *T){*this=T;}
	BIGNUM (int T){memset(s,0,sizeof s);len=1;*this=T;}
	
	BIGNUM operator -(BIGNUM T){
		for(int i=1;i<=len;i++){
			s[i]-=T.s[i];
			if(s[i]<0){s[i]+=Ten;s[i+1]--;}
		}
		while(!s[len]&&len>1)len--;
		return *this;
	}
	
	BIGNUM Div2(){
		for(int i=len;i;i--){
			if(s[i]&1) s[i-1]+=Ten;
			s[i]>>=1;
		}
		s[0]=0;
		while(!s[len]&&len>1)len--;
		return *this;
	}
	BIGNUM Mul2(){
		for(int i=len;i>=1;i--){
			s[i]<<=1;
			s[i+1]+=s[i]/Ten;
			s[i]%=Ten;
		}
		while(s[len+1])++len;
		while(!s[len]&&len>1)len--;
		return *this;
	}
	
	bool operator <=(BIGNUM T){
		if(len!=T.len)return len<T.len;
		for(int i=len;i>=1;i--)if(s[i]!=T.s[i])return s[i]<T.s[i];
		return true;
	}
	bool Check(){
		for(int i=1;i<=len;i++)if(s[i])return false;return true;
	}
	
	void print(){
		printf("%d",s[len]);
		for(int i=len-1;i>=1;i--)printf("%08d",s[i]);
	}
}A,B;

char In[2][MAXN];
int Sum;

int main(){

	scanf("%s\n%s",In[0],In[1]);
	A=In[0];B=In[1];
	while(!A.Check()&&!B.Check()){
		if(!(A.s[1]&1)&&!(B.s[1]&1)) Sum++,A=A.Div2(),B=B.Div2();
		else if(!(A.s[1]&1)) A=A.Div2();
		else if(!(B.s[1]&1)) B=B.Div2();
		if(A<=B) B=B-A;
		else A=A-B;
	}
	if(B<=A) B=A;
	while( Sum-- )
		B=B.Mul2();
	
	B.print();
	return 0;
}
