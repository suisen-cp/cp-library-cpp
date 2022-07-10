#define PROBLEM "https://atcoder.jp/contests/abc258/tasks/abc258_Ex"

#include <iostream>
#include <vector>
#include <atcoder/modint>

#include "library/linear_algebra/array_matrix.hpp"

using mint = atcoder::modint998244353;
using matrix = suisen::SquareArrayMatrix<mint, 4>;
 
matrix T { {
    0, 0, 1, 0,
    1, 0, 0, 0,
    0, 0, 1, 1,
    0, 0, 1, 0
} };
matrix U { { 
    0, 0, 0, 0,
    1, 0, 0, 0,
    0, 0, 0, 1,
    0, 0, 1, 0
} };
 
int main() {
    int n;
    long long s;
    std::cin >> n >> s;
    
    std::vector<long long> a(n);
    for (auto &e : a) std::cin >> e;
    a.push_back(s);
 
    std::array<mint, 4> x { 1, 0, 1, 0 };
    long long p = 0;
    for (long long t : a) {
        x = (t == s ? T : U) * (T.pow(t - 1 - p) * x);
        p = t;
    }
    std::cout << x[0].val() << std::endl;
 
    return 0;
}