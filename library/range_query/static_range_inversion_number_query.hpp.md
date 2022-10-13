---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/range_query/static_range_inversion_number_query/static_range_inversions_query.test.cpp
    title: test/src/range_query/static_range_inversion_number_query/static_range_inversions_query.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Static Range Inversion Number Query
    links: []
  bundledCode: "#line 1 \"library/range_query/static_range_inversion_number_query.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cmath>\n#include <limits>\n#include <vector>\n\
    \n/**\n * @brief Static Range Inversion Number Query\n */\n\nnamespace suisen\
    \ {\n    template <typename T>\n    struct StaticRangeInversionNumberQuery {\n\
    \        StaticRangeInversionNumberQuery(std::vector<T> a) : _block_siz(std::max(1,\
    \ int(::sqrt(a.size())))), _block_num(ceil_div(a.size(),_block_siz)) {\n     \
    \       a.resize(_block_siz * _block_num, std::numeric_limits<T>::max());\n\n\
    \            _sorted.resize(_block_num);\n            for (int block_id = 0; block_id\
    \ < _block_num; ++block_id) {\n                const int offset = block_id * _block_siz;\n\
    \                _sorted[block_id].resize(_block_siz);\n                for (int\
    \ i = 0; i < _block_siz; ++i) _sorted[block_id][i] = { a[offset + i], offset +\
    \ i };\n                std::sort(_sorted[block_id].begin(), _sorted[block_id].end());\n\
    \            }\n\n            _pinv = build_pinv<std::less<T>>(a);\n         \
    \   std::reverse(a.begin(), a.end());\n            _sinv = build_pinv<std::greater<T>>(a);\n\
    \            std::reverse(_sinv.begin(), _sinv.end());\n        }\n\n        /**\n\
    \         * @brief Calcuates the inversion number of the subarray (a_l, ..., a_{r-1}).\n\
    \         * @param l left (closed)\n         * @param r right (open)\n       \
    \  * @return Inversion number of (a_l, ..., a_{r-1})\n         */\n        long\
    \ long operator()(int l, int r) const {\n            const int bl = l / _block_siz,\
    \ br = ceil_div(r, _block_siz);\n            // [bl][bl+1,...,br-2][br-1]\n  \
    \          if (br - bl == 1) {\n                /**\n                 *      \
    \       l   r\n                 *         | A | B | C |\n                 * Blocks:\
    \ |           |\n                 *\n                 * Inv(B)=Inv(AB)+Inv(BC)-Inv(ABC)+Inv(A,C)\n\
    \                 */\n                long long res = _pinv[bl][r - bl * _block_siz]\
    \ + _sinv[bl + 1][(bl + 1) * _block_siz - l] - _pinv[bl][_block_siz];\n      \
    \          for (int k = _block_siz - 1, cnt = 0; k >= 0; --k) {\n            \
    \        cnt += _sorted[bl][k].second < l;\n                    if (_sorted[bl][k].second\
    \ >= r) {\n                        res += cnt;\n                    }\n      \
    \          }\n                return res;\n            } else {\n            \
    \    /**\n                 *           l                         r\n         \
    \        *           | A |        B        | C |\n                 * Blocks: |\
    \     |     |     |     |     |\n                 *\n                 * Inv(ABC)=Inv(AB)+Inv(BC)-Inv(B)+Inv(A,C)\n\
    \                 */\n                const int ml = (bl + 1) * _block_siz, mr\
    \ = (br - 1) * _block_siz;\n                long long res = _pinv[bl + 1][r -\
    \ ml] + _sinv[br - 1][mr - l] - _pinv[bl + 1][mr - ml];\n                for (int\
    \ k = _block_siz - 1, j = _block_siz, cnt = 0; k >= 0; --k) {\n              \
    \      if (_sorted[br - 1][k].second >= r) continue;\n                    while\
    \ (j > 0 and _sorted[bl][j - 1].first > _sorted[br - 1][k].first) {\n        \
    \                cnt += _sorted[bl][--j].second >= l;\n                    }\n\
    \                    res += cnt;\n                }\n                return res;\n\
    \            }\n        }\n\n    private:\n        int _block_siz, _block_num;\n\
    \n        // _pinv[i][j] := inversion number of the subarray (a_{i * _block_siz},\
    \ ..., a_{i * _block_siz + j - 1})\n        // _sinv[i][j] := inversion number\
    \ of the subarray (a_{i * _block_siz - j}, ..., a_{i * _block_siz - 1})\n    \
    \    std::vector<std::vector<long long>> _pinv, _sinv;\n\n        // _sorted[i]\
    \ := sorted array of { (a_{i * _block_siz + j}, i * _block_siz + j) | 0 <= j <\
    \ _block_siz }\n        std::vector<std::vector<std::pair<T, int>>> _sorted;\n\
    \n        template <typename Compare>\n        std::vector<std::vector<long long>>\
    \ build_pinv(const std::vector<T>& a) const {\n            Compare cmp{};\n  \
    \          auto cmp_pair = [&](auto& p, auto& q) { return cmp(p.first, q.first);\
    \ };\n\n            std::vector<std::vector<long long>> pinv(_block_num + 1);\n\
    \n            // invariant: suf is the sorted array of { (a_i, i) | i is in the\
    \ k-th block s.t. k > block_id }\n            std::vector<std::pair<T, int>> suf;\n\
    \            for (int block_id = _block_num - 1; block_id >= 0; --block_id) {\n\
    \                const int offset = block_id * _block_siz;\n                pinv[block_id].resize(_block_siz\
    \ * (_block_num - block_id) + 1);\n                std::vector<std::pair<T, int>>\
    \ pre(_block_siz);\n                for (int i = 0; i < _block_siz; ++i) {\n \
    \                   pre[i] = { a[offset + i], offset + i };\n                \
    \    pinv[block_id][i + 1] = pinv[block_id][i];\n                    for (int\
    \ j = 0; j < i; ++j) pinv[block_id][i + 1] += cmp(a[offset + i], a[offset + j]);\n\
    \                }\n                std::sort(pre.begin(), pre.end(), cmp_pair);\n\
    \n                /**\n                 * | A |  B  |x|\n                 * Inv(ABx)=Inv(AB)+Inv(Bx)-Inv(B)+Inv(A,x)\n\
    \                 */\n\n                 // calculates Inv(A,a_i) for all i >=\
    \ _block_siz * block_id\n                for (int i = _block_siz * (_block_num\
    \ - 1 - block_id) - 1, j = _block_siz; i >= 0; --i) {\n                    while\
    \ (j > 0 and cmp(suf[i].first, pre[j - 1].first)) --j;\n                    pinv[block_id][suf[i].second\
    \ - offset + 1] += _block_siz - j;\n                }\n\n                for (int\
    \ i = _block_siz; i < _block_siz * (_block_num - block_id); ++i) {\n         \
    \           pinv[block_id][i + 1] += pinv[block_id][i] + pinv[block_id + 1][i\
    \ + 1 - _block_siz] - pinv[block_id + 1][i - _block_siz];\n                }\n\
    \n                std::copy(pre.begin(), pre.end(), std::back_inserter(suf));\n\
    \                std::inplace_merge(suf.begin(), suf.end() - _block_siz, suf.end(),\
    \ cmp_pair);\n            }\n            return pinv;\n        }\n\n        static\
    \ constexpr int ceil_div(int num, int den) { return (num + den - 1) / den; }\n\
    \    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_STATIC_RANGE_INVERSION_NUMBER_QUERY\n#define SUISEN_STATIC_RANGE_INVERSION_NUMBER_QUERY\n\
    \n#include <algorithm>\n#include <cmath>\n#include <limits>\n#include <vector>\n\
    \n/**\n * @brief Static Range Inversion Number Query\n */\n\nnamespace suisen\
    \ {\n    template <typename T>\n    struct StaticRangeInversionNumberQuery {\n\
    \        StaticRangeInversionNumberQuery(std::vector<T> a) : _block_siz(std::max(1,\
    \ int(::sqrt(a.size())))), _block_num(ceil_div(a.size(),_block_siz)) {\n     \
    \       a.resize(_block_siz * _block_num, std::numeric_limits<T>::max());\n\n\
    \            _sorted.resize(_block_num);\n            for (int block_id = 0; block_id\
    \ < _block_num; ++block_id) {\n                const int offset = block_id * _block_siz;\n\
    \                _sorted[block_id].resize(_block_siz);\n                for (int\
    \ i = 0; i < _block_siz; ++i) _sorted[block_id][i] = { a[offset + i], offset +\
    \ i };\n                std::sort(_sorted[block_id].begin(), _sorted[block_id].end());\n\
    \            }\n\n            _pinv = build_pinv<std::less<T>>(a);\n         \
    \   std::reverse(a.begin(), a.end());\n            _sinv = build_pinv<std::greater<T>>(a);\n\
    \            std::reverse(_sinv.begin(), _sinv.end());\n        }\n\n        /**\n\
    \         * @brief Calcuates the inversion number of the subarray (a_l, ..., a_{r-1}).\n\
    \         * @param l left (closed)\n         * @param r right (open)\n       \
    \  * @return Inversion number of (a_l, ..., a_{r-1})\n         */\n        long\
    \ long operator()(int l, int r) const {\n            const int bl = l / _block_siz,\
    \ br = ceil_div(r, _block_siz);\n            // [bl][bl+1,...,br-2][br-1]\n  \
    \          if (br - bl == 1) {\n                /**\n                 *      \
    \       l   r\n                 *         | A | B | C |\n                 * Blocks:\
    \ |           |\n                 *\n                 * Inv(B)=Inv(AB)+Inv(BC)-Inv(ABC)+Inv(A,C)\n\
    \                 */\n                long long res = _pinv[bl][r - bl * _block_siz]\
    \ + _sinv[bl + 1][(bl + 1) * _block_siz - l] - _pinv[bl][_block_siz];\n      \
    \          for (int k = _block_siz - 1, cnt = 0; k >= 0; --k) {\n            \
    \        cnt += _sorted[bl][k].second < l;\n                    if (_sorted[bl][k].second\
    \ >= r) {\n                        res += cnt;\n                    }\n      \
    \          }\n                return res;\n            } else {\n            \
    \    /**\n                 *           l                         r\n         \
    \        *           | A |        B        | C |\n                 * Blocks: |\
    \     |     |     |     |     |\n                 *\n                 * Inv(ABC)=Inv(AB)+Inv(BC)-Inv(B)+Inv(A,C)\n\
    \                 */\n                const int ml = (bl + 1) * _block_siz, mr\
    \ = (br - 1) * _block_siz;\n                long long res = _pinv[bl + 1][r -\
    \ ml] + _sinv[br - 1][mr - l] - _pinv[bl + 1][mr - ml];\n                for (int\
    \ k = _block_siz - 1, j = _block_siz, cnt = 0; k >= 0; --k) {\n              \
    \      if (_sorted[br - 1][k].second >= r) continue;\n                    while\
    \ (j > 0 and _sorted[bl][j - 1].first > _sorted[br - 1][k].first) {\n        \
    \                cnt += _sorted[bl][--j].second >= l;\n                    }\n\
    \                    res += cnt;\n                }\n                return res;\n\
    \            }\n        }\n\n    private:\n        int _block_siz, _block_num;\n\
    \n        // _pinv[i][j] := inversion number of the subarray (a_{i * _block_siz},\
    \ ..., a_{i * _block_siz + j - 1})\n        // _sinv[i][j] := inversion number\
    \ of the subarray (a_{i * _block_siz - j}, ..., a_{i * _block_siz - 1})\n    \
    \    std::vector<std::vector<long long>> _pinv, _sinv;\n\n        // _sorted[i]\
    \ := sorted array of { (a_{i * _block_siz + j}, i * _block_siz + j) | 0 <= j <\
    \ _block_siz }\n        std::vector<std::vector<std::pair<T, int>>> _sorted;\n\
    \n        template <typename Compare>\n        std::vector<std::vector<long long>>\
    \ build_pinv(const std::vector<T>& a) const {\n            Compare cmp{};\n  \
    \          auto cmp_pair = [&](auto& p, auto& q) { return cmp(p.first, q.first);\
    \ };\n\n            std::vector<std::vector<long long>> pinv(_block_num + 1);\n\
    \n            // invariant: suf is the sorted array of { (a_i, i) | i is in the\
    \ k-th block s.t. k > block_id }\n            std::vector<std::pair<T, int>> suf;\n\
    \            for (int block_id = _block_num - 1; block_id >= 0; --block_id) {\n\
    \                const int offset = block_id * _block_siz;\n                pinv[block_id].resize(_block_siz\
    \ * (_block_num - block_id) + 1);\n                std::vector<std::pair<T, int>>\
    \ pre(_block_siz);\n                for (int i = 0; i < _block_siz; ++i) {\n \
    \                   pre[i] = { a[offset + i], offset + i };\n                \
    \    pinv[block_id][i + 1] = pinv[block_id][i];\n                    for (int\
    \ j = 0; j < i; ++j) pinv[block_id][i + 1] += cmp(a[offset + i], a[offset + j]);\n\
    \                }\n                std::sort(pre.begin(), pre.end(), cmp_pair);\n\
    \n                /**\n                 * | A |  B  |x|\n                 * Inv(ABx)=Inv(AB)+Inv(Bx)-Inv(B)+Inv(A,x)\n\
    \                 */\n\n                 // calculates Inv(A,a_i) for all i >=\
    \ _block_siz * block_id\n                for (int i = _block_siz * (_block_num\
    \ - 1 - block_id) - 1, j = _block_siz; i >= 0; --i) {\n                    while\
    \ (j > 0 and cmp(suf[i].first, pre[j - 1].first)) --j;\n                    pinv[block_id][suf[i].second\
    \ - offset + 1] += _block_siz - j;\n                }\n\n                for (int\
    \ i = _block_siz; i < _block_siz * (_block_num - block_id); ++i) {\n         \
    \           pinv[block_id][i + 1] += pinv[block_id][i] + pinv[block_id + 1][i\
    \ + 1 - _block_siz] - pinv[block_id + 1][i - _block_siz];\n                }\n\
    \n                std::copy(pre.begin(), pre.end(), std::back_inserter(suf));\n\
    \                std::inplace_merge(suf.begin(), suf.end() - _block_siz, suf.end(),\
    \ cmp_pair);\n            }\n            return pinv;\n        }\n\n        static\
    \ constexpr int ceil_div(int num, int den) { return (num + den - 1) / den; }\n\
    \    };\n} // namespace suisen\n\n\n#endif // SUISEN_STATIC_RANGE_INVERSION_NUMBER_QUERY\n"
  dependsOn: []
  isVerificationFile: false
  path: library/range_query/static_range_inversion_number_query.hpp
  requiredBy: []
  timestamp: '2022-10-13 20:07:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/range_query/static_range_inversion_number_query/static_range_inversions_query.test.cpp
documentation_of: library/range_query/static_range_inversion_number_query.hpp
layout: document
title: Static Range Inversion Number Query
---
## Static Range Inversion Number Query