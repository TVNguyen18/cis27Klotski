/**
* Program Name: KlotSki Game
* Discussion  : Declaration File --
*				  stack.h
* Written by  : Anh Tran
* Date        : 2019/05/17
*/

#ifndef STACK_H
#define STACK_H

using namespace std;

struct stackNode {
	int* data;
	struct stackNode* next;
};
typedef struct stackNode TStackNode;
typedef struct stackNode* TStackNodeAddr;
typedef struct stackNode* TStackNodePtr;

class Stack {
public:
	Stack();
	~Stack();
	void push(int*);
	int* pop(void);
	int isEmpty(void);
	int emptyStack(void);
private:
	int stackCount;
	TStackNodePtr top;
};

#endif