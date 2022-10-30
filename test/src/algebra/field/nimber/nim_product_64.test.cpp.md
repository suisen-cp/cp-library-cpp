---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/algebra/field/nimber.hpp
    title: library/algebra/field/nimber.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/nim_product_64
    links:
    - https://judge.yosupo.jp/problem/nim_product_64
  bundledCode: "#line 1 \"test/src/algebra/field/nimber/nim_product_64.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/nim_product_64\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/algebra/field/nimber.hpp\"\n\n\n\n#include <array>\n\
    #include <cassert>\n#include <cstdint>\n#line 8 \"library/algebra/field/nimber.hpp\"\
    \n\n#ifdef _MSC_VER\n#  include <intrin.h>\n#else\n#  include <x86intrin.h>\n\
    #endif\n\nnamespace suisen {\n    namespace internal::nimber {\n        constexpr\
    \ size_t L = 8;\n        constexpr size_t B = 1 << L;\n\n        constexpr uint8_t\
    \ get_kth_block(uint64_t x, uint8_t k) {\n            using namespace internal::nimber;\n\
    \            return (x >> (L * k)) & 0xffu;\n        }\n\n        // x * y\n \
    \       struct table_x_mul_y_constexpr {\n            std::array<std::array<uint64_t,\
    \ B>, B> tab;\n            constexpr table_x_mul_y_constexpr() : tab() {\n   \
    \             for (uint32_t x = 0; x < B; ++x) for (uint32_t y = 0; y < B; ++y)\
    \ {\n                    tab[x][y] = mul_rec(x, y);\n                }\n     \
    \       }\n            constexpr uint64_t operator()(uint32_t x, uint32_t y) const\
    \ {\n                return tab[x][y];\n            }\n            constexpr uint64_t\
    \ mul_rec(uint64_t x, uint64_t y) const {\n                if (x > y) return mul_rec(y,\
    \ x);\n                if (x == 0) return 0;\n                if (x == 1) return\
    \ y;\n                if (x < B and y < B and tab[x][y]) return tab[x][y];\n \
    \               for (uint8_t shamt = 32;; shamt >>= 1) {\n                   \
    \ uint64_t mask = (uint64_t(1) << shamt) - 1;\n                    uint64_t xu\
    \ = x >> shamt, xl = x & mask;\n                    uint64_t yu = y >> shamt,\
    \ yl = y & mask;\n                    if (xu) {\n                        uint64_t\
    \ zll = mul_rec(xl, yl);\n                        uint64_t zul = mul_rec(xu, yl);\n\
    \                        uint64_t zlu = mul_rec(xl, yu);\n                   \
    \     uint64_t zuu = mul_rec(xu, yu);\n                        return zll ^ ((zlu\
    \ ^ zul ^ zuu) << shamt) ^ mul_rec(zuu, uint64_t(1) << (shamt - 1));\n       \
    \             } else if (yu) {\n                        return (mul_rec(xl, yu)\
    \ << shamt) ^ mul_rec(xl, yl);\n                    }\n                }\n   \
    \         }\n        } table_x_mul_y{};\n\n        // 2^8i * 2^8j * x\n      \
    \  struct table_2_8i_mul_2_8j_mul_x_constexpr {\n            std::array<std::array<std::array<uint64_t,\
    \ B>, L>, L> tab;\n            constexpr table_2_8i_mul_2_8j_mul_x_constexpr()\
    \ : tab() {\n                for (uint32_t i = 0; i < L; ++i) for (uint32_t j\
    \ = 0; j < L; ++j) {\n                    uint64_t mul_2_8i_2_8j = table_x_mul_y.mul_rec(uint64_t(1)\
    \ << (8 * i), uint64_t(1) << (8 * j));\n                    for (uint32_t x =\
    \ 0; x < B; ++x) {\n                        tab[i][j][x] = table_x_mul_y.mul_rec(mul_2_8i_2_8j,\
    \ x);\n                    }\n                }\n            }\n            constexpr\
    \ uint64_t operator()(uint32_t i, uint32_t j, uint32_t x) const {\n          \
    \      return tab[i][j][x];\n            }\n        } table_2_8i_mul_2_8j_mul_x{};\n\
    \n        template <typename std::size_t SIZE = 64>\n        struct nimber {\n\
    \            static_assert(SIZE > 0 and (SIZE & -SIZE) == SIZE); // SIZE must\
    \ be power of 2.\n\n            constexpr nimber(uint64_t x = 0) : _val(x) {}\n\
    \n            constexpr uint64_t val() const { return _val; }\n\n            static\
    \ constexpr nimber zero() { return 0; }\n            static constexpr nimber one()\
    \  { return 1; }\n\n            friend constexpr bool operator==(const nimber&\
    \ x, const nimber& y) { return x._val == y._val; }\n            friend constexpr\
    \ bool operator!=(const nimber& x, const nimber& y) { return x._val != y._val;\
    \ }\n            friend constexpr bool operator< (const nimber& x, const nimber&\
    \ y) { return x._val <  y._val; }\n            friend constexpr bool operator<=(const\
    \ nimber& x, const nimber& y) { return x._val <= y._val; }\n            friend\
    \ constexpr bool operator> (const nimber& x, const nimber& y) { return x._val\
    \ >  y._val; }\n            friend constexpr bool operator>=(const nimber& x,\
    \ const nimber& y) { return x._val >= y._val; }\n\n            friend constexpr\
    \ nimber operator+(const nimber& x) { return x; }\n            friend constexpr\
    \ nimber operator-(const nimber& x) { return x; }\n\n            friend constexpr\
    \ nimber operator+(const nimber& x, const nimber& y) { return x._val ^ y._val;\
    \ }\n            friend constexpr nimber operator-(const nimber& x, const nimber&\
    \ y) { return x._val ^ y._val; }\n            friend constexpr nimber operator*(const\
    \ nimber& x, const nimber& y) {\n                uint64_t res = 0;\n         \
    \       for (uint8_t i = 0; i < block_num; ++i) {\n                    uint64_t\
    \ xi = get_kth_block(x._val, i);\n                    for (uint8_t j = 0; j <\
    \ block_num; ++j) {\n                        uint64_t yj = get_kth_block(y._val,\
    \ j);\n                        res ^= table_2_8i_mul_2_8j_mul_x(i, j, table_x_mul_y(xi,\
    \ yj));\n                    }\n                }\n                return res;\n\
    \            }\n            friend constexpr nimber operator/(const nimber& x,\
    \ const nimber& y) { return x * y.inv(); }\n            \n            friend constexpr\
    \ nimber& operator+=(nimber& x, const nimber& y) { return x = x + y; }\n     \
    \       friend constexpr nimber& operator-=(nimber& x, const nimber& y) { return\
    \ x = x - y; }\n            friend constexpr nimber& operator*=(nimber& x, const\
    \ nimber& y) { return x = x * y; }\n            friend constexpr nimber& operator/=(nimber&\
    \ x, const nimber& y) { return x = x / y; }\n\n            nimber inv() const\
    \ {\n                uint32_t q = 0;\n                while (__uint128_t(1) <<\
    \ (1 << q) <= _val) ++q;\n                return pow((__uint128_t(1) << (1 <<\
    \ q)) - 2);\n            }\n            nimber pow(uint64_t b) const {\n     \
    \           nimber res = 1, pow_a = *this;\n                for (; b; b >>= 1)\
    \ {\n                    if (b & 1) res *= pow_a;\n                    pow_a *=\
    \ pow_a;\n                }\n                return res;\n            }\n\n  \
    \          constexpr operator bool() { return _val != 0; }\n            constexpr\
    \ operator uint64_t() { return _val; }\n\n            friend std::ostream& operator<<(std::ostream&\
    \ ous, const nimber& x) { return ous << x._val; }\n            friend std::istream&\
    \ operator>>(std::istream& ins, nimber& x) { return ins >> x._val; }\n       \
    \ private:\n            uint64_t _val;\n\n            static constexpr std::size_t\
    \ block_num = (SIZE + L - 1) / L;\n        };\n    }\n    using nimber64_t = internal::nimber::nimber<64>;\n\
    \    using nimber32_t = internal::nimber::nimber<32>;\n    using nimber16_t =\
    \ internal::nimber::nimber<16>;\n    using nimber8_t = internal::nimber::nimber<8>;\n\
    \    using nimber4_t = internal::nimber::nimber<4>;\n    using nimber2_t = internal::nimber::nimber<2>;\n\
    \    using nimber1_t = internal::nimber::nimber<1>;\n    using nimber = nimber64_t;\n\
    } // namespace suisen\n\nnamespace std {\n    template <size_t SIZE>\n    struct\
    \ hash<suisen::internal::nimber::nimber<SIZE>> {\n        size_t operator()(const\
    \ suisen::internal::nimber::nimber<SIZE>& x) const { return hash<uint64_t>()(x.val());\
    \ }\n    };\n} // namespace std\n\n\n#line 6 \"test/src/algebra/field/nimber/nim_product_64.test.cpp\"\
    \n\nint main() {\n    using suisen::nimber64_t;\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int t;\n    std::cin >> t;\n    while (t -->\
    \ 0) {\n        nimber64_t x, y;\n        std::cin >> x >> y;\n        std::cout\
    \ << nimber64_t(x) * y << '\\n';\n    }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/nim_product_64\"\n\n#include\
    \ <iostream>\n\n#include \"library/algebra/field/nimber.hpp\"\n\nint main() {\n\
    \    using suisen::nimber64_t;\n\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int t;\n    std::cin >> t;\n    while (t --> 0) {\n        nimber64_t x,\
    \ y;\n        std::cin >> x >> y;\n        std::cout << nimber64_t(x) * y << '\\\
    n';\n    }\n\n    return 0;\n}"
  dependsOn:
  - library/algebra/field/nimber.hpp
  isVerificationFile: true
  path: test/src/algebra/field/nimber/nim_product_64.test.cpp
  requiredBy: []
  timestamp: '2022-10-23 23:56:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/algebra/field/nimber/nim_product_64.test.cpp
layout: document
redirect_from:
- /verify/test/src/algebra/field/nimber/nim_product_64.test.cpp
- /verify/test/src/algebra/field/nimber/nim_product_64.test.cpp.html
title: test/src/algebra/field/nimber/nim_product_64.test.cpp
---
