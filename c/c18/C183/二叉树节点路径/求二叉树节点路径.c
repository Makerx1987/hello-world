#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXLEN 100
#define NLAYER 4
#define MAXSIZE 16
typedef struct BiTNode // 定义二叉树节点结构
{
	char data;						 // 数据域
	struct BiTNode *LChild, *RChild; // 左右孩子指针域
} BiTNode, *BiTree;
BiTree T;
typedef BiTree elemtype;
typedef struct sqstack
{
	elemtype stack[MAXSIZE];
	int top;
} sqstack;
sqstack S, S3;
void Initstack(sqstack *s)
{
	s->top = 0;
}
void Push(sqstack *s, elemtype x)
{
	if (s->top == MAXSIZE - 1)
		printf("ERROR,Overflow!\n");
	else
	{
		s->top++;
		s->stack[s->top] = x;
	}
}
void Pop(sqstack *s)
{
	if (s->top == 0)
		printf("ERROR,Underflow!\n");
	else
	{
		printf("%c  ", s->stack[s->top]->data);
		s->top--;
	}
}
void Popall(sqstack *s)
{
	if (s->top == 0)
		printf("ERROR,Underflow!\n");
	else
	{
		printf("\n\n路径为：");
		while (s->top > 0)
		{
			printf("%c<--", s->stack[s->top]->data);
			s->top--;
		}
	}
	printf("结束");
}
void sqdelete(sqstack *s)
{
	if (s->top == 0)
		printf("ERROR,Underflow!\n");
	else
	{
		s->top--;
	}
}
//(1) 建立二叉树
void CreateBiTree(BiTree *bt)
{ // 按照先序序列建立二叉树的二叉链表的过程
	char ch;
	scanf("%c", &ch);
	if (ch == '#')
		*bt = NULL;
	else
	{
		*bt = (BiTree)calloc(1, sizeof(BiTNode)); // 生成一个新结点
		(*bt)->data = ch;
		CreateBiTree(&((*bt)->LChild)); // 生成左子树
		CreateBiTree(&((*bt)->RChild)); // 生成右子树
	}
}

//(2) 树型打印二叉树
void TranslevelPrint(BiTree bt)
{ //本算法实现二叉树的按层打印
	struct node
	{
		BiTree vec[MAXLEN]; // 存放树结点
		int layer[MAXLEN];  // 结点所在的层
		int locate[MAXLEN]; // 打印结点的位置
		int front, rear;
	} q; // 定义队列q
	int i, j, k;
	int nLocate;
	j = 1;
	k = 0;
	q.front = 0; // 初始化队列q队头，队尾
	q.rear = 0;
	printf("   ");
	q.vec[q.rear] = bt; // 将二叉树根节点入队列
	q.layer[q.rear] = 1;
	q.locate[q.rear] = 20;
	q.rear = q.rear + 1;
	while (q.front < q.rear)
	{
		bt = q.vec[q.front];
		i = q.layer[q.front];
		nLocate = q.locate[q.front];
		if (j < i) // 进层打印时换行
		{
			printf("\n");
			printf("\n");
			j = j + 1;
			k = 0;
			while (k < nLocate)
			{
				printf("   ");
				k++;
			}
		}
		while (k < (nLocate - 1)) // 利用结点深度控制横向位置
		{
			printf("   ");
			k++;
		}
		printf("%c", bt->data);
		q.front = q.front + 1;
		if (bt->LChild != NULL) // 存在左子树，将左子树根节点入队列
		{
			q.vec[q.rear] = bt->LChild;
			q.layer[q.rear] = i + 1;
			q.locate[q.rear] = (int)(nLocate - pow(2, NLAYER - i - 1));
			q.rear = q.rear + 1;
		}
		if (bt->RChild != NULL) // 存在右子树，将右子树根节点入队列
		{
			q.vec[q.rear] = bt->RChild;
			q.layer[q.rear] = i + 1;
			q.locate[q.rear] = (int)(nLocate + pow(2, NLAYER - i - 1));
			q.rear = q.rear + 1;
		}
	}
}

//(3) 输出结点
void Visit(char ch)
{
	printf("%c ", ch);
}

//(4) 先序遍历二叉树
void PreOrder(BiTree root)
{ // 先序遍历二叉树, root为指向二叉树(或某一子树)根结点的指针
	if (root != NULL)
	{
		Visit(root->data);		// 访问根结点
		PreOrder(root->LChild); // 先序遍历左子树
		PreOrder(root->RChild); // 先序遍历右子树
	}
}

