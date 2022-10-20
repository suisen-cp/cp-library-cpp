#ifndef SUISEN_RUN_ENUMERATE
#define SUISEN_RUN_ENUMERATE

#include <limits>
#include <tuple>
#include <atcoder/string>

namespace suisen {
    struct Run {
        int period;
        int l, r;
        Run() = default;
        Run(int period, int l, int r) : period(period), l(l), r(r) {}
        friend bool operator<(const Run& r1, const Run& r2) {
            return r1.period != r2.period ? r1.period < r2.period : r1.l != r2.l ? r1.l < r2.l : r1.r < r2.r;
        }
        friend bool operator>(const Run& r1, const Run& r2) { return r2 < r1; }
        friend bool operator<=(const Run& r1, const Run& r2) { return not (r2 < r1); }
        friend bool operator>=(const Run& r1, const Run& r2) { return not (r1 < r2); }
        friend bool operator==(const Run& r1, const Run& r2) { return r1.period == r2.period and r1.l == r2.l and r1.r == r2.r; }
        friend bool operator!=(const Run& r1, const Run& r2) { return not (r1 == r2); }
    };

    template <typename Container, typename = std::void_t<typename Container::value_type>>
    std::vector<Run> run_enumerate(Container& s, typename Container::value_type sentinel = std::numeric_limits<typename Container::value_type>::min()) {
        for (auto& e : s) assert(e != sentinel);

        std::vector<Run> glob_result;

        using T = typename Container::value_type;
        auto div_conq = [&](auto div_conq, int l, int r) -> std::vector<Run> {
            if (r - l <= 1) return {};

            const int m = (l + r) >> 1;
            std::vector<Run> run_l = div_conq(div_conq, l, m);
            std::vector<Run> run_r = div_conq(div_conq, m, r);

            std::vector<T> rl;
            std::copy(std::begin(s) + m, std::begin(s) + r, std::back_inserter(rl));
            rl.push_back(sentinel);
            std::copy(std::begin(s) + l, std::begin(s) + m, std::back_inserter(rl));
            std::vector<int> z_rl = atcoder::z_algorithm(rl);

            std::reverse(std::begin(rl), std::end(rl));
            std::vector<int> z_rl_rev = atcoder::z_algorithm(rl);

            const int siz = rl.size();

            std::vector<Run> result;

            auto add_ans = [&](Run&& run) { (run.l == l or run.r == r ? result : glob_result).emplace_back(std::move(run)); };

            const int len_l = m - l, len_r = r - m;
            std::vector<Run> run_m(len_r / 2 + 1);
            for (auto& run : run_r) {
                if (run.l != m) {
                    add_ans(std::move(run));
                    continue;
                }
                run_m[run.period] = std::move(run);
            }
            for (auto& run : run_l) {
                if (run.r != m) {
                    add_ans(std::move(run));
                    continue;
                }
                const int period = run.period;
                if (z_rl[siz - period] == period) {
                    if (run_m[period].period) {
                        run.r = run_m[period].r;
                        run_m[period] = Run{};
                        add_ans(std::move(run));
                    } else {
                        run.r = m + period + z_rl[period];
                        add_ans(std::move(run));
                    }
                } else {
                    run.r = m + z_rl[siz - period];
                    add_ans(std::move(run));
                }
            }
            for (auto& run : run_m) if (run.period) {
                const int period = run.period;
                if (z_rl[siz - period] == period) {
                    if (2 * period <= len_l and z_rl[siz - 2 * period] >= period) continue;
                    run.l = m - period - z_rl_rev[period];
                    add_ans(std::move(run));
                } else {
                    run.l = m - z_rl_rev[siz - period];
                    add_ans(std::move(run));
                }
            }

            for (int period = 1; period <= len_l; ++period) {
                bool skip_r = 2 * period <= len_r and z_rl[period] >= period;
                bool skip_l = 2 * period <= len_l and z_rl[siz - 2 * period] >= period;
                if (z_rl[siz - period] == period) {
                    if (skip_l or skip_r) continue;

                    const int beg_pos = m - period - z_rl_rev[period];
                    const int end_pos = m + period + z_rl[period];
                    add_ans(Run{ period, beg_pos, end_pos });
                } else {
                    if (not skip_r) {
                        const int beg_pos = m - z_rl_rev[siz - period];
                        const int end_pos = m + period + z_rl[period];
                        if (end_pos - beg_pos >= 2 * period) {
                            add_ans(Run{ period, beg_pos, end_pos });
                        }
                    }
                    if (not skip_l) {
                        const int beg_pos = m - period - z_rl_rev[period];
                        const int end_pos = m + z_rl[siz - period];
                        if (end_pos - beg_pos >= 2 * period) {
                            add_ans(Run{ period, beg_pos, end_pos });
                        }
                    }
                }
            }
            return result;
        };
        const int n = s.size();
        std::vector<std::tuple<int, int, int>> runs;
        for (Run& run : div_conq(div_conq, 0, n)) {
            runs.emplace_back(run.l, run.r, run.period);
        }
        for (Run& run : glob_result) {
            runs.emplace_back(run.l, run.r, run.period);
        }
        std::sort(std::begin(runs), std::end(runs));
        runs.erase(
            std::unique(
                std::begin(runs), std::end(runs),
                [](auto& r1, auto& r2) {
                    return std::get<0>(r1) == std::get<0>(r2) and std::get<1>(r1) == std::get<1>(r2);
                }
            ), std::end(runs)
                    );
        std::vector<Run> res;
        for (auto& [l, r, t] : runs) res.emplace_back(t, l, r);
        return res;
    }
} // namespace suisen


#endif // SUISEN_RUN_ENUMERATE
