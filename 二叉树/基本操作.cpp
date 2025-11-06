#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;

char s[N]; int n;
int lc[N],rc[N],rt;
int top; char pt[N];
int lef;

int dfs(int u)
{
    if(s[top]=='#') return 0;
    pt[u]=s[top];
    top++; lc[u]=dfs(u<<1);
    top++; rc[u]=dfs(u<<1|1);
    return u;
}

void pres(int u)
{
    printf("%c",pt[u]);
    if(lc[u]) pres(lc[u]);
    if(rc[u]) pres(rc[u]);
    if(!lc[u]&&!rc[u]) lef++;
}

void midp(int u)
{
    if(lc[u]) midp(lc[u]);
    printf("%c",pt[u]);
    if(rc[u]) midp(rc[u]);
}

void sufp(int u)
{
    if(lc[u]) sufp(lc[u]);
    if(rc[u]) sufp(rc[u]);
    printf("%c",pt[u]);
}

void put_tree(int u,int dep)
{
    for(int i=1;i<=dep;i++) putchar(' ');
    printf("%c\n",pt[u]);
    if(lc[u]) put_tree(lc[u],dep+4);
    if(rc[u]) put_tree(rc[u],dep+4);
}

int main()
{
    scanf("%s",s+1); n=strlen(s+1);
    puts("BiTree");
    top=1; rt=dfs(1);
    put_tree(rt,0);
    printf("pre_sequence  : "); pres(rt); puts("");
    printf("in_sequence   : "); midp(rt); puts("");
    printf("post_sequence : "); sufp(rt); puts("");
    printf("Number of leaf: %d\n",lef);
    for(int i=0;i<26;i++) swap(lc[i],rc[i]);
    puts("BiTree swapped");
    put_tree(rt,0);
    printf("pre_sequence  : "); pres(rt); puts("");
    printf("in_sequence   : "); midp(rt); puts("");
    printf("post_sequence : "); sufp(rt); puts("");
}