//(5) 中序遍历二叉树
void InOrder(BiTree root)
{ // 中序遍历二叉树, root为指向二叉树(或某一子树)根结点的指针
	if (root != NULL)
	{
		InOrder(root->LChild); // 中序遍历左子树
		Visit(root->data);	 // 访问根结点
		InOrder(root->RChild); // 中序遍历右子树
	}
}
int PostTreeDepth(BiTree root);
//(6) 后序遍历二叉树
void PostOrder(BiTree root)
{ //后序遍历二叉树，root为指向二叉树(或某一子树)根结点的指针
	BiTree lroot, rroot;
	int i = 0;
	if (root != NULL)
	{
		Push(&S, root);
		lroot = root->LChild;
		rroot = root->RChild;
		while (S.top != 0)
		{
			while (lroot != NULL)
			{
				Push(&S, lroot);
				lroot = lroot->LChild;
			}
			i = S.top;
			root = S.stack[i]->RChild;

			while (root == NULL)
			{

				Pop(&S);
				--i;
				if (i <= 0)
					break;
				if (S.stack[i] == S3.stack[S3.top])
				{
					sqdelete(&S3);
					continue;
				}
				root = S.stack[i]->RChild;
			}
			if (i <= 0)
				break;
			Push(&S3, S.stack[i]);
			Push(&S, root);
			lroot = root->LChild;
		}
	}
}
//6.1调试模式后序遍历二叉树，root为指向二叉树(或某一子树)根结点的指针
void PostOrderbug(BiTree root)
{
	BiTree lroot, rroot;
	int i = 0;
	if (root != NULL)
	{
		Push(&S, root);
		printf("%c进栈\n", root->data);
		lroot = root->LChild;
		rroot = root->RChild;
		while (S.top != 0)
		{
			while (lroot != NULL)
			{
				Push(&S, lroot);
				printf("%c进栈\n", lroot->data);
				lroot = lroot->LChild;
			}
			i = S.top;
			root = S.stack[i]->RChild;

			while (root == NULL)
			{

				Pop(&S);
				printf("出栈\n");
				--i;
				if (i <= 0)
					break;
				if (S.stack[i] == S3.stack[S3.top])
				{
					sqdelete(&S3);
					printf("上一个岔口记忆\n");
					continue;
				}
				root = S.stack[i]->RChild;
			}
			if (i <= 0)
				break;
			Push(&S3, S.stack[i]);
			printf("%c创建岔口记忆\n", S.stack[i]->data);
			Push(&S, root);
			printf("%c进栈\n", root->data);
			lroot = root->LChild;
		}
	}
}
//6.3查询路径
void PostOrderfind(BiTree root, char x)
{
	BiTree lroot, rroot;
	int i = 0;
	if (root != NULL)
	{
		Push(&S, root);
		if (S.stack[S.top]->data == x)
		{
			printf("非递归后序遍历找到结点！");
			Popall(&S);
			return;
		}
		lroot = root->LChild;
		rroot = root->RChild;
		while (S.top != 0)
		{
			while (lroot != NULL)
			{
				Push(&S, lroot);
				if (S.stack[S.top]->data == x)
				{
					printf("非递归后序遍历找到结点！");
					Popall(&S);
					return;
				}
				lroot = lroot->LChild;
			}
			i = S.top;
			root = S.stack[i]->RChild;

			while (root == NULL)
			{

				Pop(&S);
				--i;
				if (i <= 0)
					break;
				if (S.stack[i] == S3.stack[S3.top])
				{

					sqdelete(&S3);
					continue;
				}
				root = S.stack[i]->RChild;
			}
			if (i <= 0)
				break;
			Push(&S3, S.stack[i]);
			Push(&S, root);
			if (S.stack[S.top]->data == x)
			{
				printf("非递归后序遍历找到结点！");
				Popall(&S);
				return;
			}
			lroot = root->LChild;
		}
	}
}
//(7) 输出叶子结点
void PreOrderLeaf(BiTree root)
{ //先序遍历二叉树并输出叶子结点, root为指向二叉树根结点的指针
	if (root != NULL)
	{
		if (root->LChild == NULL && root->RChild == NULL)
			printf("%c ", root->data); // 输出叶子结点
		PreOrderLeaf(root->LChild);	// 先序遍历左子树
		PreOrderLeaf(root->RChild);	// 先序遍历右子树
	}
}

