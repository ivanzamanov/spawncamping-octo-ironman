#include<stdio.h>

#include"stack.hpp"

int main() {
  Stack<int> st;
  for(int i=0; i<10000; i++)
    st.push(i);
  while(st)
    st.pop();
  printf("Cap: %d\n", st.getCap());
}
