#include<iostream>

#include"ring-buffer.hpp"

// HEAPIFY

int main() {
  RingBuffer buf('z' - 'a' + 1);

  for (int i = 0; i < 5; i++) {
    char c = 'a' - 1;
    while(!buf.isFull()) {
      c++;
      buf.write(&c, 1);
    }

    while(!buf.isEmpty()) {
      buf.read(&c, 1);
      std::cout << c << ' ';
    }
    std::cout << '\n';
  }
}
