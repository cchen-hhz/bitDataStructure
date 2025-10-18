void change(int n,int m,NODE*head)
{
    typedef struct{int rem;NODE*node;}Rem;
    int cap=64;
    Rem*map=(Rem*)malloc(cap*sizeof(Rem));
    if(!map){head->next=NULL;return;}
    int maplen=0;
    NODE*tail=head;
    int r=n%m;
    if(r==0){tail->next=NULL;free(map);return;}
    while(1){
        int found=-1;
        for(int i=0;i<maplen;i++)if(map[i].rem==r){found=i;break;}
        if(found!=-1){tail->next=map[found].node;break;}
        int old=r;
        long long temp=(long long)r*10LL;
        int digit=(int)(temp/m);
        r=(int)(temp%m);
        NODE*node=(NODE*)malloc(sizeof(NODE));
        if(!node){tail->next=NULL;free(map);return;}
        node->data=digit;
        node->next=NULL;
        tail->next=node;
        tail=node;
        if(maplen>=cap){
            int newcap=cap*2;
            Rem*pm=(Rem*)realloc(map,newcap*sizeof(Rem));
            if(!pm){free(map);tail->next=NULL;return;}
            map=pm;cap=newcap;
        }
        map[maplen].rem=old;
        map[maplen].node=node;
        maplen++;
        if(r==0){tail->next=NULL;break;}
    }
    free(map);
}