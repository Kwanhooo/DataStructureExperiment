#include <iostream>
#include <cstdio>
#include <malloc.h>

#define ERROR 0
#define SUCCESS 1
#define TRUE 1
#define FALSE 0
#define INIT_NODE_SIZE 10

//ERROR_EXIT_CODE
#define	UNKNOWN_ERROR 0x474544D8

//开启DEBUG输出
#define DEBUG_MODE_ON

typedef int Status;
typedef char elemType;

//二叉树节点
typedef struct TreeNode
{
	TreeNode* left;
	TreeNode* right;
	elemType data;
}*Node;

//二叉树
typedef struct BinaryTree
{
	Node root;
	int node_amount;
}Tree;

Node create()
{
	std::cout << "create() is called!" << std::endl;
	Node n;
	char temp_char;
	temp_char = getchar();
	if (temp_char == '#')
		return NULL;
	n = (Node)malloc(sizeof(TreeNode));
	if (n == NULL)
		exit(OVERFLOW);
	n->data = temp_char;
	n->left = create();
	n->right = create();
	return n;
}

void visit(Node n)
{
	std::cout << n->data ;
}

//三种遍历方式
//测试用例:
//Input:
//+**/A##B##C##D##E##
//InOrder
//A/B*C*D+E
//PostOrder
//AB/C*D*E+
Status pre_order_traverse(Node n)
{
	if (n == NULL)
		return NULL;
	visit(n);
	pre_order_traverse(n->left);
	pre_order_traverse(n->right);
	return SUCCESS;
}

Status mid_order_traverse(Node n)
{
	if (n == NULL)
		return NULL;
	mid_order_traverse(n->left);
	visit(n);
	mid_order_traverse(n->right);
	return SUCCESS;
}

Status after_order_traverse(Node n)
{
	if (n == NULL)
		return NULL;
	after_order_traverse(n->left);
	after_order_traverse(n->right);
	visit(n);
	return SUCCESS;
}

int main()
{
	Tree test_tree;
	std::cout << "Tips: 以下采用先序的方式创建Binary Tree，使用\'#\'代表该分支的终结" << std::endl;
	test_tree.root = create();
	std::cout << "先序遍历的结果：" << std::endl;
	pre_order_traverse(test_tree.root);
	std::cout << std::endl;
	std::cout << "中序遍历的结果：" << std::endl;
	mid_order_traverse(test_tree.root);
	std::cout << std::endl;
	std::cout << "后序遍历的结果：" << std::endl;
	after_order_traverse(test_tree.root);
	std::cout << std::endl;
	return 0;
}