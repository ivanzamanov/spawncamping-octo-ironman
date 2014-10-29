#ifndef __UTIL_H__
#define __UTIL_H__

#include<cstring>
#include<sstream>

#include"stack.hpp"

#define SEPARATOR '_'

// static int applyOperation(char op, int operand1, int operand2) {
//   switch(op) {
//   case '*':
//     return operand1 * operand2;
//   case '+':
//     return operand1 + operand2;
//   case '-':
//     return operand1 - operand2;
//   case '/':
//     return operand1 / operand2;
//   default:
//     return 0;
//   }
// }

// static bool isOp(char c) {
//   return c == '*' || c == '+' || c == '-' || c == '/';
// }

// static bool isNumeric(char c) {
//   return c >= '0' && c <= '9';
// }

// int eval_straight_polish(const char* str) {
//   std::stringstream stream(reverse);
//   IntStack operands;
//   char c = stream.get();
//   int operand;
//   if(isNumeric(c)) {
//     stream.unget();
//     stream >> operand;
//     operands.push(operand);
//   } else if(isOp(c)) {
//     operands.push(' ');
//     operands.push();
//   }

//   while(!stream.eof()) {
//     c = stream.get();
//     if(isNumeric(c)) {
//       stream.unget();
//       stream >> operand;
//       operands.push(operand);
//     } else if(isOp(c)) {
//       int operand1 = operands.pop();
//       int operand2 = operands.pop();
//       int result = applyOperation(c, operand1, operand2);
//       operands.push(result);
//     }
//   }
//   return operands.pop();
// }

// int eval_straight_polish(const char* str) {
//   int length = strlen(str);
//   char* reverse = new char[length + 1];
//   reverse[length] = 0;
//   for(int i=0; i<length; i++)
//     reverse[i] = str[length - i - 1];
  
//   IntStack operands;
//   CharStack operations;
//   std::stringstream stream(reverse);

//   while(!stream.eof()) {
//     char c = stream.get();
//     if(isNumeric(c)) {
//       stream.unget();
//       int operand;
//       stream >> operand;
//       operands.push(operand);
//     } else if(isOp(c)) {
//       int operand1 = operands.pop();
//       int operand2 = operands.pop();
//       int result = applyOperation(c, operand1, operand2);
//       operands.push(result);
//     }
//   }
//   return operands.pop();
// }

//
// Brace check utils
//
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

//
// Permutations utils
//
struct CharRange {
  CharRange(char start, char end): start(start), end(end) { };
  char start;
  char end;
  int length() const {
    return end - start + 1;
  };
};

struct RangeIterator {
  RangeIterator(const RangeIterator& other): start(other.start), end(other.end), current(other.current) { };
  RangeIterator(const CharRange& range): start(range.start), end(range.end), current(range.start) { };
  RangeIterator(char start, char end): start(start), end(end), current(start) { };

  int next() {
    return current++;
  };
  bool hasNext() {
    return current < end;
  };
  char start, end, current;
};

#endif
