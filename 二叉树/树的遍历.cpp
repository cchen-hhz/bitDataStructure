#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;

vector<int>ver[N];
int rt;
char s[N];
int n;
int st[N],top;
int cnt[N]; int mx;

void dfs(int u,int dep)
{
    int w=(int)ver[u].size();
    cnt[w]++; mx=max(mx,w);
    for(int i=1;i<=dep;i++) putchar(' ');
    putchar(u+'a'); puts("");
    for(int v:ver[u]) dfs(v,dep+4);
}

int main()
{
    cin.getline(s,sizeof(s));
    n=strlen(s);
    for(int i=0;i<n;i++)
    {
        if(s[i]=='(') 
        {
            int w=s[i+1]-'a';
            if(top) ver[st[top]].push_back(w);
            else rt=w;
            st[++top]=w;
        }
        else if(s[i]==')') top--;
        else continue;
    }
    if(rt>=0&&rt<=25) dfs(rt,0);
    printf("Degree of tree: %d\n",mx);
    for(int i=0;i<=mx;i++)
        printf("Number of nodes of degree %d: %d\n",i,cnt[i]);
}