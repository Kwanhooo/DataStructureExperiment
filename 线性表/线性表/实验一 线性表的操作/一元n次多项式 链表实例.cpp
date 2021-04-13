#include <iostream>
#include <string>
#include <cstdio>
#include <malloc.h>

using namespace std;

#define SUCCESS 1
#define ERROR 0
#define INIT_SIZE 100
#define MAX_SIZE 200
#define TRUE 1
#define FALSE 0
#define INVALID_INPUT 666

//Status作为函数返回值的类型，返回函数工作的状态
typedef int Status;

//节点类型
typedef struct LinkListNode
{
	//data
	int exp;
	float coe;

	//index
	struct LinkListNode* next;
}*Link, * Position;

//链表类型
typedef struct SinglyLinkList
{
	Link head, tail;
	int elemAmount;
}LinkList;

int ElemAmount_1 = 0;
int ElemAmount_2 = 0;
int ElemAmount_3 = 0;

//初始化一个链表，其中包含了头指针，尾指针和元素个数变量
Status InitList(LinkList& l)
{
	Link p;
	p = (Link)malloc(20);
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

//判断一串字符串是否为数字串并返回布尔值
bool IsNumber(const char* str)
{

	double aa;
	int nn = sscanf_s(str, "%lf", &aa);
	return nn != 0;
}

//获取多项式的系数和指数
Status GetPoly(int length, LinkList l) {
	Link last = l.head;
	Link cur;
	cur = (Link)malloc(20);
	last->next = cur;

	for (size_t i = 0; i < length; i++)
	{
		if (cur == NULL)
		{
			perror("ERROR");
			return NULL;
		}
		else
		{
			char check[100];
			printf("请输入第%d项的指数：", i + 1);
			cin >> check;
			if (!IsNumber(check)) {
				perror("Invalid Input");
				exit(INVALID_INPUT);
			}
			else
				cur->exp = atoi(check);
			printf("请输入第%d项的系数：", i + 1);
			cin >> check;
			if (!IsNumber(check)) {
				perror("Invalid Input");
				exit(INVALID_INPUT);
			}
			else
				cur->coe = atoi(check);
		}
		last = cur;
		cur = (Link)malloc(20);
		last->next = cur;
	}
	l.tail = last;
	free(cur);
	return SUCCESS;
}

//输出多项式
Status PrintPoly(int length, LinkList l) {
	Link node = l.head->next;
	for (size_t i = 0; i < length - 1; i++)
	{
		if (node->coe == 0)
			continue;
		else {
			if (node->coe == 1)
				printf(" X^%d +", node->exp);
			else
				printf(" (%.2f)*X^%d +", node->coe, node->exp);
		}
		node = node->next;
	}

	if (node->coe != 0)
	{
		if (node->coe == 1)
			printf(" X^%d", node->exp);
		else
			printf(" (%.2f)*X^%d", node->coe, node->exp);
	}
	return SUCCESS;
}

//将多项式按照降幂排序重新排列
Status SortPoly(int& length, LinkList& l) {
	bool isChanged = true;
	bool isEqual = true;
	int equalCase = 0;
	Link node = l.head;

	//降幂排序所有的项
	while (isChanged)
	{
		isChanged = false;

		node = l.head->next;
		Link last = l.head;

		for (size_t i = 0; i < length; i++)
		{
			if (node->exp < node->next->exp) {
				Link temp;
				temp = node->next;
				node->next = temp->next;
				last->next = temp;
				temp->next = node;
				isChanged = true;
				last = last->next;
			}
			else {
				last = node;
				node = node->next;
			}
		}

	}

	//以下代码段用于合并，并释放一个指数值相同的节点
	node = l.head->next;
	for (size_t i = 0; i < length - 1; i++)
	{

		if (node->exp == node->next->exp) {
			node->coe = node->next->coe + node->coe;
			LinkListNode* tmp = node->next;
			node->next = tmp->next;
			equalCase++;
			free(tmp);
		}
		else
			node = node->next;
	}
	length -= equalCase;
	return SUCCESS;
}

//将两个多项式合并，按照降幂顺序排列
Status MergePoly(LinkList poly_1, LinkList poly_2, LinkList& poly_3) {
	InitList(poly_3);
	poly_3.head->next = poly_1.head->next;
	LinkListNode* p = poly_3.head->next;

	for (size_t i = 0; i < ElemAmount_1 - 1; i++)
	{
		p = p->next;
	}
	p->next = poly_2.head->next;
	ElemAmount_3 = ElemAmount_1 + ElemAmount_2;
	SortPoly(ElemAmount_3, poly_3);
	return SUCCESS;
}

int main() {
start:
	char* check = new char[50];//用于缓存输入的项数
	cout << "下面请输入第1个多项式" << endl;
	cout << "第1个多项式的项数是：";
	cin >> check;
	if (!IsNumber(check)) {//检测是否为非法输入
		perror("Invalid Input");
		exit(INVALID_INPUT);
	}
	else
		ElemAmount_1 = atoi(check);
	LinkList poly_1;
	InitList(poly_1);
	GetPoly(ElemAmount_1, poly_1);
	cout << "\n您输入的第1个多项式为：\n";
	PrintPoly(ElemAmount_1, poly_1);
	SortPoly(ElemAmount_1, poly_1);
	cout << endl << "降幂排序之后为：" << endl;
	PrintPoly(ElemAmount_1, poly_1);

	cout << "\n\n\n下面请输入第2个多项式" << endl;
	cout << "第2个多项式的项数是：";
	cin >> check;
	if (!IsNumber(check)) {
		perror("Invalid Input");
		exit(INVALID_INPUT);
	}
	else
		ElemAmount_2 = atoi(check);
	delete check;
	LinkList poly_2;
	InitList(poly_2);
	GetPoly(ElemAmount_2, poly_2);
	cout << "\n您输入的第2个多项式为：\n";
	PrintPoly(ElemAmount_2, poly_2);
	SortPoly(ElemAmount_2, poly_2);
	cout << endl << "降幂排序之后为：" << endl;
	PrintPoly(ElemAmount_2, poly_2);

	LinkList poly_3;
	MergePoly(poly_1, poly_2, poly_3);

	printf("\n\n多项式1和多项式2合并，降幂排序之后为：\n");
	PrintPoly(ElemAmount_3, poly_3);
	goto start;
	return 0;
	
}
