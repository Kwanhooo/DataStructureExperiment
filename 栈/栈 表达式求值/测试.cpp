#include "StackBasicOperation.h"

using namespace std;

bool isNum(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	else
		return false;
}

Status InsidePriority(char operatorType)
{
	switch (operatorType) {
	case '#': 	return 0;
	case '(': 	return 1;
	case '+': 	return 3;
	case '-': 	return 3;
	case '*': 	return 5;
	case '/': 	return 5;
	case '%': 	return 5;
	case '^': 	return 7;
	case ')': 	return 8;
	}
}

Status OutsidePriority(char operatorType)
{
	switch (operatorType) {
	case '#': 	return 0;
	case '(': 	return 8;
	case '+': 	return 6;
	case '-': 	return 2;
	case '*': 	return 4;
	case '/': 	return 4;
	case '%': 	return 4;
	case '^': 	return 6;
	case ')': 	return 1;
	}
}

string RPNTranslator(string s)
{
	string rpnExp = "#";
	Stack OpStack;
	InitStack(OpStack);
	char tempChar;
	for (int i = 0; i < s.length(); ++i)
	{
		if (isNum(s.at(i)))
		{
			cout << "进了第1个if" << endl << endl;
			rpnExp += s.at(i);
			continue;
		}
		if (s.at(i) == '(')
		{
			Push(OpStack, '(');
		}
		if (StackEmpty(OpStack))
		{
			cout << "进了第2个if" << endl << endl;
			Push(OpStack, s.at(i));
			continue;
		}
		if (s.at(i) == ')')
		{
			Status authenticator;
			cout << "进了第3个if" << endl << endl;
			while (GetTop(OpStack) != '(')
			{
				cout << "进了第3个if的while" << endl << endl;
				authenticator = Pop(OpStack, tempChar);
				if (authenticator == ERROR)
				{
					exit(OVERFLOW);
				}
				rpnExp += tempChar;
				cout << "卡住时的tempchar:" << tempChar << endl;
				cout << "卡住时的rpnexp:" << rpnExp << endl;
			}
			cout << "从第3个if的while中弹出" << endl << endl;
			Pop(OpStack, tempChar);
			rpnExp += tempChar;
		}
		else
		{
			cout << "进了else" << endl << endl;
			if (InsidePriority(GetTop(OpStack)) > OutsidePriority(s.at(i)))
			{
				cout << "进了else嵌套的if" << endl << endl;
				while (InsidePriority(GetTop(OpStack)) > OutsidePriority(s.at(i)))
				{
					cout << "进了else的while" << endl << endl;
					Pop(OpStack, tempChar);
					rpnExp += tempChar;
				}
				cout << "从else的while中弹出" << endl << endl;
				Push(OpStack, s.at(i));
			}
		}
		cout << "完成一次for循环" << endl << endl;
		cout << rpnExp << endl;
	}

	cout << "跳出for循环，此时的rpnExp为：" << rpnExp << endl;

	if (StackEmpty(OpStack) == 0)
	{
		do
		{
			Pop(OpStack, tempChar);
			rpnExp += tempChar;
		} while (StackEmpty(OpStack) == 0);
	}
	return rpnExp;
}

int main()
{
	printf("请输入一个中缀表达式：\n");
	string infixExp;
	cin >> infixExp;
	string rpnExp;
	rpnExp = RPNTranslator(infixExp);
	printf("转换为后缀表达式后的结果为：\n");
	cout << rpnExp;
}