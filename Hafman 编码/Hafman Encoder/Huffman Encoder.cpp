#pragma warning

#include <iostream>
#include <cstring>

#define MAX_SIZE 100
#define OVERFLOW 3

typedef int Status;
typedef char** HuffmanCode;

typedef struct HuffmanTreeNode
{
	int weight;
	int left;
	int right;
	int parent;
}Node,*Tree;

Tree CreateHuffmanTree(int* weight,int charater_amount)
{
	int node_amount = 2 * charater_amount - 1;
	Tree t = (Tree)malloc(node_amount);
}

int main()
{
	//Alphabet Freqence List(Ranging form space to z)
	int alphabet_weight[] = { 186,64 ,13, 22, 32, 103, 21, 15, 47, 57, 1, 5, 32, 20 ,57, 63 ,15 ,1 ,48, 51 ,80 ,23 ,8 ,18 ,1 ,16 ,1 };
	int charater_amount = 27;

	HuffmanCode test_code;
	Tree test_tree = CreateHuffmanTree(alphabet_weight,charater_amount);
}
