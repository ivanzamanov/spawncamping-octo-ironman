#pragma once
#include "StackMax.h"
using namespace std;

class QueueMax
{
	StackMax pushStack;
	StackMax popStack;
	int pushStackBottom;
	int popStackBottom;
public:
	int front();
	int back();
	void pop();
	bool empty();
	void push(int val);
	int max();
};

