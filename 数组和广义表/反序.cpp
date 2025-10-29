#include<bits/stdc++.h>
using namespace std;

string s;

int main() {
    cin>>s;
    int n=s.size();
    for(int i=n-1;i>=0;i--) {
        if(s[i]=='(') putchar(')');
        else if(s[i]==')') putchar('(');
        else putchar(s[i]);
    }
    puts("");
}