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

int node_amount = 0;

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
	std::cout << n->data;
}

Status pre_order_traverse(Node n)
{
	if (n == NULL)
		return NULL;
	visit(n);
	pre_order_traverse(n->left);
	pre_order_traverse(n->right);
	return SUCCESS;
}

Status in_order_traverse(Node n)
{
	if (n == NULL)
		return NULL;
	in_order_traverse(n->left);
	visit(n);
	in_order_traverse(n->right);
	return SUCCESS;
}

Status post_order_traverse(Node n)
{
	if (n == NULL)
		return NULL;
	post_order_traverse(n->left);
	post_order_traverse(n->right);
	visit(n);
	return SUCCESS;
}

void count_record()
{
	node_amount++;
}

int get_node_amount(Node n)
{
	if (n == NULL)
		return NULL;
	count_record();
	get_node_amount(n->left);
	get_node_amount(n->right);
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
	in_order_traverse(test_tree.root);
	std::cout << std::endl;
	std::cout << "后序遍历的结果：" << std::endl;
	post_order_traverse(test_tree.root);
	std::cout << std::endl;

	get_node_amount(test_tree.root);
	std::cout << "二叉树的节点总数为：" << node_amount << std::endl;
	
	return 0;
}