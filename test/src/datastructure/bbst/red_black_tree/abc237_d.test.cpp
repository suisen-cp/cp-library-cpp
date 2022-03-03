#define PROBLEM "https://atcoder.jp/contests/abc237/tasks/abc237_d"

#include <iostream>
#include "library/datastructure/bbst/red_black_tree.hpp"

using Node = suisen::bbst::RedBlackTreeNode<int>;
using Tree = Node::tree_type;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::string s;
    std::cin >> n >> s;

    Node::init_pool(1000010);

    Tree t = Node::push_back(Node::empty_tree(), 0);
    int pos = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'L') {
            t = Node::insert(t, pos, i + 1);
        } else {
            t = Node::insert(t, ++pos, i + 1);
        }
    }
    std::vector<int> res;
    Node::dump(t, std::back_inserter(res));

    for (int i = 0; i <= n; ++i) {
        std::cout << res[i] << " \n"[i == n];
    }

    return 0;
}
