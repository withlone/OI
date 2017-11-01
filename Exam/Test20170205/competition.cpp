#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int MAXN = 500010;

int p[MAXN],Father[MAXN];
int n,k;

int Find(int t){return t==Father[t]?t:Father[t]=Find(Father[t]);}

bool Check(int x){
    int Now=1,Tot=1;
    for(int i=1;i<=n+1;i++) Father[i]=i;
    p[1]=x;
    Father[x]=Father[x+1];
    for(int i=1;i<=log2(n);i++){
        for(int j=1;j<=Now;j++){
            p[++Tot]=Find(max(1,p[j]-k));
            Father[p[Tot]]=Father[p[Tot]+1];
            if(p[Tot]==n+1) return false;
        }
        Now=Tot;
        if(Now==n) break;
    }
    return true;
}

void Divide(){
    int l=1,r=n,Mid;
    while(l<r-1){
        Mid=(l+r)>>1;
        if(Check(Mid)) l=Mid;
        else r=Mid;
    }
    if(Check(r)) printf("%d\n",r);
    else printf("%d\n",l);
}

int main(){
	freopen("competition.in","r",stdin);
	freopen("competition.out","w",stdout);
    scanf("%d%d",&n,&k);
    Divide();
    return 0;
}
