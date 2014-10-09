#include<iostream>

class IntStream {
public:
  IntStream():next(0){ };
  ~IntStream() { };

  virtual int get() {
    return ++next;
  };

  IntStream& operator>>(int& n) {
    n = get();
    return *this;
  };

protected:
  int next;
};

class RNGStream : public IntStream {
public:
  RNGStream():IntStream() { };

  int get() {
    int prev = P1 * next + P2;
    next = prev;
    return next;
  };

private:
  static const int P1 = 13007;
  static const int P2 = 26449;
};

int main() {
  RNGStream str;
  for(int i=0; i<100; i++) {
    int n;
    str >> n;
    std::cout << n << '\n';
  }
}
