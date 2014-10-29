#ifndef __UTIL_H__
#define __UTIL_H__

#include<cstring>
#include<sstream>

#include"../oct-24/stack.hpp"

static double applyOperation(char op, double operand1, double operand2) {
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

struct Item {
  Item():value(' '), isOperand(false) { };
  Item(int value, bool isOperand):
    value(value), isOperand(isOperand) { };
  Item& operator=(const Item& other) {
    isOperand = other.isOperand;
    value = other.value;
    return *this;
  };
  double value;
  bool isOperand;
};

static bool isOp(char c) {
  return c == '*' || c == '+' || c == '-' || c == '/';
}

static bool isNumeric(char c) {
  return c >= '0' && c <= '9';
}

Item readItem(std::stringstream& stream) {
  char c = stream.get();
  double operand;
  if(isNumeric(c)) {
    stream.unget();
    stream >> operand;
    return Item(operand, true);
  } else {
    return Item(c, false);
  }
}

double eval_straight_polish(const char* str) {
  std::stringstream stream(str);
  Stack<Item> operands;
  Stack<double> operations;
  Item token;
  token = readItem(stream);
  if(token.isOperand) {
    operands.push(token);
  } else {
    operations.push(token.value);
    operands.push(Item(' ', false));
  }

  while(stream) {
    token = readItem(stream);
    if(token.isOperand) {
      if(operands.peek().isOperand == false) {
        // Marker, delay op
        operands.push(token);
      } else {
        double operand;
        char operation;
        while(!operands.isEmpty() && operands.peek().isOperand) {
          operand = operands.pop().value;
          operands.pop(); // Pop marker
          operation = operations.pop();
          token = Item(applyOperation(operation, operand, token.value), true);
        }
        operands.push(token);
      }
    } else if(isOp(token.value)) {
      // Operation
      operands.push(Item(' ', false));
      operations.push(token.value);
    }
  }

  return operands.pop().value;
}

#endif
