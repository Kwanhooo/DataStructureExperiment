#pragma once
#include <iostream>
#include <cstdio>
#include <malloc.h>
#include <string>

#define ERROR 0
#define SUCCESS 1
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE 300
#define STACK_INCREMENT 10

typedef int Status;
typedef char Elemtype;

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
	if (s.base == NULL)
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

//获取栈顶的数据元素
Elemtype GetTop(Stack s)
{
	if (s.top != s.base)

		return *(s.top - 1);
}

//将新的元素推入栈中
Status Push(Stack& s, Elemtype e)
{
	if ((s.top - s.base) >= s.stack_size) {//检查是否栈存满
		//重新追加空间，大小为STACK_INCREMENT
		s.base = (Elemtype*)realloc(s.base, s.stack_size + STACK_INCREMENT);
		//检查时是否成功分配到了内存空间
		if (s.base == NULL)
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

//销毁一个栈
Status DestroyStack(Stack& s)
{
	if (s.base != NULL)
	{
		free(s.base);
		s.base = NULL;
		s.top = NULL;
		s.stack_size = 0;
		return SUCCESS;
	}
	else
		return ERROR;
}

Status ClearStack(Stack& s)
{
	if (s.base != NULL)
	{
		s.top = s.base;
		return SUCCESS;
	}
	else
		return ERROR;
}

Status StackEmpty(Stack s)
{
	if (s.base == s.top)
		return TRUE;
	else
		return FALSE;
}

int GetLength(Stack s)
{
	if (s.base == s.top)
		return 0;
	else
	{
		return s.top - s.base;
	}
}

Status StackTraverse(Stack s, Status(*visit)(Elemtype))
{
	Elemtype* traverser = s.base;
	while (traverser < s.top)
	{
		if (!visit(*traverser))
			break;
		traverser++;
	}
	return SUCCESS;
}