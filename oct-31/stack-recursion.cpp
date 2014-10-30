#include<iostream>

#define SIZE 8

bool board[SIZE][SIZE];

bool isRowTaken(int row) {
  bool result = false;

  for(int i = 0; i < SIZE; i++)
    result = result | board[row][i];

  return result;
}

bool isColumnTaken(int col) {
  bool result = false;

  for(int i = 0; i < SIZE; i++)
    result = result | board[i][col];

  return result;
}

bool isDiagonalTaken(int i, int j) {
  
}

bool isGood(int i, int j) {
  return !isRowTaken(i) & !isColumnTaken(j) & !isDiagonalTaken(i, j);
}

int main() {
  for(int i = 0; i < SIZE; i++)
    for(int j = 0; j < SIZE; j++)
      board[i][j] = 0;
}
