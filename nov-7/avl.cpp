#include<stack>

#include"avl.hpp"

static bool searchInNode(AVLNode* node, int n);
static void insertInNode(AVLNode*& node, int n);
static void removeFromNode(AVLNode*& node, int n);

static void deleteNodes(AVLNode* node);
static void copyNodeRecursive(AVLNode*& dest, AVLNode* src);

AVLTree::AVLTree(): root(0) { }

AVLTree::AVLTree(const AVLTree& tree) {
  copyNodeRecursive(root, tree.root);
}

AVLTree::~AVLTree() {
  deleteNodes(root);
}

const AVLTree& AVLTree::operator=(const AVLTree& tree) {
  deleteNodes(root);
  copyNodeRecursive(root, tree.root);
  return *this;
}

void AVLTree::insert(int n) {
  if(!root)
    root = new AVLNode(n);
  else
    insertInNode(root, n);
}

bool AVLTree::search(int n) {
  return root && searchInNode(root, n);
}

void AVLTree::remove(int n) {
  if(!root)
    return;

  removeFromNode(root, n);
}

// Actual implementation
void deleteNodes(AVLNode* node) {
  if(node) {
    deleteNodes(node->left);
    deleteNodes(node->right);
    delete node;
  }
}

void copyNodeRecursive(AVLNode*& dest, AVLNode* src) {
  if(!src)
    return;
  else
    dest = new AVLNode(src->data);

  copyNodeRecursive(dest->left, src->left);
  copyNodeRecursive(dest->right, src->right);
}

int max(int i1, int i2) {
  return (i1 > i2) ? i1 : i2;
}

int height(AVLNode* node) {
  if(node) {
    return 1 + max(height(node->left), height(node->right));
  } else
    return 0;
}

// If balanced, will return 0,
// -2 - must rotate left
// +2 - must rotate right
int getBalance(AVLNode* node) {
  int leftHeight = node->left && node->left->height;
  int rightHeight = node->right && node->right->height;
  return leftHeight - rightHeight;
}

void updateHeight(AVLNode* node) {
  bool hasChildren = node-> left & node->right;
  node->height = (hasChildren) + max(node->left && node->left->height, node->right && node->right->height);
}

void insertInNode(AVLNode*& node, int n) {
  if(!node) {
    node = new AVLNode(n);
  } else if(n > node->data) {
    insertInNode(node->right, n);
    updateHeight(node);
    rebalance(node);
  }
  else if (n < node->data) {
    insertInNode(node->left, n);
    updateHeight(node);
    rebalance(node);
  }
}

bool searchInNode(AVLNode* node, int n) {
  if(!node)
    return false;

  if(n > node->data)
    return searchInNode(node->right, n);
  else if (n < node->data)
    return searchInNode(node->left, n);
  else
    return true;
}

void removeFromNode(AVLNode*& node, int n) {
  if(!node)
    return;

  if(node->data == n) {
    int childCount = ((bool)node->left) + ((bool)node->right);

    if(childCount == 0) {
      delete node;
      node = 0;
    } else if (childCount == 1) {
      removeFromNode(node->left, n);
      removeFromNode(node->right, n);
    } else {
      AVLNode* child = node->left;
      node->data = child->data;
      removeFromNode(child, child->data);
    }
  } else {
    if(n > node->data)
      removeFromNode(node->right, n);
    else if (n < node->data)
      removeFromNode(node->left, n);
  }
}

void dfsHelper(AVLNode* node, void (*visit)(AVLNode*)) {
  if(node) {
    visit(node);
    dfsHelper(node->left, visit);
    dfsHelper(node->right, visit);
  }
}

void AVLTree::DFS(void (*visit)(AVLNode*)) {
  dfsHelper(root, visit);
}

void rotateLeft(AVLNode*& root) {
  AVLNode* saved = root->right;
  root->right = saved->left;
  saved->left = root;
  root = saved;
}

void rotateRight(AVLNode*& root) {
  AVLNode* saved = root->left;
  root->left = saved->right;
  saved->right = root;
  root = saved;
}

