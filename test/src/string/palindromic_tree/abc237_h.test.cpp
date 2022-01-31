#define PROBLEM "https://atcoder.jp/contests/abc237/tasks/abc237_h"

#include <iostream>

#include "library/graph/bipartite_matching.hpp"
#include "library/string/palindromic_tree.hpp"

using suisen::BipartiteMatching;
using suisen::PalindromicTree;
using suisen::PalindromicTreeVec;
using suisen::PalindromicTreeArr;

int main() {
    std::string s;
    std::cin >> s;

    std::vector<int> s2;
    for (char c : s) s2.push_back(c - 'a');

    PalindromicTree<char, std::string> t(s);

    PalindromicTreeVec<int> tv(s2);
    PalindromicTreeArr<int, 26> ta(s2); 

    const int n = t.node_num() - 2;
    std::vector<int> par = t.parents();
    
    assert(par == tv.parents());
    assert(par == ta.parents());

    BipartiteMatching matching(n, n);
    for (int i = 0; i < n; ++i) {
        int j = t.suffix_link(i + 2) - 2, k = par[i + 2] - 2;
        assert(j == tv.suffix_link(i + 2) - 2);
        assert(j == ta.suffix_link(i + 2) - 2);
        if (j >= 0) matching.add_edge(i, j);
        if (k >= 0) matching.add_edge(i, k);
    }

    std::cout << n - matching.solve() << std::endl;

    return 0;
}