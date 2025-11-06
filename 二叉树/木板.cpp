#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
typedef long long ll;

int n;
ll a[N];
int lc[N],rc[N];
int st[N],top;

void solve() {
    top=0;
    st[0]=0;
    for(int i=1;i<=n;i++) {
        while(top>0&&a[i]<=a[st[top]]) top--;
        lc[i]=st[top];
        st[++top]=i;
    }
    top=0;
    st[0]=n+1;
    for(int i=n;i>=1;i--) {
        while(top>0&&a[i]<=a[st[top]]) top--;
        rc[i]=st[top];
        st[++top]=i;
    }
    ll ans=0;
    for(int i=1;i<=n;i++) {
        ans=max(ans,a[i]*(rc[i]-lc[i]-1));
    } 
    printf("%lld\n",ans);
}

int main() {
    while(scanf("%d",&n)) {
        if(n==0) return 0;
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
        solve();
    }
}