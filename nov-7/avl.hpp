#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

struct AVLNode {
  AVLNode(): left(0), right(0) { };
  AVLNode(int data): left(0), right(0), data(data) { };
  AVLNode* left;
  AVLNode* right;
  int data;
};

class AVLTree {
public:
  AVLTree();
  AVLTree(const AVLTree&);
  const AVLTree& operator=(const AVLTree&);
  ~AVLTree();

  void insert(int n);
  void remove(int n);
  bool search(int n);

  void DFS(void (*visit)(AVLNode*));
  AVLNode* root;
private:
  //  AVLNode* root;
};

#endif
