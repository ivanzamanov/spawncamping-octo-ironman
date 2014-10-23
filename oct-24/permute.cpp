#include<iostream>

struct CharRange {
  CharRange(char start, char end): start(start), end(end) { };
  char start;
  char end;
  int length() const {
    return end - start + 1;
  };
};

struct RangeIterator {
  RangeIterator(const CharRange& range): start(range.start), end(range.end), current(range.start) { };
  RangeIterator(char start, char end): start(start), end(end), current(start) { };
  operator bool() {
    return current <= end;
  };
  int next() {
    return ((bool) * this * -1) && current++;
  };
  char start, end, current;
};

void permute(char* buffer, int index, int total, char used[10]) {
  if(index == total - 1) {
    for(char i = '0'; i <= '9'; i++) {
      if(used[i - '0'] == 0) {
        buffer[index] = i;
        std::cout << buffer << '\n';
      }
    }
  } else {
    for(char i = '0'; i <= '9'; i++) {
      if(used[i - '0'] == 0) {
        buffer[index] = i;
        used[i - '0'] = 1;
        permute(buffer, index + 1, total, used);
        used[i - '0'] = 0;
      }
    }
  }
}

void permute_chars(int count, const CharRange& range) {
  char* buffer = new char[count + 1];
  char* used = new char[range.length()];
  buffer[count] = 0;
  permute(buffer, 0, count, used);
  delete buffer;
}

int main() {
  permute_chars(3, CharRange('0', '3'));
}
