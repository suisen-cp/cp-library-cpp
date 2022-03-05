#ifndef SUISEN_MO
#define SUISEN_MO

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

namespace suisen {
    struct Mo {
        Mo() {}
        Mo(const int n, const std::vector<std::pair<int, int>> &queries) : n(n), q(queries.size()), b(std::max(1, int(n / (::sqrt(q) + 1)))), qs(queries), ord(q) {
            std::iota(ord.begin(), ord.end(), 0);
            std::sort(
                ord.begin(), ord.end(),
                [&, this](int i, int j) {
                    const auto &[li, ri] = qs[i];
                    const auto &[lj, rj] = qs[j];
                    const int bi = li / b, bj = lj / b;
                    if (bi != bj) return bi < bj;
                    if (ri != rj) return bi & 1 ? ri > rj : ri < rj;
                    return li < lj;
                }
            );
        }

        // getter methods used in updating functions: AddL, DelL, etc.
        auto get_left()  const { return l; }
        auto get_right() const { return r; }
        auto get_range() const { return std::make_pair(l, r); }

        /**
         * [Parameters]
         * Eval : () -> T : return the current answer
         * AddL : int -> any (discarded) : add    `l` to   the current range [l + 1, r)
         * DelL : int -> any (discarded) : delete `l` from the current range [l, r)
         * AddR : int -> any (discarded) : add    `r` to   the current range [l, r)
         * DelR : int -> any (discarded) : delete `r` from the current range [l, r + 1)
         * 
         * [Note]
         * starting from the range [0, 0).
         */
        template <typename Eval, typename AddL, typename DelL, typename AddR, typename DelR>
        auto solve(Eval eval, AddL add_l, DelL del_l, AddR add_r, DelR del_r) {
            l = 0, r = 0;
            std::vector<decltype(eval())> res(q);
            for (int qi : ord) {
                const auto &[nl, nr] = qs[qi];
                while (r < nr) add_r(r), ++r;
                while (l > nl) --l, add_l(l);
                while (r > nr) --r, del_r(r);
                while (l < nl) del_l(l), ++l;
                res[qi] = eval();
            }
            return res;
        }
    
        /**
         * [Parameters]
         * Eval : () -> T : return the current answer
         * Add : int -> any (discarded) : add    `i` to   the current range [i + 1, r) or [l, i)
         * Del : int -> any (discarded) : delete `i` from the current range [i, r) or [l, i + 1)
         * 
         * [Note]
         * starting from the range [0, 0).
         */
        template <typename Eval, typename Add, typename Del>
        auto solve(Eval eval, Add add, Del del) {
            return solve(eval, add, del, add, del);
        }

    private:
        int n, q, b;
        std::vector<std::pair<int, int>> qs;
        std::vector<int> ord;
        int l = 0, r = 0;
    };
} // namespace suisen

#endif // SUISEN_MO
