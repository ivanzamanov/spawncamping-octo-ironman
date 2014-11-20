#include"heap.hpp"

int main() {
  PriorityQueue q;
  for(int i = 0; i < 20; i++)
    q.push(i);
  q.print("heap.dot");

  while(!q.empty()) {
    printf("%d\n", q.pop());
  }
}
