#include<iostream>
#include<fstream>
#include<cstring>

char toDec(char c) {
  if(c >= '0' && c <= '9') {
    return c - '0';
  } else {
    return c - 'A' + 10;
  }
}

unsigned char hexToByte(const char* hex) {
  unsigned char result = 0;
  result = (toDec(*hex) << 4) | toDec(*(hex+1));
  return result;
}

struct Pixel {
  char r;
  char g;
  char b;

  void operator()(char r, char g, char b) {
    this->r = r;
    this->g = g;
    this->b = b;
  };
  void operator()(const char* color) {
    if(*color == '#') {
      r = hexToByte(color+1);
      g = hexToByte(color+3);
      b = hexToByte(color+5);
    }
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
      //img(x,y)("#CDCDCD");
    }
  }

  std::ofstream output("test.ppm");
  img.print(output);
  output.close();
}
