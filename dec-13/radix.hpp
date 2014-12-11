#ifndef __RADIX_H__
#define __RADIX_H__

#include<vector>
#include<iostream>

int fast_pow(int, int);
int pow10(int);
void radix_sort(int*, int);
int get_digit(int, int);

int get_digit(int number, int digit) {
  return (number / pow10(digit)) % 10;
}

static int pow10cache[20] = {0};
int pow10(int pow) {
  if(pow10cache[pow] == 0) {
    pow10cache[pow] = fast_pow(10, pow);
  }

  return pow10cache[pow];
}

int fast_pow(int base, int pow) {
  if(pow == 0)
    return 1;
  else if(pow == 1)
    return base;
  else if(pow % 2)
    return base * fast_pow(base, pow - 1);
  else {
    int powed = fast_pow(base, pow / 2);
    return powed * powed;
  }
}

void printBuckets(std::vector<int> *buckets) {
    for(int i = 0; i < 10; i++) {
      std::vector<int>::iterator it = buckets[i].begin();
      std::cout << i << ": ";

      while(it != buckets[i].end()) {
        std::cout << *it;
        it++;
      }
      std::cout << '\n';
    }
}

void radix_sort(int* array, int n) {
  std::vector<int> buckets[10];
  bool hasNumbers = true;
  int maxDigit = 10;

  for(int digitN = 0; digitN <= maxDigit; digitN++) {
    for(int i = 0; i < n; i++) {
      int digit = get_digit(array[i], digitN);
      buckets[digit].push_back(array[i]);
      hasNumbers = hasNumbers || array[i] < pow10(digitN);
    }

    int index = 0;
    //    printBuckets(buckets);
    for(int i = 0; i < 10; i++) {
      std::vector<int>::iterator it = buckets[i].begin();

      while(it != buckets[i].end()) {
        array[index] = *it;
        index++;
        it++;
      }

      buckets[i].clear();
    }
  }
}

#endif
