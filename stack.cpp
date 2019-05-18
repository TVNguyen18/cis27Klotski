/**
* Program Name: KlotSki Game
* Discussion  : stack.cpp
* Written by  : Anh Tran
* Date        : 2019/05/17
*/

#include "stack.h"

using namespace std;

Stack::Stack() : stackCount(0), top(nullptr) {}
Stack::~Stack()
{
	stackNode* temp;
	while (stackCount > 0) {
		temp = top;
		top = top->next;
		delete[] temp->data;
		temp->data = nullptr;
		delete temp;
		temp = nullptr;
		stackCount--;
	}
}
void Stack::push(int* newPosMatrix)
{
	TStackNodeAddr newNode = new TStackNode;
	newNode->data = new int[20];
	for (int i = 0; i < 20; i++) {
		newNode->data[i] = *(newPosMatrix + i);
	}
	newNode->next = top;
	top = newNode;
	stackCount++;
}
int* Stack::pop()
{
	int* tempData = new int[20];
	TStackNodePtr tempNode = top;
	for (int i = 0; i < 20; i++) {
		tempData[i] = top->data[i];
	}	
	top = top->next;
	delete[] tempNode->data;
	tempNode->data = nullptr;
	delete tempNode;
	tempNode = nullptr;
	stackCount--;
	return tempData;
}
int Stack::isEmpty()
{
	return (stackCount == 0);
}
int Stack::emptyStack(void)
{
	while (!this->isEmpty()) {
		this->pop();
	}
	return 0;
}
;
