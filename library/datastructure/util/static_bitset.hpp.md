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
  bundledCode: "#line 1 \"library/datastructure/util/static_bitset.hpp\"\n\n\n\n#include\
    \ <array>\n#include <cstdint>\n#include <iostream>\n\nnamespace suisen {\n   \
    \ template <std::size_t N>\n    struct static_bitset {\n    private:\n       \
    \ static constexpr std::size_t L = (N + 63) >> 6;\n    public:\n        static_bitset()\
    \ {}\n        static_bitset(std::array<uint64_t, L> data) : _data(data) {}\n\n\
    \        static_bitset<N>& operator&=(const static_bitset<N>& rhs) {\n       \
    \     for (std::size_t i = 0; i < L; ++i) _data[i] &= rhs._data[i];\n        \
    \    return *this;\n        }\n        static_bitset<N>& operator|=(const static_bitset<N>&\
    \ rhs) {\n            for (std::size_t i = 0; i < L; ++i) _data[i] |= rhs._data[i];\n\
    \            return *this;\n        }\n        static_bitset<N>& operator^=(const\
    \ static_bitset<N>& rhs) {\n            for (std::size_t i = 0; i < L; ++i) _data[i]\
    \ ^= rhs._data[i];\n            return *this;\n        }\n        static_bitset<N>\
    \ operator&(const static_bitset<N>& rhs) const {\n            return static_bitset<N>(_data)\
    \ &= rhs;\n        }\n        static_bitset<N> operator|(const static_bitset<N>&\
    \ rhs) const {\n            return static_bitset<N>(_data) |= rhs;\n        }\n\
    \        static_bitset<N> operator^(const static_bitset<N>& rhs) const {\n   \
    \         return static_bitset<N>(_data) ^= rhs;\n        }\n        static_bitset<N>\
    \ operator~() const {\n            static_bitset<N> res;\n            for (std::size_t\
    \ i = 0; i < L; ++i) res._data[i] = ~_data[i];\n            return res;\n    \
    \    }\n        static_bitset<N>& operator<<=(const std::size_t shamt) {\n   \
    \         if (shamt >= N) {\n                _data.fill(0);\n                return\
    \ *this;\n            }\n            std::size_t large_shamt = outer_index(shamt);\n\
    \            std::size_t small_shamt = inner_index(shamt);\n            if (small_shamt)\
    \ {\n                std::size_t rshamt = 64 - small_shamt;\n                for\
    \ (std::size_t i = L - 1; i > large_shamt; --i) {\n                    _data[i]\
    \ = (_data[i - large_shamt] << small_shamt) | (_data[i - large_shamt - 1] >> rshamt);\n\
    \                }\n                _data[large_shamt] = _data[0] << small_shamt;\n\
    \            } else {\n                for (std::size_t i = L; i-- > large_shamt;)\
    \ {\n                    _data[i] = _data[i - large_shamt];\n                }\n\
    \            }\n            for (std::size_t i = large_shamt; i-- > 0;) _data[i]\
    \ = 0;\n            return *this;\n        }\n        static_bitset<N>& operator>>=(const\
    \ std::size_t shamt) {\n            if (shamt >= N) {\n                _data.fill(0);\n\
    \                return *this;\n            }\n            if (shamt == 0) {\n\
    \                return *this;\n            }\n            std::size_t large_shamt\
    \ = outer_index(shamt);\n            std::size_t small_shamt = inner_index(shamt);\n\
    \            if (small_shamt) {\n                std::size_t lshamt = 64 - small_shamt;\n\
    \                for (std::size_t i = 0; i + large_shamt + 1 < L; ++i) {\n   \
    \                 _data[i] = (_data[i + large_shamt] >> small_shamt) | (_data[i\
    \ + large_shamt + 1] << lshamt);\n                }\n                _data[L -\
    \ large_shamt - 1] = _data[L - 1] >> small_shamt;\n            } else {\n    \
    \            for (std::size_t i = 0; i + large_shamt < L; ++i) {\n           \
    \         _data[i] = _data[i + large_shamt];\n                }\n            }\n\
    \            for (std::size_t i = L - large_shamt; i < L; ++i) _data[i] = 0;\n\
    \            return *this;\n        }\n        static_bitset<N> operator<<(const\
    \ std::size_t shamt) const {\n            return static_bitset<N>(_data) <<= shamt;\n\
    \        }\n        static_bitset<N> operator>>(const std::size_t shamt) const\
    \ {\n            return static_bitset<N>(_data) >>= shamt;\n        }\n      \
    \  bool operator!=(const static_bitset<N>& rhs) const {\n            for (std::size_t\
    \ i = L; i-- > 0;) if (_data[i] != rhs._data[i]) return true;\n            return\
    \ false;\n        }\n        bool operator==(const static_bitset<N>& rhs) const\
    \ {\n            return not (*this != rhs);\n        }\n        bool operator<(const\
    \ static_bitset<N>& rhs) const {\n            for (std::size_t i = L; i-- > 0;)\
    \ if (_data[i] != rhs._data[i]) return _data[i] < rhs._data[i];\n            return\
    \ false;\n        }\n        bool operator<=(const static_bitset<N>& rhs) const\
    \ {\n            return not (*this > rhs);\n        }\n        bool operator>(const\
    \ static_bitset<N>& rhs) const {\n            return rhs < *this;\n        }\n\
    \        bool operator>=(const static_bitset<N>& rhs) const {\n            return\
    \ not (*this < rhs);\n        }\n        bool operator[](std::size_t i) {\n  \
    \          return (_data[outer_index(i)] >> inner_index(i)) & 1;\n        }\n\
    \        operator bool() const {\n            for (const auto& e : _data) if (e)\
    \ return true;\n            return false;\n        }\n        void range_set(const\
    \ std::size_t l, const std::size_t r, bool val = true) {\n            if (l >=\
    \ r) return;\n            const std::size_t out_l = outer_index(l), out_r = outer_index(r\
    \ - 1);\n            const std::size_t in_l = inner_index(l), in_r = inner_index(r\
    \ - 1);\n            const uint64_t mask_r = in_r == 63 ? ~0ULL : (1ULL << (in_r\
    \ + 1)) - 1ULL;\n            const uint64_t mask_l = in_l == 0 ? 0ULL : (1ULL\
    \ << in_l) - 1ULL;\n            if (val) {\n                if (out_l < out_r)\
    \ {\n                    _data[out_l] |= ~0ULL ^ mask_l;\n                   \
    \ for (std::size_t i = out_l + 1; i < out_r; ++i) _data[i] = ~0ULL;\n        \
    \            _data[out_r] |= mask_r;\n                } else {\n             \
    \       _data[out_l] |= mask_r ^ mask_l;\n                }\n            } else\
    \ {\n                if (out_l < out_r) {\n                    _data[out_l] &=\
    \ mask_l;\n                    for (std::size_t i = out_l + 1; i < out_r; ++i)\
    \ _data[i] = 0ULL;\n                    _data[out_r] &= ~mask_r;\n           \
    \     } else {\n                    _data[out_l] &= ~(mask_r ^ mask_l);\n    \
    \            }\n            }\n        }\n        void set(const std::size_t n,\
    \ bool val = true) {\n            if (val) {\n                _data[outer_index(n)]\
    \ |= uint64_t(1) << inner_index(n);\n            } else {\n                _data[outer_index(n)]\
    \ &= ~(uint64_t(1) << inner_index(n));\n            }\n        }\n        void\
    \ flip(const std::size_t n) {\n            _data[outer_index(n)] ^= 1ULL << inner_index(n);\n\
    \        }\n        void clear() {\n            _data.fill(0);\n        }\n  \
    \      const std::array<uint64_t, L>& data() const {\n            return _data;\n\
    \        }\n        friend std::ostream& operator<<(std::ostream& out, const static_bitset<N>&\
    \ bs) {\n            for (std::size_t i = N; i-- > 0;) out << char('0' + bs[i]);\n\
    \            return out;\n        }\n    private:\n        std::array<uint64_t,\
    \ L> _data{};\n\n        static constexpr std::size_t outer_index(std::size_t\
    \ k) {\n            return k >> 6;\n        }\n        static constexpr std::size_t\
    \ inner_index(std::size_t k) {\n            return k & 63;\n        }\n    };\n\
    } // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_STATIC_BITSET\n#define SUISEN_STATIC_BITSET\n\n#include <array>\n\
    #include <cstdint>\n#include <iostream>\n\nnamespace suisen {\n    template <std::size_t\
    \ N>\n    struct static_bitset {\n    private:\n        static constexpr std::size_t\
    \ L = (N + 63) >> 6;\n    public:\n        static_bitset() {}\n        static_bitset(std::array<uint64_t,\
    \ L> data) : _data(data) {}\n\n        static_bitset<N>& operator&=(const static_bitset<N>&\
    \ rhs) {\n            for (std::size_t i = 0; i < L; ++i) _data[i] &= rhs._data[i];\n\
    \            return *this;\n        }\n        static_bitset<N>& operator|=(const\
    \ static_bitset<N>& rhs) {\n            for (std::size_t i = 0; i < L; ++i) _data[i]\
    \ |= rhs._data[i];\n            return *this;\n        }\n        static_bitset<N>&\
    \ operator^=(const static_bitset<N>& rhs) {\n            for (std::size_t i =\
    \ 0; i < L; ++i) _data[i] ^= rhs._data[i];\n            return *this;\n      \
    \  }\n        static_bitset<N> operator&(const static_bitset<N>& rhs) const {\n\
    \            return static_bitset<N>(_data) &= rhs;\n        }\n        static_bitset<N>\
    \ operator|(const static_bitset<N>& rhs) const {\n            return static_bitset<N>(_data)\
    \ |= rhs;\n        }\n        static_bitset<N> operator^(const static_bitset<N>&\
    \ rhs) const {\n            return static_bitset<N>(_data) ^= rhs;\n        }\n\
    \        static_bitset<N> operator~() const {\n            static_bitset<N> res;\n\
    \            for (std::size_t i = 0; i < L; ++i) res._data[i] = ~_data[i];\n \
    \           return res;\n        }\n        static_bitset<N>& operator<<=(const\
    \ std::size_t shamt) {\n            if (shamt >= N) {\n                _data.fill(0);\n\
    \                return *this;\n            }\n            std::size_t large_shamt\
    \ = outer_index(shamt);\n            std::size_t small_shamt = inner_index(shamt);\n\
    \            if (small_shamt) {\n                std::size_t rshamt = 64 - small_shamt;\n\
    \                for (std::size_t i = L - 1; i > large_shamt; --i) {\n       \
    \             _data[i] = (_data[i - large_shamt] << small_shamt) | (_data[i -\
    \ large_shamt - 1] >> rshamt);\n                }\n                _data[large_shamt]\
    \ = _data[0] << small_shamt;\n            } else {\n                for (std::size_t\
    \ i = L; i-- > large_shamt;) {\n                    _data[i] = _data[i - large_shamt];\n\
    \                }\n            }\n            for (std::size_t i = large_shamt;\
    \ i-- > 0;) _data[i] = 0;\n            return *this;\n        }\n        static_bitset<N>&\
    \ operator>>=(const std::size_t shamt) {\n            if (shamt >= N) {\n    \
    \            _data.fill(0);\n                return *this;\n            }\n  \
    \          if (shamt == 0) {\n                return *this;\n            }\n \
    \           std::size_t large_shamt = outer_index(shamt);\n            std::size_t\
    \ small_shamt = inner_index(shamt);\n            if (small_shamt) {\n        \
    \        std::size_t lshamt = 64 - small_shamt;\n                for (std::size_t\
    \ i = 0; i + large_shamt + 1 < L; ++i) {\n                    _data[i] = (_data[i\
    \ + large_shamt] >> small_shamt) | (_data[i + large_shamt + 1] << lshamt);\n \
    \               }\n                _data[L - large_shamt - 1] = _data[L - 1] >>\
    \ small_shamt;\n            } else {\n                for (std::size_t i = 0;\
    \ i + large_shamt < L; ++i) {\n                    _data[i] = _data[i + large_shamt];\n\
    \                }\n            }\n            for (std::size_t i = L - large_shamt;\
    \ i < L; ++i) _data[i] = 0;\n            return *this;\n        }\n        static_bitset<N>\
    \ operator<<(const std::size_t shamt) const {\n            return static_bitset<N>(_data)\
    \ <<= shamt;\n        }\n        static_bitset<N> operator>>(const std::size_t\
    \ shamt) const {\n            return static_bitset<N>(_data) >>= shamt;\n    \
    \    }\n        bool operator!=(const static_bitset<N>& rhs) const {\n       \
    \     for (std::size_t i = L; i-- > 0;) if (_data[i] != rhs._data[i]) return true;\n\
    \            return false;\n        }\n        bool operator==(const static_bitset<N>&\
    \ rhs) const {\n            return not (*this != rhs);\n        }\n        bool\
    \ operator<(const static_bitset<N>& rhs) const {\n            for (std::size_t\
    \ i = L; i-- > 0;) if (_data[i] != rhs._data[i]) return _data[i] < rhs._data[i];\n\
    \            return false;\n        }\n        bool operator<=(const static_bitset<N>&\
    \ rhs) const {\n            return not (*this > rhs);\n        }\n        bool\
    \ operator>(const static_bitset<N>& rhs) const {\n            return rhs < *this;\n\
    \        }\n        bool operator>=(const static_bitset<N>& rhs) const {\n   \
    \         return not (*this < rhs);\n        }\n        bool operator[](std::size_t\
    \ i) {\n            return (_data[outer_index(i)] >> inner_index(i)) & 1;\n  \
    \      }\n        operator bool() const {\n            for (const auto& e : _data)\
    \ if (e) return true;\n            return false;\n        }\n        void range_set(const\
    \ std::size_t l, const std::size_t r, bool val = true) {\n            if (l >=\
    \ r) return;\n            const std::size_t out_l = outer_index(l), out_r = outer_index(r\
    \ - 1);\n            const std::size_t in_l = inner_index(l), in_r = inner_index(r\
    \ - 1);\n            const uint64_t mask_r = in_r == 63 ? ~0ULL : (1ULL << (in_r\
    \ + 1)) - 1ULL;\n            const uint64_t mask_l = in_l == 0 ? 0ULL : (1ULL\
    \ << in_l) - 1ULL;\n            if (val) {\n                if (out_l < out_r)\
    \ {\n                    _data[out_l] |= ~0ULL ^ mask_l;\n                   \
    \ for (std::size_t i = out_l + 1; i < out_r; ++i) _data[i] = ~0ULL;\n        \
    \            _data[out_r] |= mask_r;\n                } else {\n             \
    \       _data[out_l] |= mask_r ^ mask_l;\n                }\n            } else\
    \ {\n                if (out_l < out_r) {\n                    _data[out_l] &=\
    \ mask_l;\n                    for (std::size_t i = out_l + 1; i < out_r; ++i)\
    \ _data[i] = 0ULL;\n                    _data[out_r] &= ~mask_r;\n           \
    \     } else {\n                    _data[out_l] &= ~(mask_r ^ mask_l);\n    \
    \            }\n            }\n        }\n        void set(const std::size_t n,\
    \ bool val = true) {\n            if (val) {\n                _data[outer_index(n)]\
    \ |= uint64_t(1) << inner_index(n);\n            } else {\n                _data[outer_index(n)]\
    \ &= ~(uint64_t(1) << inner_index(n));\n            }\n        }\n        void\
    \ flip(const std::size_t n) {\n            _data[outer_index(n)] ^= 1ULL << inner_index(n);\n\
    \        }\n        void clear() {\n            _data.fill(0);\n        }\n  \
    \      const std::array<uint64_t, L>& data() const {\n            return _data;\n\
    \        }\n        friend std::ostream& operator<<(std::ostream& out, const static_bitset<N>&\
    \ bs) {\n            for (std::size_t i = N; i-- > 0;) out << char('0' + bs[i]);\n\
    \            return out;\n        }\n    private:\n        std::array<uint64_t,\
    \ L> _data{};\n\n        static constexpr std::size_t outer_index(std::size_t\
    \ k) {\n            return k >> 6;\n        }\n        static constexpr std::size_t\
    \ inner_index(std::size_t k) {\n            return k & 63;\n        }\n    };\n\
    } // namespace suisen\n\n\n#endif // SUISEN_STATIC_BITSET\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/util/static_bitset.hpp
  requiredBy: []
  timestamp: '2022-04-10 03:32:30+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/util/static_bitset.hpp
layout: document
title: Static Bitset
---
## Static Bitset