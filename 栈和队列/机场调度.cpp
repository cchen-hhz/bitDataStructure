#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  
#include<math.h>  
int main()  
{  
    int paodao,jiangluo,qifei;  
    int jiang,fei;  
    int i,j,k,m=0,n=0;  
    scanf("%d %d %d",&paodao,&jiangluo,&qifei);  
    int chang[paodao];  
    memset(chang,0,sizeof(chang));  
    int jiang1=0,fei1=0,time=0;  
    int flag=0;  
    int busy[paodao];  
    float busys=0;  
    float abusy=0;  
    for(i=0;i<paodao;i++)  
    {  
        busy[i]=0;  
    }  
    float wait1=0,wait2=0;  
    printf("Current Time:    0\n");  
    scanf("%d %d",&jiang,&fei);  
    jiang1+=jiang;  
    fei1+=fei;  
    while(jiang1>=0&&fei1>=0)  
    {  
        for(i=0;i<paodao;i++)  
        {  
            if(chang[i]==0)  
            {  
                if(jiang1>0)  
                {  
                    m+=1;  
                    printf("airplane %d is ready to land on runway %02d\n",5000+m,i+1);  
                    chang[i]=jiangluo;  
                    jiang1-=1;  
                }  
                else if(jiang1==0&&fei1!=0)  
                {  
                    n+=1;  
                    printf("airplane %04d is ready to takeoff on runway %02d\n",n,i+1);  
                    chang[i]=qifei;  
                    fei1-=1;  
                }     
            }  
            if(chang[i]!=0)  
            {  
                busy[i]++;  
            }  
        }  
        time+=1;  
        printf("Current Time: %4d\n",time);  
        if(jiang1>0)  
        {  
            wait1+=jiang1;  
        }  
        if(fei1>0)  
        {  
            wait2+=fei1;  
        }  
        for(i=0;i<paodao;i++)  
        {  
            if(chang[i]==1)  
            {  
                printf("runway %02d is free\n",i+1);  
                chang[i]=0;  
            }  
            else if(chang[i]>1)  
            {  
                chang[i]-=1;  
            }  
        }  
        scanf("%d %d",&jiang,&fei);  
        if(jiang>=0&&fei>=0)  
        {  
            jiang1+=jiang;  
            fei1+=fei;  
        }  
        else if(jiang<0&&fei<0)  
        {  
            break;  
        }  
    }  
    while(jiang1>=0&&fei1>=0)  
    {  
        flag=0;  
        for(i=0;i<paodao;i++)  
        {  
            if(chang[i]==0)  
            {  
                if(jiang1>0)  
                {  
                    m+=1;  
                    printf("airplane %d is ready to land on runway %02d\n",5000+m,i+1);  
                    chang[i]=jiangluo;  
                    jiang1-=1;  
                }  
                else if(jiang1==0&&fei1!=0)  
                {  
                    n+=1;  
                    printf("airplane %04d is ready to takeoff on runway %02d\n",n,i+1);  
                    chang[i]=qifei;  
                    fei1-=1;  
                }     
            }  
            if(chang[i]!=0)  
            {  
                busy[i]++;  
            }  
        }  
        time+=1;  
        printf("Current Time: %4d\n",time);  
        if(jiang1>0)  
        {  
            wait1+=jiang1;  
        }  
        if(fei1>0)  
        {  
            wait2+=fei1;  
        }  
        for(i=0;i<paodao;i++)  
        {  
            if(chang[i]==1)  
            {  
                printf("runway %02d is free\n",i+1);  
                chang[i]=0;  
            }  
            else if(chang[i]>1)  
            {  
                chang[i]-=1;  
            }  
        }  
        if(jiang1==0&&fei1==0)  
        {  
            for(i=0;i<paodao;i++)  
            {  
                if(chang[i]!=0)  
                {  
                    flag=1;  
                }  
            }  
            if(flag==0)  
            {  
                break;  
            }  
        }  
    }  
    printf("simulation finished\n");  
    printf("simulation time: %4d\n",time);  
    float await1,await2;  
    await1=wait1/m;  
    await2=wait2/n;  
    printf("average waiting time of landing: %4.1f\n",await1);  
    printf("average waiting time of takeoff: %4.1f\n",await2);  
    for(i=0;i<paodao;i++)  
    {  
        printf("runway %02d busy time: %4d\n",i+1,busy[i]);  
        busys+=busy[i];  
    }  
    abusy=(busys*100)/(time*paodao);  
    printf("runway average busy time percentage: %4.1f%%\n",abusy);  
}