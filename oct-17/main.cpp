#include<iostream>
#include<fstream>
#include<cstring>

#include"ppm.hpp"

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
