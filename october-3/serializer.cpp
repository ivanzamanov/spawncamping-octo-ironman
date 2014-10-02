#include<fstream>
#include<iostream>

struct Point {
    int x;
    int y;
};

void serialize(std::ofstream& oStream, const Point* p) {
    oStream << p->x << " " << p->y << '\n';
}

void deserialize(std::ifstream& iStream, Point* p) {
    iStream >> p->x >> p->y;
}

int main(int argc, const char** argv) {
    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);

    int count;
    while(input) {
        Point p;
        deserialize(input, &p);
        std::cout << "Read point " << p.x << " " << p.y << '\n';
        serialize(output, &p);
        count++;
    }
    std::cout << "Processed " << count << " points\n";
}
