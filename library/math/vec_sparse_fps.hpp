#ifndef SUISEN_VEC_SPARSE_FPS
#define SUISEN_VEC_SPARSE_FPS

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

namespace suisen {
    template <typename IndexType, typename ValueType, std::enable_if_t<std::is_integral_v<IndexType>, std::nullptr_t> = nullptr>
    struct VecSparseFPS {
        using index_type = IndexType;
        using value_type = ValueType;

        using convolution_t = std::vector<value_type> (*)(const std::vector<value_type> &, const std::vector<value_type> &);

        VecSparseFPS() {}
        template <typename IT, typename VT>
        VecSparseFPS(std::vector<std::pair<IT, VT>> data, bool sorted = false) {
            if (not sorted) std::sort(data.begin(), data.end(), [](auto &p1, auto &p2) { return p1.first < p2.first; });
            for (const auto &[i, v] : data) add_to_last(i, v);
        }

        static void set_multiplication(convolution_t multiplication) {
            VecSparseFPS<index_type, value_type>::mult = multiplication;
        }

        value_type operator[](index_type i) {
            auto it = std::upper_bound(_f.begin(), _f.end(), i, [](index_type i, const auto& p) { return i < p.first; });
            if (it == _f.begin()) return 0;
            const auto &[j, p] = *--it;
            return i - j < int(p.size()) ? p[i - j] : value_type(0);
        }

        VecSparseFPS operator-() const {
            VecSparseFPS res;
            for (const auto &[i, f] : _f) {
                auto &back = res._f.emplace_back(i, {});
                for (const auto &v : f) back.second.push_back(-v);
            }
            return res;
        }
        friend VecSparseFPS operator+(const VecSparseFPS &f, const VecSparseFPS &g) {
            const int n = f._f.size(), m = g._f.size();
            VecSparseFPS h;
            for (int i = 0, j = 0; i < n and j < m;) {
                if (j == m or (i < n and f._f[i].first < g._f[j].first)) {
                    h.add_to_last(f._f[i++]);
                } else {
                    h.add_to_last(g._f[j++]);
                }
            }
            return h;
        }
        friend VecSparseFPS operator-(const VecSparseFPS &f, const VecSparseFPS &g) {
            return f + -g;
        }
        friend VecSparseFPS operator*(const VecSparseFPS &f, const VecSparseFPS &g) {
            std::vector<std::pair<index_type, std::vector<value_type>>> data;
            for (const auto &[i, a] : f._f) for (const auto &[j, b] : g._f) {
                data.emplace_back(i + j, VecSparseFPS<index_type, value_type>::mult(a, b));
            }
            std::sort(data.begin(), data.end(), [](auto &p1, auto &p2) { return p1.first < p2.first; });
            VecSparseFPS h;
            for (auto &[i, a] : data) {
                h.add_to_last(i, std::move(a));
            }
            return h;
        }
        friend VecSparseFPS operator*(const VecSparseFPS &f, const std::vector<value_type> &g) {
            VecSparseFPS h;
            for (const auto &[i, a] : f._f) h.add_to_last({ i, VecSparseFPS<index_type, value_type>::mult(a, g) });
            return h;
        }
        friend VecSparseFPS operator*(const std::vector<value_type> &f, const VecSparseFPS &g) {
            return g * f;
        }

        auto begin() { return _f.begin(); }
        auto end() { return _f.end(); }

        void clear() { _f.clear(); }

        void add_to_last(index_type i, const value_type &v) {
            if (_f.size()) {
                auto &[j, p] = _f.back();
                assert(j <= i);
                int d = p.size();
                if (j + d == i) {
                    p.push_back(v);
                    return;
                } else if (j + d > i) {
                    p[i - j] += v;
                    return;
                }
            }
            _f.emplace_back(i, std::vector<value_type> { v });
        }

        void add_to_last(const std::pair<index_type, std::vector<value_type>> &ig) {
            const auto &[i, g] = ig;
            if (_f.size()) {
                auto &[j, p] = _f.back();
                assert(j <= i);
                int pd = p.size();
                if (j + pd >= i) {
                    int gd = g.size();
                    int offset = i - j;
                    p.resize(std::max(pd, offset + gd));
                    for (int k = 0; k < gd; ++k) p[offset + k] += g[k];
                    return;
                }
            }
            _f.push_back(ig);
        }

        static value_type bostan_mori(VecSparseFPS P, std::vector<value_type> Q, long long m) {
            for (; m; m >>= 1) {
                std::vector<mint> mQ = Q;
                for (int i = 1; i < int(Q.size()); i += 2) mQ[i] = -mQ[i];
                auto nP = P * mQ;
                P.clear();
                for (auto &[i, f] : nP) {
                    int sz = f.size();
                    for (int k = (i % 2 != m % 2); k < sz; k += 2) P.add_to_last((i + k) >> 1, f[k]);
                }
                auto nQ = VecSparseFPS<index_type, value_type>::mult(Q, mQ);
                Q.clear();
                for (int i = 0; i < int(nQ.size()); i += 2) Q.push_back(nQ[i]);
            }
            return P[0];
        }

    private:
        static inline convolution_t mult = [](const auto &, const auto &) {
            std::cerr << "convolution function is not available." << std::endl;
            assert(false);
            return std::vector<value_type>{};
        };

        std::vector<std::pair<index_type, std::vector<value_type>>> _f;
    };
} // namespace suisen

#endif // SUISEN_VEC_SPARSE_FPS
