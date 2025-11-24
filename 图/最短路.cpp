#include<bits/stdc++.h>
using namespace std;
const int N=31;

int dis[N][N];
int n,m;
char s;
char uc,vc; int w;
int u,v;
int main() {
    memset(dis,0x3f,sizeof(dis));
    scanf("%d%*c%d%*c%c",&n,&m,&s);
    for(int i=1;i<=n;i++) dis[i][i]=0;
    for(int i=1;i<=m;i++) {
        scanf("%*c%*c%c%*c%c%*c%d%*c",&uc,&vc,&w);
        u=uc-'a'+1; v=vc-'a'+1;
        dis[u][v]=min(dis[u][v],w);
    }
    for(int k=1;k<=n;k++) {
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=n;j++) {
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
    }
    int st=s-'a'+1;
    for(int i=1;i<=n;i++) {
        printf("%c:",i+'a'-1);
        printf("%d\n",dis[st][i]);
    }
}