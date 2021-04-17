#include <iostream>
#include <malloc.h>
#include <cstdio>
#include<cassert>

#define ERROR 0
#define SUCCESS 1
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE 300
#define STACK_INCREMENT 10
#define QUEUE_MAXSIZE 100

//ERROR_EXIT_CODE
#define	UNKNOWN_ERROR 0x474544D8

//开启DEBUG输出
#define DEBUG_MODE_ON

typedef int Status;
typedef char DataType;

//全局变量
int node_amount = 0;
int degree_1_node_amount = 0;
int degree_2_node_amount = 0;
int leaf_node_amount = 0;
long long signed int max_elem;
long long signed int min_elem;

//二叉树节点
typedef struct TreeNode
{
	TreeNode* left;
	TreeNode* right;
	DataType data;

	int pre_order_counted_times;
	bool in_order_isCounted;
	bool post_order_isCounted;
}*Node;

//二叉树
typedef struct BinaryTree
{
	Node root;
	int node_amount;
}Tree;


//循环队列的顺序存储结构
typedef Node QElemType;

typedef struct {
	QElemType data[QUEUE_MAXSIZE];
	int front; //头指针
	int rear;//尾指针，队列非空时，指向队尾元素的下一个位置
}SqQueue;

//访问队列
Status queue_visit(QElemType item) {
	printf("%p", item);
	return SUCCESS;
}

//初始化空队列
Status InitQueue(SqQueue* sQ) {
	sQ->front = 0;
	sQ->rear = 0;
	return SUCCESS;
}

//将队列清空
Status ClearQueue(SqQueue* Q) {
	Q->front = Q->rear = 0;
	return SUCCESS;
}

//判断队列是否为空
Status QueueEmpty(SqQueue Q) {
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}

//返回队列中的元素个数
int QueueLength(SqQueue Q) {
	return (Q.rear - Q.front + QUEUE_MAXSIZE) % QUEUE_MAXSIZE;
}

//返回队头元素
Status GetHead(SqQueue Q, QElemType* e) {
	if (Q.front == Q.rear)//是否为空队列
		return ERROR;
	*e = Q.data[Q.front];
	return SUCCESS;
}

//在队尾插入元素
Status EnterQueue(SqQueue* Q, QElemType e) {
	if ((Q->rear + 1) % QUEUE_MAXSIZE == Q->front)//队列已满
		return ERROR;

	Q->data[Q->rear] = e;//插入队尾
	Q->rear = (Q->rear + 1) % QUEUE_MAXSIZE;//尾部指针后移，如果到最后则转到头部
	return SUCCESS;
}

//元素出队
Status DelQueue(SqQueue* Q, QElemType* e) {
	if (Q->front == Q->rear)//队列空
		return ERROR;
	*e = Q->data[Q->front];//返回队头元素
	Q->front = (Q->front + 1) % QUEUE_MAXSIZE;//队头指针后移，如到最后转到头部
	return SUCCESS;
}

//遍历队列元素
Status QueueTraverse(SqQueue Q) {
	int i = Q.front;
	while ((i + Q.front) != Q.rear) {
		queue_visit(Q.data[i]);
		i = (i + 1) % QUEUE_MAXSIZE;
	}
	printf("\n");
	return SUCCESS;
}


//以下为栈模块
typedef Node Elemtype;

typedef struct SqStack
{
	Elemtype* base;
	Elemtype* top;
	int stack_size;
}Stack;

//初始化一个栈
Status InitStack(Stack& s)
{
	s.base = (Elemtype*)malloc(STACK_INIT_SIZE * sizeof(Elemtype));
	if (s.base == nullptr)
	{
		perror("Unable to allocate to memory space");
		exit(OVERFLOW);
	}
	else {
		s.top = s.base;
		s.stack_size = STACK_INIT_SIZE;
		return SUCCESS;
	}
}

