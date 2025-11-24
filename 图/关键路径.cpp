#include<bits/stdc++.h>
using namespace std;
const int N=1010;
#define mkp make_pair

string ns[N];
int n,m;
char x;
int u,v,w;
vector<pair<int,int> >ver[N];
vector<int>deg,las;
vector<int>tans;
vector<vector<int> >ans[N]; int dis[N];
int st,ed;

bool topu() {
    priority_queue<int,vector<int>,greater<int> >q;
    for(int i=0;i<n;i++) las[i]=deg[i];
    for(int i=0;i<n;i++) {
        if(!deg[i]) q.push(i);
    }
    int cnt=0;
    if(q.size()!=1) return 0;
    st=q.top();
    while(!q.empty()) {
        int u=q.top();  q.pop();
        cnt++; tans.push_back(u);
        if(cnt==n) ed=u;
        for(auto o:ver[u]) {
            int v=o.first,w=o.second;
            deg[v]--;
            if(!deg[v]) q.push(v);
        }
    }
    if(cnt!=n) return 0;
    return 1;
}

void calcdis() {
    for(int i=0;i<n;i++) deg[i]=las[i];
    ans[st].push_back(vector<int>{st});
    dis[st]=0;
    priority_queue<int,vector<int>,greater<int> >q;
    q.push(st);
    while(!q.empty()) {
        int u=q.top(); q.pop();
        for(auto o:ver[u]) {
            int v=o.first,w=o.second;
            deg[v]--;
            if(dis[v]<dis[u]+w) {
                dis[v]=dis[u]+w;
                ans[v].clear();
                for(auto pt:ans[u]) {
                    pt.push_back(v);
                    ans[v].push_back(pt);
                }
            }
            else if(dis[v]==dis[u]+w) {
                for(auto pt:ans[u]) {
                    pt.push_back(v);
                    ans[v].push_back(pt);
                }
            }
            if(!deg[v]) q.push(v); 
        }
    }
}

bool cmp(vector<int>s1,vector<int>s2) {
    int len=min(s1.size(),s2.size());
    for(int i=0;i<len;i++) {
        if(s1[i]<s2[i]) return 1;
        else if(s1[i]>s2[i]) return 0;
    }
    return s1.size()<=s2.size();
}

int main() {
    scanf("%d,%d",&n,&m);
    deg=vector<int>(n);
    las=vector<int>(n);
    getchar();
    for(int i=0;i<n;i++) {
        char buf[64];
        scanf("%[^,\n]",buf);
        ns[i]=buf;
        getchar();
    }
    for(int i=1;i<=m;i++) {
        scanf("<%d,%d,%d>",&u,&v,&w); getchar();
        ver[u].push_back(mkp(v,w));
        deg[v]++;
    }
    for(int i=0;i<n;i++) {
        sort(ver[u].begin(),ver[u].end());
    }
    if(!topu()) {
        puts("NO TOPOLOGICAL PATH");
        return 0;
    }
    calcdis();
    sort(ans[ed].begin(),ans[ed].end(),cmp);
    for(int i=0;i<(int)tans.size();i++) {
        cout<<ns[tans[i]];
        if(i==(int)tans.size()-1) puts("");
        else putchar('-');
    }
    for(auto t:ans[ed]) {
        for(int i=0;i<(int)t.size();i++) {
            cout<<ns[t[i]];
            if(i==(int)t.size()-1) puts("");
            else putchar('-'); 
        }
    }
}