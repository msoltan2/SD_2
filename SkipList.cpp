#include "SkipList.h"
#include <random>

template <typename T>
SkipList<T>::SkipList() {
    mt.seed(std::random_device{}());
    heads.push_back(new SkipNode(T()));
}

template <typename T>
SkipList<T>::~SkipList() {
    SkipNode<T>* curr = heads[0];
    while (curr) {
        SkipNode<T>* next = curr->right;
        delete curr;
        curr = next;
    }
    heads.clear();
}

template <typename T>
void SkipList<T>::insert(const T& data) {
    std::vector<SkipNode<T>*> path;

    SkipNode<T>* curr = heads.back();
    while (curr) {
        if (curr->right && curr->right->data < data) {
            curr = curr->right;
        } else {
            path.push_back(curr);
            curr = curr->down;
        }
    }

    SkipNode<T>* downNode = nullptr;
    bool promote = true;
    int level = 0;

    while (promote && level < static_cast<int>(heads.size())) {
        SkipNode<T>* left = path.back();
        path.pop_back();

        SkipNode<T>* newNode = new SkipNode(data);
        newNode->left = left;
        newNode->right = left->right;
        if (left->right) left->right->left = newNode;
        left->right = newNode;

        newNode->down = downNode;
        if (downNode) downNode->up = newNode;

        downNode = newNode;
        promote = (mt() % 2) == 0;
        ++level;
    }

    if (promote) {
        SkipNode<T>* newHead = new SkipNode(T());
        newHead->down = heads.back();
        heads.back()->up = newHead;
        heads.push_back(newHead);

        SkipNode<T>* newNode = new SkipNode(data);
        newNode->left = newHead;
        newHead->right = newNode;
        newNode->down = downNode;
        if (downNode) downNode->up = newNode;
    }
}

template <typename T>
void SkipList<T>::remove(const T& data) {
    SkipNode<T>* found = nullptr;

    found = search(data);
    if (!found) return;

    SkipNode<T>* nodeToRemove = found;
    while (nodeToRemove) {
        if (nodeToRemove->left) nodeToRemove->left->right = nodeToRemove->right;
        if (nodeToRemove->right) nodeToRemove->right->left = nodeToRemove->left;

        SkipNode<T>* below = nodeToRemove->down;

        if (below) {
            nodeToRemove = below;
        } else {
            SkipNode<T>* toDelete = nodeToRemove;
            while (toDelete) {
                SkipNode<T>* above = toDelete->up;
                delete toDelete;
                toDelete = above;
            }
            break;
        }
    }

    while (heads.size() > 1 && !heads.back()->right) {
        delete heads.back();
        heads.pop_back();
    }
}

template <typename T>
SkipNode<T>* SkipList<T>::search(const T& data) const {
    SkipNode<T>* curr = heads.back();

    while (curr) {
        if (curr->right && curr->right->data < data) {
            curr = curr->right;
        } else if (curr->right && curr->right->data == data) {
            return curr->right;
        } else {
            curr = curr->down;
        }
    }

    return nullptr;
}