#include<iostream>

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

void permute_chars(int count) {
  char* buffer = new char[count + 1];
  char used[10] = {0};
  buffer[count] = 0;
  permute(buffer, 0, count, used);
  delete buffer;
}

int main() {
  permute_chars(3);
}
