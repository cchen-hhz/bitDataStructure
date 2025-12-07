#include<cstdio>
#include<cstdlib>
#include<cstdlib>

#define LH +1   //左高
#define EH 0    //等高
#define RH -1   //右高
typedef struct NODE
{
	char data; //数据域 
	int bf; //平衡因子 
	struct NODE *lchild; //左孩子 
	struct NODE *rchild; //右孩子 
}BSnode, *BSTree;

void R_Rotate(BSTree *ptr)//右旋
{
	BSTree lc = (*ptr)->lchild; //lc指向的*ptr的左孩子的根结点 
	(*ptr)->lchild = lc->rchild; //lc的右子树挂接为*ptr的左子树 
	lc->rchild = *ptr;
	*ptr = lc; //ptr指向新的结点" 
}
void L_Rotate(BSTree *ptr)//左旋
{
	BSTree rc = (*ptr)->rchild;   //rc指向的*ptr的由孩子的根结点
	(*ptr)->rchild = rc->lchild;   //rc的左子树挂接为*ptr的右子树
	rc->lchild = *ptr;
	*ptr = rc;                  //ptr指向新的结点
}
void LeftBalance(BSTree *root)//左平衡旋转处理
{
	BSTree lc;
	BSTree rd;
	lc = (*root)->lchild; //ls指向*root的左根结点
						  //检测*root的左子树的平衡度，并作相应处理
	switch (lc->bf)
	{
		case LH:
		{
			//新结点插入在*root的左孩子的左子树上，要做单右旋处理
			(*root)->bf = lc->bf = EH;
			R_Rotate(root);
			break;
		}
		case RH:
		{
			//新结点插入在*root左孩子的右子树上要做双旋处理
			//rd指向*t的左孩子的右子树根上
			rd = lc->rchild;
			switch (rd->bf)
			{
				//修改*root及其左孩子的平衡因子
				case LH:
				{
					(*root)->bf = RH;
					lc->bf = EH;
					break;
				}
				case EH:
				{
					(*root)->bf = lc->bf = EH;
					break;
				}
				case RH:
				{
					(*root)->bf = EH;
					lc->bf = LH;
					break;
				}
			}
			rd->bf = EH;
			//对*root的左子树左左旋平衡处理
			L_Rotate(&(*root)->lchild);
			//对*root做右旋平衡处理
			R_Rotate(root);
		}
	}
}
void RightBalance(BSTree *root)//右平衡旋转处理
{
	BSTree lc;
	BSTree rd;
	lc = (*root)->rchild;

	switch (lc->bf)
	{
		case RH:
		{
			(*root)->bf = lc->bf = EH;
			L_Rotate(root);
			break;
		}
		case LH:
		{
			rd = lc->lchild;
			switch (rd->bf)
			{
				case LH:
				{
					(*root)->bf = EH;
					lc->bf = RH;
					break;
				}
				case EH:
				{
					(*root)->bf = lc->bf = EH;
					break;
				}
				case RH:
				{
					(*root)->bf = LH;
					lc->bf = EH;
					break;
				}
			}
			rd->bf = EH;
			R_Rotate(&(*root)->rchild);
			L_Rotate(root);
		}
	}
}

int InsertAVL(BSTree *root, char e, bool *taller)
{
	if ((*root) == NULL)
	{
		//该树为一棵空树，创建一个新节点作为根节点
		(*root) = (BSTree)malloc(sizeof(BSnode));
		(*root)->bf = EH;
		(*root)->data = e;
		(*root)->lchild = NULL;
		(*root)->rchild = NULL;
		*taller = true;
	}
	else if (e == (*root)->data)//关键字相同，则不再继续插入
	{
		*taller = false;
		return 0;
	}
	else if (e < (*root)->data)//应该继续在*root的左子树进行搜索
	{
		if (!InsertAVL(&(*root)->lchild, e, taller))//未插入
		{
			return 0;
		}
		//已插入到*root的左子树中并且左子树长高
		if (*taller)
		{
			//检查*root的平衡度
			switch ((*root)->bf)
			{
				//原本左子树比右子树高
				case LH:
				{
					//平衡因子为-1
					//左旋
					LeftBalance(root);
					*taller = false;
					break;
				}
				//原本左右树一样高，现在因为左子树长高树长高
				case EH:
				{
					//平衡因子为0
					(*root)->bf = LH;
					*taller = true;
					break;
				}
				//原本右子树比左子树高，现在等高
				case RH:
				{
					//平衡因子为1
					(*root)->bf = EH;
					*taller = false;
					break;
				}
			}
		}
	}
	else
	{
		//应继续在*root的右子树中进行搜索    
		if (!InsertAVL(&(*root)->rchild, e, taller))//未插入
		{
			return 0;
		}
		//已插入到*root的右子树且右子树长高
		if (*taller)
		{
			//检查*root的平衡度
			switch ((*root)->bf)
			{
				case LH:
				{
					//原本左子树比右子树高，现在相等
					(*root)->bf = EH;
					*taller = false;
					break;
				}
				case EH:
				{
					//原来左右子树登高，现在因为右子树长高树长高
					(*root)->bf = RH;
					*taller = true;
					break;
				}
				case RH:
				{
					//原本右子树比左子树高，需要做右旋平衡处理 
					RightBalance(root);
					*taller = false;
					break;
				}
			}
		}
	}
	return 1;
}
void printBIT(BSTree root, int x)
{
	if (root != NULL)
	{
		printBIT(root->rchild, x + 1);
		for (int i = 0; i < x; i++)
			printf("    ");
		printf("%c\n", root->data);
		printBIT(root->lchild, x + 1);
	}
}
void preorder(BSTree root)
{
	if (root != NULL)
	{
		printf("%c", root->data);
		preorder(root->lchild);
		preorder(root->rchild);
	}
}
void inorder(BSTree root)//二叉树的中序遍历
{
	if (root != NULL)
	{
		inorder(root->lchild);
		printf("%c", root->data);
		inorder(root->rchild);
	}
}
void postorder(BSTree root)
{
	if (root != NULL)
	{
		postorder(root->lchild);
		postorder(root->rchild);
		printf("%c", root->data);
	}
}
int main()
{
	char e;
	bool taller;//taller变量反应T长高与否
	BSTree root = NULL;

	while (e = getchar())
	{
		if (e == '\n')
			break;
		InsertAVL(&root, e, &taller);
	}
	//先序
	printf("Preorder: ");
	preorder(root);
	printf("\n");
	//中序
	printf("Inorder: ");
	inorder(root);
	printf("\n");
	//后序
	printf("Postorder: ");
	postorder(root);
	printf("\n");
	
	printf("Tree:\n");
	printBIT(root, 0);
	//system("pause");
	return 0;
}