//将新的元素推入栈中
Status Push(Stack& s, Elemtype e)
{
	if ((s.top - s.base) >= s.stack_size) {//检查是否栈存满
		//重新追加空间，大小为STACK_INCREMENT
		s.base = (Elemtype*)realloc(s.base, s.stack_size + STACK_INCREMENT);
		//检查时是否成功分配到了内存空间
		if (s.base == nullptr)
		{
			perror("Unable to allocate to memory space");
			exit(OVERFLOW);
		}
		//更新栈顶位置和栈大小(stack_size)记录
		s.top = s.base + s.stack_size;
		s.stack_size = s.stack_size + STACK_INCREMENT;
	}
	//*s.top++ = e;
	*s.top = e;
	s.top++;
	return SUCCESS;
}

//出栈
Status Pop(Stack& s, Elemtype& e)
{
	if (s.top == s.base)
	{
		return ERROR;
	}
	else
	{
		s.top--;
		e = *s.top;
		return SUCCESS;
	}
}

//判断栈是否为空
Status StackEmpty(Stack s)
{
	if (s.base == s.top)
		return TRUE;
	else
		return FALSE;
}

//创建二叉树节点
Node create()
{
	//std::cout << "create() is called!" << std::endl;
	Node n;
	DataType temp_var;
	temp_var = getchar();
	if (temp_var == '#')
		return nullptr;
	n = (Node)malloc(sizeof(TreeNode));
	if (n == nullptr)
		exit(OVERFLOW);
	n->data = temp_var;
	n->pre_order_counted_times = 0;
	n->in_order_isCounted = false;
	n->post_order_isCounted = false;
	n->left = create();
	n->right = create();
	return n;
}

//访问二叉树节点并输出储存的数据
void visit(Node n)
{
	std::cout << n->data;
}

//先序递归遍历
Status pre_order_traverse(Node n)
{
	if (n == nullptr)
		return NULL;
	visit(n);
	pre_order_traverse(n->left);
	pre_order_traverse(n->right);
	return SUCCESS;
}

//中序递归遍历
Status in_order_traverse(Node n)
{
	if (n == nullptr)
		return NULL;
	in_order_traverse(n->left);
	visit(n);
	in_order_traverse(n->right);
	return SUCCESS;
}

//后序递归遍历
Status post_order_traverse(Node n)
{
	if (n == nullptr)
		return NULL;
	post_order_traverse(n->left);
	post_order_traverse(n->right);
	visit(n);
	return SUCCESS;
}

SqQueue q;
Node root_node;

//遍历队列
Status queue_traverse(Node n)
{
	if (n == root_node && n->left == nullptr && n->right == nullptr)
	{
		visit(n);
		return SUCCESS;
	}
	visit(n);
	if (n->left != nullptr)
		EnterQueue(&q, n->left);
	if (n->right != nullptr)
		EnterQueue(&q, n->right);
	if (QueueEmpty(q) && n != root_node)
		return SUCCESS;
	DelQueue(&q, &n);
	queue_traverse(n);
}

void count_record()
{
	node_amount++;
}

int recursion_get_node_amount(Node n)//递归做法
{
	if (n == nullptr)
		return NULL;
	count_record();
	recursion_get_node_amount(n->left);
	recursion_get_node_amount(n->right);
	return SUCCESS;
}

