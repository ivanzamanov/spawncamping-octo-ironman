#include<stdio.h>
#include<iostream>

#include"stack.hpp"
#include"util.hpp"

void testPrefix(const char* expr, int expected) {
  printf("%s = %d, expected = %d\n", expr, eval_straight_polish(expr), expected);
}

void testBraces(const char* expr) {
  printf("Validating expression: %s\nResult: %d\n", expr, (int)validateBraces(expr));
}

int main() {
  // testBraces("(())");
  // testBraces("(()}");
  testPrefix("++3,4,5", 9);
  testPrefix("-,*,/,15,-,7,+,1,1,3,+,2,+,1,1", 5);
  testPrefix("/,-,*,2,5,*,1,2,-,11,9", 4);
  testPrefix("-,*,/,15,-,7,+,1,1,3,+,2,+,1,1", 5);
  testPrefix("/,-,*,2,5,*,1,2,-,11,9", 4);
}
