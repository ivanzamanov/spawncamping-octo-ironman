#include<cstdio>

void testBasic(const char* file) {
    FILE* fd = fopen(file, "r");
    int number, count = 0;
    while(fscanf(fd, "%d", &number) && !feof(fd)) {
        count++;
        printf("%d\n", number);
    }
    fclose(fd);
    printf("Read %d strings\n", count);
}

int main(int argc, const char** argv) {
    testBasic(argv[1]);
}
