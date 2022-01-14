#define PROBLEM "https://atcoder.jp/contests/agc044/tasks/agc044_c"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "library/transform/kronecker_power.hpp"
using suisen::kronecker_power_transform::kronecker_power_transform;

void utit_transform(int&, int &x1, int &x2) {
    std::swap(x1, x2);
}

constexpr int pow3(int b) {
    int res = 1;
    while (b --> 0) res *= 3;
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    const int sz = pow3(n), lsz = pow3(n - n / 2), usz = pow3(n / 2);

    std::string s;
    std::cin >> s;
    const int k = s.size();

    std::vector<bool> cnt_s(k + 1, false);
    std::vector<int> ql(lsz);
    std::iota(ql.begin(), ql.end(), 0);
    std::vector<std::vector<int>> carry(lsz);
    for (int i = 0; i < k; ++i) {
        cnt_s[i + 1] = cnt_s[i] ^ (s[i] == 'S');
        if (s[i] == 'S') {
            kronecker_power_transform<int, 3, utit_transform>(ql);
        } else {
            std::rotate(ql.begin(), ql.end() - 1, ql.end());
            carry[ql[0]].push_back(i);
        }
    }

    std::vector<int> p(sz);

    for (int lower = 0; lower < lsz; ++lower) {
        std::vector<int> qu(usz);
        std::iota(qu.begin(), qu.end(), 0);
        int pj = 0;
        for (int j : carry[ql[lower]]) {
            if (cnt_s[j] ^ cnt_s[pj]) kronecker_power_transform<int, 3, utit_transform>(qu);
            pj = j;
            std::rotate(qu.begin(), qu.end() - 1, qu.end());
        }
        if (cnt_s[pj] ^ cnt_s[k]) kronecker_power_transform<int, 3, utit_transform>(qu);
        for (int upper = 0; upper < usz; ++upper) {
            int pos = upper * lsz + lower;
            int idx = qu[upper] * lsz + ql[lower];
            p[idx] = pos;
        }
    }
    
    for (int i = 0; i < sz; ++i) {
        std::cout << p[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}