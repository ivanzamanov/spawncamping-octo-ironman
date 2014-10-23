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

  int next() {
    return current++;
  };
  bool hasNext() {
    return current < end;
  };
  char start, end, current;
};

void permute(char* buffer, int index, int total, const CharRange& range, char used[10]) {
  RangeIterator it(range);
  if(index == total - 1) {
    while(it.hasNext()) {
      char i = it.next();
      if(used[i - '0'] == 0) {
        buffer[index] = i;
        std::cout << buffer << '\n';
      }
    }
  } else {
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
}

int main() {
  permute_chars(3, CharRange('0', '4'));
}
