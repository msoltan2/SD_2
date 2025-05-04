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

    void rotateLeft(Node<T>*& x);
    void rotateRight(Node<T>*& x);
    void fixInsert(Node<T>*& node);
    void fixDelete(Node<T>*& node);
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


#include "redblacktree.cpp" 

#endif