#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <random>

template <typename Y>
struct SkipNode {
  Y data;
  SkipNode* left;
  SkipNode* right;
  SkipNode* up;
  SkipNode* down;

  explicit SkipNode(Y data) : data(data), left(NULL), right(NULL), up(NULL), down(NULL) {}
};

template <typename T>
class SkipList {

  std::vector <SkipNode<T>*> heads;
  std::mt19937 mt;

  public:
    SkipList();
    ~SkipList();
    void insert(const T& data);
    void remove(const T& data);
    SkipNode<T>* search(const T& data) const;
};


#include "SkipList.cpp"

#endif