//(8) 输出叶子结点的个数
int LeafCount(BiTree root)
{
	int LeafNum;
	if (root == NULL)
		LeafNum = 0;
	else if ((root->LChild == NULL) && (root->RChild == NULL))
		LeafNum = 1;
	else
		LeafNum = LeafCount(root->LChild) + LeafCount(root->RChild); // 叶子数为左右子树的叶子数目之和

	return LeafNum;
}

//(9) 输出二叉树的深度
int PostTreeDepth(BiTree root) // 后序遍历求二叉树的深度递归算法
{
	int hl, hr, max;
	if (root != NULL)
	{
		hl = PostTreeDepth(root->LChild); // 求左子树的深度
		hr = PostTreeDepth(root->RChild); // 求右子树的深度
		max = hl > hr ? hl : hr;		  // 得到左、右子树深度较大者
		return (max + 1);				  // 返回树的深度
	}
	else
		return (0); // 如果是空树，则返回0
}

//(10) 主要工作函数。操作区用户界面
void mainwork()
{
	int yourchoice;

	printf("\n------------------------欢迎使用二叉树基本操作程序---------------------------\n");
	printf("\n                               菜 单 选 择                                 \n\n");
	printf("        1. 树状输出二叉树                        2. 先序遍历二叉树             \n");
	printf("        3. 中序遍历二叉树                        4. 非递归后序遍历二叉树（调试请输400）             \n");
	printf("        5. 输出叶子结点                          6. 输出叶子结点个数           \n");
	printf("        7. 输出二叉树的深度                      8. 退出                       \n");
	printf("        9. 查询结点路径                                            \n");
	printf("\n-----------------------------------------------------------------------------\n");
	printf("请输入你的选择：");
	scanf("%d", &yourchoice);
	while (!(yourchoice == 1 || yourchoice == 2 || yourchoice == 3 || yourchoice == 4 || yourchoice == 5 || yourchoice == 6 || yourchoice == 7 || yourchoice == 8 || yourchoice == 9 || yourchoice == 400))
	{
		printf("输入选择不明确，请重输\n");
		scanf("%d", &yourchoice);
	}
	while (1)
	{
		char x;
		switch (yourchoice)
		{
		case 1:
			printf("树的形状为:\n");
			TranslevelPrint(T);
			getch();
			break;
		case 2:
			printf("先序遍历序列为:");
			PreOrder(T);
			break;
		case 3:
			printf("\n中序遍历序列为:");
			InOrder(T);
			break;
		case 4:
			printf("\n非递归后序遍历序列为:");
			PostOrder(T);
			break;
		case 400:
			printf("\n调试非递归后序遍历:\n");
			PostOrderbug(T);
			break;
		case 5:
			printf("叶子结点为:");
			PreOrderLeaf(T);
			break;
		case 6:
			printf("叶子结点个数为:%d", LeafCount(T));
			break;
		case 7:
			printf("二叉树的深度为:%d", PostTreeDepth(T));
			break;
		case 8:
			system("cls");
			exit(0);
			break;
		case 9:
			printf("\n查找从指定结点到根节点的路径；若不存在结点，返回后序遍历；存在，返回路径。指定结点为:");
			fflush(stdin);
			scanf("%c", &x);
			PostOrderfind(T, x);
			break;
		default:
			break;
		}

		printf("\n------------------------欢迎使用二叉树基本操作程序---------------------------\n");
		printf("\n                               菜 单 选 择                                 \n\n");
		printf("        1. 树状输出二叉树                        2. 先序遍历二叉树             \n");
		printf("        3. 中序遍历二叉树                        4. 非递归后序遍历二叉树（调试请输400）             \n");
		printf("        5. 输出叶子结点                          6. 输出叶子结点个数           \n");
		printf("        7. 输出二叉树的深度                      8. 退出                       \n");
		printf("        9. 查询结点路径                                            \n");
		printf("\n-----------------------------------------------------------------------------\n");

		printf("\n请输入你的选择：");
		scanf("%d", &yourchoice);
	} //endwhile(1)

} //mainwork

//(11) 主函数。创建二叉树，调用工作区模块函数
void main()
{

	printf("首先请输入二叉树的先根结点序列，#表示空结点，叶子结点必须留出空结点：\n比如：ABD##E##CH###  ABDF###EG##H##CI##J##  ABCDEFGHI################################  ABDH##I##EJ##K##CFL##M##G#N## 等等，\n一个#表示挂在右子树，两个#则挂在最近的祖先节点……以此类推\n\n");
	CreateBiTree(&T);
	fflush(stdin);
	Initstack(&S);
	printf("请按菜单提示操作：\n");
	mainwork();
}