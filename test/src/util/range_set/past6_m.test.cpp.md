---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links:
    - https://atcoder.jp/contests/past202104-open/tasks/past202104_m
  bundledCode: "#line 1 \"test/src/util/range_set/past6_m.test.cpp\"\n// cannot find\
    \ testcases in drop box...\n\n// #define PROBLEM \"https://atcoder.jp/contests/past202104-open/tasks/past202104_m\"\
    \n\n// #include <iostream>\n// #include <tuple>\n// #include <vector>\n\n// #include\
    \ \"library/util/coordinate_compressor.hpp\"\n// #include \"library/util/range_set.hpp\"\
    \n// using suisen::CoordinateCompressorBuilder;\n// using suisen::RangeSet;\n\n\
    // int main() {\n//     std::ios::sync_with_stdio(false);\n//     std::cin.tie(nullptr);\n\
    \n//     int n;\n//     std::cin >> n;\n\n//     CoordinateCompressorBuilder<int>\
    \ builder;\n\n//     std::vector<int> init(n);\n//     for (int &e : init) {\n\
    //         std::cin >> e;\n//         builder.push(e);\n//     }\n\n//     int\
    \ q;\n//     std::cin >> q;\n//     std::vector<std::tuple<int, int, int>> queries(q);\n\
    //     for (auto &[l, r, x] : queries) {\n//         std::cin >> l >> r >> x;\n\
    //         --l;\n//         builder.push(x);\n//     }\n\n//     auto compressor\
    \ = builder.build();\n//     for (int &e : init) {\n//         e = compressor[e];\n\
    //     }\n//     for (auto &query : queries) {\n//         std::get<2>(query)\
    \ = compressor[std::get<2>(query)];\n//     }\n\n//     int m = compressor.size();\n\
    //     std::vector<RangeSet<int>> sets(m);\n\n//     int log = 0;\n//     while\
    \ (1 << log < m) ++log;\n//     std::vector<RangeSet<int>> bits(log);\n\n//  \
    \   for (int i = 0; i < n; ++i) {\n//         int v = init[i];\n//         for\
    \ (int bit = 0; bit < log; ++bit) {\n//             if ((v >> bit) & 1) bits[bit].insert(i);\n\
    //         }\n//         sets[v].insert(i);\n//     }\n\n//     auto get = [&](int\
    \ i) {\n//         int res = 0;\n//         for (int bit = 0; bit < log; ++bit)\
    \ {\n//             res |= bits[bit].contains(i) << bit;\n//         }\n//   \
    \      return res;\n//     };\n\n//     auto update = [&](int l, int r, int x)\
    \ {\n//         for (int bit = 0; bit < log; ++bit) {\n//             if ((x >>\
    \ bit) & 1) {\n//                 bits[bit].insert(l, r - 1);\n//            \
    \ } else {\n//                 bits[bit].erase(l, r - 1);\n//             }\n\
    //         }\n//     };\n\n//     long long ans = 0;\n//     for (const auto &set\
    \ : sets) {\n//         long long sz = set.size();\n//         ans += sz * (sz\
    \ - 1) / 2;\n//     }\n    \n//     for (int i = 0; i < q; ++i) {\n//        \
    \ auto [l, r, x] = queries[i];\n\n//         std::vector<int> rem;\n//       \
    \  for (int cur = l; cur < r;) {\n//             const int v = get(cur);\n// \
    \            rem.push_back(v);\n//             cur = std::min(r, sets[v].minimum_excluded(cur));\n\
    //         }\n\n//         for (int v : rem) {\n//             auto &set = sets[v];\n\
    //             long long sz = set.size();\n//             ans -= sz * (sz - 1)\
    \ / 2;\n//             sz -= set.erase(l, r - 1);\n//             ans += sz *\
    \ (sz - 1) / 2;\n//         }\n\n//         auto &set = sets[x];\n//         long\
    \ long sz = set.size();\n//         ans -= sz * (sz - 1) / 2;\n//         sz +=\
    \ set.insert(l, r - 1);\n//         ans += sz * (sz - 1) / 2;\n\n//         update(l,\
    \ r, x);\n\n//         std::cout << ans << '\\n';\n//     }\n//     return 0;\n\
    // }\n"
  code: "// cannot find testcases in drop box...\n\n// #define PROBLEM \"https://atcoder.jp/contests/past202104-open/tasks/past202104_m\"\
    \n\n// #include <iostream>\n// #include <tuple>\n// #include <vector>\n\n// #include\
    \ \"library/util/coordinate_compressor.hpp\"\n// #include \"library/util/range_set.hpp\"\
    \n// using suisen::CoordinateCompressorBuilder;\n// using suisen::RangeSet;\n\n\
    // int main() {\n//     std::ios::sync_with_stdio(false);\n//     std::cin.tie(nullptr);\n\
    \n//     int n;\n//     std::cin >> n;\n\n//     CoordinateCompressorBuilder<int>\
    \ builder;\n\n//     std::vector<int> init(n);\n//     for (int &e : init) {\n\
    //         std::cin >> e;\n//         builder.push(e);\n//     }\n\n//     int\
    \ q;\n//     std::cin >> q;\n//     std::vector<std::tuple<int, int, int>> queries(q);\n\
    //     for (auto &[l, r, x] : queries) {\n//         std::cin >> l >> r >> x;\n\
    //         --l;\n//         builder.push(x);\n//     }\n\n//     auto compressor\
    \ = builder.build();\n//     for (int &e : init) {\n//         e = compressor[e];\n\
    //     }\n//     for (auto &query : queries) {\n//         std::get<2>(query)\
    \ = compressor[std::get<2>(query)];\n//     }\n\n//     int m = compressor.size();\n\
    //     std::vector<RangeSet<int>> sets(m);\n\n//     int log = 0;\n//     while\
    \ (1 << log < m) ++log;\n//     std::vector<RangeSet<int>> bits(log);\n\n//  \
    \   for (int i = 0; i < n; ++i) {\n//         int v = init[i];\n//         for\
    \ (int bit = 0; bit < log; ++bit) {\n//             if ((v >> bit) & 1) bits[bit].insert(i);\n\
    //         }\n//         sets[v].insert(i);\n//     }\n\n//     auto get = [&](int\
    \ i) {\n//         int res = 0;\n//         for (int bit = 0; bit < log; ++bit)\
    \ {\n//             res |= bits[bit].contains(i) << bit;\n//         }\n//   \
    \      return res;\n//     };\n\n//     auto update = [&](int l, int r, int x)\
    \ {\n//         for (int bit = 0; bit < log; ++bit) {\n//             if ((x >>\
    \ bit) & 1) {\n//                 bits[bit].insert(l, r - 1);\n//            \
    \ } else {\n//                 bits[bit].erase(l, r - 1);\n//             }\n\
    //         }\n//     };\n\n//     long long ans = 0;\n//     for (const auto &set\
    \ : sets) {\n//         long long sz = set.size();\n//         ans += sz * (sz\
    \ - 1) / 2;\n//     }\n    \n//     for (int i = 0; i < q; ++i) {\n//        \
    \ auto [l, r, x] = queries[i];\n\n//         std::vector<int> rem;\n//       \
    \  for (int cur = l; cur < r;) {\n//             const int v = get(cur);\n// \
    \            rem.push_back(v);\n//             cur = std::min(r, sets[v].minimum_excluded(cur));\n\
    //         }\n\n//         for (int v : rem) {\n//             auto &set = sets[v];\n\
    //             long long sz = set.size();\n//             ans -= sz * (sz - 1)\
    \ / 2;\n//             sz -= set.erase(l, r - 1);\n//             ans += sz *\
    \ (sz - 1) / 2;\n//         }\n\n//         auto &set = sets[x];\n//         long\
    \ long sz = set.size();\n//         ans -= sz * (sz - 1) / 2;\n//         sz +=\
    \ set.insert(l, r - 1);\n//         ans += sz * (sz - 1) / 2;\n\n//         update(l,\
    \ r, x);\n\n//         std::cout << ans << '\\n';\n//     }\n//     return 0;\n\
    // }"
  dependsOn: []
  isVerificationFile: true
  path: test/src/util/range_set/past6_m.test.cpp
  requiredBy: []
  timestamp: '2021-09-21 22:25:06+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/util/range_set/past6_m.test.cpp
layout: document
redirect_from:
- /verify/test/src/util/range_set/past6_m.test.cpp
- /verify/test/src/util/range_set/past6_m.test.cpp.html
title: test/src/util/range_set/past6_m.test.cpp
---
