#ifndef __PPM_H__
#define __PPM_H___

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
  result = (toDec(*hex) << 4) | toDec(*(hex + 1));
  return result;
}

struct Pixel {
  unsigned char r;
  unsigned char g;
  unsigned char b;

  void operator()(unsigned char r, unsigned char g, unsigned char b) {
    this->r = r;
    this->g = g;
    this->b = b;
  };
  void operator()(const char* color) {
    if(*color == '#') {
      r = hexToByte(color + 1);
      g = hexToByte(color + 3);
      b = hexToByte(color + 5);
    }
  };
  bool operator==(int color) {
    return toInt() == color;
  };
  int __attribute__ ((noinline)) toInt() {
    return ((int)r << 8) |
           ((int)g << 4) |
           (int)b;
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
    return getPixel(x, y);
  };
  Pixel& getPixel(int x, int y) {
    Pixel& result = data[y * width + x];
    return result;
  };

  int getWidth() const {
    return width;
  };
  int getHeight() const {
    return height;
  };

  void clear(const char* color) {
    for(int i = 0; i < getWidth(); i++) {
      for(int j = 0; j < getHeight(); j++) {
        (*this)(i, j)(color);
      }
    }
  };

  void print(std::ofstream& output) {
    output << "P6\n";
    output << width << '\n';
    output << height << '\n';
    output << 255 << '\n';
    output.write((char*)data, width * height * sizeof(Pixel));
  };
};

#endif
