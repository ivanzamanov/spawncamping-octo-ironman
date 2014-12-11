#include"RealVector.hpp"

RealVector::RealVector():
  head(0) { }

RealVector::~RealVector() {
  VectorNode* next;

  while(head) {
    next = head->next;
    delete head;
    head = next;
  }
}

void insertComponent(VectorNode* current, int component, double value) {
  if(!(current->next && current->component <= component)) {
    insertComponent(current->next, component, value);
  } else {
    if(current->component == component) {
      current->value = value;
    } else {
      VectorNode* next = current->next;
      current->next = new RealVector(component, value);
      current->next->next = next;
    }
  }
}

void RealVector::setComponent(int component, double value) {
  VectorNode* current = head;
  if(!head) {
    head = new VectorNode(component, value);
    return;
  } else {
    insertComponent(head, component, value);
  }
}

void RealVector::sum(const RealVector& other) {
  VectorNode* currentThis = head, currentOther = other.head;

  while(currentThis && currentOther) {
    if(currentThis->component == currentOther->component) {
      currentThis->value = currentThis->value + currentOther->value;
      currentThis = currentThis->next;
      currentOther = currentOther->next;
    } else if (currentThis->component < currentOther->component) {
      currentThis = currentThis->next;
    } else {
      insertComponent(currentThis, currentOther.component, currentOther.value);
      currentOther = currentOther->next;
      currentThis = currentThis->next;
    }
  }

  while(currentOther) {
    insertComponent(currentThis, currentOther.component, currentOther.value);
    currentThis = currentThis->next;
    currentOther = currentOther->next;
  }
}

void RealVector::substract(const RealVector& other) {
  VectorNode* currentThis = head, currentOther = other.head;

  while(currentThis && currentOther) {
    if(currentThis->component == currentOther->component) {
      currentThis->value = currentThis->value - currentOther->value;
      currentThis = currentThis->next;
      currentOther = currentOther->next;
    } else if (currentThis->component < currentOther->component) {
      currentThis = currentThis->next;
    } else {
      insertComponent(currentThis, currentOther.component, -currentOther.value);
      currentOther = currentOther->next;
      currentThis = currentThis->next;
    }
  }

  while(currentOther) {
    insertComponent(currentThis, currentOther.component, currentOther.value);
    currentThis = currentThis->next;
    currentOther = currentOther->next;
  }
}

double product(const RealVector& other) const {
  double result = 0;
  VectorNode* currentThis = head, currentOther = other.head;

  while(currentThis && currentOther) {
    if(currentThis->component == currentOther->component) {
      currentThis = currentThis->next;
      currentOther = currentOther->next;
      result += currentThis->value * currentOther->value;
    } else if (currentThis->component < currentOther->component) {
      currentThis = currentThis->next;
    } else {
      currentOther = currentOther->next;
    }
  }
}

void RealVector::print() {
  VectorNode* current = head;

  while(current) {
    cout << "(" << current->component << "," << current.value << ")\n";
  }
}
