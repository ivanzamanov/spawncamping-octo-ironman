#include<iostream>

#include"util.hpp"
#include"stack.hpp"

void permute(char* buffer, int index, int total, const CharRange& range, char used[10]) {
  if(index == total - 1) {
    RangeIterator it(range);
    while(it.hasNext()) {
      char i = it.next();
      if(used[i - '0'] == 0) {
        buffer[index] = i;
        std::cout << buffer << '\n';
      }
    }
  } else {
    RangeIterator it(range);
    while(it.hasNext()) {
      char i = it.next();
      if(used[i - '0'] == 0) {
        buffer[index] = i;
        used[i - '0'] = 1;
        permute(buffer, index + 1, total, range, used);
        used[i - '0'] = 0;
      }
    }
  }
}

void permute_chars(int count, const CharRange& range) {
  char* buffer = new char[count + 1];
  char* used = new char[range.length()];
  for(int i=0; i<range.length(); i++)
    used[i] = 0;
  buffer[count] = 0;
  permute(buffer, 0, count, range, used);
  delete buffer;
  delete used;
}

int main() {
  permute_chars(5, CharRange('0', '5'));
}
