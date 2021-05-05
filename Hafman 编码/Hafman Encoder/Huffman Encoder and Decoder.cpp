#pragma warning (disable:4996)

#include <iostream>
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

//ERROR_EXIT_CODE
#define INVALID_INPUT 0x474544D8

//开启DEBUG输出
//#define DEBUG_MODE_ON

using namespace std;

//全局变量
int array_length;

typedef int Status;

//哈夫曼树节点
typedef struct HuffmanTreeNode {
	char letter;
	int weight;
	HuffmanTreeNode* left;
	HuffmanTreeNode* right;
	bool isDeleted;
	int pre_order_counted_times;
} *TreeNode;

//哈夫曼树
struct HuffmanTree {
	HuffmanTreeNode* root;
};

typedef TreeNode ElemType;

typedef struct SqStack {
	ElemType* base;
	ElemType* top;
	int stack_size;
} Stack;

//初始化一个栈
Status InitStack(Stack& s) {
	s.base = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if (s.base == nullptr) {
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
Status Push(Stack& s, TreeNode e) {
	if ((s.top - s.base) >= s.stack_size) {//检查是否栈存满
		//重新追加空间，大小为STACK_INCREMENT
		s.base = (ElemType*)realloc(s.base, s.stack_size + STACK_INCREMENT);
		//检查时是否成功分配到了内存空间
		if (s.base == nullptr) {
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
Status Pop(Stack& s, ElemType& e) {
	if (s.top == s.base) {
		return ERROR;
	}
	else {
		s.top--;
		e = *s.top;
		return SUCCESS;
	}
}

//判断栈是否为空
Status StackEmpty(Stack s) {
	if (s.base == s.top)
		return TRUE;
	else
		return FALSE;
}

//将字母频度表存入二叉树节点，并将二叉树节点的地址存入数组中
void GetAlphabetFreq(TreeNode* node_array) {
	cout << "**********获取字母频度表**********" << endl;

	auto sp = (TreeNode)malloc(sizeof(HuffmanTreeNode));
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

	for (int i = 0; i < 26; ++i) {
		auto tn = (TreeNode)malloc(sizeof(HuffmanTreeNode));
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

TreeNode GetMinWeight(TreeNode* node_array) {
	int min_index = 10000;
	int min_weight = 10000;
	for (int i = 0; i < array_length; ++i) {
		if (node_array[i]->weight < min_weight && !node_array[i]->isDeleted) {
			min_weight = node_array[i]->weight;
			min_index = i;
		}
	}
	node_array[min_index]->isDeleted = true;
	return node_array[min_index];
}

bool isEmpty(TreeNode* node_array) {
	for (int i = 0; i < array_length; ++i)
		if (!node_array[i]->isDeleted)
			return false;
	return true;
}

void SaveNodeToArray(TreeNode new_node, TreeNode* node_array) {
	node_array[array_length] = new_node;
	array_length++;
}

void CreateHuffmanTree(HuffmanTree& t, TreeNode* node_array) {
	TreeNode parent_node;
	while (true) {
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

//产生Huffman编码
void HuffmanCodeGenerator(HuffmanTree t, string* huffman_code_list) {
	string s;
	s = "";
	TreeNode n = t.root;
	Stack node_stack;
	InitStack(node_stack);
	while (true) {
		if (n == t.root) {
			if (n->pre_order_counted_times == 0) {
				n->pre_order_counted_times++;
				Push(node_stack, n);
				n = n->left;
				s += '1';
			}
			if (n->pre_order_counted_times == 1) {
				n->pre_order_counted_times++;
				Push(node_stack, n);
				n = n->right;
				s += '0';
			}
			if (n->pre_order_counted_times == 2)
				break;
		}
		else {
			if (n->letter == '#') {
				if (n->pre_order_counted_times == 0) {
					n->pre_order_counted_times++;
					Push(node_stack, n);
					n = n->left;
					s += '1';
				}
				if (n->pre_order_counted_times == 1) {
					n->pre_order_counted_times++;
					Push(node_stack, n);
					n = n->right;
					s += '0';
				}
				if (n->pre_order_counted_times == 2) {
					Pop(node_stack, n);
					s = s.substr(0, s.length() - 1);
				}
			}
			else {
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

string SearchHuffmanCode(char c, string* huffman_code_list) {
	return huffman_code_list[c - 'a' + 1];
}

string HuffmanEncoder(string plaintext, string* huffman_code_list) {
	transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::tolower);
	string ciphertext;
	for (char i : plaintext) {
		if (i == ' ')
			ciphertext += huffman_code_list[0];
		else
			ciphertext += SearchHuffmanCode(i, huffman_code_list);
	}
	return ciphertext;
}

string HuffmanDecoder(const string& ciphertext, string* huffman_code_list) {
	string plaintext;
	int length = 1; //10010000100001100011111101000011100011011110
	int start_index = 0;
	bool isMatch = false;
	while (true) {
		if (start_index + length > ciphertext.length())
			return plaintext;
		string temp = ciphertext.substr(start_index, length);
		for (int i = 0; i < 27; ++i) {
			if (temp == huffman_code_list[i]) {
				isMatch = true;
				if (i == 0)
					plaintext += ' ';
				else
					plaintext += (char)(i + 'a' - 1);
			}
		}
		if (isMatch) {
			start_index += length;
			length = 1;
			isMatch = false;
		}
		else {
			if (start_index + length >= ciphertext.length()) {
				cout << "未知编码阻止了解码程序的运行！" << endl;
				exit(INVALID_INPUT);
			}
			length++;
		}
	}
}

string GetBinCode(const string& s)
{
	string bin_code;
	cout << "**********原文的二进制编码**********" << endl;
	for (char i : s)
	{
		char temp[100];
		itoa(i, temp, 2);
		cout << i << '\t' << temp << endl;
		bin_code += temp;
	}
	return bin_code;
}

int main() {
	cout << "Tips:Here is the Sample Frequency of the alphabet:" << endl
		<< "186 64 13 22 32 103 21 15 47 57 1 5 32 20 57 63 15 1 48 51 80 23 8 18 1 16 1" << endl << endl << endl;
	//创建Huffman树
	auto* node_array = new TreeNode[1000];
	GetAlphabetFreq(node_array);
	HuffmanTree test_tree{};
	CreateHuffmanTree(test_tree, node_array);
	auto* huffman_code_list = new string[30];

	//获取27种字符的Huffman编码
	HuffmanCodeGenerator(test_tree, huffman_code_list);

	//对应地将英文转换为Huffman编码处理后的密文
start:
	cout << "**********请选择编码或者解码**********\n  #键入 1 将明文转写为Huffman Code#\n  #键入 2 将Huffman Code转化为明文#" << endl;
	char choice;
	fflush(stdin);
	cin >> choice;

	switch (choice) {
	case '1': {
		char plaintext[1000] = { 0 };
		cout << endl << endl << "**************请输入原文**************" << endl;
		cin.ignore();
		gets_s(plaintext);
		string ciphertext = HuffmanEncoder(plaintext, huffman_code_list);
		cout << "Huffman Code如下：" << endl;
		cout << ciphertext << endl;
		cout << "***************转写结束***************" << endl << endl;
		string bin_text = GetBinCode(plaintext);
		cout << "***********原文的二进制编码***********" << endl;
		cout << bin_text << endl;
		double compression_ratio = (1.0 - (double)ciphertext.length() / (double)bin_text.length()) * 100;
		cout << endl << "压缩率 ---> " << compression_ratio << '%' << endl;
		break;
	}
	case '2': {
		char ciphertext[1000] = { 0 };
		cout << endl << endl << "**********请输入Huffman Code**********" << endl;
		cin.ignore();
		gets_s(ciphertext);
		string plaintext = HuffmanDecoder(ciphertext, huffman_code_list);
		cout << "明文如下：" << endl;
		cout << plaintext << endl;
		cout << "***************转写结束***************" << endl << endl << endl;
		string bin_text = GetBinCode(plaintext);
		cout << "***********原文的二进制编码***********" << endl;
		cout << bin_text << endl;
		string ciphertext_copy = ciphertext;
		double compression_ratio = ((double)bin_text.length() / (double)ciphertext_copy.length() - 1.0) * 100;
		cout << endl << "体积增长率 ---> " << compression_ratio << '%' << endl;
		break;
	}
	default:
		exit(INVALID_INPUT);
	}
	cout << "*************程序运行结束*************" << endl << endl << endl << endl << endl;
	goto start;
}

//测试用例
//#186 64 13 22 32 103 21 15 47 57 1 5 32 20 57 63 15 1 48 51 80 23 8 18 1 16 1

//#Huffman---10010000100001100011111101000011100011011110
//#Plaintext---i love you