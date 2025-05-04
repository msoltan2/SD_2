#include "redblacktree.h"
#include <iostream>

int main() {
    RedBlackTree<int> tree;

    std::cout << "Inserting elements into the tree...\n";
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);
    tree.insert(25);
    
    std::cout << "\nTesting search:\n";
    Node<int>* result = tree.search(15);
    if (result != nullptr && result->data == 15) { 
        std::cout << "Found: " << result->data << " (Color: " 
                  << (result->color == RED ? "RED" : "BLACK") << ")\n";
    } else {
        std::cout << "15 not found in the tree.\n";
    }

    result = tree.search(100);
    if (result != nullptr && result->data == 100) { 
        std::cout << "Found: " << result->data << " (Color: " 
                  << (result->color == RED ? "RED" : "BLACK") << ")\n";
    } else {
        std::cout << "100 not found in the tree.\n";
    }

    std::cout << "\nTesting deletion:\n";
    std::cout << "Removing 15...\n";
    tree.remove(15);

    result = tree.search(15);
    if (result != nullptr && result->data == 15) { 
        std::cout << "15 still exists in the tree.\n";
    } else {
        std::cout << "15 successfully removed from the tree.\n";
    }

    std::cout << "Removing 10 (root)...\n";
    tree.remove(10);

    result = tree.search(10);
    if (result != nullptr && result->data == 10) { 
        std::cout << "10 still exists in the tree.\n";
    } else {
        std::cout << "10 successfully removed from the tree.\n";
    }

    std::cout << "Removing 100 (non-existent element)...\n";
    tree.remove(100);

    std::cout << "All tests completed.\n";

    return 0;
}