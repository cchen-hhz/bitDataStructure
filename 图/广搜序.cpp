#include<bits/stdc++.h>
using namespace std;

const int N = 110;
const int M = 10010; 

char ver[N];
int head[N];
int tot = 0;
int n = 0;
bool vis[N];

struct Edge {
    int to;
    int next;
} edge[M];

void add(int u, int v) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void bfs() {
    printf("the Breadth-First-Seacrh list:");
    queue<int>q;
    for(int i=0;i<n;i++) {
        if(vis[i]) continue;
        vis[i]=1; q.push(i);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            printf("%c", ver[u]);
            
            for(int i = head[u]; i != -1; i = edge[i].next) {
                int v = edge[i].to;
                if(!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    } 
    puts("");
}

int main() {
    memset(head, -1, sizeof(head));
    
    char s[10];
    while(scanf("%s", s)) {
        if(s[0] == '*') break;
        ver[n++] = s[0];
    }

    int u, v;
    while(scanf("%d,%d", &u, &v)) {
        if(u == -1 && v == -1) break;
        add(u, v);
        add(v, u);
    }
    
    puts("the ALGraph is");
    for(int i = 0; i < n; i++) {
        printf("%c", ver[i]);
        for(int j = head[i]; j != -1; j = edge[j].next) {
            printf(" %d", edge[j].to);
        }
        puts("");
    }
    
    bfs();
    
    return 0;
}