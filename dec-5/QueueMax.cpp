#include "QueueMax.h"
#include <algorithm>

int QueueMax::front() {
	int front = 0;
	if (!popStack.empty()) {
		front = popStack.top();
	} else {
		front = pushStackBottom;
	}
	return front;
}

int QueueMax::back() {
	int back = 0;
	if (!pushStack.empty()) {
		back = pushStack.top();
	} else {
		back = popStackBottom;
	}
	return back;
}

void QueueMax::pop() {
	if (popStack.empty()) {
		popStackBottom = pushStack.top();
		while (!pushStack.empty()) {
			popStack.push(pushStack.top());
			pushStack.pop();
		}
	}
	popStack.pop();
}

bool QueueMax::empty() {
	return pushStack.empty() && popStack.empty();
}

void QueueMax::push(int val) {
	if (pushStack.empty()) {
		pushStackBottom = val;
	}
	pushStack.push(val);
}

int QueueMax::max() {
	int max = 0;
	bool pushEmpty = pushStack.empty(),
		popEmpty = popStack.empty();
	if (pushEmpty && popEmpty) max = -1;
	if (!pushEmpty && !popEmpty) {
		max = std::max(pushStack.max(), popStack.max());
	} else if (!pushEmpty) {
		max = pushStack.max();
	} else {
		max = popStack.max();
	}
	return max;
}
