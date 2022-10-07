#ifndef SUISEN_INDEX_CALCULUS
#define SUISEN_INDEX_CALCULUS

#include <algorithm>
#include <cmath>
#include <optional>

#include "library/number/ext_gcd.hpp"
#include "library/number/sieve_of_eratosthenes.hpp"

namespace suisen {
    struct IndexCalculus {
    private:
        using mint_p = atcoder::dynamic_modint<1000000001>;
        using mint_pm1 = atcoder::dynamic_modint<1000000002>;

        using row = std::pair<std::vector<std::pair<int, mint_pm1>>, mint_pm1>;

        static constexpr int L = 1000000;
        static inline Sieve<L> sieve{};
    public:
        IndexCalculus(int p, int g) : _p(p), _alpha(g), _b(bound(p)), _ps(primes(_b)), _l(_ps.size()), _es(_l, 0), _ps_inv(_b + 1) {
            for (int i = 0; i < int(_ps.size()); ++i) {
                _ps_inv[_ps[i]] = i;
            }
        }

        int operator()(int beta) {
            beta %= _p;
            if (_p == 2) {
                if (beta == 0) return -1;
                return 0;
            }
            return with_modint_context(
                [&, this]() -> int {
                    if (beta == 0) return -1;
                    const int inv_beta = mint_p(beta).inv().val();

                    auto find_index = [](const row& r, int col) {
                        auto find_col_cmp = [](const std::pair<int, mint_pm1>& cell, int v) { return cell.first < v; };
                        const int idx = std::lower_bound(r.first.begin(), r.first.end(), col, find_col_cmp) - r.first.begin();
                        return idx == int(r.first.size()) or r.first[idx].first != col ? -1 : idx;
                    };

                    auto up = [&, this](std::vector<row> &mat) {
                        std::vector<row> nmat;
                        int ans = -1;
                        for (int i = mat.size() - 1; i >= 0; --i) {
                            row eq;
                            eq.second = mat[i].second;
                            for (auto [j, val] : mat[i].first) {
                                if (j < _l and _es[j] != 0) {
                                    eq.second -= _es[j] * val;
                                } else {
                                    eq.first.emplace_back(j, val);
                                }
                            }
                            if (eq.first.size() == 1) {
                                auto [j, val] = eq.first.front();
                                auto rhs = eq.second;
                                const int d = std::gcd(_p - 1, val.val());
                                if (d != 1) continue;
                                assert(rhs.val() % d == 0);
                                const int q = (_p - 1) / d;
                                auto log_pj = gcd_inv(val.val() / d, q).first * (rhs.val() / d) % q;
                                if (j == _l) {
                                    ans = log_pj;
                                } else {
                                    _es[j] = log_pj;
                                }
                            } else {
                                nmat.emplace_back(std::move(eq));
                            }
                        }
                        nmat.swap(mat);
                        return ans;
                    };

                    std::vector<row> mat(_l + 1);

                    for (int i = 0; i < _l + 1; ++i) {
                        mat[i] = gen_equation(inv_beta);
                    }
                    for (int i = 0; i < int(mat.size()); ++i) {
                        int j = _l + 1;
                        int pivot = -1;

                        for (int i2 = i; i2 < int(mat.size()); ++i2) {
                            int j2 = mat[i2].first.front().first;
                            if (j2 < j) j = j2, pivot = i2;
                        }
                        std::swap(mat[pivot], mat[i]);
                        for (int i2 = i + 1; i2 < int(mat.size()); ++i2) {
                            int idx = find_index(mat[i2], j);
                            if (idx < 0) continue;
                            assert(mat[i].first[0].first == j);
                            mint_pm1 val = mat[i].first[0].second;
                            eliminate(val, mat[i], mat[i2].first[idx].second, mat[i2]);
                            if (mat[i2].first.empty()) {
                                assert(mat[i2].second == 0);
                                std::swap(mat[i2], mat.back());
                                mat.pop_back();
                                --i2;
                            } else {
                                assert(mat[i2].first[0].first > j);
                            }
                        }
                    }
                    if (const int ans = up(mat); ans >= 0) return ans;

                    while (true) {
                        const int row_num = mat.size();

                        row r = gen_equation(inv_beta);

                        bool inserted = false;
                        for (int i = 0; i < row_num; ++i) {
                            if (r.first.empty()) break;
                            auto [j, val] = mat[i].first.front();
                            if (r.first[0].first < j) {
                                mat.insert(mat.begin() + i, r);
                                inserted = true;
                                break;
                            }
                            const int idx = find_index(r, j);
                            if (idx < 0) continue;
                            eliminate(val, mat[i], r.first[idx].second, r);
                        }
                        if (not inserted) {
                            if (r.first.size()) {
                                mat.emplace_back(r);
                            } else {
                                continue;
                            }
                        }
                        if (const int ans = up(mat); ans >= 0) return ans;
                    }
                }
            );
        }

