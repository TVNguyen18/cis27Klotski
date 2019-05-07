#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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
	int* pop();
	int isEmpty();
private:
	int stackCount;
	TStackNodePtr top;
};

#endif