//非递归先序遍历并统计节点数据
void pre_get_node_info(Tree t)
{
	Node n = t.root;
	Stack node_stack;
	InitStack(node_stack);
	while (true)
	{
		if (n == t.root)
		{

			if (t.root->left != nullptr && t.root->right != nullptr)
			{
				if (t.root->pre_order_counted_times == 0)
				{
					max_elem = static_cast<int>(t.root->data);//在根节点初始化最大值，最小值基准
					min_elem = static_cast<int>(t.root->data);
					degree_2_node_amount++;
					visit(n);
					node_amount++;
					t.root->pre_order_counted_times++;
					Push(node_stack, t.root);
					n = t.root->left;
					continue;
				}
				if (t.root->pre_order_counted_times == 1)
				{
					t.root->pre_order_counted_times++;
					Push(node_stack, t.root);
					n = t.root->right;
					continue;
				}
				if (t.root->pre_order_counted_times == 2)
				{
					break;
				}
			}
			if (t.root->left != nullptr && t.root->right == nullptr)
			{
				if (t.root->pre_order_counted_times == 0)
				{
					max_elem = static_cast<int>(t.root->data);//在根节点初始化最大值，最小值基准
					min_elem = static_cast<int>(t.root->data);
					degree_1_node_amount++;
					visit(n);
					node_amount++;
					t.root->pre_order_counted_times++;
					Push(node_stack, t.root);
					n = t.root->left;
					continue;
				}
				if (t.root->pre_order_counted_times == 1)
				{
					break;
				}
			}
			if (t.root->left == nullptr && t.root->right != nullptr)
			{
				if (t.root->pre_order_counted_times == 0)
				{
					max_elem = static_cast<int>(t.root->data);//在根节点初始化最大值，最小值基准
					min_elem = static_cast<int>(t.root->data);
					degree_1_node_amount++;
					visit(n);
					node_amount++;
					t.root->pre_order_counted_times++;
					Push(node_stack, t.root);
					n = t.root->right;
					continue;
				}
				if (t.root->pre_order_counted_times == 1)
				{
					break;
				}
			}
			if (t.root->left == nullptr && t.root->right == nullptr)
			{
				max_elem = static_cast<int>(t.root->data);//最大/最小值皆为根节点本身
				min_elem = static_cast<int>(t.root->data);
				leaf_node_amount++;
				visit(n);
				node_amount = 1;
				break;
			}
		}

		if (n->left != nullptr && n->right != nullptr && n != t.root)
		{
			if (n->pre_order_counted_times == 0)
			{
				if (static_cast<int>(n->data) > max_elem)
					max_elem = n->data;
				if (static_cast<int>(n->data) < min_elem)
					min_elem = n->data;
				degree_2_node_amount++;
				visit(n);
				node_amount++;
				n->pre_order_counted_times++;
				Push(node_stack, n);
				n = n->left;
				continue;
			}
			if (n->pre_order_counted_times == 1)
			{
				n->pre_order_counted_times++;
				Push(node_stack, n);
				n = n->right;
				continue;
			}
			if (n->pre_order_counted_times == 2)
			{
				Pop(node_stack, n);
			}
		}
		if (n->left != nullptr && n->right == nullptr)
		{
			if (n->pre_order_counted_times == 0)
			{
				if (static_cast<int>(n->data) > max_elem)
					max_elem = n->data;
				if (static_cast<int>(n->data) < min_elem)
					min_elem = n->data;
				degree_1_node_amount++;
				visit(n);
				node_amount++;
				n->pre_order_counted_times++;
				Push(node_stack, n);
				n = n->left;
				continue;
			}
			if (n->pre_order_counted_times == 1)
			{
				Pop(node_stack, n);
				continue;
			}
		}
		if (n->left == nullptr && n->right != nullptr)
		{
			if (n->pre_order_counted_times == 0)
			{
				if (static_cast<int>(n->data) > max_elem)
					max_elem = n->data;
				if (static_cast<int>(n->data) < min_elem)
					min_elem = n->data;
				degree_1_node_amount++;
				visit(n);
				node_amount++;
				n->pre_order_counted_times++;
				Push(node_stack, n);
				n = n->right;
				continue;
			}
			if (n->pre_order_counted_times == 1)
			{
				Pop(node_stack, n);
				continue;
			}
		}
		if (n->left == nullptr && n->right == nullptr)
		{
			if (static_cast<int>(n->data) > max_elem)
				max_elem = n->data;
			if (static_cast<int>(n->data) < min_elem)
				min_elem = n->data;
			leaf_node_amount++;
			visit(n);
			node_amount++;
			Pop(node_stack, n);
		}
	}
}

//非递归中序遍历
void in_order_stack_traverse(Tree t)
{
	Stack s;
	InitStack(s);
	Node n = t.root;
	if (n->left == nullptr && n->right == nullptr)
	{
		visit(n);
		return;
	}
	while (true)
	{
		if (n->left != nullptr && !n->left->in_order_isCounted)
		{
			Push(s, n);
			n = n->left;
			continue;
		}
		else
		{
			if (!n->in_order_isCounted)
			{
				visit(n);
				n->in_order_isCounted = true;
			}
			if (n->right != nullptr && !n->right->in_order_isCounted)
			{
				Push(s, n);
				n = n->right;
				continue;
			}
			Pop(s, n);
		}
		if (StackEmpty(s))
		{
			if (n->left != nullptr && n->right != nullptr && n->left->in_order_isCounted &&
				n->right->in_order_isCounted)
				return;
			if (n->left != nullptr && n->right == nullptr && n->left->in_order_isCounted && n->in_order_isCounted == true)
				return;
			if (n->left == nullptr && n->right != nullptr && n->right->in_order_isCounted && n->in_order_isCounted == true)
				return;
		}
	}
}

