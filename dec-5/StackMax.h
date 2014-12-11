#pragma once
#include <stack>
using namespace std;

class StackMax {
private:
	stack<int> dataStack;
	stack<int> maxStack;
public:
	void pop();
	void push(int value);
	bool empty();
	int top();
	int max();
};