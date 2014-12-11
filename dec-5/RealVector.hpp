#ifndef __REAL_VECTOR__
#define __REAL_VECTOR__

struct VectorNode {
  VectorNode():next(0), data(0) { }
  VectorNode(int component, double value):
    next(0), component(component), value(value) { }

  VectorNode* next;
  int component;
  double value;
};

class RealVector {
public:
  RealVector();
  ~RealVector();

  void setComponent(int, double);
  void sum(const RealVector& other);
  void substract(const RealVector& other);
  int product(const RealVector& other) const;

  void print() const;
private:
  VectorNode* head;
};

#endif
