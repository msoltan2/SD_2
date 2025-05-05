#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>

enum Color { RED, BLACK };

template <typename T>
struct Node {
  T data;
  Color color;
  Node* left;
  Node* right;
  Node* parent;

  Node(T data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class RedBlackTree {
private:
    Node<T>* root;
    Node<T>* NIL;

    void rotateLeft(Node<T>* x);
    void rotateRight(Node<T>* x);
    void fixInsert(Node<T>* node);
    void fixDelete(Node<T>* node);
    void transplant(Node<T>* u, Node<T>* v);
    Node<T>* minimum(Node<T>* node) const;

public:
    RedBlackTree();
    ~RedBlackTree();
    void insert(const T& data);
    void remove(const T& data);
    Node<T>* search(const T& data) const;
    Node<T>* search(Node<T>* node, const T& data) const; 
    void deleteTree(Node<T>* node);
};


template <typename T>
RedBlackTree<T>::RedBlackTree() {
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
void RedBlackTree<T>::rotateLeft(Node<T>* x) {
  Node<T>* y = x->right;
  x->right = y->left;
  
  if(y->left != NIL) 
      y->left->parent = x;
      
  y->parent = x->parent;
  
  if(x->parent == nullptr)
      root = y;
  else if(x == x->parent->left) 
      x->parent->left = y;
  else 
      x->parent->right = y;
      
  y->left = x;
  x->parent = y;
}

template <typename T>
void RedBlackTree<T>::rotateRight(Node<T>* x) {
  Node<T>* y = x->left;
  x->left = y->right;
  
  if(y->right != NIL) 
      y->right->parent = x;
      
  y->parent = x->parent;
  
  if(x->parent == nullptr)
      root = y;
  else if(x == x->parent->right) 
      x->parent->right = y;
  else 
      x->parent->left = y;
      
  y->right = x;
  x->parent = y;
}

template <typename T>
void RedBlackTree<T>::insert(const T& data) {
  Node<T>* nod = new Node<T>(data);
  nod->left = NIL;
  nod->right = NIL;
  nod->color = RED;

  Node<T>* parent = nullptr;
  Node<T>* current = root;

  while(current != NIL){
    parent = current;
    if (data < current->data) current = current->left; 
    else current = current->right;
  }
  
  nod->parent = parent;
  
  if (parent == nullptr) 
      root = nod;
  else if (data < parent->data) 
      parent->left = nod;
  else 
      parent->right = nod;

  fixInsert(nod);
}

template <typename T>
void RedBlackTree<T>::fixInsert(Node<T>* z) {
  while (z != root && z->parent && z->parent->color == RED) {
    if (z->parent == z->parent->parent->left) {
      Node<T>* y = z->parent->parent->right;
      if (y && y->color == RED) {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          rotateLeft(z);
        }
        if (z->parent) {
          z->parent->color = BLACK;
          if (z->parent->parent) {
            z->parent->parent->color = RED;
            rotateRight(z->parent->parent);
          }
        }
      }
    } else {
      Node<T>* y = z->parent->parent->left;
      if (y && y->color == RED) {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rotateRight(z);
        }
        if (z->parent) {
          z->parent->color = BLACK;
          if (z->parent->parent) {
            z->parent->parent->color = RED;
            rotateLeft(z->parent->parent);
          }
        }
      }
    }
  }
  root->color = BLACK;
}

template <typename T>
Node<T>* RedBlackTree<T>::minimum(Node<T>* node) const {
  while(node != NIL && node->left != NIL){
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
    else {
      u->parent->right = v;
    }
    
    if (v != nullptr) {
      v->parent = u->parent;
    }
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

  if (yOriginalColor == BLACK && x != nullptr) {
      fixDelete(x);
  }
}

template <typename T>
void RedBlackTree<T>::fixDelete(Node<T>* x) {
  while (x != root && x != nullptr && x->color == BLACK) {
    if (x == x->parent->left) {
      Node<T>* w = x->parent->right;

      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        rotateLeft(x->parent);
        w = x->parent->right;
      }

      if ((w->left == NIL || w->left->color == BLACK) && 
          (w->right == NIL || w->right->color == BLACK)) {
        w->color = RED;
        x = x->parent;
      } else {
        if (w->right == NIL || w->right->color == BLACK) {
          if (w->left != NIL)
            w->left->color = BLACK;
          w->color = RED;
          rotateRight(w);
          w = x->parent->right;
        }

        w->color = x->parent->color;
        x->parent->color = BLACK;
        if (w->right != NIL)
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

      if ((w->right == NIL || w->right->color == BLACK) && 
          (w->left == NIL || w->left->color == BLACK)) {
        w->color = RED;
        x = x->parent;
      } else {
        if (w->left == NIL || w->left->color == BLACK) {
          if (w->right != NIL)
            w->right->color = BLACK;
          w->color = RED;
          rotateLeft(w);
          w = x->parent->left;
        }

        w->color = x->parent->color;
        x->parent->color = BLACK;
        if (w->left != NIL)
          w->left->color = BLACK;
        rotateRight(x->parent);
        x = root;
      }
    }
  }
  
  if (x != nullptr)
    x->color = BLACK;
}

#endif