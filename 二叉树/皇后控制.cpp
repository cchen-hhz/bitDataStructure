#include<bits/stdc++.h>
using namespace std;
const int N=15;

int n,m;
int vis[N][N];
int sum[N];
int cnt,ans;

void update(int x,int y,int w) {
    if(w==1) {
        cnt+=(vis[x][y]==0);
        if(vis[x][y]==0) sum[x]++;
        vis[x][y]+=w;
    }
    else {
        cnt-=(vis[x][y]==1);
        if(vis[x][y]==1) sum[x]--;
        vis[x][y]+=w;
    }
}

void place(int x,int y,int op) {
    for(int i=1;i<=n;i++) {
        update(x,i,op);
        if(i!=x) update(i,y,op);
        if(x+i<=n&&y+i<=n) update(x+i,y+i,op);
        if(x+i<=n&&y-i>=1) update(x+i,y-i,op);
        if(x-i>=1&&y+i<=n) update(x-i,y+i,op);
        if(x-i>=1&&y-i>=1) update(x-i,y-i,op);
    }
}

void dfs(int row,int now) {
    if(now==m) {
        ans+=(cnt==n*n);
        return;
    }
    if(row>n) return;
    dfs(row+1,now);
    for(int i=1;i<=n;i++) {
        if(!vis[row][i]) {
            place(row,i,1);
            dfs(row+1,now+1);
            place(row,i,-1);
        }
    }
}

int main() {
    scanf("%d%d",&n,&m);
    dfs(1,0);
    printf("%d\n",ans);
}