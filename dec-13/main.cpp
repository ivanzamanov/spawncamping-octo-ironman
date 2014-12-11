#include"radix.hpp"
#include<iostream>

int main() {
  int powed = pow10(7);
  std::cout << powed << '\n';

  for(int i = 5; i >= 0; i--) {
    int digit = get_digit(123456, i);
    std::cout << digit;
  }
  std::cout << std::endl;

  const int N = 10;
  int arr[N] = {17, 23, 66, 1231, 6643,
                 3252, 23523, 1222, 5532, 988};
  radix_sort(arr, 10);
  for(int i = 0; i < 10; i++) {
    std::cout << arr[i] << ' ';
  }
  std::cout << std::endl;
}
