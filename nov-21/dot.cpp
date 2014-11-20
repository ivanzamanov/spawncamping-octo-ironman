#include<stdio.h>

#include"dot.hpp"

void DotPrinter::start() {
  if(filePath != 0) {
    file = fopen(filePath, "w");
    fprintf(file, "digraph {\nrankdir = TB;\n");
  } else
    printf("digraph {\nrankdir = TB;\n");
}

void DotPrinter::end() {
  if(filePath != 0) {
    fprintf(file, "}\n");
    fclose(file);
  } else
    printf("}\n");
}

void DotPrinter::edge(int src, int dest) {
  if(filePath != 0)
    fprintf(file, "%d -> %d\n", src, dest);
  else
    printf("%d -> %d\n", src, dest);
}

void DotPrinter::edge(int src, char label, int dest, int payload) {
  if(filePath != 0)
    fprintf(file, "%d -> %d [label=\"%c:%d\"]\n", src, dest, label, payload);
  else
    printf("%d -> %d [label=\"%c\"]\n", src, dest, label);
}

void DotPrinter::node(int id) {
  if(filePath != 0)
    fprintf(file, "%d\n", id);
  else
    printf("%d\n", id);
}

void DotPrinter::node(int id, bool isFinal) {
  if(filePath != 0)
    fprintf(file, "%d [shape=%s]\n", id, isFinal ? "doublecircle" : "circle");
  else
    printf("%d [shape=%s]\n", id, isFinal ? "doublecircle" : "circle");
}