    private:
        int _p, _alpha, _b;

        std::vector<int> _ps;
        int _l;
        std::vector<int> _es;

        std::vector<int> _ps_inv;

        template <typename F>
        std::invoke_result_t<F> with_modint_context(F&& f) {
            const int old_mod_p = mint_p::mod();
            const int old_mod_pm1 = mint_pm1::mod();
            mint_p::set_mod(_p);
            mint_pm1::set_mod(_p - 1);
            std::invoke_result_t<F> res = f();
            mint_p::set_mod(old_mod_p);
            mint_pm1::set_mod(old_mod_pm1);
            return res;
        }

        row gen_equation(int inv_beta) const {
            static std::mt19937_64 rng{ std::random_device{}() };
            while (true) {
                int k = rng() % (_p - 1) + 1;
                auto opt_fac = try_factorize((mint_p(_alpha).pow(k) * inv_beta).val());
                if (not opt_fac.has_value()) continue;
                mint_pm1 rhs = k;
                std::vector<std::pair<int, mint_pm1>> lhs;
                for (auto [i, c] : *opt_fac) {
                    if (_es[i] != 0) {
                        rhs -= c * _es[i];
                    } else {
                        lhs.emplace_back(i, c);
                    }
                }
                lhs.emplace_back(_l, 1);
                return { lhs, rhs };
            }
        }

        std::optional<std::vector<std::pair<int, int>>> try_factorize(int v) const {
            std::vector<std::pair<int, int>> res;
            const int num_p = _ps.size();
            for (int i = 0; i < num_p; ++i) {
                // if ((i == 10 and v > L)) return std::nullopt;
                if (v < L) {
                    const int max_p = _ps.back();
                    for (auto [p, c] : sieve.factorize(v)) {
                        if (p > max_p) return std::nullopt;
                        res.emplace_back(_ps_inv[p], c);
                    }
                    std::sort(res.begin(), res.end());
                    return res;
                }
                if (v % _ps[i] == 0) {
                    int q = 0;
                    do {
                        v /= _ps[i];
                        ++q;
                    } while (v % _ps[i] == 0);
                    res.emplace_back(i, q);
                }
            }
            if (v != 1) return std::nullopt;
            return res;
        }

        static int bound(int p) {
            // return ::exp(::sqrt(std::max(0., ::log(p) * ::log(::log(p)))) / 2) + 1;
            return 200;
        }
        static std::vector<int> primes(int b) {
            std::vector<int> ps;
            std::vector<int8_t> sieve(b + 1, true);
            for (int p = 2; p <= b; ++p) {
                if (not sieve[p]) continue;
                ps.push_back(p);
                for (int q = p * p; q <= b; q += p) sieve[q] = false;
            }
            return ps;
        }

        static row add(const mint_pm1 c1, const row& r1, const mint_pm1 c2, const row& r2) {
            row res;
            const int s1 = r1.first.size(), s2 = r2.first.size();
            for (int i = 0, j = 0; i < s1 or j < s2;) {
                const int idx1 = i == s1 ? std::numeric_limits<int>::max() : r1.first[i].first;
                const int idx2 = j == s2 ? std::numeric_limits<int>::max() : r2.first[j].first;
                int idx;
                mint_pm1 val;
                if (idx1 < idx2) {
                    idx = idx1;
                    val = c1 * r1.first[i++].second;
                } else if (idx2 < idx1) {
                    idx = idx2;
                    val = c2 * r2.first[j++].second;
                } else {
                    idx = idx1;
                    val = c1 * r1.first[i++].second + c2 * r2.first[j++].second;
                }
                if (val != 0) {
                    res.first.emplace_back(idx, val);
                }
            }
            res.second = c1 * r1.second + c2 * r2.second;
            return res;
        }

        static void eliminate(mint_pm1 &t1, row& r1, mint_pm1 t2, row& r2) {
            for (; t2 != 0;) {
                if (t1.val() > t2.val()) {
                    std::swap(r1, r2);
                    std::swap(t1, t2);
                }
                const int q = t2.val() / t1.val();
                r2 = add(1, r2, -q, r1);
                t2 -= t1 * q;
            }
        }
    };
} // namespace suisen


#endif // SUISEN_INDEX_CALCULUS
