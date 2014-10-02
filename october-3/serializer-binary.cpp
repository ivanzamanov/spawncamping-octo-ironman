#include<fstream>
#include<iostream>

struct Point {
    int x;
    int y;
};

void readInt(std::ifstream& iStream, int* n) {
    iStream.read((char*)n, sizeof(int));
}

void writeInt(std::ofstream& oStream, int n) {
    oStream.write((char*)&n, sizeof(int));
}

void serialize(std::ofstream& oStream, const Point* p) {
    writeInt(oStream, p->x);
    writeInt(oStream, p->y);
    // Write a separator
    oStream.put('\n');
}

void deserialize(std::ifstream& iStream, Point* p) {
    readInt(iStream, &(p->x));
    readInt(iStream, &(p->y));
    // Read the separator
    iStream.get();
}

int main(int argc, const char** argv) {
    printf("input: %s\n", argv[1]);
    printf("output: %s\n", argv[2]);
    std::ifstream input(argv[1], std::ifstream::binary);
    std::ofstream output(argv[2], std::ofstream::binary);

    int count;
    while(input) {
        Point p;
        deserialize(input, &p);
        //std::cout << "Read point " << p.x << " " << p.y << '\n';
        serialize(output, &p);
        count++;
    }
    std::cout << "Processed " << count << " points\n";
}
