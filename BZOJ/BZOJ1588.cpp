#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
 
const int INT_MAX = 10000000;
const int INT_MIN = -INT_MAX;
const int MAXN = 32767+1;
#define Keep for(;;)
 
int n,Ans,Min,In;
 
struct SPLAY{
    int Root,Num;
    struct Node{
        int Son[2],Father,Same,Key;
    }Tree[MAXN];
     
    int GetSon(int Read){return Read==Tree[Tree[Read].Father].Son[1];}
     
    void Build(int Key){
        Tree[++Num].Key=Key;
        Tree[Num].Same=1;
    }
     
    void Rotate(int Pos){
        int Tmp=GetSon(Pos);int Father=Tree[Pos].Father;int GrandFather=Tree[Father].Father;
        if(!Father) return;
        Tree[Father].Son[Tmp]=Tree[Pos].Son[Tmp^1];
        if(Tree[Pos].Son[Tmp^1]) Tree[Tree[Pos].Son[Tmp^1]].Father=Father;
         
        Tree[Pos].Son[Tmp^1]=Father;
        Tree[Father].Father=Pos;
         
        Tree[Pos].Father=GrandFather;
        if(GrandFather) Tree[GrandFather].Son[Tree[GrandFather].Son[1]==Father]=Pos;
    }
     
    void Maintain(int Pos){
        for(int Father;Father=Tree[Pos].Father;Rotate(Pos))
            if(Tree[Father].Father)
                Rotate(GetSon(Pos)==GetSon(Father)?Father:Pos);
        Root=Pos;
    }
     
    void Insert(int Key){
        if(!Root){
            Build(Key);
            Root=Num;
            return;
        }
        int Pos=Root,Father=0;
        Keep{
            if(Key==Tree[Pos].Key){
                Tree[Pos].Same++;
                Maintain(Pos);
                return;
            }
            Father=Pos;Pos=Tree[Pos].Son[Key>Tree[Pos].Key];
            if(!Pos){
                Build(Key);
                Tree[Num].Father=Father;
                Tree[Father].Son[Key>Tree[Father].Key]=Num;
                Maintain(Num);
                return;
            }
        }
    }
     
    int Pre(){
        if(Tree[Root].Same>1) return Tree[Root].Key;
        if(!Tree[Root].Son[0]||!(Tree[Root].Son[0]+Tree[Root].Son[1])) return INT_MIN;
        int Pos=Tree[Root].Son[0];
        while(Tree[Pos].Son[1]) Pos=Tree[Pos].Son[1];
        return Tree[Pos].Key;
    }
     
    int Next(){
        if(Tree[Root].Same>1) return Tree[Root].Key;
        if(!Tree[Root].Son[1]||!(Tree[Root].Son[0]+Tree[Root].Son[1])) return INT_MAX;
        int Pos=Tree[Root].Son[1];
        while(Tree[Pos].Son[0]) Pos=Tree[Pos].Son[0];
        return Tree[Pos].Key;
    }
     
}Splay;
 
int main(){
    scanf("%d%d",&n,&In);
    Splay.Insert(In);
    Ans=In;
    for(int i=2;i<=n;i++){
        scanf("%d",&In);
        Splay.Insert(In);
        Min=min(abs(In-Splay.Pre()),abs(Splay.Next()-In));
        Ans+=Min;
    }
     
    printf("%d\n",Ans);
     
    return 0;
}
