#include<cstdio>
#include<algorithm>
#include<vector>

int n;
std::vector<int>a;

void shiftd(std::vector<int>&a, int l, int r) {
    int u=l;
    int ch=u<<1;
    while(ch<=r) {
        if(ch+1<=r&&a[ch]<a[ch+1]) ch++;
        if(a[u]>=a[ch]) return;
        else {
            std::swap(a[u],a[ch]);
            u=ch;
            ch=u<<1;
        }
    }
}

void print(int n) {
    for(int i=1;i<=n;i++) {
        printf("%d ",a[i]);
    }
    putchar('\n');
}

int main() {
    scanf("%d",&n);
    a=std::vector<int>(n+1);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=n/2;i>=1;i--) shiftd(a,i,n);
    print(n);
    for(int i=1;i<=2;i++) {
        std::swap(a[1],a[n-i+1]);
        shiftd(a,1,n-i);
        print(n-i);
    }
}