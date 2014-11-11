#include<iostream>

#include"avl.hpp"
#include"dot.hpp"

extern void rotateLeft(AVLNode* &node);

DotPrinter printer("tree.dot");

void print(AVLNode* node) {
  if(!node)
    return;
  printer.node(node->data, false);
  if(node->left)
    printer.edge(node->data, ' ', node->left->data, 0);
  if(node->right)
    printer.edge(node->data, ' ', node->right->data, 0);
}

int main() {
  AVLTree tree;
  tree.insert(3);
  tree.insert(4);
  tree.insert(5);

  //tree.DFS(print);

  rotateLeft(tree.root);

  printer.start();
  tree.DFS(print);
  printer.end();
}
