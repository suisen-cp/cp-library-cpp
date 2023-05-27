#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>

#include "library/polynomial/compose.hpp"

#include <atcoder/modint>

using mint = atcoder::modint998244353;

namespace atcoder {
    std::istream& operator>>(std::istream& in, mint& a) {
        long long e; in >> e; a = e;
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const mint& a) {
        out << a.val();
        return out;
    }
} // namespace atcoder

std::vector<mint> naive(std::vector<mint> f, std::vector<mint> g, int n) {
    if (n == 0) return {};

    f.resize(n);

    std::vector<mint> powg(n);
    powg[0] = 1;

    std::vector<mint> fg(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fg[j] += f[i] * powg[j];
        }
        powg = atcoder::convolution(powg, g);
        powg.resize(n);
    }
    return fg;
}

void test() {
    {
        std::vector<mint> f { 1, 2, 3, 4 };
        std::vector<mint> g { 5, 4, 3, 2 };
        assert((suisen::compose(f, g, 5) == naive(f, g, 5)));
        assert((suisen::compose(f, g, 4) == naive(f, g, 4)));
        assert((suisen::compose(f, g, 3) == naive(f, g, 3)));
        assert((suisen::compose(f, g, 2) == naive(f, g, 2)));
        assert((suisen::compose(f, g, 1) == naive(f, g, 1)));
        assert((suisen::compose(f, g, 0) == naive(f, g, 0)));
    }
    {
        std::vector<mint> f { 1, 2, 3, 4, 5, 6, 7 };
        std::vector<mint> g { 5, 4, 3, 2 };
        assert((suisen::compose(f, g, 8) == naive(f, g, 8)));
        assert((suisen::compose(f, g, 7) == naive(f, g, 7)));
        assert((suisen::compose(f, g, 6) == naive(f, g, 6)));
        assert((suisen::compose(f, g, 5) == naive(f, g, 5)));
        assert((suisen::compose(f, g, 4) == naive(f, g, 4)));
        assert((suisen::compose(f, g, 3) == naive(f, g, 3)));
        assert((suisen::compose(f, g, 2) == naive(f, g, 2)));
        assert((suisen::compose(f, g, 1) == naive(f, g, 1)));
        assert((suisen::compose(f, g, 0) == naive(f, g, 0)));
    }
    {
        std::vector<mint> f {};
        std::vector<mint> g { 5, 4, 3 };
        assert((suisen::compose(f, g, 5) == naive(f, g, 5)));
        assert((suisen::compose(f, g, 4) == naive(f, g, 4)));
        assert((suisen::compose(f, g, 3) == naive(f, g, 3)));
        assert((suisen::compose(f, g, 2) == naive(f, g, 2)));
        assert((suisen::compose(f, g, 1) == naive(f, g, 1)));
        assert((suisen::compose(f, g, 0) == naive(f, g, 0)));
    }
    {
        std::vector<mint> f { 2 };
        std::vector<mint> g { 5, 4, 3 };
        assert((suisen::compose(f, g, 5) == naive(f, g, 5)));
        assert((suisen::compose(f, g, 4) == naive(f, g, 4)));
        assert((suisen::compose(f, g, 3) == naive(f, g, 3)));
        assert((suisen::compose(f, g, 2) == naive(f, g, 2)));
        assert((suisen::compose(f, g, 1) == naive(f, g, 1)));
        assert((suisen::compose(f, g, 0) == naive(f, g, 0)));
    }
    {
        std::vector<mint> f { 2 };
        std::vector<mint> g { 3 };
        assert((suisen::compose(f, g, 5) == naive(f, g, 5)));
        assert((suisen::compose(f, g, 4) == naive(f, g, 4)));
        assert((suisen::compose(f, g, 3) == naive(f, g, 3)));
        assert((suisen::compose(f, g, 2) == naive(f, g, 2)));
        assert((suisen::compose(f, g, 1) == naive(f, g, 1)));
        assert((suisen::compose(f, g, 0) == naive(f, g, 0)));
    }
    {
        std::vector<mint> f { 5, 4, 3 };
        std::vector<mint> g { 2 };
        assert((suisen::compose(f, g, 5) == naive(f, g, 5)));
        assert((suisen::compose(f, g, 4) == naive(f, g, 4)));
        assert((suisen::compose(f, g, 3) == naive(f, g, 3)));
        assert((suisen::compose(f, g, 2) == naive(f, g, 2)));
        assert((suisen::compose(f, g, 1) == naive(f, g, 1)));
        assert((suisen::compose(f, g, 0) == naive(f, g, 0)));
    }
    {
        std::vector<mint> f { 5, 4, 3 };
        std::vector<mint> g {};
        assert((suisen::compose(f, g, 5) == naive(f, g, 5)));
        assert((suisen::compose(f, g, 4) == naive(f, g, 4)));
        assert((suisen::compose(f, g, 3) == naive(f, g, 3)));
        assert((suisen::compose(f, g, 2) == naive(f, g, 2)));
        assert((suisen::compose(f, g, 1) == naive(f, g, 1)));
        assert((suisen::compose(f, g, 0) == naive(f, g, 0)));
    }
    {
        std::vector<mint> f {};
        std::vector<mint> g {};
        assert((suisen::compose(f, g, 5) == naive(f, g, 5)));
        assert((suisen::compose(f, g, 4) == naive(f, g, 4)));
        assert((suisen::compose(f, g, 3) == naive(f, g, 3)));
        assert((suisen::compose(f, g, 2) == naive(f, g, 2)));
        assert((suisen::compose(f, g, 1) == naive(f, g, 1)));
        assert((suisen::compose(f, g, 0) == naive(f, g, 0)));
    }
}

int main() {
    test();
    std::cout << "Hello World" << std::endl;
    return 0;
}
