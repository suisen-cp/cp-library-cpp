#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& a) {
    out << '{';
    for (auto& e : a) out << e << ',';
    return out << '}';
}

#include "library/datastructure/bbst/implicit_treap.hpp"

template <typename T>
struct NaiveSolutionForDynamicArray {
    NaiveSolutionForDynamicArray() = default;
    NaiveSolutionForDynamicArray(const std::vector<T>& dat): _n(dat.size()), _dat(dat) {}

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

using Tree = suisen::DynamicArray<S>;
using Naive = NaiveSolutionForDynamicArray<S>;

#include <random>
#include <algorithm>

constexpr int Q_get = 0;
constexpr int Q_set = 1;
constexpr int Q_insert = 2;
constexpr int Q_erase = 3;
constexpr int Q_rotate = 4;
constexpr int QueryTypeNum = 5;

void test() {
    int N = 3000, Q = 3000, MAX_VAL = 1000000000;

    std::mt19937 rng{ std::random_device{}() };

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
        } else {
            assert(false);
        }
    }
}

void test2() {
    std::mt19937 rng{ std::random_device{}() };
    Tree seq;
    const int n = 300, k = 20;

    std::vector<int> q(n * k);
    for (int i = 0; i < n * k; ++i) {
        q[i] = i % n;
    }
    std::shuffle(q.begin(), q.end(), rng);

    for (int v : q) {
        if (rng() % 2) {
            auto it = seq.lower_bound(v);
            seq.insert(it, v);
            int k = it.index();
            assert(k == 0 or seq[k - 1] < v);
            assert(k == seq.size() - 1 or seq[k + 1] >= v);
        } else {
            auto it = seq.upper_bound(v);
            seq.insert(it, v);
            int k = it.index();
            assert(k == 0 or seq[k - 1] <= v);
            assert(k == seq.size() - 1 or seq[k + 1] > v);
        }
    }

    for (int v : q) {
        auto it = seq.lower_bound(v);
        int k = it.index();
        seq.erase(it);
        assert(k == 0 or seq[k - 1] < v);
        assert(k == seq.size() or seq[k] >= v);
    }

    std::vector<int> sorted = q;
    std::sort(sorted.begin(), sorted.end());

    seq.free();
    seq = sorted;

    assert(std::equal(sorted.begin(), sorted.end(), seq.begin()));
    assert(std::equal(sorted.rbegin(), sorted.rend(), seq.rbegin()));

    for (int i = 0; i < n * k; ++i) {
        assert(seq.begin()[i] == i / k);
    }

    {
        auto it = seq.begin();
        for (int q = 0; q < 100000; ++q) {
            int a = rng() % (n * k + 1);
            auto it2 = seq.begin() + a;
            it += it2 - it;
            if (a < n * k) {
                assert(*it == a / k);
            }
        }
    }

    for (int q = 0; q < 10000; ++q) {
        int a = rng() % (n * k + 1);
        int b = rng() % (n * k + 1);
        int d = b - a;
        assert((seq.begin() + a) + d == seq.begin() + b);
        assert(seq.begin() + a == (seq.begin() + b) - d);

        auto it1 = seq.begin() + a;
        auto it2 = seq.begin() + b;

        if (d > 0) {
            assert(not (it1 == it2));
            assert(it1 != it2);
            assert(not (it1 > it2));
            assert(not (it1 >= it2));
            assert(it1 < it2);
            assert(it1 <= it2);
        } else if (d < 0) {
            assert(not (it1 == it2));
            assert(it1 != it2);
            assert(not (it1 < it2));
            assert(not (it1 <= it2));
            assert(it1 > it2);
            assert(it1 >= it2);
        } else {
            assert(not (it1 != it2));
            assert(it1 == it2);
            assert(not (it1 > it2));
            assert(not (it1 < it2));
            assert(it1 <= it2);
            assert(it1 >= it2);
        }

        if (a != n * k and b != n * k) {
            assert(*it1 == a / k);
            assert(*it2 == b / k);

            it1 += d;

            assert(not (it1 != it2));
            assert(it1 == it2);
            assert(not (it1 < it2));
            assert(not (it1 > it2));
            assert(it1 <= it2);
            assert(it1 >= it2);
            assert(*it1 == *it2);
        }
    }

    std::vector<int> naive = sorted;
    assert(std::equal(naive.begin(), naive.end(), seq.begin()));

    for (int& e : seq) --e;
    for (int& e : naive) --e;
    assert(std::equal(naive.begin(), naive.end(), seq.begin()));
    assert(std::equal(naive.rbegin(), naive.rend(), seq.rbegin()));

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