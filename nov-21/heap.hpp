#ifndef __HEAP_H__
#define __HEAP_H__

#include"dot.hpp"

class PriorityQueue {
public:
  PriorityQueue();
  ~PriorityQueue();
  void push(int n);
  int pop();
  bool empty();
  void print(const char* file_path);
private:
  int get_parent(int i);
  void checkSize();
  int cap;
  int size;
  int* data;
};

#endif
