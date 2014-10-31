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
      if((xOffset != 0) | (yOffset != 0)) {
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

void rotate(Point& p, bool CCW) {
  int x = p.x, y = p.y;
  if(CCW) {
    p.x = x * 0 - y * 1;
    p.y = x * 1 - y * 0;
  } else {
    p.x = x * 0 + y * 1;
    p.y = - x * 1 - y * 0;
  }
}

Point sum(Point& p1, Point& p2) {
  Point result;
  result.x = p1.x + p2.x;
  result.y = p1.y + p2.y;
  return result;
}

Point dif(Point& p1, Point& p2) {
  Point result;
  result.x = p1.x - p2.x;
  result.y = p1.y - p2.y;
  return result;
}

void edgeDetect(Image& img, const char* edgeColorString) {
  Pixel pix;
  pix(edgeColorString);
  int edgeColor = pix.toInt();
  int startColor = img(0, 0).toInt();

  Point start, direction, current;
  direction.x = 0;
  direction.y = 1;
  for(int i = 0, stop = false; i < img.getWidth() && !stop; i++) {
    for(int j = 0; j < img.getHeight() && !stop; j++) {
      if(img(i, j).toInt() != startColor) {
        start.x = i;
        start.y = j;
        stop = true;
      }
    }
  }

  current = start;
  do {
    if(img(current.x, current.y).toInt() == startColor) {
      img(current.x, current.y)(edgeColorString);
      rotate(direction, true);
      current = sum(current, direction);
    } else {
      rotate(direction, false);
      current = sum(current, direction);
    }
  } while(current.x != start.x || current.y != start.y);
  img(current.x, current.y)(edgeColorString);
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

  edgeDetect(img, "#ff00ff");
  std::ofstream output("test.ppm");
  fill(img, 60, 60, "#cdcdcd");
  img.print(output);
  output.close();
}
