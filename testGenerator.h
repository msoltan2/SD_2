#pragma once

#include <vector>
#include <random>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include "utils.h"
using namespace __gnu_pbds;
template<class T> using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

Test genTest(int insertions, int deletions, int searches) {
    std::random_device rd;
    std::mt19937 mt(time(nullptr));
    Test test;

    std::vector<int> values(insertions);
    std::iota(values.begin(), values.end(), 1);

    // Shuffle the vector
    std::shuffle(values.begin(), values.end(), mt);

    ordered_set<int> ms;

    test.numOp = insertions + deletions + searches;

    while (insertions || deletions || searches) {
        std::vector <int> v;
        if (insertions) v.push_back(1);
        if (deletions && !ms.empty()) v.push_back(2);
        if (searches && !ms.empty()) v.push_back(3);
        int idx = mt() % (int) v.size();
        int op = v[idx];

        if (op == 1) {
            int num = values.back();
            values.pop_back();
            ms.insert(num);
            test.ops.push_back({1, num});
            insertions--;
        }
        else if (op == 2) {
            int idx = mt() % (int) ms.size();
            auto it = ms.find_by_order(idx);
            test.ops.push_back({2, *it});
            ms.erase(it);
            deletions--;
        }
        else if (op == 3) {
            int idx = mt() % (int) ms.size();
            auto it = ms.find_by_order(idx);
            test.ops.push_back({3, *it});
            searches--;
        }
    }
    return test;

}