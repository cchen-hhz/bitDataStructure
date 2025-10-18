#include<bits/stdc++.h>
using namespace std;
const int N=210;
int mx[]={1,0,0,-1},my[]={0,1,-1,0};
int n,m;
struct node{
    int x,y;
};
node fm[N][N]; 

int main() {
    scanf("%d%d",&n,&m);
    vector<vector<int> >mp(n,vector<int>(m));
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            scanf("%d",&mp[i][j]);
            fm[i][j]=node{-1,-1};
        }
    }
    queue<node>q;
    q.push(node{0,0});
    while(!q.empty()) {
        node f=q.front(); q.pop();
        int x=f.x,y=f.y;
        for(int i=0;i<4;i++) {
            int nx=x+mx[i],ny=y+my[i];
            if(nx<0||ny<0||nx>=n||ny>=m||mp[nx][ny]) continue;
            if(fm[nx][ny].x!=-1||(nx==0&&ny==0)) continue;
            fm[nx][ny]=node{x,y};
            q.push(node{nx,ny});
        }
    }
    if(fm[n-1][m-1].x==-1) puts("There is no solution!");
    else {
        int x=n-1,y=m-1;
        vector<node>ans;
        while(x!=-1) {
            ans.push_back(node{x,y});
            node u=fm[x][y];
            x=u.x,y=u.y;
        }
        while(!ans.empty()) {
            printf("<%d,%d> ",ans.back().x+1,ans.back().y+1);
            ans.pop_back();
        }
        puts("");
    }
}