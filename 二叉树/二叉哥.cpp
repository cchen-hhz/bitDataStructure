#include<bits/stdc++.h>
int num,s,flag;  
   
void count(int n,int m)  
{  
    if(s>m||n==0) return;  
    int a=pow(2,s)-1;  
    if(n-a>0)   
    {  
        num+=pow(2,s-1);  
        if(!flag) s++;  
        count(n-a,m);  
    }  
    if(n-a==0)  
    {  
        num+=pow(2,s-1);  
        return;  
    }  
    if(n-a<0)  
    {  
        s--;  
        flag=1;  
        count(n-1,m);  
    }  
    return;  
}  
  
int main(){  
    int t,n,m;  
    scanf("%d",&t);  
    while(t--)  
    {  
        scanf("%d%d",&n,&m);  
        if(n<m+1)  
        {  
            printf("0\n");  
            continue;  
        }  
        if(n==m+1)  
        {  
            printf("1\n");  
            continue;  
        }  
        n=n-m-1;  
        num=1;  
        s=1;  
        flag=0;  
        count(n,m);  
        printf("%d\n",num);   
    }  
}