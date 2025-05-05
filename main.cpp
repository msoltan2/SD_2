#include "redblacktree.h"
#include "SkipList.h"
#include "testGenerator.h"
#include "utils.h"
#include <iostream>

int main() {
    RedBlackTree<int> sk;
    int n;
    std::cin >> n;

    for (int test = 1; test <= n; ++test) {
        int insertions, deletions, searches;
        std::cin >> insertions >> deletions >> searches;
        Test tst = genTest(insertions, deletions, searches);
        std::cout << "\nTest " << test << " || ";
        std::cout << "Total = " << formatNumber(insertions + deletions + searches) << " Insertions = " <<
            formatNumber(insertions) << " Deletions = " << formatNumber(deletions) << " Searches = " << formatNumber(searches) << "\n";
        std::cout << "\n";
        std::cout << std::left << std::setw(25) << "Algorithm"
                  << std::setw(15) << "Time (ms)" ;
        std::cout << "\n";
        std::cout << std::string(45, '-') << "\n";

        {
            auto start = std::chrono::high_resolution_clock::now();
            SkipList<int> skipList;
            for (auto [type, val]: tst.ops) {
                if (type == 1) skipList.insert(val);
                else if (type == 2) skipList.remove(val);
                else if (type == 3) skipList.search(val);
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << std::left << std::setw(25) << "Skip List"
                      << std::setw(15) << formatTime(duration)
                      << "\n";
        }
        {
            auto start = std::chrono::high_resolution_clock::now();
            RedBlackTree<int> redBlackTree;
            for (auto [type, val]: tst.ops) {
                if (type == 1) redBlackTree.insert(val);
                else if (type == 2) redBlackTree.remove(val);
                else if (type == 3) redBlackTree.search(val);
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << std::left << std::setw(25) << "Red Black Tree"
                      << std::setw(15) << formatTime(duration)
                      << "\n";
        }
    }
}