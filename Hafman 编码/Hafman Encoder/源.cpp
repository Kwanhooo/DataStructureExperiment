#pragma warning (disable:4996)

#include <iostream>
#include <malloc.h>
#include <cstdio>
#include<cassert>
#include <string>
#include <algorithm>

#define ERROR 0
#define SUCCESS 1
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE 300
#define STACK_INCREMENT 10
#define QUEUE_MAXSIZE 100
#define OVERFLOW 3

//ERROR_EXIT_CODE
#define	INVALID_INPUT 0x474544D8

//开启DEBUG输出
#define DEBUG_MODE_ON

using namespace std;

typedef int Status;

int array_length;

//哈夫曼树节点
typedef struct HuffmanTreeNode
{
	char letter;
	int weight;
	string* huffman_code;
	HuffmanTreeNode* left;
	HuffmanTreeNode* right;
	bool isDeleted;
	int pre_order_counted_times;
}*TreeNode;

//哈夫曼树
typedef struct HuffmanTree
{
	HuffmanTreeNode* root;
	int node_amount;
}Tree;

typedef TreeNode Elemtype;

//将字母频度表存入二叉树节点，并将二叉树节点的地址存入数组中
void GetAlphabetFreq(TreeNode* node_array)
{
	cout << "**********获取字母频度表**********" << endl;

	TreeNode sp = (TreeNode)malloc(sizeof(HuffmanTreeNode));
	if (sp == nullptr)
		exit(OVERFLOW);
	sp->letter = ' ';
	cout << "请输入\' 空格 \'的权值：";
	cin >> sp->weight;
	sp->isDeleted = false;
	sp->left = nullptr;
	sp->right = nullptr;
	sp->pre_order_counted_times = 0;
	node_array[0] = sp;

	for (int i = 0; i < 26; ++i)
	{
		TreeNode tn = (TreeNode)malloc(sizeof(HuffmanTreeNode));
		if (tn == nullptr)
			exit(OVERFLOW);
		tn->letter = (char)('a' + i);
		cout << "请输入\' " << tn->letter << " \'的权值：";
		cin >> tn->weight;
		tn->isDeleted = false;
		tn->left = nullptr;
		tn->right = nullptr;
		tn->pre_order_counted_times = 0;
		node_array[i + 1] = tn;
	}
	cout << endl << "**********获取结束**********" << endl;
	array_length = 27;
}

TreeNode GetMinWeight(TreeNode* node_array)
{
	int min_index = 10000;
	int min_weight = 10000;
	for (int i = 0; i < array_length; ++i)
	{
		if (node_array[i]->weight < min_weight && node_array[i]->isDeleted == false)
		{
			min_weight = node_array[i]->weight;
			min_index = i;
		}
	}
	node_array[min_index]->isDeleted = true;
	return node_array[min_index];
}

bool isEmpty(TreeNode* node_array)
{
	for (int i = 0; i < array_length; ++i)
		if (node_array[i]->isDeleted == false)
			return false;
	return true;
}

void SaveNodeToArray(TreeNode new_node, TreeNode* node_array)
{
	node_array[array_length] = new_node;
	array_length++;
}

void CreateHuffmanTree(HuffmanTree& t, TreeNode* node_array)
{
	TreeNode parent_node = nullptr;
	while (true)
	{
		TreeNode node_1, node_2;
		node_1 = GetMinWeight(node_array);
		node_2 = GetMinWeight(node_array);
		parent_node = (TreeNode)malloc(sizeof(HuffmanTreeNode));
		if (parent_node == nullptr)
			exit(OVERFLOW);
		parent_node->isDeleted = false;
		parent_node->left = node_1;
		parent_node->right = node_2;
		parent_node->letter = '#';
		parent_node->weight = node_1->weight + node_2->weight;
		parent_node->pre_order_counted_times = 0;
		if (isEmpty(node_array))
			break;
		SaveNodeToArray(parent_node, node_array);
	}
	t.root = parent_node;
}

//访问二叉树节点并输出储存的数据
void visit(TreeNode n, string s)
{
	if (n->letter == '#')
		return;

	std::cout << '\'' << n->letter << '\'' << "的权值为：" << n->weight << ",Huffman编码为：" << s << endl;
}

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
Status Push(Stack& s, TreeNode e)
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

