#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 20001;
const int MAXM = 100001;

int n,m;
int Father[MAXN*2];

struct Machine{
    int u,v,Pain;
    bool operator < (Machine a) const {return Pain>a.Pain;}
}Divide[MAXM];

int Find(int);

int main(){
    freopen("divide.in","r",stdin);
    freopen("divide.out","w",stdout);
    
    scanf("%d%d",&n,&m);
    
    for(int i=1;i<=2*n;i++) Father[i]=i;
    
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&Divide[i].u,&Divide[i].v,&Divide[i].Pain);
    
    sort(1+Divide,1+m+Divide);
    
    for(int i=1;i<=m;i++){
        int u=Find(Divide[i].u),v=Find(Divide[i].v);
        if(u!=v){
            Father[u]=Find(Divide[i].v+n);
            Father[v]=Find(Divide[i].u+n);
        }
        else{
            printf("%d\n",Divide[i].Pain);
            return 0;
        }
    }
    printf("0\n");
    return 0;
}

int Find(int t){return t==Father[t]?t:Father[t]=Find(Father[t]);}
