#include<iostream>

#include"../oct-17/ppm.hpp"
#include"../oct-24/stack.hpp"

struct Point {
  int x, y;
};

Point create_point(int x, int y) {
  Point result;
  result.x = x;
  result.y = y;
  return result;
}

void pushNeighbours(Stack<Point>& stack, int x, int y) {
  Point p;

  for(int xOffset = -1; xOffset <= 1; xOffset++) {
    for(int yOffset = -1; yOffset <= 1; yOffset++) {
      if(xOffset != 0 | yOffset != 0) {
        p.x = x + xOffset;
        p.y = y + yOffset;
        stack.push(p);
      }
    }
  }
}

void fill(Image& img, int startX, int startY, const char* color) {
  Stack<Point> stack;
  stack.push(create_point(startX, startY));
  int areaColor = img(startX, startY).toInt();
  Pixel p;
  p(color);
  int newColor = p.toInt();

  while(!stack.isEmpty()) {
    Point rowStart = stack.pop();
    if(rowStart.x < 0 || rowStart.x >= img.getWidth() || rowStart.y < 0 || rowStart.y >= img.getHeight() || newColor == img(rowStart.x, rowStart.y).toInt())
      continue;

    for (int x = rowStart.x; (x < img.getWidth()) & (img(x, rowStart.y).toInt() == areaColor); x++) {
      img(x, rowStart.y)(color);
      pushNeighbours(stack, x, rowStart.y);
    }

    for (int x = rowStart.x - 1; (x >= 0) & (img(x, rowStart.y).toInt() == areaColor); x--) {
      img(x, rowStart.y)(color);
      pushNeighbours(stack, x, rowStart.y);
    }
  }
}

int main() {
  Image img(512, 512);
  img.clear("#ffffff");
  int rectW = 128, rectH = 128;

  for(int i = 0; i < rectW; i++) {
    for(int j = 0; j < rectH; j++) {
      img(i + 50, j + 50)("#000000");
    }
  }

  //edgeDetect(img);
  std::ofstream output("test.ppm");
  fill(img, 60, 60, "#cdcdcd");
  img.print(output);
  output.close();
}
