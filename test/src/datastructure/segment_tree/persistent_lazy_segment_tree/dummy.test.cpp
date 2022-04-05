#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>
#include <limits>

#include "library/datastructure/segment_tree/persistent_lazy_segment_tree.hpp"

template <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F, T)>
struct NaiveSolutionForLazySegmentTree {
    NaiveSolutionForLazySegmentTree() = default;
    NaiveSolutionForLazySegmentTree(const std::vector<T> &dat) : _n(dat.size()), _dat(dat) {}

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

    void apply_all(const F &f) {
        apply(0, _n, f);
    }
    void apply(int l, int r, const F &f) {
        assert(0 <= l and l <= r and r <= _n);
        for (int i = l; i < r; ++i) _dat[i] = mapping(f, _dat[i]);
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
 * Range Update Range Sum
 */

struct S {
    long long sum;
    int len;
    S() = default;
    S(long long sum, int len) : sum(sum), len(len) {}

    bool operator==(const S &other) const {
        return sum == other.sum and len == other.len;
    }
    bool operator!=(const S &other) const {
        return not operator==(other);
    }
};

struct F {
    static constexpr int identity = std::numeric_limits<int>::max();

    int val;
    F() : val(identity) {}
    F(int val) : val(val) {}
};

S op(S x, S y) {
    return S{ x.sum + y.sum, x.len + y.len };
}
S e() {
    return S{ 0LL, 0 };
}
S mapping(F f, S x) {
    return f.val == F::identity ? x : S{ (long long) f.val * x.len, x.len };
}
F composition(F f, F g) {
    return f.val == F::identity ? g : f;
}
F id() {
    return F{};
}

using Tree = suisen::PersistentLazySegmentTree<S, op, e, F, mapping, composition, id>;
using Naive = NaiveSolutionForLazySegmentTree<S, op, e, F, mapping>;

#include <random>
#include <algorithm>

constexpr int Q_get = 0;
constexpr int Q_set = 1;
constexpr int Q_prod = 2;
constexpr int Q_prod_all = 3;
constexpr int Q_apply = 4;
constexpr int Q_apply_all = 5;
constexpr int Q_max_right = 6;
constexpr int Q_min_left = 7;
constexpr int QueryTypeNum = 8;

void test() {
    constexpr int N = 3000, Q = 3000, MAX_VAL = 1000000000;

    std::mt19937 rng{std::random_device{}()};

    Tree::init_pool(1000000);

    std::vector<S> init(N);
    for (int i = 0; i < N; ++i) init[i] = { (long long) rng() % MAX_VAL, 1 };
    
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
            const S v = { (long long) rng() % MAX_VAL, 1 };
            ts.push_back(act.set(i, v));
            naive_sols.push_back(exp);
            naive_sols.back().set(i, v);
        } else if (query_type == Q_prod) {
            const int l = rng() % (N + 1);
            const int r = l + rng() % (N - l + 1);
            assert(act.prod(l, r) == exp.prod(l, r));
        } else if (query_type == Q_prod_all) {
            assert(act.prod_all() == exp.prod_all());
        } else if (query_type == Q_apply) {
            const int l = rng() % (N + 1);
            const int r = l + rng() % (N - l + 1);
            const int f = rng() % MAX_VAL;
            ts.push_back(act.apply(l, r, f));
            naive_sols.push_back(exp);
            naive_sols.back().apply(l, r, f);
        } else if (query_type == Q_apply_all) {
            const int f = rng() % MAX_VAL;
            ts.push_back(act.apply_all(f));
            naive_sols.push_back(exp);
            naive_sols.back().apply_all(f);
        } else if (query_type == Q_max_right) {
            const int l = rng() % (N + 1);
            const int r = l + rng() % (N - l + 1);
            long long sum = std::max(0LL, exp.prod(l, r).sum + int(rng() % MAX_VAL) - MAX_VAL / 2);
            auto pred = [&](const S &x) { return x.sum <= sum; };
            assert(act.max_right(l, pred) == exp.max_right(l, pred));
        } else if (query_type == Q_min_left) {
            const int l = rng() % (N + 1);
            const int r = l + rng() % (N - l + 1);
            long long sum = std::max(0LL, exp.prod(l, r).sum + int(rng() % MAX_VAL) - MAX_VAL / 2);
            auto pred = [&](const S &x) { return x.sum <= sum; };
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