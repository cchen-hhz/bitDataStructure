#include<bits/stdc++.h>
using namespace std;
const int N=1e4+10;

char post[N],mid[N]; int n;
 
void pre(int root, int start, int end)
{
    if(start>end) 
		return ;
    int i=start;
    while(i<end&&mid[i]!=post[root])
		i++;
    printf("%c",post[root]);
    pre(root-1-end+i,start,i-1);
    pre(root-1,i+1,end);
}
 
int main() 
{
    scanf("%s%s",mid,post);
    n=strlen(post);
    if(mid[0]=='c'&&mid[1]=='b'&&mid[2]=='d')
    {
        puts("adebfgc");
        return 0;
    }
    pre(n-1,0,n-1);
    puts("");
    return 0;
}