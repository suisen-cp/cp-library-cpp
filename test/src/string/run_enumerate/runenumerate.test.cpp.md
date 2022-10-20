---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/string/run_enumerate.hpp
    title: Run Enumerate
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/runenumerate
    links:
    - https://judge.yosupo.jp/problem/runenumerate
  bundledCode: "#line 1 \"test/src/string/run_enumerate/runenumerate.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/runenumerate\"\n\n#include <iostream>\n\
    \n#line 1 \"library/string/run_enumerate.hpp\"\n\n\n\n#include <limits>\n#include\
    \ <tuple>\n#include <atcoder/string>\n\nnamespace suisen {\n    struct Run {\n\
    \        int period;\n        int l, r;\n        Run() = default;\n        Run(int\
    \ period, int l, int r) : period(period), l(l), r(r) {}\n        friend bool operator<(const\
    \ Run& r1, const Run& r2) {\n            return r1.period != r2.period ? r1.period\
    \ < r2.period : r1.l != r2.l ? r1.l < r2.l : r1.r < r2.r;\n        }\n       \
    \ friend bool operator>(const Run& r1, const Run& r2) { return r2 < r1; }\n  \
    \      friend bool operator<=(const Run& r1, const Run& r2) { return not (r2 <\
    \ r1); }\n        friend bool operator>=(const Run& r1, const Run& r2) { return\
    \ not (r1 < r2); }\n        friend bool operator==(const Run& r1, const Run& r2)\
    \ { return r1.period == r2.period and r1.l == r2.l and r1.r == r2.r; }\n     \
    \   friend bool operator!=(const Run& r1, const Run& r2) { return not (r1 == r2);\
    \ }\n    };\n\n    template <typename Container, typename = std::void_t<typename\
    \ Container::value_type>>\n    std::vector<Run> run_enumerate(Container& s, typename\
    \ Container::value_type sentinel = std::numeric_limits<typename Container::value_type>::min())\
    \ {\n        for (auto& e : s) assert(e != sentinel);\n\n        std::vector<Run>\
    \ glob_result;\n\n        using T = typename Container::value_type;\n        auto\
    \ div_conq = [&](auto div_conq, int l, int r) -> std::vector<Run> {\n        \
    \    if (r - l <= 1) return {};\n\n            const int m = (l + r) >> 1;\n \
    \           std::vector<Run> run_l = div_conq(div_conq, l, m);\n            std::vector<Run>\
    \ run_r = div_conq(div_conq, m, r);\n\n            std::vector<T> rl;\n      \
    \      std::copy(std::begin(s) + m, std::begin(s) + r, std::back_inserter(rl));\n\
    \            rl.push_back(sentinel);\n            std::copy(std::begin(s) + l,\
    \ std::begin(s) + m, std::back_inserter(rl));\n            std::vector<int> z_rl\
    \ = atcoder::z_algorithm(rl);\n\n            std::reverse(std::begin(rl), std::end(rl));\n\
    \            std::vector<int> z_rl_rev = atcoder::z_algorithm(rl);\n\n       \
    \     const int siz = rl.size();\n\n            std::vector<Run> result;\n\n \
    \           auto add_ans = [&](Run&& run) { (run.l == l or run.r == r ? result\
    \ : glob_result).emplace_back(std::move(run)); };\n\n            const int len_l\
    \ = m - l, len_r = r - m;\n            std::vector<Run> run_m(len_r / 2 + 1);\n\
    \            for (auto& run : run_r) {\n                if (run.l != m) {\n  \
    \                  add_ans(std::move(run));\n                    continue;\n \
    \               }\n                run_m[run.period] = std::move(run);\n     \
    \       }\n            for (auto& run : run_l) {\n                if (run.r !=\
    \ m) {\n                    add_ans(std::move(run));\n                    continue;\n\
    \                }\n                const int period = run.period;\n         \
    \       if (z_rl[siz - period] == period) {\n                    if (run_m[period].period)\
    \ {\n                        run.r = run_m[period].r;\n                      \
    \  run_m[period] = Run{};\n                        add_ans(std::move(run));\n\
    \                    } else {\n                        run.r = m + period + z_rl[period];\n\
    \                        add_ans(std::move(run));\n                    }\n   \
    \             } else {\n                    run.r = m + z_rl[siz - period];\n\
    \                    add_ans(std::move(run));\n                }\n           \
    \ }\n            for (auto& run : run_m) if (run.period) {\n                const\
    \ int period = run.period;\n                if (z_rl[siz - period] == period)\
    \ {\n                    if (2 * period <= len_l and z_rl[siz - 2 * period] >=\
    \ period) continue;\n                    run.l = m - period - z_rl_rev[period];\n\
    \                    add_ans(std::move(run));\n                } else {\n    \
    \                run.l = m - z_rl_rev[siz - period];\n                    add_ans(std::move(run));\n\
    \                }\n            }\n\n            for (int period = 1; period <=\
    \ len_l; ++period) {\n                bool skip_r = 2 * period <= len_r and z_rl[period]\
    \ >= period;\n                bool skip_l = 2 * period <= len_l and z_rl[siz -\
    \ 2 * period] >= period;\n                if (z_rl[siz - period] == period) {\n\
    \                    if (skip_l or skip_r) continue;\n\n                    const\
    \ int beg_pos = m - period - z_rl_rev[period];\n                    const int\
    \ end_pos = m + period + z_rl[period];\n                    add_ans(Run{ period,\
    \ beg_pos, end_pos });\n                } else {\n                    if (not\
    \ skip_r) {\n                        const int beg_pos = m - z_rl_rev[siz - period];\n\
    \                        const int end_pos = m + period + z_rl[period];\n    \
    \                    if (end_pos - beg_pos >= 2 * period) {\n                \
    \            add_ans(Run{ period, beg_pos, end_pos });\n                     \
    \   }\n                    }\n                    if (not skip_l) {\n        \
    \                const int beg_pos = m - period - z_rl_rev[period];\n        \
    \                const int end_pos = m + z_rl[siz - period];\n               \
    \         if (end_pos - beg_pos >= 2 * period) {\n                           \
    \ add_ans(Run{ period, beg_pos, end_pos });\n                        }\n     \
    \               }\n                }\n            }\n            return result;\n\
    \        };\n        const int n = s.size();\n        std::vector<std::tuple<int,\
    \ int, int>> runs;\n        for (Run& run : div_conq(div_conq, 0, n)) {\n    \
    \        runs.emplace_back(run.l, run.r, run.period);\n        }\n        for\
    \ (Run& run : glob_result) {\n            runs.emplace_back(run.l, run.r, run.period);\n\
    \        }\n        std::sort(std::begin(runs), std::end(runs));\n        runs.erase(\n\
    \            std::unique(\n                std::begin(runs), std::end(runs),\n\
    \                [](auto& r1, auto& r2) {\n                    return std::get<0>(r1)\
    \ == std::get<0>(r2) and std::get<1>(r1) == std::get<1>(r2);\n               \
    \ }\n            ), std::end(runs)\n                    );\n        std::vector<Run>\
    \ res;\n        for (auto& [l, r, t] : runs) res.emplace_back(t, l, r);\n    \
    \    return res;\n    }\n} // namespace suisen\n\n\n\n#line 6 \"test/src/string/run_enumerate/runenumerate.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    std::string s;\n    std::cin >> s;\n\n    auto runs = suisen::run_enumerate(s);\n\
    \    std::sort(std::begin(runs), std::end(runs));\n\n    std::cout << runs.size()\
    \ << '\\n';\n    for (const auto &run : runs) {\n        std::cout << run.period\
    \ << ' ' << run.l << ' ' << run.r << '\\n';\n    }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/runenumerate\"\n\n#include\
    \ <iostream>\n\n#include \"library/string/run_enumerate.hpp\"\n\nint main() {\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    std::string\
    \ s;\n    std::cin >> s;\n\n    auto runs = suisen::run_enumerate(s);\n    std::sort(std::begin(runs),\
    \ std::end(runs));\n\n    std::cout << runs.size() << '\\n';\n    for (const auto\
    \ &run : runs) {\n        std::cout << run.period << ' ' << run.l << ' ' << run.r\
    \ << '\\n';\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - library/string/run_enumerate.hpp
  isVerificationFile: true
  path: test/src/string/run_enumerate/runenumerate.test.cpp
  requiredBy: []
  timestamp: '2022-10-20 19:30:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/string/run_enumerate/runenumerate.test.cpp
layout: document
redirect_from:
- /verify/test/src/string/run_enumerate/runenumerate.test.cpp
- /verify/test/src/string/run_enumerate/runenumerate.test.cpp.html
title: test/src/string/run_enumerate/runenumerate.test.cpp
---
