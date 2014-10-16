#include<cstring>
#include<iostream>
#include<fstream>

class WordNGramStream {
public:
  WordNGramStream(const char* file, int n):
    input(file), n(n)
  { };
  ~WordNGramStream() {
    input.close();
  };
  WordNGramStream& operator>>(char* str) {
    int offset = 0;
    int secondWordPos = 0;
    int i = 0;
    for(; i<n && !input.eof(); i++) {
      input >> (str + offset);
      int length = strlen(str + offset);
      if(length == 0)
	break;
      offset += length;
      if(secondWordPos == 0)
	secondWordPos = input.tellg();
      *(str + offset) = ' ';
      offset++;
      str[offset] = 0;
    }
    str[offset - 1] = 0;
    if(i != n)
      *str = 0;
    else if(secondWordPos != 0)
      input.seekg(secondWordPos);
    return *this;
  };

private:
    std::ifstream input;
    int n;
};

class CharNGramStream {
public:
  CharNGramStream(const char* word, int n):n(n) {
    offset = 0;
    length = strlen(word);
    this->word = new char[length + 1];
    strncpy(this->word, word, length + 1);
  };
  ~CharNGramStream() { delete word; };

  CharNGramStream& operator>>(char* out) {
    if(offset + n - 1 == length) {
      *out = 0;
    } else {
      strncpy(out, word+offset, n);
      offset++;
      out[n] = 0;
    }
    return *this;
  };
private:
  char* word;
  int n;
  int length;
  int offset;
};

int main() {
  WordNGramStream wstr("data.txt", 3);
  char wngram[2000];
  wstr >> wngram;
  while(*wngram) {
    printf("%s\n", wngram);
    wstr >> wngram;
  }
}
