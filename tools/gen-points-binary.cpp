#include<iostream>

int main() {
    for(int i=0; i<100000000; i++) {
        int y = i%10000;
        if(i != '\n' && y != '\n') {
            std::cout.write((char*)&i, sizeof(int));
            std::cout.write((char*)&y, sizeof(int));
            std::cout.put('\n');
        }
    }
}
