#include<bits/stdc++.h>
using namespace std;
const int N=3010;

struct dsu{
    vector<int>fa,siz;
    dsu(int n) {
        fa.resize(n); siz.resize(n,1);
        iota(fa.begin(),fa.end(),0);
    }
    int findf(int x) {
        return fa[x]==x?x:fa[x]=findf(fa[x]);
    }
    void merge(int u,int v) {
        int a=findf(u),b=findf(v);
        if(a==b) return;
        if(siz[a]>siz[b]) swap(a,b);
        fa[a]=b; siz[b]+=siz[a];
    }
};

struct eg{
    int u,v,w;
}e[N];
bool cmp(eg a,eg b) {
    return a.w<b.w;
}
int n,m;

int main() {
    scanf("%d%d",&n,&m);
    dsu t(n+1);
    for(int i=1;i<=m;i++) {
        scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    }
    sort(e+1,e+1+m,cmp);
    int ans=0;
    int cnt=0;
    for(int i=1;i<=m;i++) {
        int u=e[i].u,v=e[i].v,w=e[i].w;
        if(t.findf(u)==t.findf(v)) continue;
        ans+=w; cnt++;
        t.merge(u,v);
    }
    if(cnt!=n-1) puts("-1");
    else printf("%d\n",ans);
}