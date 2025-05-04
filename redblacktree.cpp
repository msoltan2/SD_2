#include "redblacktree.h"

template <typename T>
RedBlackTree<T>::RedBlackTree() : root(nullptr) {
  NIL = new Node<T>(T());
  NIL->color = BLACK;
  NIL->left = nullptr;
  NIL->right = nullptr; 
  NIL->parent = nullptr;
  root = NIL;
}

template <typename T>
RedBlackTree<T>::~RedBlackTree() {
    deleteTree(root); 
    delete NIL; 
}

template <typename T>
void RedBlackTree<T>::deleteTree(Node<T>* node) {
    if (node != NIL) { 
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

template <typename T>
void RedBlackTree<T>::rotateLeft(Node<T>*& x) {
  Node<T>* y = x->right;
  x->right = y->left;
  if(y->left != NIL) y->left->parent = x;
  y->parent = x->parent;
  if(!x->parent) root = y;
  else if(x == x->parent->left) x->parent->left = y;
  else x->parent->right = y;
  y->left = x;
  x->parent = y;
}

template <typename T>
void RedBlackTree<T>::rotateRight(Node<T>*& x) {
  Node<T>* y = x->left;
  x->left = y->right;
  if(y->right != NIL) y->right->parent = x;
  y->parent = x->parent;
  if(!x->parent) root = y;
  else if(x == x->parent->right) x->parent->right = y;
  else x->parent->left = y;
  y->right = x;
  x->parent = y;
}

template <typename T>
void RedBlackTree<T>::insert(const T& data) {
  Node<T>* nod = new Node<T>(data);
  nod->left = NIL;
  nod->right = NIL;

  Node<T>* parent = nullptr;
  Node<T>* current = root;

  while(current != NIL){
    parent = current;
    if (data < current->data) current = current->left; 
    else current = current->right;
  }
  nod->parent = parent;
  if (parent == nullptr) root = nod;
  else if (data < parent->data) parent->left = nod;
  else parent->right = nod;

  fixInsert(nod);
}

template <typename T>
void RedBlackTree<T>::fixInsert(Node<T>*& z) {
  while (z->parent && z->parent->color == RED) {
    if (z->parent == z->parent->parent->left) {
      Node<T>* y = z->parent->parent->right;
      if (y->color == RED) {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          rotateLeft(z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rotateRight(z->parent->parent);
      }
    } else {
      Node<T>* y = z->parent->parent->left;
      if (y->color == RED) {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rotateRight(z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rotateLeft(z->parent->parent);
      }
    }
  }
  root->color = BLACK;
}


template <typename T>
Node<T>* RedBlackTree<T>::minimum(Node<T>* node) const {
  while(node->left != NIL){
    node = node->left;
  }
  return node;
}

template <typename T>
Node<T>* RedBlackTree<T>::search(const T& data) const {
  return search(root, data);
}

template <typename T>
Node<T>* RedBlackTree<T>::search(Node<T>* node, const T& data) const {
  if (node == NIL || data == node->data) {
    return node; 
  }
  if (data < node->data) {
    return search(node->left, data);
  }
  return search(node->right, data); 
}

template <typename T>
void RedBlackTree<T>::transplant(Node<T>* u, Node<T>* v) {
    if(u->parent == nullptr){
      root = v;
    }
    else if (u == u->parent->left){
      u->parent->left = v;
    }
    else u->parent->right = v;
    v->parent = u->parent;
}

template <typename T>
void RedBlackTree<T>::remove(const T& data) {
  Node<T>* z = search(root, data); 
  if (z == NIL) {
      return; 
  }

  Node<T>* y = z; 
  Node<T>* x;   
  Color yOriginalColor = y->color;

  if (z->left == NIL) {
      x = z->right;
      transplant(z, z->right);
  } else if (z->right == NIL) {
      x = z->left;
      transplant(z, z->left);
  } else {
      y = minimum(z->right);
      yOriginalColor = y->color;
      x = y->right;

      if (y->parent == z) {
          x->parent = y;
      } else {
          transplant(y, y->right);
          y->right = z->right;
          y->right->parent = y;
      }

      transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
  }

  delete z;

  if (yOriginalColor == BLACK) {
      fixDelete(x);
  }
}


template <typename T>
void RedBlackTree<T>::fixDelete(Node<T>*& x) {
  while (x != root && x->color == BLACK) {
    if (x == x->parent->left) {
      Node<T>* w = x->parent->right;

      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        rotateLeft(x->parent);
        w = x->parent->right;
      }

      if (w->left->color == BLACK && w->right->color == BLACK) {
        w->color = RED;
        x = x->parent;
      } else {
        if (w->right->color == BLACK) {
          w->left->color = BLACK;
          w->color = RED;
          rotateRight(w);
          w = x->parent->right;
        }

        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        rotateLeft(x->parent);
        x = root;
      }
    } else {
      Node<T>* w = x->parent->left;

      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        rotateRight(x->parent);
        w = x->parent->left;
      }

      if (w->right->color == BLACK && w->left->color == BLACK) {
        w->color = RED;
        x = x->parent;
      } else {
        if (w->left->color == BLACK) {
          w->right->color = BLACK;
          w->color = RED;
          rotateLeft(w);
          w = x->parent->left;
        }

        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->left->color = BLACK;
        rotateRight(x->parent);
        x = root;
      }
    }
  }
  x->color = BLACK;
}