Status ListInsert(SqList &L,int i,ElemType e)
{
	if(i<1||i>L.length+1)return ERROR;
	if(L.length>=L.listsize){
		ElemType*newbase=(ElemType*)realloc(L.elem,(L.listsize+LIST_MAX_SIZE)*sizeof(ElemType));
		if(!newbase)return ERROR;
		L.elem=newbase;
		L.listsize+=LIST_MAX_SIZE;
	}
	for(int j=L.length;j>=i;j--)L.elem[j]=L.elem[j-1];
	L.elem[i-1]=e;
	L.length++;
	return OK;
}

Status GetElem(SqList L,int i,ElemType &e)
{
	if(i<1||i>L.length)return ERROR;
	e=L.elem[i-1];
	return OK;
}

int ListLength(SqList L)
{
	return L.length;
}