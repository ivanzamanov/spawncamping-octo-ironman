#include<iostream>
#include<fstream>
#include<cstring>

struct Pixel {
  char r;
  char g;
  char b;

  void operator()(char r, char g, char b) {
    this->r = r;
    this->g = g;
    this->b = b;
  };
};

class Image {
  int width, height;
  Pixel* data;
public:
  Image(int width, int height):
    width(width), height(height) {
    data = new Pixel[width * height];
  };
  Image(const char* filename) {
    std::ifstream input(filename);
    char buffer[32];
    input >> buffer;
    if(strcmp(buffer, "P6") != 0) {
      return;
    }
    // Read width, height and max value, assume is 255 or lower
    input >> width;
    input >> height;
    input >> buffer;
    data = new Pixel[width * height];
    input.get();
    input.read((char*) data, width * height * sizeof(Pixel));
    input.close();
  };
  ~Image() {
    delete data;
  };

  Pixel& operator()(int x, int y) {
    return data[y * width + x];
  };

  int getWidth() const { return width; };
  int getHeight() const { return height; };

  void print(std::ofstream& output) {
    output << "P6\n";
    output << width << '\n';
    output << height << '\n';
    output << 255 << '\n';
    output.write((char*)data, width * height * sizeof(Pixel));
  };
};

int main() {
  Image img(255, 255);
  for(int x=0; x<img.getWidth(); x++) {
    for(int y=0; y<img.getHeight(); y++) {
      img(x,y)(x, y, x & y);
    }
  }
  std::ofstream output("test.ppm"), output2("test2.ppm");
  img.print(output);
  output.close();

  Image img2("test.ppm");
  img2.print(output2);
}
