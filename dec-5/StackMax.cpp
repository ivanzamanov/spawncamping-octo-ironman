#include "StackMax.h"

void StackMax::pop() {
	dataStack.pop();
	maxStack.pop();
}

void StackMax::push(int value) {
	if (maxStack.empty()) {
		maxStack.push(value);
	} else {
		int currentMax = maxStack.top();
		maxStack.push(currentMax > value ? currentMax : value);
	}
	dataStack.push(value);
}

bool StackMax::empty() {
	return dataStack.empty();
}

int StackMax::top() {
	return dataStack.top();
}

int StackMax::max() {
	return maxStack.top();
}