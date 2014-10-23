#ifndef __UTIL_H__
#define __UTIL_H__

#include<string>
#include<sstream>

#include"stack.hpp"

static int applyOperation(char op, int operand1, int operand2) {
  switch(op) {
  case '*':
    return operand1 * operand2;
  case '+':
    return operand1 + operand2;
  case '-':
    return operand1 - operand2;
  case '/':
    return operand1 / operand2;
  default:
    return 0;
  }
}

static bool isOp(char c) {
  return c == '*' || c == '+' || c == '-' || c == '/';
}

static bool isNumeric(char c) {
  return c >= '0' && c <= '9';
}

int eval_straight_polish(const char* str) {
  std::stringstream expr(str);
  Stack<char> operations;
  Stack<int> operands;

  while(!expr.eof()) {
    char c = expr.get();
    if(isNumeric(c)) {
      expr.unget();
      int operand;
      expr >> operand;
      operands.push(operand);
      while(operands.getSize() >= 2 && operations.peek() == ' ') {
        operations.pop();
        char op = operations.pop();
        int operand1 = operands.pop();
        int operand2 = operands.pop();
        int applied = applyOperation(op, operand1, operand2);
        operands.push(applied);
      }
    } else if(isOp(c)){
      operations.push(c);
      operations.push(' ');
    }
  }
  return operands.pop();
}

#endif
