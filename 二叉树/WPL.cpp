#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

priority_queue<ll,vector<ll>,greater<ll> >qs;
int n; int w;
ll ans;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&w);
        qs.push(w);
    }
    for(int i=1;i<n;i++)
    {
        ll w1=qs.top(); qs.pop();
        ll w2=qs.top(); qs.pop();
        ans+=w1+w2;
        qs.push(w1+w2);
    }
    printf("WPL=%lld\n",ans);
}