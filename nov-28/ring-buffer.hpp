#ifndef __RING_BUFFER__
#define __RING_BUFFER__

#include<cstdlib>
#include<cstring>

class RingBuffer {
public:
  RingBuffer(int cap):cap(cap),
                      head(0),
                      available(0) {
    data = (char*) malloc(cap);
  }

  RingBuffer(const RingBuffer& other) {
    copy(other);
  }

  ~RingBuffer() {
    destroy();
  }

  const RingBuffer& operator=(const RingBuffer& other) {
    destroy();
    copy(other);
    return *this;
  }

  int write(const char* source, int max) {
    int written = 0;
    int offset = 0;
    while(written < max && !isFull()) {
      data[(head + available) % cap] = source[offset];
      available++;
      written++;
    }
    return written;
  }

  int read2(const char* dest, int max) {
    
  }

  int read(char* dest, int max) {
    int offset = 0;
    while(offset < max && !isEmpty()) {
      dest[offset] = data[head];
      offset++;
      advance();
    }
    return offset;
  }

  bool isEmpty() {
    return available == 0;
  }

  bool isFull() {
    return available == cap;
  }

private:
  void advance(int step=1) {
    head = (head + step) % cap;
    available -= step;
  }

  void copy(const RingBuffer& other) {
    cap = other.cap;
    data = (char*) malloc(cap);

    head = other.head;
    available = other.available;
    memcpy(data + head, other.data + head, available);
  }

  void destroy() {
    free(data);
  }

  char* data;
  int cap;
  int head;
  int available;
};

#endif
