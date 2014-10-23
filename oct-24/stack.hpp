#ifndef __STACK_H__
#define __STACK_H__

#include<stdio.h>

template<class T>
class Stack {
public:
  Stack<T>(): cap(8), head(-1) {
    data = new T[cap];
  };
  virtual ~Stack<T>() {
    delete data;
  };
  Stack<T>(const Stack<T>& stack): cap(stack.cap), head(stack.head) {
    data = new T[cap];
    for(int i=0; i<stack.cap; i++) {
      data[i] = stack.data[i];
    }
  };
  const Stack<T> operator=(const Stack<T> stack) {
    delete data;
    cap = stack.cap;
    head = stack.head;
    data = new T[cap];
    for(int i=0; i<stack.cap; i++) {
      data[i] = stack.data[i];
    }
  };

  void push(T item) {
    if(head == cap - 1) {
      expand();
    }
    data[++head] = item;
  };
  T& pop() {
    if(head > 2 && head == cap / 4) {
      shrink();
    }
    return data[--head];
  };
  T& peek() {
    return data[head];
  };
  bool isEmpty() {
    return head >= 0;
  };
  operator bool() {
    return isEmpty();
  };
  int getCap() {
    return cap;
  };
private:
  T* data;
  int cap;
  int head;
  // Merge in a single function
  void expand() {
    int newCap = cap * 2;
    printf("Expanding to %d\n", newCap);
    T* newData = new T[newCap];
    for(int i=0; i<cap; i++) {
      newData[i] = data[i];
    }
    delete data;
    data = newData;
    cap = newCap;
  };
  void shrink() {
    int newCap = cap / 2;
    printf("Shrinking to %d\n", newCap);
    T* newData = new T[newCap];
    for(int i=0; i<newCap; i++) {
      newData[i] = data[i];
    }
    delete data;
    data = newData;
    cap = newCap;
  };
};

#endif
