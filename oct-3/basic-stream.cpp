#include<iostream>
#include<fstream>

void testStream(const char* file) {
    std::ifstream inputStream(file);
    int number, count = 0;
    inputStream >> number;
    while(inputStream) {
        count++;
        std::cout << number << '\n';
        inputStream >> number;
    }
    inputStream.close();
    std::cout << "Read " << count << "strings\n";
}

int main(int argc, const char** argv) {
    testStream(argv[1]);
}
