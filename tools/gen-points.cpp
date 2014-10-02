#include<stdio.h>

int main() {
    for(int i=0; i<100000000; i++) {
        printf("%d %d\n", i, i%10000);
    }
}