//非递归方式后序遍历
void post_order_stack_traverse(Tree t)
{
	Node n;
	n = t.root;
	Stack s;
	InitStack(s);
	if (n->left == nullptr && n->right == nullptr)
	{
		visit(n);
		return;
	}
	while (true)
	{
		if (n->left != nullptr && !n->left->post_order_isCounted)
		{
			Push(s, n);
			n = n->left;
			continue;
		}
		else
		{
			if (n->right != nullptr && !n->right->post_order_isCounted)
			{
				Push(s, n);
				n = n->right;
				continue;
			}
			else
			{
				if (!n->post_order_isCounted)
				{
					visit(n);
					n->post_order_isCounted = true;
				}
				Pop(s, n);
			}
		}
		if (StackEmpty(s))
		{
			if (n->left != nullptr && n->right != nullptr && n->left->post_order_isCounted &&
				n->right->post_order_isCounted && n->post_order_isCounted)
				return;
			if (n->left != nullptr && n->right == nullptr && n->left->post_order_isCounted && n->post_order_isCounted)
				return;
			if (n->left == nullptr && n->right != nullptr && n->right->post_order_isCounted && n->post_order_isCounted)
				return;
		}
	}
}

//测试用例:
//Input:
//+**/A##B##C##D##E##
//InOrder
//A/B*C*D+E
//PostOrder
//AB/C*D*E+

int main()
{
	//初始化一颗树（先序创建）
	Tree test_tree;
	std::cout << "Tips: 以下采用先序的方式创建Binary Tree，使用\'#\'代表该分支的终结" << std::endl;
	test_tree.root = create();


	//递归方法遍历
	std::cout << "递归方法的先序遍历的结果：" << std::endl;
	pre_order_traverse(test_tree.root);
	std::cout << std::endl;

	std::cout << "递归方法的中序遍历的结果：" << std::endl;
	in_order_traverse(test_tree.root);
	std::cout << std::endl;

	std::cout << "递归方法的后序遍历的结果：" << std::endl;
	post_order_traverse(test_tree.root);
	std::cout << std::endl << std::endl;

	//非递归方法遍历
	std::cout << "非递归方法的先序遍历的结果：" << std::endl;
	pre_get_node_info(test_tree);
	std::cout << std::endl;

	std::cout << "非递归方法的中序遍历的结果：" << std::endl;
	in_order_stack_traverse(test_tree);
	std::cout << std::endl;

	std::cout << "非递归方法的后序遍历的结果：" << std::endl;
	post_order_stack_traverse(test_tree);
	std::cout << std::endl << std::endl;


	//队列按层次遍历
	InitQueue(&q);
	root_node = test_tree.root;
	std::cout << "使用队列按层次遍历的结果：" << std::endl;
	queue_traverse(test_tree.root);
	std::cout << std::endl << std::endl;


	//输出节点统计信息
	std::cout << "利用递归方法查找到的二叉树的节点总数为：" << node_amount << std::endl;
	std::cout << "非递归方法查找到的二叉树的节点总数为：" << node_amount << std::endl;
	std::cout << "非递归方法查找到的二叉树度为2的节点总数为：" << degree_2_node_amount << std::endl;
	std::cout << "非递归方法查找到的二叉树度为1的节点总数为：" << degree_1_node_amount << std::endl;
	std::cout << "非递归方法查找到的二叉树叶子节点总数为：" << leaf_node_amount << std::endl;
	std::cout << "二叉树中数值最小的元素数值为：" << static_cast<int> (min_elem) << '\t' << \
		"转换为原始类型即：" << static_cast<DataType>(min_elem) << std::endl;
	std::cout << "二叉树中数值最大的元素数值为：" << static_cast<int> (max_elem) << '\t' << \
		"转换为原始类型即：" << static_cast<DataType>(max_elem) << std::endl;

	return 0;
}