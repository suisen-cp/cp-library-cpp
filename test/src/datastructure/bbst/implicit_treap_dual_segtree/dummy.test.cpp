#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream &out, const std::vector<T> &a) {
    out << '{';
    for (auto &e : a) out << e << ',';
    return out << '}';
}

#include "library/datastructure/bbst/implicit_treap_dual_segtree.hpp"

template <typename T, typename F, T(*mapping)(F, T)>
struct NaiveSolutionForDualSegmentTree {
    NaiveSolutionForDualSegmentTree() = default;
    NaiveSolutionForDualSegmentTree(const std::vector<T> &dat) : _n(dat.size()), _dat(dat) {}

    T get(int i) const {
        assert(0 <= i and i < _n);
        return _dat[i];
    }
    void set(int i, const T& val) {
        assert(0 <= i and i < _n);
        _dat[i] = val;
    }

    void insert(int i, const T& val) {
        assert(0 <= i and i <= _n);
        ++_n;
        _dat.insert(_dat.begin() + i, val);
    }
    void erase(int i) {
        assert(0 <= i and i < _n);
        --_n;
        _dat.erase(_dat.begin() + i);
    }

    void apply_all(const F &f) {
        apply(0, _n, f);
    }
    void apply(int l, int r, const F &f) {
        assert(0 <= l and l <= r and r <= _n);
        for (int i = l; i < r; ++i) _dat[i] = mapping(f, _dat[i]);
    }

    void reverse_all() {
        reverse(0, _n);
    }
    void reverse(int l, int r) {
        assert(0 <= l and l <= r and r <= _n);
        for (--r; l < r; ++l, --r) {
            std::swap(_dat[l], _dat[r]);
        }
    }

    void rotate(int i) {
        assert(0 <= i and i <= _n);
        std::rotate(_dat.begin(), _dat.begin() + i, _dat.end());
    }

    std::vector<T> dump() { return _dat; }
private:
    int _n;
    std::vector<T> _dat;
};

/**
 * Range Update Point Get
 */

using S = int;

struct F {
    static constexpr int identity = std::numeric_limits<int>::max();

    int val;
    F() : val(identity) {}
    F(int val) : val(val) {}
};

S mapping(F f, S x) {
    return f.val == F::identity ? x : f.val;
}
F composition(F f, F g) {
    return f.val == F::identity ? g : f.val;
}
F id() {
    return F{};
}

using Tree = suisen::DynamicDualSegmentTree<S, F, mapping, composition, id>;
using Naive = NaiveSolutionForDualSegmentTree<S, F, mapping>;

#include <random>
#include <algorithm>

constexpr int Q_get = 0;
constexpr int Q_set = 1;
constexpr int Q_insert = 2;
constexpr int Q_erase = 3;
constexpr int Q_rotate = 8;
constexpr int Q_apply = 4;
constexpr int Q_apply_all = 5;
constexpr int Q_reverse = 6;
constexpr int Q_reverse_all = 7;
constexpr int QueryTypeNum = 9;

void test() {
    int N = 3000, Q = 3000, MAX_VAL = 1000000000;

    std::mt19937 rng{std::random_device{}()};

    std::vector<S> init(N);
    for (int i = 0; i < N; ++i) init[i] = rng() % MAX_VAL;
    
    Tree t1(init);
    Naive t2(init);

    for (int i = 0; i < Q; ++i) {
        const int query_type = rng() % QueryTypeNum;
        if (query_type == Q_get) {
            const int i = rng() % N;
            assert(t1[i] == t2.get(i));
        } else if (query_type == Q_set) {
            const int i = rng() % N;
            const S v = rng() % MAX_VAL;
            t1[i] = v;
            t2.set(i, v);
        } else if (query_type == Q_insert) {
            const int i = rng() % (N + 1);
            const S v = rng() % MAX_VAL;
            t1.insert(i, v);
            t2.insert(i, v);
            ++N;
        } else if (query_type == Q_erase) {
            const int i = rng() % N;
            t1.erase(i);
            t2.erase(i);
            --N;
        } else if (query_type == Q_rotate) {
            const int i = rng() % (N + 1);
            t1.rotate(i);
            t2.rotate(i);
        } else if (query_type == Q_apply) {
            const int l = rng() % (N + 1);
            const int r = l + rng() % (N - l + 1);
            const int f = rng() % MAX_VAL;
            t1.apply(l, r, f);
            t2.apply(l, r, f);
        } else if (query_type == Q_apply_all) {
            const int f = rng() % MAX_VAL;
            t1.apply_all(f);
            t2.apply_all(f);
        } else if (query_type == Q_reverse) {
            const int l = rng() % (N + 1);
            const int r = l + rng() % (N - l + 1);
            t1.reverse(l, r);
            t2.reverse(l, r);
        } else if (query_type == Q_reverse_all) {
            t1.reverse_all();
            t2.reverse_all();
        } else {
            assert(false);
        }
    }
}

int main() {
    test();
    std::cout << "Hello World" << std::endl;
    return 0;
}