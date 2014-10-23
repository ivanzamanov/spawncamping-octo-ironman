#ifndef __UTIL_H__
#define __UTIL_H__

#include<string>
#include<sstream>

#include"stack.hpp"

#define SEPARATOR '_'

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
  CharStack operations;
  IntStack operands;

  while(!expr.eof()) {
    char c = expr.get();
    if(isNumeric(c)) {
      expr.unget();
      int operand;
      expr >> operand;
      operands.push(operand);
      while(operands.getSize() >= 2 && operations.peek() == SEPARATOR) {
        operations.print();
        operands.print();
        operations.pop();
        char op = operations.pop();
        int operand1 = operands.pop();
        int operand2 = operands.pop();
        int applied = applyOperation(op, operand1, operand2);
        operands.push(applied);
      }
    } else if(isOp(c)){
      operations.push(c);
      operations.push(SEPARATOR);
    }
  }
  return operands.pop();
}

static void fillPair(unsigned char* table, unsigned char c1, unsigned char c2) {
  table[c1] = c2;
  table[c2] = c1;
}

static unsigned char* fillBracesTable() {
  unsigned char* result = new unsigned char[256];
  for(int i=0; i<256; i++)
    result[i] = 0;
  fillPair(result, '(', ')');
  fillPair(result, '{', '}');
  fillPair(result, '[', ']');
  return result;
}

static unsigned char* bracesTable = fillBracesTable();

static bool isOpeningBrace(char c) {
  return c == '(' || c == '{' || c == '[';
}

static bool isClosingBrace(char c) {
  return c == ')' || c == '}' || c == ']';
}

static bool isMatching(char unsigned brace1, char unsigned brace2) {
  return bracesTable[brace1] == brace2;
}

int validateBraces(const char* expr) {
  int offset = 0;
  CharStack stack;
  unsigned char symbol = *(expr + offset);
  while(symbol) {
    symbol = *(expr + offset);
    if(isOpeningBrace(symbol)) {
      stack.push(symbol);
    } else if (isClosingBrace(symbol)) {
      if(isMatching(stack.peek(), symbol))
        stack.pop();
      else
        return offset;
    }
    offset++;
  }
  return 0;
}

#endif
