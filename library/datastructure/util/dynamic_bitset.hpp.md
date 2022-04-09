---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/util/dynamic_bitset.hpp\"\n\n\n\n\
    #include <iostream>\n#include <limits>\n#include <vector>\n\nnamespace suisen\
    \ {\nclass dynamic_bitset {\n    public:\n        explicit dynamic_bitset() {}\n\
    \        explicit dynamic_bitset(const unsigned int n) {\n            _bits.assign(outer_index(n)\
    \ + 1, 0ULL);\n        }\n        inline int size() const {\n            return\
    \ _bits.size() * BLOCK_SIZE;\n        }\n        dynamic_bitset& operator|=(const\
    \ dynamic_bitset& other) {\n            ensure_size(other.size());\n         \
    \   int siz = other._bits.size();\n            for (int i = 0; i < siz; ++i) {\n\
    \                _bits[i] |= other._bits[i];\n            }\n            cut_leading_zeros();\n\
    \            return *this;\n        }\n        dynamic_bitset& operator&=(const\
    \ dynamic_bitset& other) {\n            ensure_size(other.size());\n         \
    \   int siz = other._bits.size();\n            for (int i = 0; i < siz; ++i) {\n\
    \                _bits[i] &= other._bits[i];\n            }\n            _bits.erase(_bits.begin()\
    \ + siz, _bits.end());\n            cut_leading_zeros();\n            return *this;\n\
    \        }\n        dynamic_bitset& operator^=(const dynamic_bitset& other) {\n\
    \            ensure_size(other.size());\n            int siz = other._bits.size();\n\
    \            for (int i = 0; i < siz; ++i) {\n                _bits[i] ^= other._bits[i];\n\
    \            }\n            cut_leading_zeros();\n            return *this;\n\
    \        }\n        dynamic_bitset& operator<<=(const unsigned int shamt) {\n\
    \            if (size() == 0) return *this;\n            int ishamt = outer_index(shamt);\n\
    \            int lshamt = inner_index(shamt);\n            if (lshamt) {\n   \
    \             ensure_size(size() + shamt);\n                int rshamt = BLOCK_SIZE\
    \ - lshamt;\n                int siz = _bits.size();\n                for (int\
    \ i = siz - 1; i > ishamt; --i) {\n                    _bits[i] = (_bits[i - ishamt]\
    \ << lshamt) | (_bits[i - ishamt - 1] >> rshamt);\n                }\n       \
    \         _bits[ishamt] = _bits[0] << lshamt;\n                std::fill(_bits.begin(),\
    \ _bits.begin() + ishamt, 0ULL);\n            } else {\n                _bits.insert(_bits.begin(),\
    \ ishamt, 0ULL);\n            }\n            cut_leading_zeros();\n          \
    \  return *this;\n        }\n        dynamic_bitset& operator>>=(const unsigned\
    \ int shamt) {\n            int ishamt = outer_index(shamt);\n            if (ishamt\
    \ >= _bits.size()) {\n                _bits.clear();\n                return *this;\n\
    \            }\n            int rshamt = inner_index(shamt);\n            if (rshamt)\
    \ {\n                int lshamt = BLOCK_SIZE - rshamt;\n                int sz\
    \ = _bits.size();\n                for (int i = 0; i + ishamt + 1 < sz; ++i) {\n\
    \                    _bits[i] = (_bits[i + ishamt] >> rshamt) | (_bits[i + ishamt\
    \ + 1] << lshamt);\n                }\n                _bits[sz - ishamt - 1]\
    \ = _bits[sz - 1] >> rshamt;\n                _bits.erase(_bits.end() - ishamt,\
    \ _bits.end());\n            } else {\n                _bits.erase(_bits.begin(),\
    \ _bits.begin() + ishamt);\n            }\n            cut_leading_zeros();\n\
    \            return *this;\n        }\n        dynamic_bitset operator|(const\
    \ dynamic_bitset& other) {\n            return dynamic_bitset(_bits) |= other;\n\
    \        }\n        dynamic_bitset operator&(const dynamic_bitset& other) {\n\
    \            return dynamic_bitset(_bits) &= other;\n        }\n        dynamic_bitset\
    \ operator^(const dynamic_bitset& other) {\n            return dynamic_bitset(_bits)\
    \ ^= other;\n        }\n        dynamic_bitset operator<<(const unsigned int shamt)\
    \ {\n            return dynamic_bitset(_bits) <<= shamt;\n        }\n        dynamic_bitset\
    \ operator>>(const unsigned int shamt) {\n            return dynamic_bitset(_bits)\
    \ >>= shamt;\n        }\n        bool operator[](const unsigned int n) const {\n\
    \            if (n >= size()) return false;\n            return (_bits[outer_index(n)]\
    \ >> inner_index(n)) & 1;\n        }\n        void set(const unsigned int n, bool\
    \ val = true) {\n            if (not val and n >= size()) return;\n          \
    \  if (val) {\n                ensure_size(n + 1);\n                _bits[outer_index(n)]\
    \ |= 1ULL << inner_index(n);\n            } else {\n                _bits[outer_index(n)]\
    \ &= ~(1ULL << inner_index(n));\n            }\n        }\n        void range_set(const\
    \ unsigned int l, const unsigned int r, bool val = true) {\n            if (not\
    \ val and l >= size()) return;\n            const int out_l = outer_index(l),\
    \ out_r = outer_index(r - 1);\n            const int in_l = inner_index(l), in_r\
    \ = inner_index(r - 1);\n            const unsigned long long mask_r = in_r ==\
    \ 63 ? ~0ULL : (1ULL << (in_r + 1)) - 1ULL;\n            const unsigned long long\
    \ mask_l = in_l == 0  ?  0ULL : (1ULL << in_l) - 1ULL;\n            if (val) {\n\
    \                ensure_size(r + 1);\n                if (out_l < out_r) {\n \
    \                   _bits[out_l] |= ~0ULL ^ mask_l;\n                    for (int\
    \ i = out_l + 1; i <= out_r - 1; ++i) {\n                        _bits[i] = ~0ULL;\n\
    \                    }\n                    _bits[out_r] |= mask_r;\n        \
    \        } else {\n                    _bits[out_l] |= mask_r ^ mask_l;\n    \
    \            }\n            } else {\n                if (out_l < out_r) {\n \
    \                   _bits[out_l] &= mask_l;\n                    for (int i =\
    \ out_l + 1; i <= out_r - 1; ++i) {\n                        _bits[i] = 0ULL;\n\
    \                    }\n                    _bits[out_r] &= ~mask_r;\n       \
    \         } else {\n                    _bits[out_l] &= ~(mask_r ^ mask_l);\n\
    \                }\n                cut_leading_zeros();\n            }\n    \
    \    }\n        void clear() {\n            _bits.clear();\n        }\n      \
    \  void flip(const unsigned int n) {\n            ensure_size(n + 1);\n      \
    \      _bits[outer_index(n)] ^= 1ULL << inner_index(n);\n        }\n        friend\
    \ std::ostream& operator<<(std::ostream &out, const dynamic_bitset &bs) {\n  \
    \          std::string res;\n            for (auto it = bs._bits.rbegin(); it\
    \ != bs._bits.rend(); ++it) {\n                unsigned long long bits = *it;\n\
    \                for (int j = BLOCK_SIZE - 1; j >= 0; --j) {\n               \
    \     res += char('0' + ((bits >> j) & 1));\n                }\n            }\n\
    \            out << res;\n            return out;\n        }\n        const std::vector<unsigned\
    \ long long>& data() const {\n            return _bits;\n        }\n    private:\n\
    \        static constexpr unsigned int BLOCK_SIZE = std::numeric_limits<unsigned\
    \ long long>::digits;\n        static constexpr unsigned int LOG_BLOCK_SIZE =\
    \ __builtin_ctz(BLOCK_SIZE);\n    \n        std::vector<unsigned long long> _bits;\n\
    \n        dynamic_bitset(const std::vector<unsigned long long> &bits) : _bits(bits)\
    \ {}\n\n        static constexpr unsigned int outer_index(unsigned int k) {\n\
    \            return k >> LOG_BLOCK_SIZE;\n        }\n        static constexpr\
    \ unsigned int inner_index(unsigned int k) {\n            return k & (BLOCK_SIZE\
    \ - 1);\n        }\n        void ensure_size(const unsigned int n) {\n       \
    \     int old_size = _bits.size();\n            int new_size = outer_index(n ==\
    \ 0 ? n : n - 1) + 1;\n            if (new_size > old_size) {\n              \
    \  _bits.resize(new_size, 0ULL);\n            }\n        }\n        void cut_leading_zeros()\
    \ {\n            while (_bits.size() and _bits.back() == 0ULL) _bits.pop_back();\n\
    \        }\n};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_DYN_BITSET\n#define SUISEN_DYN_BITSET\n\n#include <iostream>\n\
    #include <limits>\n#include <vector>\n\nnamespace suisen {\nclass dynamic_bitset\
    \ {\n    public:\n        explicit dynamic_bitset() {}\n        explicit dynamic_bitset(const\
    \ unsigned int n) {\n            _bits.assign(outer_index(n) + 1, 0ULL);\n   \
    \     }\n        inline int size() const {\n            return _bits.size() *\
    \ BLOCK_SIZE;\n        }\n        dynamic_bitset& operator|=(const dynamic_bitset&\
    \ other) {\n            ensure_size(other.size());\n            int siz = other._bits.size();\n\
    \            for (int i = 0; i < siz; ++i) {\n                _bits[i] |= other._bits[i];\n\
    \            }\n            cut_leading_zeros();\n            return *this;\n\
    \        }\n        dynamic_bitset& operator&=(const dynamic_bitset& other) {\n\
    \            ensure_size(other.size());\n            int siz = other._bits.size();\n\
    \            for (int i = 0; i < siz; ++i) {\n                _bits[i] &= other._bits[i];\n\
    \            }\n            _bits.erase(_bits.begin() + siz, _bits.end());\n \
    \           cut_leading_zeros();\n            return *this;\n        }\n     \
    \   dynamic_bitset& operator^=(const dynamic_bitset& other) {\n            ensure_size(other.size());\n\
    \            int siz = other._bits.size();\n            for (int i = 0; i < siz;\
    \ ++i) {\n                _bits[i] ^= other._bits[i];\n            }\n       \
    \     cut_leading_zeros();\n            return *this;\n        }\n        dynamic_bitset&\
    \ operator<<=(const unsigned int shamt) {\n            if (size() == 0) return\
    \ *this;\n            int ishamt = outer_index(shamt);\n            int lshamt\
    \ = inner_index(shamt);\n            if (lshamt) {\n                ensure_size(size()\
    \ + shamt);\n                int rshamt = BLOCK_SIZE - lshamt;\n             \
    \   int siz = _bits.size();\n                for (int i = siz - 1; i > ishamt;\
    \ --i) {\n                    _bits[i] = (_bits[i - ishamt] << lshamt) | (_bits[i\
    \ - ishamt - 1] >> rshamt);\n                }\n                _bits[ishamt]\
    \ = _bits[0] << lshamt;\n                std::fill(_bits.begin(), _bits.begin()\
    \ + ishamt, 0ULL);\n            } else {\n                _bits.insert(_bits.begin(),\
    \ ishamt, 0ULL);\n            }\n            cut_leading_zeros();\n          \
    \  return *this;\n        }\n        dynamic_bitset& operator>>=(const unsigned\
    \ int shamt) {\n            int ishamt = outer_index(shamt);\n            if (ishamt\
    \ >= _bits.size()) {\n                _bits.clear();\n                return *this;\n\
    \            }\n            int rshamt = inner_index(shamt);\n            if (rshamt)\
    \ {\n                int lshamt = BLOCK_SIZE - rshamt;\n                int sz\
    \ = _bits.size();\n                for (int i = 0; i + ishamt + 1 < sz; ++i) {\n\
    \                    _bits[i] = (_bits[i + ishamt] >> rshamt) | (_bits[i + ishamt\
    \ + 1] << lshamt);\n                }\n                _bits[sz - ishamt - 1]\
    \ = _bits[sz - 1] >> rshamt;\n                _bits.erase(_bits.end() - ishamt,\
    \ _bits.end());\n            } else {\n                _bits.erase(_bits.begin(),\
    \ _bits.begin() + ishamt);\n            }\n            cut_leading_zeros();\n\
    \            return *this;\n        }\n        dynamic_bitset operator|(const\
    \ dynamic_bitset& other) {\n            return dynamic_bitset(_bits) |= other;\n\
    \        }\n        dynamic_bitset operator&(const dynamic_bitset& other) {\n\
    \            return dynamic_bitset(_bits) &= other;\n        }\n        dynamic_bitset\
    \ operator^(const dynamic_bitset& other) {\n            return dynamic_bitset(_bits)\
    \ ^= other;\n        }\n        dynamic_bitset operator<<(const unsigned int shamt)\
    \ {\n            return dynamic_bitset(_bits) <<= shamt;\n        }\n        dynamic_bitset\
    \ operator>>(const unsigned int shamt) {\n            return dynamic_bitset(_bits)\
    \ >>= shamt;\n        }\n        bool operator[](const unsigned int n) const {\n\
    \            if (n >= size()) return false;\n            return (_bits[outer_index(n)]\
    \ >> inner_index(n)) & 1;\n        }\n        void set(const unsigned int n, bool\
    \ val = true) {\n            if (not val and n >= size()) return;\n          \
    \  if (val) {\n                ensure_size(n + 1);\n                _bits[outer_index(n)]\
    \ |= 1ULL << inner_index(n);\n            } else {\n                _bits[outer_index(n)]\
    \ &= ~(1ULL << inner_index(n));\n            }\n        }\n        void range_set(const\
    \ unsigned int l, const unsigned int r, bool val = true) {\n            if (not\
    \ val and l >= size()) return;\n            const int out_l = outer_index(l),\
    \ out_r = outer_index(r - 1);\n            const int in_l = inner_index(l), in_r\
    \ = inner_index(r - 1);\n            const unsigned long long mask_r = in_r ==\
    \ 63 ? ~0ULL : (1ULL << (in_r + 1)) - 1ULL;\n            const unsigned long long\
    \ mask_l = in_l == 0  ?  0ULL : (1ULL << in_l) - 1ULL;\n            if (val) {\n\
    \                ensure_size(r + 1);\n                if (out_l < out_r) {\n \
    \                   _bits[out_l] |= ~0ULL ^ mask_l;\n                    for (int\
    \ i = out_l + 1; i <= out_r - 1; ++i) {\n                        _bits[i] = ~0ULL;\n\
    \                    }\n                    _bits[out_r] |= mask_r;\n        \
    \        } else {\n                    _bits[out_l] |= mask_r ^ mask_l;\n    \
    \            }\n            } else {\n                if (out_l < out_r) {\n \
    \                   _bits[out_l] &= mask_l;\n                    for (int i =\
    \ out_l + 1; i <= out_r - 1; ++i) {\n                        _bits[i] = 0ULL;\n\
    \                    }\n                    _bits[out_r] &= ~mask_r;\n       \
    \         } else {\n                    _bits[out_l] &= ~(mask_r ^ mask_l);\n\
    \                }\n                cut_leading_zeros();\n            }\n    \
    \    }\n        void clear() {\n            _bits.clear();\n        }\n      \
    \  void flip(const unsigned int n) {\n            ensure_size(n + 1);\n      \
    \      _bits[outer_index(n)] ^= 1ULL << inner_index(n);\n        }\n        friend\
    \ std::ostream& operator<<(std::ostream &out, const dynamic_bitset &bs) {\n  \
    \          std::string res;\n            for (auto it = bs._bits.rbegin(); it\
    \ != bs._bits.rend(); ++it) {\n                unsigned long long bits = *it;\n\
    \                for (int j = BLOCK_SIZE - 1; j >= 0; --j) {\n               \
    \     res += char('0' + ((bits >> j) & 1));\n                }\n            }\n\
    \            out << res;\n            return out;\n        }\n        const std::vector<unsigned\
    \ long long>& data() const {\n            return _bits;\n        }\n    private:\n\
    \        static constexpr unsigned int BLOCK_SIZE = std::numeric_limits<unsigned\
    \ long long>::digits;\n        static constexpr unsigned int LOG_BLOCK_SIZE =\
    \ __builtin_ctz(BLOCK_SIZE);\n    \n        std::vector<unsigned long long> _bits;\n\
    \n        dynamic_bitset(const std::vector<unsigned long long> &bits) : _bits(bits)\
    \ {}\n\n        static constexpr unsigned int outer_index(unsigned int k) {\n\
    \            return k >> LOG_BLOCK_SIZE;\n        }\n        static constexpr\
    \ unsigned int inner_index(unsigned int k) {\n            return k & (BLOCK_SIZE\
    \ - 1);\n        }\n        void ensure_size(const unsigned int n) {\n       \
    \     int old_size = _bits.size();\n            int new_size = outer_index(n ==\
    \ 0 ? n : n - 1) + 1;\n            if (new_size > old_size) {\n              \
    \  _bits.resize(new_size, 0ULL);\n            }\n        }\n        void cut_leading_zeros()\
    \ {\n            while (_bits.size() and _bits.back() == 0ULL) _bits.pop_back();\n\
    \        }\n};\n} // namespace suisen\n\n#endif // SUISEN_DYN_BITSET"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/util/dynamic_bitset.hpp
  requiredBy: []
  timestamp: '2022-04-10 03:32:30+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/util/dynamic_bitset.hpp
layout: document
redirect_from:
- /library/library/datastructure/util/dynamic_bitset.hpp
- /library/library/datastructure/util/dynamic_bitset.hpp.html
title: library/datastructure/util/dynamic_bitset.hpp
---
