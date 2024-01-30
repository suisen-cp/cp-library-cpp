---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/range_query/static_range_mode_query.hpp
    title: Static Range Mode Query
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_mode_query
    links:
    - https://judge.yosupo.jp/problem/static_range_mode_query
  bundledCode: "#line 1 \"test/src/range_query/static_range_mode_query/static_range_mode_query.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_mode_query\"\n\
    \n#line 1 \"library/range_query/static_range_mode_query.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <cmath>\n#include <vector>\n\nnamespace\
    \ suisen {\n    template <typename T>\n    struct StaticRangeModeQuery {\n   \
    \     StaticRangeModeQuery() = default;\n        explicit StaticRangeModeQuery(const\
    \ std::vector<T> &a): _len(a.size()), _block_size(::sqrt(_len)), _block_num(_cld(_len,\
    \ _block_size)) {\n            // Computing the mapping from compressed values\
    \ to original values\n            _sorted = a;\n            std::sort(_sorted.begin(),\
    \ _sorted.end());\n            _sorted.erase(std::unique(_sorted.begin(), _sorted.end()),\
    \ _sorted.end());\n            const int k = _sorted.size();\n\n            //\
    \ Bucket sort\n            _a.resize(_len);\n            _start.assign(k + 1,\
    \ 0);\n            for (int i = 0; i < _len; ++i) {\n                // Compress\n\
    \                _a[i] = std::lower_bound(_sorted.begin(), _sorted.end(), a[i])\
    \ - _sorted.begin();\n                ++_start[_a[i]];\n            }\n      \
    \      for (int i = 0; i < k; ++i) _start[i + 1] += _start[i];\n            _pos.resize(_len);\n\
    \            _pos_inv.resize(_len);\n            for (int i = _len - 1; i >= 0;\
    \ --i) {\n                const int pos_index = --_start[_a[i]];\n           \
    \     _pos[pos_index] = i;\n                _pos_inv[i] = pos_index;\n       \
    \     }\n\n            // Precomputing\n            _mode_blocks.assign((_block_num\
    \ + 1) * (_block_num + 1), { 0, 0 });\n            std::vector<int> freq(k);\n\
    \            for (int l_block = 0; l_block <= _block_num; ++l_block) {\n     \
    \           freq.assign(k, 0);\n                std::pair<int, int> mode{ 0, 0\
    \ }; // (max freq, mode)\n                for (int r_block = l_block + 1; r_block\
    \ <= _block_num; ++r_block) {\n                    const int l_index = (r_block\
    \ - 1) * _block_size;\n                    const int r_index = std::min(_len,\
    \ r_block * _block_size);\n                    for (int i = l_index; i < r_index;\
    \ ++i) {\n                        mode = std::max(mode, { ++freq[_a[i]], _a[i]\
    \ });\n                    }\n                    _query_blocks(l_block, r_block)\
    \ = mode;\n                }\n            }\n        }\n\n        std::pair<T,\
    \ int> query(const int l, const int r) const {\n            assert(0 <= l and\
    \ l < r and r <= _len);\n            const int l_block = _cld(l, _block_size);\n\
    \            const int r_block = _fld(r, _block_size);\n            auto [freq,\
    \ mode] = _query_blocks(l_block, r_block);\n            for (int i = l; i < std::min(r,\
    \ l_block * _block_size); ++i) {\n                const int v = _a[i], pos_index\
    \ = _pos_inv[i];\n                if (not _check_right_bound(v, pos_index + freq,\
    \ r)) continue;\n                do ++freq; while (_check_right_bound(v, pos_index\
    \ + freq, r));\n                mode = v;\n            }\n            for (int\
    \ i = r - 1; i >= std::max(l, r_block * _block_size); --i) {\n               \
    \ const int v = _a[i], pos_index = _pos_inv[i];\n                if (not _check_left_bound(v,\
    \ pos_index - freq, l)) continue;\n                do ++freq; while (_check_left_bound(v,\
    \ pos_index - freq, l));\n                mode = v;\n            }\n         \
    \   return { _sorted[mode], freq };\n        }\n        std::pair<T, int> operator()(int\
    \ l, int r) const { return query(l, r); }\n    private:\n        int _len, _block_size,\
    \ _block_num;\n        // Mapping from compressed values to original values\n\
    \        std::vector<T> _sorted;\n        // Array of compressed values\n    \
    \    std::vector<int> _a;\n        // Permutation sorted by (_a[i], i)\n     \
    \   std::vector<int> _pos;\n        // Inverse permutation of _pos\n        std::vector<int>\
    \ _pos_inv;\n        // _start[v] = min{ i | _a[_pos[i]]=v }\n        std::vector<int>\
    \ _start;\n        // Flatten array of _mode_blocks[l][r] := (max freq, mode)\
    \ of _a[l*_block_size,r*_block_size)\n        std::vector<std::pair<int, int>>\
    \ _mode_blocks;\n\n        const auto& _query_blocks(int l_block, int r_block)\
    \ const { return _mode_blocks[l_block * (_block_num + 1) + r_block]; }\n     \
    \   auto& _query_blocks(int l_block, int r_block) { return _mode_blocks[l_block\
    \ * (_block_num + 1) + r_block]; }\n\n        int _check_left_bound(int v, int\
    \ pos_index, int l) const { return _start[v] <= pos_index and l <= _pos[pos_index];\
    \ }\n        int _check_right_bound(int v, int pos_index, int r) const { return\
    \ pos_index < _start[v + 1] and _pos[pos_index] < r; }\n\n        static int _cld(int\
    \ num, int den) { return (num + den - 1) / den; }\n        static int _fld(int\
    \ num, int den) { return num / den; }\n    };\n} // namespace suisen\n\n\n#line\
    \ 4 \"test/src/range_query/static_range_mode_query/static_range_mode_query.test.cpp\"\
    \n\n#include <iostream>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<int>\
    \ a(n);\n    for (auto &e : a) std::cin >> e;\n\n    suisen::StaticRangeModeQuery\
    \ range_mode(a);\n    while (q--) {\n        int l, r;\n        std::cin >> l\
    \ >> r;\n        auto [val, num] = range_mode(l, r);\n        std::cout << val\
    \ << ' ' << num << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_mode_query\"\
    \n\n#include \"library/range_query/static_range_mode_query.hpp\"\n\n#include <iostream>\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<int> a(n);\n    for\
    \ (auto &e : a) std::cin >> e;\n\n    suisen::StaticRangeModeQuery range_mode(a);\n\
    \    while (q--) {\n        int l, r;\n        std::cin >> l >> r;\n        auto\
    \ [val, num] = range_mode(l, r);\n        std::cout << val << ' ' << num << '\\\
    n';\n    }\n}"
  dependsOn:
  - library/range_query/static_range_mode_query.hpp
  isVerificationFile: true
  path: test/src/range_query/static_range_mode_query/static_range_mode_query.test.cpp
  requiredBy: []
  timestamp: '2024-01-30 19:29:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/range_query/static_range_mode_query/static_range_mode_query.test.cpp
layout: document
redirect_from:
- /verify/test/src/range_query/static_range_mode_query/static_range_mode_query.test.cpp
- /verify/test/src/range_query/static_range_mode_query/static_range_mode_query.test.cpp.html
title: test/src/range_query/static_range_mode_query/static_range_mode_query.test.cpp
---