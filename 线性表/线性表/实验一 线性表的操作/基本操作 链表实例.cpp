#include <iostream>
#include <cstdio>
#include <malloc.h>
#include <process.h>

using namespace std;

#define SUCCESS 1
#define ERROR 0
#define INIT_SIZE 10
#define MAX_SIZE 100
#define TRUE 1
#define FALSE 0

//int可改为其它数据类型
typedef int ElemType;
typedef int Status;

//节点类型
typedef struct LinkListNode
{
	ElemType data;
	struct LinkListNode* next;
}*Link, * Position;

//链表类型
typedef struct SinglyLinkList
{
	Link head, tail;
	int elemAmount;
}LinkList;

Status MakeNode(Link* p, ElemType e)
{
	*p = (Link)malloc(sizeof(LinkListNode));
	if (p == NULL)
	{
		perror("ERROR");
		return NULL;
	}
	else
	{
		(*p)->data = e;
		return SUCCESS;
	}
}

void FreeNode(Link p, LinkList l)
{
	Link search = l.head;
	while (search != NULL && search->next != p)
	{
		search = search->next;
	}
	if (search->next = p)
	{
		search->next = p->next;
	}
	free(p);
}

//初始化链表
Status InitList(LinkList& l)
{
	Link p;
	p = (Link)malloc(sizeof(Link));
	if (p != NULL)
	{
		p->next = NULL;
		l.head = p;
		l.tail = p;
		l.elemAmount = 0;
		return SUCCESS;
	}
	else
		perror("Cannot Initial LinkList");
}

//摧毁一个链表
Status DestroyList(LinkList& l)
{
	Link p = l.head;
	Link tmp;
	while (p != NULL)
	{
		tmp = p;
		p = p->next;
		free(tmp);
	}
	l.head = NULL;
	l.tail = NULL;
	l.elemAmount = NULL;
	return SUCCESS;
}

//链表清空
Status ClearList(LinkList& l)
{
	l.elemAmount = 0;
	return SUCCESS;
}

//将一个节点插入到头节点前
Status InsFirst(Link headNode, Link insertNode)
{
	insertNode->next = headNode;
	return SUCCESS;
}

//删除头节点
Status DelFirst(Link headNode, Link& q)
{
	q = headNode->next;
	free(headNode);
	return SUCCESS;
}
 
//在链表的尾部插入一个节点
Status Append(LinkList& l, Link s)
{
	l.tail->next = s;
	return SUCCESS;
}

//删除节点
Status Remove(LinkList& l, Link& q)
{
	q = l.tail;
	Link p = l.head;
	while (p->next != l.tail)
	{
		p = p->next;
	}
	l.tail = p;
	return SUCCESS;
}

//在p节点之前插入一个节点
Status InsBefore(LinkList& l, Link& p, Link s)
{
	Link tmp = l.head;
	while (tmp->next != p)
	{
		tmp = tmp->next;
	}
	tmp->next = s;
	s->next = p;
	p = s;
	return SUCCESS;
}

//在p节点之后插入一个节点
Status InsAfter(LinkList& l, Link& p, Link s)
{
	Link tmp = p->next;
	p->next = s;
	s->next = tmp;
	p = s;
	return SUCCESS;
}

//为节点p中的数据域赋值
Status SetCurElem(Link& p, ElemType e)
{
	p->data = e;
	return SUCCESS;
}

//获取p节点中存储的数据值
ElemType GetCurElem(Link p)
{
	return p->data;
}

//判断链表是否为空
Status ListEmpty(LinkList l)
{
	if (!l.head)
	{
		perror("The LinkList is not exist!");
		return ERROR;
	}
	if (l.head->next == NULL)
		return TRUE;
	else
		return FALSE;
}

//求取链表的元素个数
int ListLength(LinkList l)
{
	if (!l.head)
	{
		perror("The LinkList is not exist!");
		return ERROR;
	}
	return l.elemAmount;
}

//获取头指针
Position GetHead(LinkList l)
{
	return l.head;
}

//获取尾指针
Position GetLast(LinkList l)
{
	return l.tail;
}

//获取p节点的前驱
Position PriorPos(LinkList l, Link p)
{
	if (p = l.head)
		return ERROR;
	else
	{
		Link tmp = l.head;
		while (tmp->next != p)
		{
			tmp = tmp->next;
		}
		return tmp;
	}
}

//获取p节点的后继
Position NextPos(LinkList l, Link p)
{
	if (p = l.tail)
		return ERROR;
	else
	{
		return p->next;
	}
}

//返回指向链表中第index个节点的指针
Status LocatePos(LinkList l, int index, Link& p)
{
	if (!(index >= '0' && index <= '9') || index > l.elemAmount)
	{
		perror("Invalid index figure");
		return ERROR;
	}
	Link tmp = l.head;
	for (int i = 1; i < index; ++i)
	{
		tmp = tmp->next;
	}
	p = tmp;
	return SUCCESS;
}

//在链表L中寻找储存满足compare()条件的节点位置，并返回指向该节点的指针
Position LocateElem(LinkList l, ElemType e, Status(*compare)(ElemType, ElemType))
{
	Link p = l.head;
	while (p != NULL && !(compare(((*p).data), e)))
	{
		p = p->next;
	}
	return p;
}

//遍历链表
Status ListTraverse(LinkList l, Status (*visit)(LinkList l)) 
{
	Link p=l.head;
	while (p!=NULL)
	{
		if (visit(l))
			p = p->next;
		else
			return ERROR;
	}
	return SUCCESS;
}