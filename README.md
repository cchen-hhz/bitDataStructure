# 数据结构编程题

你妈死了！

目前只有栈和队列的，因为最构式。

股票和机场调度来自 CSDN，别的是用 ai 写的。至于为什么：

最后两个 AI 也写不对，空格问题一大堆，你tm b题纠结空格数量是不是有大彬，AI修了好几版就是有几个数据过不去，qnmd 大模拟。

劳资打竞赛就没见过这么逆天的。

## 一些总结

感觉 openAI 对码风的把控不太好，和我给的代码区别比较大，可以看 `表达式求值1` 的部分。

gemini 的码风对标就比较好，比较相近，可以看 `表达式求值2` 的部分。

码风提示词代码取自 (code)[https://codeforces.com/contest/2162/submission/344290644]：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3010;
#define mkp make_pair

int T,n,m;
pair<int,int>s[N];
int a[N];
int pre[N];

int calc(int a,int b) {
    for(int i=1;i<=m;i++) {
        auto [l,r]=s[i];
        if(l<=a&&r>=a) {
            if(!(l<=b&&r>=b)) return 0;
        }
    }
    return 1;
}

void gen1(int w1,int w2) {
    a[w1]=0; a[w2]=1;
    for(int i=1,k=2;i<=n;i++) {
        if(i==w1||i==w2) continue;
        a[i]=k++;
    }
}

void solve() {
    for(int i=1;i<=n;i++) pre[i]=0;
    sort(s+1,s+1+m);
    for(int i=1;i<=m;i++) {
        pre[s[i].first]++;
        pre[s[i].second+1]--;
    }
    for(int i=1;i<=n;i++) pre[i]+=pre[i-1];
    for(int i=1;i<=n;i++) {
        if(pre[i]==m) {
            a[i]=0;
            for(int j=1,k=1;j<=n;j++) {
                if(j==i) continue;
                a[j]=k++;
            }
            return;
        }
    }

    for(int i=1;i<=n;i++) {
        if(i-1>=1&&calc(i,i-1)) {gen1(i,i-1); return;}
        if(i+1<=n&&calc(i,i+1)) {gen1(i,i+1); return;}
    }
    a[1]=0; a[2]=2; a[3]=1;
    for(int i=4;i<=n;i++) a[i]=i-1;
}

int main() {
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++) {
            scanf("%d%d",&s[i].first,&s[i].second);
        }
        solve();
        for(int i=1;i<=n;i++) printf("%d ",a[i]);
        puts("");
    }
}
```