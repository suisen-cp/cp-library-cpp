---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/red_black_segment_tree.hpp
    title: "\u533A\u9593\u548C\u53D6\u5F97\u304C\u53EF\u80FD\u306A\u8D64\u9ED2\u6728"
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/red_black_tree_base.hpp
    title: Red Black Tree Base
  - icon: ':heavy_check_mark:'
    path: library/number/internal_eratosthenes.hpp
    title: Internal Eratosthenes
  - icon: ':heavy_check_mark:'
    path: library/number/modint_2^61m1.hpp
    title: Modint 2^61m1
  - icon: ':heavy_check_mark:'
    path: library/number/sieve_of_eratosthenes.hpp
    title: "\u30A8\u30E9\u30C8\u30B9\u30C6\u30CD\u30B9\u306E\u7BE9"
  - icon: ':heavy_check_mark:'
    path: library/util/object_pool.hpp
    title: Object Pool
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/string/dynamic_rolling_hash.hpp\"\n\n\n\n#include\
    \ <random>\n\n#line 1 \"library/number/sieve_of_eratosthenes.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <cmath>\n#include <vector>\n\n#line 1 \"library/number/internal_eratosthenes.hpp\"\
    \n\n\n\n#include <cstdint>\n#line 6 \"library/number/internal_eratosthenes.hpp\"\
    \n\nnamespace suisen::internal::sieve {\n\nconstexpr std::uint8_t K = 8;\nconstexpr\
    \ std::uint8_t PROD = 2 * 3 * 5;\nconstexpr std::uint8_t RM[K] = { 1,  7, 11,\
    \ 13, 17, 19, 23, 29 };\nconstexpr std::uint8_t DR[K] = { 6,  4,  2,  4,  2, \
    \ 4,  6,  2 };\nconstexpr std::uint8_t DF[K][K] = {\n    { 0, 0, 0, 0, 0, 0, 0,\
    \ 1 }, { 1, 1, 1, 0, 1, 1, 1, 1 },\n    { 2, 2, 0, 2, 0, 2, 2, 1 }, { 3, 1, 1,\
    \ 2, 1, 1, 3, 1 },\n    { 3, 3, 1, 2, 1, 3, 3, 1 }, { 4, 2, 2, 2, 2, 2, 4, 1 },\n\
    \    { 5, 3, 1, 4, 1, 3, 5, 1 }, { 6, 4, 2, 4, 2, 4, 6, 1 },\n};\nconstexpr std::uint8_t\
    \ DRP[K] = { 48, 32, 16, 32, 16, 32, 48, 16 };\nconstexpr std::uint8_t DFP[K][K]\
    \ = {\n    {  0,  0,  0,  0,  0,  0,  0,  8 }, {  8,  8,  8,  0,  8,  8,  8, \
    \ 8 },\n    { 16, 16,  0, 16,  0, 16, 16,  8 }, { 24,  8,  8, 16,  8,  8, 24,\
    \  8 },\n    { 24, 24,  8, 16,  8, 24, 24,  8 }, { 32, 16, 16, 16, 16, 16, 32,\
    \  8 },\n    { 40, 24,  8, 32,  8, 24, 40,  8 }, { 48, 32, 16, 32, 16, 32, 48,\
    \  8 },\n};\n\nconstexpr std::uint8_t MASK[K][K] = {\n    { 0x01, 0x02, 0x04,\
    \ 0x08, 0x10, 0x20, 0x40, 0x80 }, { 0x02, 0x20, 0x10, 0x01, 0x80, 0x08, 0x04,\
    \ 0x40 },\n    { 0x04, 0x10, 0x01, 0x40, 0x02, 0x80, 0x08, 0x20 }, { 0x08, 0x01,\
    \ 0x40, 0x20, 0x04, 0x02, 0x80, 0x10 },\n    { 0x10, 0x80, 0x02, 0x04, 0x20, 0x40,\
    \ 0x01, 0x08 }, { 0x20, 0x08, 0x80, 0x02, 0x40, 0x01, 0x10, 0x04 },\n    { 0x40,\
    \ 0x04, 0x08, 0x80, 0x01, 0x10, 0x20, 0x02 }, { 0x80, 0x40, 0x20, 0x10, 0x08,\
    \ 0x04, 0x02, 0x01 },\n};\nconstexpr std::uint8_t OFFSET[K][K] = {\n    { 0, 1,\
    \ 2, 3, 4, 5, 6, 7, },\n    { 1, 5, 4, 0, 7, 3, 2, 6, },\n    { 2, 4, 0, 6, 1,\
    \ 7, 3, 5, },\n    { 3, 0, 6, 5, 2, 1, 7, 4, },\n    { 4, 7, 1, 2, 5, 6, 0, 3,\
    \ },\n    { 5, 3, 7, 1, 6, 0, 4, 2, },\n    { 6, 2, 3, 7, 0, 4, 5, 1, },\n   \
    \ { 7, 6, 5, 4, 3, 2, 1, 0, },\n};\n\nconstexpr std::uint8_t mask_to_index(const\
    \ std::uint8_t bits) {\n    switch (bits) {\n        case 1 << 0: return 0;\n\
    \        case 1 << 1: return 1;\n        case 1 << 2: return 2;\n        case\
    \ 1 << 3: return 3;\n        case 1 << 4: return 4;\n        case 1 << 5: return\
    \ 5;\n        case 1 << 6: return 6;\n        case 1 << 7: return 7;\n       \
    \ default: assert(false);\n    }\n}\n} // namespace suisen::internal::sieve\n\n\
    \n#line 9 \"library/number/sieve_of_eratosthenes.hpp\"\n\nnamespace suisen {\n\
    \ntemplate <unsigned int N>\nclass SimpleSieve {\n    private:\n        static\
    \ constexpr unsigned int siz = N / internal::sieve::PROD + 1;\n        static\
    \ std::uint8_t flag[siz];\n    public:\n        SimpleSieve() {\n            using\
    \ namespace internal::sieve;\n            flag[0] |= 1;\n            unsigned\
    \ int k_max = (unsigned int) std::sqrt(N + 2) / PROD;\n            for (unsigned\
    \ int kp = 0; kp <= k_max; ++kp) {\n                for (std::uint8_t bits = ~flag[kp];\
    \ bits; bits &= bits - 1) {\n                    const std::uint8_t mp = mask_to_index(bits\
    \ & -bits), m = RM[mp];\n                    unsigned int kr = kp * (PROD * kp\
    \ + 2 * m) + m * m / PROD;\n                    for (std::uint8_t mq = mp; kr\
    \ < siz; kr += kp * DR[mq] + DF[mp][mq], ++mq &= 7) {\n                      \
    \  flag[kr] |= MASK[mp][mq];\n                    }\n                }\n     \
    \       }\n        }\n        std::vector<int> prime_list(unsigned int max_val\
    \ = N) const {\n            using namespace internal::sieve;\n            std::vector<int>\
    \ res { 2, 3, 5 };\n            res.reserve(max_val / 25);\n            for (unsigned\
    \ int i = 0, offset = 0; i < siz and offset < max_val; ++i, offset += PROD) {\n\
    \                for (uint8_t f = ~flag[i]; f;) {\n                    uint8_t\
    \ g = f & -f;\n                    res.push_back(offset + RM[mask_to_index(g)]);\n\
    \                    f ^= g;\n                }\n            }\n            while\
    \ (res.size() and (unsigned int) res.back() > max_val) res.pop_back();\n     \
    \       return res;\n        }\n        bool is_prime(const unsigned int p) const\
    \ {\n            using namespace internal::sieve;\n            switch (p) {\n\
    \                case 2: case 3: case 5: return true;\n                default:\n\
    \                    switch (p % PROD) {\n                        case RM[0]:\
    \ return ((flag[p / PROD] >> 0) & 1) == 0;\n                        case RM[1]:\
    \ return ((flag[p / PROD] >> 1) & 1) == 0;\n                        case RM[2]:\
    \ return ((flag[p / PROD] >> 2) & 1) == 0;\n                        case RM[3]:\
    \ return ((flag[p / PROD] >> 3) & 1) == 0;\n                        case RM[4]:\
    \ return ((flag[p / PROD] >> 4) & 1) == 0;\n                        case RM[5]:\
    \ return ((flag[p / PROD] >> 5) & 1) == 0;\n                        case RM[6]:\
    \ return ((flag[p / PROD] >> 6) & 1) == 0;\n                        case RM[7]:\
    \ return ((flag[p / PROD] >> 7) & 1) == 0;\n                        default: return\
    \ false;\n                    }\n            }\n        }\n};\ntemplate <unsigned\
    \ int N>\nstd::uint8_t SimpleSieve<N>::flag[SimpleSieve<N>::siz];\n\ntemplate\
    \ <unsigned int N>\nclass Sieve {\n    private:\n        static constexpr unsigned\
    \ int base_max = (N + 1) * internal::sieve::K / internal::sieve::PROD;\n     \
    \   static unsigned int pf[base_max + internal::sieve::K];\n\n    public:\n  \
    \      Sieve() {\n            using namespace internal::sieve;\n            pf[0]\
    \ = 1;\n            unsigned int k_max = ((unsigned int) std::sqrt(N + 1) - 1)\
    \ / PROD;\n            for (unsigned int kp = 0; kp <= k_max; ++kp) {\n      \
    \          const int base_i = kp * K, base_act_i = kp * PROD;\n              \
    \  for (int mp = 0; mp < K; ++mp) {\n                    const int m = RM[mp],\
    \ i = base_i + mp;\n                    if (pf[i] == 0) {\n                  \
    \      unsigned int act_i = base_act_i + m;\n                        unsigned\
    \ int base_k = (kp * (PROD * kp + 2 * m) + m * m / PROD) * K;\n              \
    \          for (std::uint8_t mq = mp; base_k <= base_max; base_k += kp * DRP[mq]\
    \ + DFP[mp][mq], ++mq &= 7) {\n                            pf[base_k + OFFSET[mp][mq]]\
    \ = act_i;\n                        }\n                    }\n               \
    \ }\n            }\n        }\n        bool is_prime(const unsigned int p) const\
    \ {\n            using namespace internal::sieve;\n            switch (p) {\n\
    \                case 2: case 3: case 5: return true;\n                default:\n\
    \                    switch (p % PROD) {\n                        case RM[0]:\
    \ return pf[p / PROD * K + 0] == 0;\n                        case RM[1]: return\
    \ pf[p / PROD * K + 1] == 0;\n                        case RM[2]: return pf[p\
    \ / PROD * K + 2] == 0;\n                        case RM[3]: return pf[p / PROD\
    \ * K + 3] == 0;\n                        case RM[4]: return pf[p / PROD * K +\
    \ 4] == 0;\n                        case RM[5]: return pf[p / PROD * K + 5] ==\
    \ 0;\n                        case RM[6]: return pf[p / PROD * K + 6] == 0;\n\
    \                        case RM[7]: return pf[p / PROD * K + 7] == 0;\n     \
    \                   default: return false;\n                    }\n          \
    \  }\n        }\n        int prime_factor(const unsigned int p) const {\n    \
    \        using namespace internal::sieve;\n            switch (p % PROD) {\n \
    \               case  0: case  2: case  4: case  6: case  8:\n               \
    \ case 10: case 12: case 14: case 16: case 18:\n                case 20: case\
    \ 22: case 24: case 26: case 28: return 2;\n                case  3: case  9:\
    \ case 15: case 21: case 27: return 3;\n                case  5: case 25: return\
    \ 5;\n                case RM[0]: return pf[p / PROD * K + 0] ? pf[p / PROD *\
    \ K + 0] : p;\n                case RM[1]: return pf[p / PROD * K + 1] ? pf[p\
    \ / PROD * K + 1] : p;\n                case RM[2]: return pf[p / PROD * K + 2]\
    \ ? pf[p / PROD * K + 2] : p;\n                case RM[3]: return pf[p / PROD\
    \ * K + 3] ? pf[p / PROD * K + 3] : p;\n                case RM[4]: return pf[p\
    \ / PROD * K + 4] ? pf[p / PROD * K + 4] : p;\n                case RM[5]: return\
    \ pf[p / PROD * K + 5] ? pf[p / PROD * K + 5] : p;\n                case RM[6]:\
    \ return pf[p / PROD * K + 6] ? pf[p / PROD * K + 6] : p;\n                case\
    \ RM[7]: return pf[p / PROD * K + 7] ? pf[p / PROD * K + 7] : p;\n           \
    \     default: assert(false);\n            }\n        }\n        /**\n       \
    \  * Returns a vector of `{ prime, index }`.\n         */\n        std::vector<std::pair<int,\
    \ int>> factorize(unsigned int n) const {\n            assert(0 < n and n <= N);\n\
    \            std::vector<std::pair<int, int>> prime_powers;\n            while\
    \ (n > 1) {\n                int p = prime_factor(n), c = 0;\n               \
    \ do { n /= p, ++c; } while (n % p == 0);\n                prime_powers.emplace_back(p,\
    \ c);\n            }\n            return prime_powers;\n        }\n        /**\n\
    \         * Returns the divisors of `n`.\n         * It is NOT guaranteed that\
    \ the returned vector is sorted.\n         */\n        std::vector<int> divisors(unsigned\
    \ int n) const {\n            assert(0 < n and n <= N);\n            std::vector<int>\
    \ divs { 1 };\n            for (auto [prime, index] : factorize(n)) {\n      \
    \          int sz = divs.size();\n                for (int i = 0; i < sz; ++i)\
    \ {\n                    int d = divs[i];\n                    for (int j = 0;\
    \ j < index; ++j) {\n                        divs.push_back(d *= prime);\n   \
    \                 }\n                }\n            }\n            return divs;\n\
    \        }\n};\ntemplate <unsigned int N>\nunsigned int Sieve<N>::pf[Sieve<N>::base_max\
    \ + internal::sieve::K];\n} // namespace suisen\n\n\n#line 1 \"library/number/modint_2^61m1.hpp\"\
    \n\n\n\n#line 6 \"library/number/modint_2^61m1.hpp\"\n\nnamespace suisen {\n \
    \   // reference: https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\n    struct\
    \ modint2p61m1 {\n        using self = modint2p61m1;\n\n        constexpr modint2p61m1():\
    \ v(0) {}\n        constexpr modint2p61m1(uint64_t v): v(fast_mod(v)) {}\n\n \
    \       static constexpr uint64_t mod() {\n            return _mod;\n        }\n\
    \n        static constexpr uint64_t fast_mod(uint64_t v) {\n            constexpr\
    \ uint32_t mid = 61;\n            constexpr uint64_t mask = (uint64_t(1) << mid)\
    \ - 1;\n            uint64_t u = v >> mid;\n            uint64_t d = v & mask;\n\
    \            uint64_t res = u + d;\n            if (res >= _mod) res -= _mod;\n\
    \            return res;\n        }\n\n        constexpr uint64_t val() const\
    \ {\n            return v;\n        }\n\n        constexpr self& operator+=(const\
    \ self& rhs) {\n            v += rhs.v;\n            if (v >= _mod) v -= _mod;\n\
    \            return *this;\n        }\n        constexpr self& operator-=(const\
    \ self& rhs) {\n            if (v < rhs.v) v += _mod;\n            v -= rhs.v;\n\
    \            return *this;\n        }\n        constexpr self& operator*=(const\
    \ self& rhs) {\n            uint64_t au = v >> mid31;     // < 2^30\n        \
    \    uint64_t ad = v & mask31;     // < 2^31\n            uint64_t bu = rhs.v\
    \ >> mid31; // < 2^30\n            uint64_t bd = rhs.v & mask31; // < 2^31\n\n\
    \            //   a * b\n            // = (au * 2^31 + ad) * (bu * 2^31 + bd)\n\
    \            // = au * bu * 2^62             # au * bu * 2^62 \u2261 au * bu *\
    \ 2 < 2^61\n            // + (au * bd + ad * bu) * 2^31 # m := au * bd + ad *\
    \ bu\n            //                              # m <= 2 * (2^31 - 1) * (2^30\
    \ - 1) = 2^62 - 6 * 2^30 + 2\n            //                              # m\
    \ = mu * 2^30 + md (0 <= mu < 2^32, 0 <= md < 2^30)\n            //          \
    \                    # m * 2^31 \u2261 mu + md * 2^31 < 2^61 + 2^31\n        \
    \    // + ad * bd                    # ad * bd <= (2^31 - 1) ** 2 = 2^62 - 2^32\
    \ + 1 < 2^62 - 2^31\n            // \u2261 au * bu * 2 + mu + md * 2^31 + ad *\
    \ bd < 2^63\n\n            uint64_t m = au * bd + ad * bu;\n            uint64_t\
    \ mu = m >> mid30;\n            uint64_t md = m & mask30;\n\n            v = fast_mod((au\
    \ * bu << 1) + mu + (md << 31) + ad * bd);\n            return *this;\n      \
    \  }\n\n        constexpr friend self operator+(const self& l, const self& r)\
    \ { return self(l) += r; }\n        constexpr friend self operator-(const self&\
    \ l, const self& r) { return self(l) -= r; }\n        constexpr friend self operator*(const\
    \ self& l, const self& r) { return self(l) *= r; }\n        constexpr friend bool\
    \ operator==(const self& l, const self& r) { return l.v == r.v; }\n\n        constexpr\
    \ self pow(long long b) const {\n            assert(b >= 0);\n            self\
    \ x = 1, p = *this;\n            for (; b; b >>= 1) {\n                if (b &\
    \ 1) x *= p;\n                p *= p;\n            }\n            return x;\n\
    \        }\n        constexpr self inv() const {\n            // a ** (p - 2)\
    \ = a ** (2**61 - 3)\n            // 2**61 - 3 = 0001_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1101\n\
    \            self x = *this, p = *this * *this;\n            for (int i = 2; i\
    \ <= 60; ++i) {\n                x *= (p *= p);\n            }\n            return\
    \ x;\n        }\n    private:\n        static constexpr uint64_t _mod = (uint64_t(1)\
    \ << 61) - 1; // 2**61-1 : prime\n\n        static constexpr uint32_t mid31 =\
    \ 31;\n        static constexpr uint64_t mask31 = (uint64_t(1) << 31) - 1;\n \
    \       static constexpr uint32_t mid30 = 30;\n        static constexpr uint64_t\
    \ mask30 = (uint64_t(1) << mid30) - 1;\n\n        uint64_t v;\n    };\n} // namespace\
    \ suisen\n\n\n\n#line 1 \"library/datastructure/bbst/red_black_segment_tree.hpp\"\
    \n\n\n\n#line 1 \"library/datastructure/bbst/red_black_tree_base.hpp\"\n\n\n\n\
    #line 5 \"library/datastructure/bbst/red_black_tree_base.hpp\"\n#include <sstream>\n\
    #include <string>\n#include <tuple>\n#line 1 \"library/util/object_pool.hpp\"\n\
    \n\n\n#include <deque>\n#line 6 \"library/util/object_pool.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, bool auto_extend = false>\n    struct ObjectPool\
    \ {\n        using value_type = T;\n        using value_pointer_type = T*;\n\n\
    \        template <typename U>\n        using container_type = std::conditional_t<auto_extend,\
    \ std::deque<U>, std::vector<U>>;\n\n        container_type<value_type> pool;\n\
    \        container_type<value_pointer_type> stock;\n        decltype(stock.begin())\
    \ it;\n\n        ObjectPool() : ObjectPool(0) {}\n        ObjectPool(int siz)\
    \ : pool(siz), stock(siz) {\n            clear();\n        }\n\n        int capacity()\
    \ const { return pool.size(); }\n        int size() const { return it - stock.begin();\
    \ }\n\n        value_pointer_type alloc() {\n            if constexpr (auto_extend)\
    \ ensure();\n            return *it++;\n        }\n\n        void free(value_pointer_type\
    \ t) {\n            *--it = t;\n        }\n\n        void clear() {\n        \
    \    int siz = pool.size();\n            it = stock.begin();\n            for\
    \ (int i = 0; i < siz; i++) stock[i] = &pool[i];\n        }\n\n        void ensure()\
    \ {\n            if (it != stock.end()) return;\n            int siz = stock.size();\n\
    \            for (int i = siz; i <= siz * 2; ++i) {\n                stock.push_back(&pool.emplace_back());\n\
    \            }\n            it = stock.begin() + siz;\n        }\n    };\n} //\
    \ namespace suisen\n\n\n#line 9 \"library/datastructure/bbst/red_black_tree_base.hpp\"\
    \n\nnamespace suisen::bbst::internal {\n    template <typename T, typename Derived>\n\
    \    struct RedBlackTreeNodeBase {\n        enum RedBlackTreeNodeColor { RED,\
    \ BLACK };\n\n        using base_type = void;\n        using size_type = int;\n\
    \n        using value_type = T;\n\n        using node_type = Derived;\n      \
    \  using tree_type = node_type*;\n\n        using color_type = RedBlackTreeNodeColor;\n\
    \n        RedBlackTreeNodeBase() = default;\n\n        static inline ObjectPool<node_type>\
    \ pool{};\n\n        static void init_pool(int siz) { pool = ObjectPool<node_type>(siz);\
    \ }\n        static int node_num() { return pool.size(); }\n\n        static tree_type\
    \ empty_tree() { return nullptr; }\n\n        static size_type size(tree_type\
    \ node) { return node ? node->_siz : 0; }\n        static bool empty(tree_type\
    \ node) { return not node; }\n\n        template <bool force_black_root = true>\n\
    \        static tree_type merge(tree_type l, tree_type r) {\n            if (not\
    \ l) return r;\n            if (not r) return l;\n\n            tree_type res\
    \ = nullptr;\n            if (size_type hl = height(l), hr = height(r); hl > hr)\
    \ {\n                l = node_type::push(l);\n                tree_type c = l->_ch[1]\
    \ = merge<false>(l->_ch[1], r);\n                if (l->_col == BLACK and c->_col\
    \ == RED and color(c->_ch[1]) == RED) {\n                    std::swap(l->_col,\
    \ c->_col);\n                    if (std::exchange(l->_ch[0]->_col, BLACK) ==\
    \ BLACK) return rotate(l, 1);\n                }\n                res = node_type::update(l);\n\
    \            } else if (hr > hl) {\n                r = node_type::push(r);\n\
    \                tree_type c = r->_ch[0] = merge<false>(l, r->_ch[0]);\n     \
    \           if (r->_col == BLACK and c->_col == RED and color(c->_ch[0]) == RED)\
    \ {\n                    std::swap(r->_col, c->_col);\n                    if\
    \ (std::exchange(r->_ch[1]->_col, BLACK) == BLACK) return rotate(r, 0);\n    \
    \            }\n                res = node_type::update(r);\n            } else\
    \ {\n                res = create_branch(l, r);\n            }\n            if\
    \ constexpr (force_black_root) res->_col = BLACK;\n            return res;\n \
    \       }\n\n        static std::pair<tree_type, tree_type> split(tree_type node,\
    \ size_type k) {\n            if (not node) return { nullptr, nullptr };\n   \
    \         node = node_type::push(node);\n            if (k == 0) return { nullptr,\
    \ node };\n            if (k == size(node)) return { node, nullptr };\n\n    \
    \        tree_type l = std::exchange(node->_ch[0], nullptr);\n            tree_type\
    \ r = std::exchange(node->_ch[1], nullptr);\n\n            free_node(node);\n\n\
    \            if (color(l) == RED) l->_col = BLACK;\n            if (color(r) ==\
    \ RED) r->_col = BLACK;\n\n            size_type szl = size(l);\n            tree_type\
    \ m;\n            if (k < szl) {\n                std::tie(l, m) = split(l, k);\n\
    \                return { l, merge(m, r) };\n            }\n            if (k\
    \ > szl) {\n                std::tie(m, r) = split(r, k - szl);\n            \
    \    return { merge(l, m), r };\n            }\n            return { l, r };\n\
    \        }\n\n        static std::tuple<tree_type, tree_type, tree_type> split_range(tree_type\
    \ node, size_type l, size_type r) {\n            auto [tlm, tr] = split(node,\
    \ r);\n            auto [tl, tm] = split(tlm, l);\n            return { tl, tm,\
    \ tr };\n        }\n\n        static tree_type insert(tree_type node, size_type\
    \ k, const value_type& val) {\n            auto [tl, tr] = split(node, k);\n \
    \           return merge(merge(tl, create_leaf(val)), tr);\n        }\n      \
    \  static tree_type push_front(tree_type node, const value_type &val) { return\
    \ insert(node, 0, val); }\n        static tree_type push_back(tree_type node,\
    \ const value_type &val) { return insert(node, size(node), val); }\n\n       \
    \ static std::pair<tree_type, value_type> erase(tree_type node, size_type k) {\n\
    \            auto [tl, tm, tr] = split_range(node, k, k + 1);\n            value_type\
    \ erased_value = tm->_val;\n            free_node(tm);\n            return { merge(tl,\
    \ tr) , erased_value };\n        }\n        static std::pair<tree_type, value_type>\
    \ pop_front(tree_type node) { return erase(node, 0); }\n        static std::pair<tree_type,\
    \ value_type> pop_back(tree_type node) { return erase(node, size(node) - 1); }\n\
    \n        template <typename Fun>\n        static tree_type update_value(tree_type\
    \ node, size_type k, Fun &&fun) {\n            auto [tl, top, tr] = split_range(node,\
    \ k, k + 1);\n            top->_val = fun(top->_val);\n            return merge(merge(tl,\
    \ top), tr);\n        }\n        static tree_type set(tree_type node, size_type\
    \ k, value_type val) {\n            return update_value(node, k, [&val]{ return\
    \ val; });\n        }\n        static std::pair<tree_type, value_type> get(tree_type\
    \ node, size_type k) {\n            auto [tl, top, tr] = split_range(node, k,\
    \ k + 1);\n            value_type res = top->_val;\n            return { merge(merge(tl,\
    \ top), tr), res };\n        }\n\n        template <typename Seq>\n        static\
    \ tree_type build(const Seq& a, int l, int r) {\n            if (r - l == 1) return\
    \ create_leaf(a[l]);\n            int m = (l + r) >> 1;\n            return merge(build(a,\
    \ l, m), build(a, m, r));\n        }\n        template <typename Seq>\n      \
    \  static tree_type build(const Seq& a) {\n            return a.empty() ? empty_tree()\
    \ : build(a, 0, a.size());\n        }\n\n        template <typename OutputIterator>\n\
    \        static void dump(tree_type node, OutputIterator it) {\n            if\
    \ (empty(node)) return;\n            auto dfs = [&](auto dfs, tree_type cur) ->\
    \ void {\n                if (cur->is_leaf()) {\n                    *it++ = cur->_val;\n\
    \                    return;\n                }\n                dfs(dfs, cur->_ch[0]);\n\
    \                dfs(dfs, cur->_ch[1]);\n            };\n            dfs(dfs,\
    \ node);\n        }\n\n        // Don't use on persistent tree.\n        static\
    \ void free(tree_type node) {\n            auto dfs = [&](auto dfs, tree_type\
    \ cur) -> void {\n                if (not cur) return;\n                dfs(dfs,\
    \ cur->_ch[0]);\n                dfs(dfs, cur->_ch[1]);\n                free_node(cur);\n\
    \            };\n            dfs(dfs, node);\n        }\n\n        template <typename\
    \ ToStr>\n        static std::string to_string(tree_type node, ToStr f) {\n  \
    \          std::vector<value_type> dat;\n            node_type::dump(node, std::back_inserter(dat));\n\
    \            std::ostringstream res;\n            int siz = dat.size();\n    \
    \        res << '[';\n            for (int i = 0; i < siz; ++i) {\n          \
    \      res << f(dat[i]);\n                if (i != siz - 1) res << \", \";\n \
    \           }\n            res << ']';\n            return res.str();\n      \
    \  }\n        static std::string to_string(tree_type node) {\n            return\
    \ to_string(node, [](const auto &e) { return e; });\n        }\n\n        static\
    \ void check_rbtree_properties(tree_type node) {\n            assert(color(node)\
    \ == BLACK);\n            auto dfs = [&](auto dfs, tree_type cur) -> int {\n \
    \               if (not cur) return 0;\n                if (cur->_col == RED)\
    \ {\n                    assert(color(cur->_ch[0]) == BLACK);\n              \
    \      assert(color(cur->_ch[1]) == BLACK);\n                }\n             \
    \   int bl = dfs(dfs, cur->_ch[0]);\n                int br = dfs(dfs, cur->_ch[1]);\n\
    \                assert(bl == br);\n                return bl + (cur->_col ==\
    \ BLACK);\n            };\n            dfs(dfs, node);\n        }\n\n    protected:\n\
    \        color_type _col;\n        tree_type _ch[2]{ nullptr, nullptr };\n   \
    \     value_type _val;\n        size_type _siz, _lev;\n\n        RedBlackTreeNodeBase(const\
    \ value_type& val) : _col(BLACK), _val(val), _siz(1), _lev(0) {}\n        RedBlackTreeNodeBase(tree_type\
    \ l, tree_type r) : _col(RED), _ch{ l, r }, _siz(l->_siz + r->_siz), _lev(l->_lev\
    \ + (l->_col == BLACK)) {}\n\n        static void clear_pool() { pool.clear();\
    \ }\n        static int pool_capacity() { return pool.capacity(); }\n\n      \
    \  static color_type color(tree_type node) { return node ? node->_col : BLACK;\
    \ }\n        static size_type height(tree_type node) { return node ? node->_lev\
    \ : 0; }\n\n        bool is_leaf() const { return not (_ch[0] or _ch[1]); }\n\n\
    \        static tree_type clone(tree_type node) {\n            return node;\n\
    \        }\n        static tree_type update(tree_type node) {\n            node->_siz\
    \ = node->is_leaf() ? 1 : size(node->_ch[0]) + size(node->_ch[1]);\n         \
    \   node->_lev = node->_ch[0] ? height(node->_ch[0]) + (node->_ch[0]->_col ==\
    \ BLACK) : 0;\n            return node;\n        }\n        static tree_type push(tree_type\
    \ node) {\n            return node;\n        }\n\n        static tree_type rotate(tree_type\
    \ node, int index) {\n            node = node_type::push(node);\n            tree_type\
    \ ch_node = node_type::push(node->_ch[index]);\n            node->_ch[index] =\
    \ std::exchange(ch_node->_ch[index ^ 1], node);\n            return node_type::update(node),\
    \ node_type::update(ch_node);\n        }\n\n        static tree_type create_leaf(const\
    \ value_type& val = value_type{}) {\n            return &(*pool.alloc() = node_type(val));\n\
    \        }\n\n        static tree_type create_branch(tree_type l, tree_type r)\
    \ {\n            return node_type::update(&(*pool.alloc() = node_type(l, r)));\n\
    \        }\n\n        static void free_node(tree_type node) {\n            if\
    \ (node) pool.free(node);\n        }\n    };\n} // namespace suisen\n\n\n#line\
    \ 5 \"library/datastructure/bbst/red_black_segment_tree.hpp\"\n\nnamespace suisen::bbst::segtree\
    \ {\n    template <typename T, T(*op)(T, T), T(*e)(), template <typename, typename>\
    \ typename BaseNode = internal::RedBlackTreeNodeBase>\n    struct RedBlackTreeNode\
    \ : public BaseNode<T, RedBlackTreeNode<T, op, e, BaseNode>> {\n        using\
    \ base_type = BaseNode<T, RedBlackTreeNode<T, op, e, BaseNode>>;\n        using\
    \ node_type = typename base_type::node_type;\n        using tree_type = typename\
    \ base_type::tree_type;\n        using size_type = typename base_type::size_type;\n\
    \        using value_type = typename base_type::value_type;\n\n        friend\
    \ base_type;\n        friend typename base_type::base_type;\n\n        RedBlackTreeNode()\
    \ : base_type() {}\n\n        static std::pair<tree_type, value_type> prod(tree_type\
    \ node, size_type l, size_type r) {\n            auto [tl, tm, tr] = base_type::split_range(node,\
    \ l, r);\n            value_type res = value(tm);\n            return { base_type::merge(base_type::merge(tl,\
    \ tm), tr), res };\n        }\n        static value_type prod_all(tree_type node)\
    \ {\n            return value(node);\n        }\n\n    private:\n        RedBlackTreeNode(const\
    \ value_type& val) : base_type(val) {}\n        RedBlackTreeNode(tree_type l,\
    \ tree_type r) : base_type(l, r) {}\n\n        static value_type value(tree_type\
    \ node) { return node ? node->_val : e(); }\n\n        static tree_type update(tree_type\
    \ node) {\n            base_type::update(node);\n            node->_val = op(value(node->_ch[0]),\
    \ value(node->_ch[1]));\n            return node;\n        }\n    };\n}\n\n\n\
    #line 9 \"library/string/dynamic_rolling_hash.hpp\"\n\nnamespace suisen {\n  \
    \  namespace internal::dynamic_rolling_hash {\n        struct BaseGen {\n    \
    \        static constexpr int max_base = 100000;\n            static inline std::mt19937\
    \ rng{ std::random_device{}() };\n            static inline Sieve<max_base> sieve{};\n\
    \n            static uint32_t generate() {\n                uint32_t base;\n \
    \               do {\n                    base = rng() % (max_base - 10) + 10;\n\
    \                    base -= (base & 1) == 0;\n                } while (not sieve.is_prime(base));\n\
    \                return base;\n            }\n        };\n\n        template <size_t\
    \ id>\n        uint32_t base() {\n            static uint32_t _base = 0;\n   \
    \         return _base ? _base : (_base = BaseGen::generate());\n        }\n\n\
    \        template <size_t base_num_>\n        struct Hash {\n            static\
    \ constexpr size_t base_num = base_num_;\n\n            using child_type = Hash<base_num\
    \ - 1>;\n            using hash_type = std::array<uint64_t, base_num>;\n\n   \
    \         modint2p61m1 hash;\n            modint2p61m1 offset;\n\n           \
    \ child_type hash_lo;\n\n            Hash() : Hash(0) {}\n            template\
    \ <typename T>\n            Hash(const T& val): hash(val), offset(base<base_num>()),\
    \ hash_lo(val) {}\n\n            operator hash_type() const {\n              \
    \  hash_type res;\n                store_hash(res);\n                return res;\n\
    \            }\n\n            template <typename Container>\n            void\
    \ store_hash(Container& h) const {\n                h[base_num - 1] = hash.val();\n\
    \                hash_lo.store_hash(h);\n            }\n\n            static Hash\
    \ identity() {\n                return { 0, 1, child_type::identity() };\n   \
    \         }\n            static Hash merge(const Hash &l, const Hash &r) {\n \
    \               return { l.hash * r.offset + r.hash, l.offset * r.offset, child_type::merge(l.hash_lo,\
    \ r.hash_lo) };\n            }\n            static Hash merge_noref(Hash l, Hash\
    \ r) {\n                return merge(l, r);\n            }\n        private:\n\
    \            Hash(const modint2p61m1& hash, const modint2p61m1& offset, const\
    \ child_type& hash_lo): hash(hash), offset(offset), hash_lo(hash_lo) {}\n    \
    \    };\n\n        template <>\n        struct Hash<1> {\n            static constexpr\
    \ size_t base_num = 1;\n\n            modint2p61m1 hash;\n            modint2p61m1\
    \ offset;\n\n            using hash_type = uint64_t;\n\n            Hash() : Hash(0)\
    \ {}\n            template <typename T>\n            Hash(const T& val): hash(val),\
    \ offset(base<base_num>()) {}\n\n            operator hash_type() const {\n  \
    \              return hash.val();\n            }\n\n            template <typename\
    \ Container>\n            void store_hash(Container& h) const {\n            \
    \    h[0] = hash.val();\n            }\n\n            static Hash identity() {\n\
    \                return { 0, 1 };\n            }\n            static Hash merge(const\
    \ Hash &l, const Hash &r) {\n                return { l.hash * r.offset + r.hash,\
    \ l.offset * r.offset };\n            }\n            static Hash merge_noref(Hash\
    \ l, Hash r) {\n                return merge(l, r);\n            }\n        private:\n\
    \            Hash(const modint2p61m1& hash, const modint2p61m1& offset): hash(hash),\
    \ offset(offset) {}\n        };\n    }\n\n    template <std::size_t base_num>\n\
    \    using Hash = internal::dynamic_rolling_hash::Hash<base_num>;\n\n    template\
    \ <size_t base_num_ = 1>\n    struct DynamicRollingHash {\n        static constexpr\
    \ size_t base_num = base_num_;\n    private:\n        using hash_ = Hash<base_num>;\n\
    \n        using node = bbst::segtree::RedBlackTreeNode<hash_, hash_::merge_noref,\
    \ hash_::identity>;\n\n        node* _seq;\n    public:\n        using hash =\
    \ typename hash_::hash_type;\n\n        DynamicRollingHash() {}\n        template\
    \ <typename Seq>\n        DynamicRollingHash(const Seq& a): DynamicRollingHash()\
    \ {\n            _seq = node::build(a);\n        }\n\n        static void init_pool(size_t\
    \ reserving_node_num) {\n            node::init_pool(reserving_node_num);\n  \
    \      }\n\n        template <typename T>\n        void set(size_t k, const T&\
    \ val) {\n            _seq = node::update_value(_seq, k, val);\n        }\n  \
    \      template <typename T>\n        void insert(size_t k, const T& val) {\n\
    \            _seq = node::insert(_seq, k, val);\n        }\n        template <typename\
    \ T>\n        void push_back(const T& val) {\n            insert(node::size(_seq),\
    \ val);\n        }\n        template <typename T>\n        void push_front(const\
    \ T& val) {\n            insert(0, val);\n        }\n        void erase(size_t\
    \ k) {\n            _seq = node::erase(_seq, k).first;\n        }\n        void\
    \ pop_back() {\n            erase(node::size(_seq) - 1);\n        }\n        void\
    \ pop_front() {\n            erase(0);\n        }\n\n        hash operator()(int\
    \ l, int r) {\n            hash_ res;\n            std::tie(_seq, res) = node::prod(_seq,\
    \ l, r);\n            return res;\n        }\n    };\n}\n\n\n"
  code: "#ifndef SUISEN_DYNAMIC_ROLLING_HASH\n#define SUISEN_DYNAMIC_ROLLING_HASH\n\
    \n#include <random>\n\n#include \"library/number/sieve_of_eratosthenes.hpp\"\n\
    #include \"library/number/modint_2^61m1.hpp\"\n#include \"library/datastructure/bbst/red_black_segment_tree.hpp\"\
    \n\nnamespace suisen {\n    namespace internal::dynamic_rolling_hash {\n     \
    \   struct BaseGen {\n            static constexpr int max_base = 100000;\n  \
    \          static inline std::mt19937 rng{ std::random_device{}() };\n       \
    \     static inline Sieve<max_base> sieve{};\n\n            static uint32_t generate()\
    \ {\n                uint32_t base;\n                do {\n                  \
    \  base = rng() % (max_base - 10) + 10;\n                    base -= (base & 1)\
    \ == 0;\n                } while (not sieve.is_prime(base));\n               \
    \ return base;\n            }\n        };\n\n        template <size_t id>\n  \
    \      uint32_t base() {\n            static uint32_t _base = 0;\n           \
    \ return _base ? _base : (_base = BaseGen::generate());\n        }\n\n       \
    \ template <size_t base_num_>\n        struct Hash {\n            static constexpr\
    \ size_t base_num = base_num_;\n\n            using child_type = Hash<base_num\
    \ - 1>;\n            using hash_type = std::array<uint64_t, base_num>;\n\n   \
    \         modint2p61m1 hash;\n            modint2p61m1 offset;\n\n           \
    \ child_type hash_lo;\n\n            Hash() : Hash(0) {}\n            template\
    \ <typename T>\n            Hash(const T& val): hash(val), offset(base<base_num>()),\
    \ hash_lo(val) {}\n\n            operator hash_type() const {\n              \
    \  hash_type res;\n                store_hash(res);\n                return res;\n\
    \            }\n\n            template <typename Container>\n            void\
    \ store_hash(Container& h) const {\n                h[base_num - 1] = hash.val();\n\
    \                hash_lo.store_hash(h);\n            }\n\n            static Hash\
    \ identity() {\n                return { 0, 1, child_type::identity() };\n   \
    \         }\n            static Hash merge(const Hash &l, const Hash &r) {\n \
    \               return { l.hash * r.offset + r.hash, l.offset * r.offset, child_type::merge(l.hash_lo,\
    \ r.hash_lo) };\n            }\n            static Hash merge_noref(Hash l, Hash\
    \ r) {\n                return merge(l, r);\n            }\n        private:\n\
    \            Hash(const modint2p61m1& hash, const modint2p61m1& offset, const\
    \ child_type& hash_lo): hash(hash), offset(offset), hash_lo(hash_lo) {}\n    \
    \    };\n\n        template <>\n        struct Hash<1> {\n            static constexpr\
    \ size_t base_num = 1;\n\n            modint2p61m1 hash;\n            modint2p61m1\
    \ offset;\n\n            using hash_type = uint64_t;\n\n            Hash() : Hash(0)\
    \ {}\n            template <typename T>\n            Hash(const T& val): hash(val),\
    \ offset(base<base_num>()) {}\n\n            operator hash_type() const {\n  \
    \              return hash.val();\n            }\n\n            template <typename\
    \ Container>\n            void store_hash(Container& h) const {\n            \
    \    h[0] = hash.val();\n            }\n\n            static Hash identity() {\n\
    \                return { 0, 1 };\n            }\n            static Hash merge(const\
    \ Hash &l, const Hash &r) {\n                return { l.hash * r.offset + r.hash,\
    \ l.offset * r.offset };\n            }\n            static Hash merge_noref(Hash\
    \ l, Hash r) {\n                return merge(l, r);\n            }\n        private:\n\
    \            Hash(const modint2p61m1& hash, const modint2p61m1& offset): hash(hash),\
    \ offset(offset) {}\n        };\n    }\n\n    template <std::size_t base_num>\n\
    \    using Hash = internal::dynamic_rolling_hash::Hash<base_num>;\n\n    template\
    \ <size_t base_num_ = 1>\n    struct DynamicRollingHash {\n        static constexpr\
    \ size_t base_num = base_num_;\n    private:\n        using hash_ = Hash<base_num>;\n\
    \n        using node = bbst::segtree::RedBlackTreeNode<hash_, hash_::merge_noref,\
    \ hash_::identity>;\n\n        node* _seq;\n    public:\n        using hash =\
    \ typename hash_::hash_type;\n\n        DynamicRollingHash() {}\n        template\
    \ <typename Seq>\n        DynamicRollingHash(const Seq& a): DynamicRollingHash()\
    \ {\n            _seq = node::build(a);\n        }\n\n        static void init_pool(size_t\
    \ reserving_node_num) {\n            node::init_pool(reserving_node_num);\n  \
    \      }\n\n        template <typename T>\n        void set(size_t k, const T&\
    \ val) {\n            _seq = node::update_value(_seq, k, val);\n        }\n  \
    \      template <typename T>\n        void insert(size_t k, const T& val) {\n\
    \            _seq = node::insert(_seq, k, val);\n        }\n        template <typename\
    \ T>\n        void push_back(const T& val) {\n            insert(node::size(_seq),\
    \ val);\n        }\n        template <typename T>\n        void push_front(const\
    \ T& val) {\n            insert(0, val);\n        }\n        void erase(size_t\
    \ k) {\n            _seq = node::erase(_seq, k).first;\n        }\n        void\
    \ pop_back() {\n            erase(node::size(_seq) - 1);\n        }\n        void\
    \ pop_front() {\n            erase(0);\n        }\n\n        hash operator()(int\
    \ l, int r) {\n            hash_ res;\n            std::tie(_seq, res) = node::prod(_seq,\
    \ l, r);\n            return res;\n        }\n    };\n}\n\n#endif // SUISEN_DYNAMIC_ROLLING_HASH\n"
  dependsOn:
  - library/number/sieve_of_eratosthenes.hpp
  - library/number/internal_eratosthenes.hpp
  - library/number/modint_2^61m1.hpp
  - library/datastructure/bbst/red_black_segment_tree.hpp
  - library/datastructure/bbst/red_black_tree_base.hpp
  - library/util/object_pool.hpp
  isVerificationFile: false
  path: library/string/dynamic_rolling_hash.hpp
  requiredBy: []
  timestamp: '2023-01-08 02:32:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/string/dynamic_rolling_hash.hpp
layout: document
title: Dynamic Rolling Hash
---
## Dynamic Rolling Hash