//产生Huffman编码
void HuffmanCodeGenerator(HuffmanTree t, string* huffman_code_list)
{
	string s;
	s = "";
	TreeNode n = t.root;
	Stack node_stack;
	InitStack(node_stack);
	while (true)
	{
		if (n == t.root)
		{
			if (n->pre_order_counted_times == 0)
			{
				n->pre_order_counted_times++;
				Push(node_stack, n);
				n = n->left;
				s += '1';
			}
			if (n->pre_order_counted_times == 1)
			{
				n->pre_order_counted_times++;
				Push(node_stack, n);
				n = n->right;
				s += '0';
			}
			if (n->pre_order_counted_times == 2)
				break;
		}
		else
		{
			if (n->letter == '#')
			{
				if (n->pre_order_counted_times == 0)
				{
					n->pre_order_counted_times++;
					Push(node_stack, n);
					n = n->left;
					s += '1';
				}
				if (n->pre_order_counted_times == 1)
				{
					n->pre_order_counted_times++;
					Push(node_stack, n);
					n = n->right;
					s += '0';
				}
				if (n->pre_order_counted_times == 2)
				{
					Pop(node_stack, n);
					s = s.substr(0, s.length() - 1);
				}
			}
			else
			{
				std::cout << '\'' << n->letter << '\'' << "的权值为：" << n->weight << ",Huffman编码为：" << s << endl;
				//n->huffman_code = (string*)malloc(100);
				//*(n->huffman_code) = s;
				if (n->letter != ' ')
					huffman_code_list[n->letter - 'a' + 1] = s;
				if (n->letter == ' ')
					huffman_code_list[0] = s;
				Pop(node_stack, n);
				s = s.substr(0, s.length() - 1);
			}
		}
	}
}

string SearchHuffmanCode(char c, string* huffman_code_list)
{
	return huffman_code_list[c - 'a' + 1];
}

string HuffmanEncoder(string plaintext, string* huffman_code_list)
{
	transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::tolower);
	string ciphertext = "";
	for (int i = 0; i < plaintext.length(); ++i)
	{
		if (plaintext.at(i) == ' ')
			ciphertext += huffman_code_list[0];
		else
			ciphertext += SearchHuffmanCode(plaintext.at(i), huffman_code_list);
	}
	return ciphertext;
}

string HuffmanDecoder(string ciphertext, string* huffman_code_list)
{
	string plaintext = "";
	int length = 1;
	int start_index = 0;
	bool isMatch = false;
	while (true)
	{
		string temp = ciphertext.substr(start_index, start_index + length - 1);
		for (int i = 0; i < 27; ++i)
		{
			if (temp==huffman_code_list[i])
			{
				isMatch = true;
				if (i == 0)
					plaintext += ' ';
				else
					plaintext += (char)(i + 'a' - 1);
			}
		}
		if (isMatch)
		{
			start_index += length;
			length = 1;
			isMatch = false;
		}
		else
			length++;
		if (start_index + length == ciphertext.length())
			return plaintext;
	}
}

int main()
{
	cout << "Sample Frequency of the alphabet:" << endl << "186 64 13 22 32 103 21 15 47 57 1 5 32 20 57 63 15 1 48 51 80 23 8 18 1 16 1" << endl << endl << endl;
	//创建Huffman树
	TreeNode* node_array = new TreeNode[1000];
	GetAlphabetFreq(node_array);
	HuffmanTree test_tree;
	CreateHuffmanTree(test_tree, node_array);
	string* huffman_code_list = new string[30];

	//获取27种字符的Huffman编码
	HuffmanCodeGenerator(test_tree, huffman_code_list);

	//对应地将英文转换为Huffman编码处理后的密文
	start:
	/*cout << "请选择编码或者解码：\n键入 1 将明文转写为Huffman Code\n键入 2 将Huffman Code转化为明文" << endl;
	char choice;
	cin >> choice;
	
	switch (choice)
	{
	case '1':{
		char plaintext[1000];
		cout << "请输入明文：";
		gets_s(plaintext);
		string ciphertext = HuffmanEncoder(plaintext, huffman_code_list);
		cout << "密文如下：" << endl;
		cout << ciphertext << endl;
			break;
		}
	case '2':{
		char ciphertext[1000];
		cout << "请输入密文：";
		gets_s(ciphertext);
		string plaintext = HuffmanDecoder(ciphertext, huffman_code_list);
		cout << "明文如下：" << endl;
		cout << plaintext << endl;
		}
	}*/
	char ciphertext[1000];
	cout << "请输入密文：";
	gets_s(ciphertext);
	string plaintext = HuffmanDecoder(ciphertext, huffman_code_list);
	cout << "明文如下：" << endl;
	cout << plaintext << endl;
	
	goto start;

	//test_only
	//cout << huffman_code_list[1];

	return 0;
}

//测试用例
//186 64 13 22 32 103 21 15 47 57 1 5 32 20 57 63 15 1 48 51 80 23 8 18 1 16 1