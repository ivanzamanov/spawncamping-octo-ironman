#include<cstdlib>
#include"heap.hpp"

PriorityQueue::PriorityQueue()
  : cap(8), size(0) {
  data = (int*)malloc(cap * sizeof(int));
}

PriorityQueue::~PriorityQueue() {
  free(data);
}

void PriorityQueue::checkSize() {
  if(size == cap) {
    cap = cap * 2;
    data = (int*)realloc(data, cap * sizeof(int));
  }
}

bool PriorityQueue::empty() {
  return size == 0;
}

void swap(int* data, int i, int j) {
  int tmp = data[i];
  data[i] = data[j];
  data[j] = tmp;
}

void PriorityQueue::push(int n) {
  checkSize();
  data[size++] = n;
  // Restore heap
  int current = size - 1, parent = get_parent(current);

  while(parent >= 0 && data[parent] < data[current]) {
    swap(data, current, parent);
    current = parent;
    parent = get_parent(current);
  }
}

bool isHeap(int* data, int n) {
  bool result = true;
  int lchild, rchild;
  for(int i=0; i<n/2; i++) {
    lchild = i * 2 + 1;
    rchild = i * 2 + 2;
    if(rchild < n)
      result = result & (data[rchild] < data[i]);
    if(lchild < n)
      result = result & (data[lchild] < data[i]);
  }
  return result;
}

int PriorityQueue::pop() {
  if(size == 0)
    return -1;

  if(!isHeap(data, size))
    return -1;
  int result = data[0];
  swap(data, 0, size - 1);
  size--;
  if(size == 0)
    return result;

  // Restore heap
  int current = 0, child, lchild, rchild;
  while(current < size) {
    lchild = current * 2 + 1;
    rchild = current * 2 + 2;
    if(rchild < size)
      child = data[lchild] > data[rchild] ? lchild : rchild;
    else 
      child = lchild;

    if(child >= size)
      break;
    if(data[child] > data[current]) {
      swap(data, child, current);
    }
    current = child;
  }

  return result;
}

int PriorityQueue::get_parent(int i) {
  return (i - 1) / 2;
}

void PriorityQueue::print(const char* file_path) {
  DotPrinter printer(file_path);
  printer.start();

  for (int i = 0; i < size; i++) {
    printer.node(i);
    int child = i * 2 + 1;

    if(child < size) {
      printer.edge(data[i], data[child]);
    }

    child = i * 2 + 2;

    if(child < size) {
      printer.edge(data[i], data[child]);
    }
  }

  printer.end();
}
