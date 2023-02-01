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

#include "library/datastructure/bbst/implicit_treap_segtree.hpp"

template <typename T, T(*op)(T, T), T(*e)()>
struct NaiveSolutionForSegmentTree {
    NaiveSolutionForSegmentTree() = default;
    NaiveSolutionForSegmentTree(const std::vector<T> &dat) : _n(dat.size()), _dat(dat) {}

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

    T prod_all() const {
        return prod(0, _n);
    }
    T prod(int l, int r) const {
        assert(0 <= l and l <= r and r <= _n);
        T res = e();
        for (int i = l; i < r; ++i) res = op(res, _dat[i]);
        return res;
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

    template <typename Pred>
    int max_right(int l, Pred &&pred) const {
        assert(0 <= l and l <= _n);
        T sum = e();
        for (int r = l; r < _n; ++r) {
            T next_sum = op(sum, _dat[r]);
            if (not pred(next_sum)) return r;
            sum = std::move(next_sum);
        }
        return _n;
    }

    template <typename Pred>
    int min_left(int r, Pred &&pred) const {
        assert(0 <= r and r <= _n);
        T sum = e();
        for (int l = r; l > 0; --l) {
            T next_sum = op(_dat[l - 1], sum);
            if (not pred(next_sum)) return l;
            sum = std::move(next_sum);
        }
        return 0;
    }

    std::vector<T> dump() { return _dat; }
private:
    int _n;
    std::vector<T> _dat;
};

/**
 * Point Set Range Sum
 */

using S = long long;

S op(S x, S y) {
    return x + y;
}
S e() {
    return 0;
}
S toggle(S x) {
    return x;
}

using Tree = suisen::DynamicSegmentTree<S, op, e, toggle>;
using Naive = NaiveSolutionForSegmentTree<S, op, e>;

#include <random>
#include <algorithm>

constexpr int Q_get = 0;
constexpr int Q_set = 1;
constexpr int Q_insert = 4;
constexpr int Q_erase = 5;
constexpr int Q_rotate = 10;
constexpr int Q_prod = 2;
constexpr int Q_prod_all = 3;
constexpr int Q_reverse = 6;
constexpr int Q_reverse_all = 7;
constexpr int Q_max_right = 8;
constexpr int Q_min_left = 9;
constexpr int QueryTypeNum = 11;

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
            assert(t1.get(i) == t2.get(i));
        } else if (query_type == Q_set) {
            const int i = rng() % N;
            const S v = rng() % MAX_VAL;
            t1.set(i, v);
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
        } else if (query_type == Q_prod) {
            const int l = rng() % (N + 1);
            const int r = l + rng() % (N - l + 1);
            assert(t1.prod(l, r) == t2.prod(l, r));
        } else if (query_type == Q_prod_all) {
            assert(t1.prod_all() == t2.prod_all());
        } else if (query_type == Q_reverse) {
            const int l = rng() % (N + 1);
            const int r = l + rng() % (N - l + 1);
            t1.reverse(l, r);
            t2.reverse(l, r);
        } else if (query_type == Q_reverse_all) {
            t1.reverse_all();
            t2.reverse_all();
        } else if (query_type == Q_max_right) {
            const int l = rng() % (N + 1);
            const int r = l + rng() % (N - l + 1);
            long long sum = std::max(0LL, t2.prod(l, r) + int(rng() % MAX_VAL) - MAX_VAL / 2);
            auto pred = [&](const S &x) { return x <= sum; };
            assert(t1.max_right(l, pred) == t2.max_right(l, pred));
        } else if (query_type == Q_min_left) {
            const int l = rng() % (N + 1);
            const int r = l + rng() % (N - l + 1);
            long long sum = std::max(0LL, t2.prod(l, r) + int(rng() % MAX_VAL) - MAX_VAL / 2);
            auto pred = [&](const S &x) { return x <= sum; };
            assert(t1.min_left(r, pred) == t2.min_left(r, pred));
        } else {
            assert(false);
        }
    }
}

void test2() {
    std::mt19937 rng{ std::random_device{}() };
    Tree seq;
    const int n = 300, k = 20;

    std::vector<S> q(n * k);
    for (int i = 0; i < n * k; ++i) {
        q[i] = i % n;
    }
    std::shuffle(q.begin(), q.end(), rng);

    for (int v : q) {
        if (rng() % 2) {
            int k = seq.lower_bound(v);
            assert(k == 0 or seq[k - 1] < v);
            assert(k == seq.size() or seq[k] >= v);
            seq.insert(k, v);
        } else {
            int k = seq.upper_bound(v);
            assert(k == 0 or seq[k - 1] <= v);
            assert(k == seq.size() or seq[k] > v);
            seq.insert(k, v);
        }
    }

    std::vector<S> sorted = q;
    std::sort(sorted.begin(), sorted.end());

    assert(std::equal(sorted.begin(), sorted.end(), seq.begin()));
    assert(std::equal(sorted.rbegin(), sorted.rend(), seq.rbegin()));

    for (int i = 0; i < n * k; ++i) {
        assert(*seq.kth_iterator(i) == i / k);
    }

    for (int q = 0; q < 10000; ++q) {
        int a = rng() % (n * k + 1);
        int b = rng() % (n * k + 1);
        int d = b - a;
        assert(seq.kth_iterator(a) + d == seq.kth_iterator(b));
        assert(seq.kth_iterator(a) == seq.kth_iterator(b) - d);
    }

    std::vector<S> naive = sorted;

    for (int q = 0; q < 500; ++q) {
        if (rng() % 2) {
            int l = rng() % (n * k + 1);
            int r = rng() % (n * k + 1);
            if (l > r) std::swap(l, r);
            seq.reverse(l, r);
            std::reverse(naive.begin() + l, naive.begin() + r);
        } else {
            assert(std::equal(naive.begin(), naive.end(), seq.begin()));
            assert(std::equal(naive.rbegin(), naive.rend(), seq.rbegin()));
            std::vector<S> dump = seq.dump();
            assert(std::equal(naive.begin(), naive.end(), dump.begin()));
        }
    }

    // for (S& e : seq) --e; // Compile Error 
    // for (S& e : naive) --e;
    // assert(std::equal(naive.begin(), naive.end(), seq.begin()));
    // assert(std::equal(naive.rbegin(), naive.rend(), seq.rbegin()));

    const Tree& const_seq = const_cast<const Tree&>(seq);
    assert(std::equal(naive.begin(), naive.end(), const_seq.begin()));
    assert(std::equal(naive.rbegin(), naive.rend(), const_seq.rbegin()));

    for (int i = 0; i < n * k; ++i) {
        assert(const_seq[i] == naive[i]);
    }
}

int main() {
    test();
    test2();
    std::cout << "Hello World" << std::endl;
    return 0;
}