#define PROBLEM "https://yukicoder.me/problems/no/263"

#include <iostream>

#include "library/string/palindromic_tree.hpp"

using suisen::PalindromicTree;

int main() {
    std::string s, t;
    std::cin >> s >> t;

    PalindromicTree<char, std::string> tree(s);
    std::vector<int> f = tree.frequency_table();
    tree.add_all("[]");
    tree.add_all(t);
    std::vector<int> g = tree.frequency_table();

    long long ans = 0;
    for (int i = 2, n = f.size(); i < n; ++i) {
        ans += (long long) f[i] * (g[i] - f[i]);
    }
    std::cout << ans << std::endl;

    // verification of other versions of palindromic tree
    {
        using suisen::PalindromicTreeVec;
        using suisen::PalindromicTreeArr;

        auto fix = [](const std::string& s) {
            std::vector<int> res;
            for (char c : s) res.push_back(c - 'A');
            return res;
        };

        PalindromicTreeVec<int> tv(fix(s));
        assert(tv.frequency_table() == f);
        tv.add(26), tv.add(27);
        tv.add_all(fix(t));
        assert(tv.frequency_table() == g);

        PalindromicTreeArr<int, 28> ta(fix(s));
        assert(ta.frequency_table() == f);
        ta.add(26), ta.add(27);
        ta.add_all(fix(t));
        assert(ta.frequency_table() == g);
    }

    return 0;
}