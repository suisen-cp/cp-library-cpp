#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>
#include <limits>

#include "library/datastructure/segment_tree/persistent_segment_tree.hpp"

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

    T prod_all() const {
        return prod(0, _n);
    }
    T prod(int l, int r) const {
        assert(0 <= l and l <= r and r <= _n);
        T res = e();
        for (int i = l; i < r; ++i) res = op(res, _dat[i]);
        return res;
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
private:
    int _n;
    std::vector<T> _dat;
};

/**
 * Point Set Range Min
 */

constexpr int inf = std::numeric_limits<int>::max() / 2;

struct S {
    int val;
    S() : S(inf) {}
    S(int val) : val(val) {}

    bool operator==(const S &other) const {
        return val == other.val;
    }
    bool operator!=(const S &other) const {
        return not operator==(other);
    }
};

S op(S x, S y) {
    return S{ std::min(x.val, y.val) };
}
S e() {
    return S{};
}

using Tree = suisen::PersistentSegmentTree<S, op, e>;
using Naive = NaiveSolutionForSegmentTree<S, op, e>;

#include <random>
#include <algorithm>

constexpr int Q_get = 0;
constexpr int Q_set = 1;
constexpr int Q_prod = 2;
constexpr int Q_prod_all = 3;
constexpr int Q_max_right = 4;
constexpr int Q_min_left = 5;
constexpr int QueryTypeNum = 6;

void test() {
    constexpr int N = 3000, Q = 3000, MAX_VAL = inf;

    std::mt19937 rng{std::random_device{}()};

    Tree::init_pool(1000000);

    std::vector<S> init(N);
    for (int i = 0; i < N; ++i) init[i] = { int(rng() % MAX_VAL) };
    
    std::vector<Tree> ts;
    std::vector<Naive> naive_sols;

    ts.push_back(Tree{init});
    naive_sols.push_back(Naive{init});

    for (int i = 0; i < Q; ++i) {
        const int query_type = rng() % QueryTypeNum;
        const int sequence_id = rng() % ts.size();
        auto &act = ts[sequence_id];
        auto &exp = naive_sols[sequence_id];
        if (query_type == Q_get) {
            const int i = rng() % N;
            assert(act.get(i) == exp.get(i));
        } else if (query_type == Q_set) {
            const int i = rng() % N;
            const S v { int(rng() % MAX_VAL) };
            ts.push_back(act.set(i, v));
            naive_sols.push_back(exp);
            naive_sols.back().set(i, v);
        } else if (query_type == Q_prod) {
            const int l = rng() % (N + 1);
            const int r = l + rng() % (N - l + 1);
            assert(act.prod(l, r) == exp.prod(l, r));
        } else if (query_type == Q_prod_all) {
            assert(act.prod_all() == exp.prod_all());
        } else if (query_type == Q_max_right) {
            const int l = rng() % (N + 1);
            const int r = l + rng() % (N - l + 1);
            const int v = std::min(inf, exp.prod(l, r).val + int(rng() % MAX_VAL) - MAX_VAL / 2);
            auto pred = [&](const S &x) { return x.val >= v; };
            assert(act.max_right(l, pred) == exp.max_right(l, pred));
        } else if (query_type == Q_min_left) {
            const int l = rng() % (N + 1);
            const int r = l + rng() % (N - l + 1);
            const int v = std::min(inf, exp.prod(l, r).val + int(rng() % MAX_VAL) - MAX_VAL / 2);
            auto pred = [&](const S &x) { return x.val >= v; };
            assert(act.min_left(r, pred) == exp.min_left(r, pred));
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