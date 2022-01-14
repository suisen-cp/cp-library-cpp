---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/ZDD.hpp
    title: library/datastructure/ZDD.hpp
  - icon: ':heavy_check_mark:'
    path: library/util/tuple_hash.hpp
    title: library/util/tuple_hash.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/maximum_independent_set
    links:
    - https://judge.yosupo.jp/problem/maximum_independent_set
  bundledCode: "#line 1 \"test/src/datastructure/ZDD/maximum_independent_set.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/maximum_independent_set\"\n\
    \n#include <iostream>\n\n#line 1 \"library/datastructure/ZDD.hpp\"\n\n\n\n#include\
    \ <array>\n#include <cstdint>\n#include <limits>\n#include <optional>\n#include\
    \ <queue>\n#include <set>\n#include <vector>\n#include <unordered_map>\n\n#line\
    \ 1 \"library/util/tuple_hash.hpp\"\n\n\n\n#line 5 \"library/util/tuple_hash.hpp\"\
    \n#include <tuple>\n\nnamespace std {\n    namespace {\n        template <class\
    \ T>\n        inline void hash_combine(std::size_t& seed, T const& v) {\n    \
    \        seed ^= hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);\n    \
    \    }\n\n        template <class Tuple, size_t Index = std::tuple_size<Tuple>::value\
    \ - 1>\n        struct HashValueImpl {\n            static void apply(size_t&\
    \ seed, Tuple const& t) {\n                HashValueImpl<Tuple, Index - 1>::apply(seed,\
    \ t);\n                hash_combine(seed, get<Index>(t));\n            }\n   \
    \     };\n\n        template <class Tuple>\n        struct HashValueImpl<Tuple,\
    \ 0> {\n            static void apply(size_t& seed, Tuple const& t) {\n      \
    \          hash_combine(seed, get<0>(t));\n            }\n        };\n    }\n\n\
    \    template <typename ...Args>\n    struct hash<std::tuple<Args...>> {\n   \
    \     size_t operator()(std::tuple<Args...> const& tt) const {\n            size_t\
    \ seed = 0;\n            HashValueImpl<std::tuple<Args...>>::apply(seed, tt);\n\
    \            return seed;\n        }\n    };\n}\n\n\n#line 14 \"library/datastructure/ZDD.hpp\"\
    \n\nnamespace suisen {\n\n    namespace internal::zdd {\n        using zdd_lev_t\
    \ = uint32_t;\n        using zdd_t = uint32_t;\n\n        constexpr zdd_t ZERO\
    \ = 0;\n        constexpr zdd_t ONE = 1;\n\n        zdd_t next_id = 2;\n\n   \
    \     std::unordered_map<std::tuple<zdd_t, zdd_t, zdd_lev_t>, zdd_t> zdd_cache;\n\
    \        std::vector<std::array<zdd_t, 2>> child(next_id);\n        std::vector<zdd_lev_t>\
    \ level(next_id);\n\n        zdd_lev_t next_lev = 1;\n\n        template <typename\
    \ Cache, typename ...Args>\n        auto check_cache(const Cache& cache, Args\
    \ &&...args) {\n            return cache.find(std::make_tuple(std::forward<Args>(args)...));\n\
    \        }\n\n        template <typename Cache, typename Result, typename ...Args>\n\
    \        auto register_result(Cache& cache, Result f, Args &&...args) {\n    \
    \        return cache[std::make_tuple(std::forward<Args>(args)...)] = f;\n   \
    \     }\n    } // namespace zdd\n    \n    struct ZDD {\n\n        ZDD(internal::zdd::zdd_t\
    \ id = internal::zdd::ZERO) : id(id) {}\n\n        static ZDD terminal0() {\n\
    \            return ZDD(internal::zdd::ZERO);\n        }\n        static ZDD terminal1()\
    \ {\n            return ZDD(internal::zdd::ONE);\n        }\n\n        static\
    \ internal::zdd::zdd_lev_t new_level() {\n            return internal::zdd::next_lev++;\n\
    \        }\n\n        static internal::zdd::zdd_t create_zdd(ZDD l, ZDD r, internal::zdd::zdd_lev_t\
    \ lev) {\n            using namespace internal::zdd;\n            if (r.id ==\
    \ ZERO) return l.id;\n            if (auto it = check_cache(zdd_cache, l.id, r.id,\
    \ lev); it != zdd_cache.end()) return it->second;\n            child.push_back(std::array<zdd_t,\
    \ 2>{ l.id, r.id });\n            level.push_back(lev);\n            return register_result(zdd_cache,\
    \ next_id++, l.id, r.id, lev);\n        }\n\n        bool is_terminal0() const\
    \ {\n            return id == internal::zdd::ZERO;\n        }\n        bool is_terminal1()\
    \ const {\n            return id == internal::zdd::ONE;\n        }\n\n       \
    \ ZDD operator[](int edge_id) const {\n            return internal::zdd::child[id][edge_id];\n\
    \        }\n        internal::zdd::zdd_lev_t top() const {\n            return\
    \ internal::zdd::level[id];\n        }\n\n        static ZDD change(ZDD f, internal::zdd::zdd_lev_t\
    \ lev) {\n            using namespace internal::zdd;\n            static std::unordered_map<std::tuple<zdd_t,\
    \ zdd_lev_t>, ZDD> cache;\n            if (lev == f.top()) {\n               \
    \ return create_zdd(f[1], f[0], lev);\n            } else if (lev < f.top()) {\n\
    \                if (auto it = check_cache(cache, f.id, lev); it != cache.end())\
    \ return it->second;\n                return register_result(cache, create_zdd(change(f[0],\
    \ lev), change(f[1], lev), f.top()), f.id, lev);\n            } else {\n     \
    \           return create_zdd(terminal0(), f, lev);\n            }\n        }\n\
    \n        static ZDD onset0(ZDD f, internal::zdd::zdd_lev_t lev) {\n         \
    \   using namespace internal::zdd;\n            if (lev == f.top()) {\n      \
    \          return create_zdd(f[1], terminal0(), lev);\n            } else if (lev\
    \ < f.top()) {\n                static std::unordered_map<std::tuple<zdd_t, zdd_lev_t>,\
    \ ZDD> cache;\n                if (auto it = check_cache(cache, f.id, lev); it\
    \ != cache.end()) return it->second;\n                return register_result(cache,\
    \ create_zdd(onset0(f[0], lev), onset0(f[1], lev), f.top()), f.id, lev);\n   \
    \         } else {\n                return terminal0();\n            }\n     \
    \   }\n\n        static ZDD onset1(ZDD f, internal::zdd::zdd_lev_t lev) {\n  \
    \          using namespace internal::zdd;\n            if (lev == f.top()) {\n\
    \                return create_zdd(terminal0(), f[1], lev);\n            } else\
    \ if (lev < f.top()) {\n                static std::unordered_map<std::tuple<zdd_t,\
    \ zdd_lev_t>, ZDD> cache;\n                if (auto it = check_cache(cache, f.id,\
    \ lev); it != cache.end()) return it->second;\n                return register_result(cache,\
    \ create_zdd(onset1(f[0], lev), onset1(f[1], lev), f.top()), f.id, lev);\n   \
    \         } else {\n                return terminal0();\n            }\n     \
    \   }\n\n        static ZDD offset(ZDD f, internal::zdd::zdd_lev_t lev) {\n  \
    \          using namespace internal::zdd;\n            if (lev == f.top()) {\n\
    \                return create_zdd(f[0], terminal0(), lev);\n            } else\
    \ if (lev < f.top()) {\n                static std::unordered_map<std::tuple<zdd_t,\
    \ zdd_lev_t>, ZDD> cache;\n                if (auto it = check_cache(cache, f.id,\
    \ lev); it != cache.end()) return it->second;\n                return register_result(cache,\
    \ create_zdd(offset(f[0], lev), offset(f[1], lev), f.top()), f.id, lev);\n   \
    \         } else {\n                return f;\n            }\n        }\n\n  \
    \      friend ZDD operator&(ZDD f, ZDD g) {\n            if (f.is_terminal0()\
    \ or g.is_terminal0()) return terminal0();\n            if (f.is_terminal1() and\
    \ g.is_terminal1()) return terminal1();\n\n            if (f.top() < g.top())\
    \ std::swap(f, g);\n\n            using namespace internal::zdd;\n           \
    \ static std::unordered_map<std::tuple<zdd_t, zdd_t>, ZDD> cache;\n          \
    \  if (auto it = check_cache(cache, f.id, g.id); it != cache.end()) return it->second;\n\
    \            \n            ZDD res = f.top() > g.top() ? f[0] & g : create_zdd(f[0]\
    \ & g[0], f[1] & g[1], f.top());\n            return register_result(cache, res,\
    \ f.id, g.id);\n        }\n\n        friend ZDD operator+(ZDD f, ZDD g) {\n  \
    \          if (f.is_terminal0() or g.is_terminal0()) return f.id ^ g.id;\n   \
    \         if (f.is_terminal1() and g.is_terminal1()) return terminal1();\n\n \
    \           if (f.top() < g.top()) std::swap(f, g);\n\n            using namespace\
    \ internal::zdd;\n            static std::unordered_map<std::tuple<zdd_t, zdd_t>,\
    \ ZDD> cache;\n            if (auto it = check_cache(cache, f.id, g.id); it !=\
    \ cache.end()) return it->second;\n\n            ZDD res = f.top() > g.top() ?\
    \ create_zdd(f[0] + g, f[1], f.top()) : create_zdd(f[0] + g[0], f[1] + g[1], f.top());\n\
    \            return register_result(cache, res, f.id, g.id);\n        }\n\n  \
    \      friend ZDD operator-(ZDD f, ZDD g) {\n            if (g.is_terminal0())\
    \ return f;\n            if (f.is_terminal0() or (f.is_terminal1() and g.is_terminal1()))\
    \ return terminal0();\n\n            using namespace internal::zdd;\n        \
    \    static std::unordered_map<std::tuple<zdd_t, zdd_t>, ZDD> cache;\n       \
    \     if (auto it = check_cache(cache, f.id, g.id); it != cache.end()) return\
    \ it->second;\n\n            ZDD res;\n            if (f.top() > g.top()) {\n\
    \                res = create_zdd(f[0] - g, f[1], f.top());\n            } else\
    \ if (f.top() == g.top()) {\n                res = create_zdd(f[0] - g[0], f[1]\
    \ - g[1], f.top());\n            } else {\n                res = f - g[0];\n \
    \           }\n            return register_result(cache, res, f.id, g.id);\n \
    \       }\n\n        friend ZDD operator^(ZDD f, ZDD g) {\n            if (f.is_terminal0()\
    \ or g.is_terminal0()) return f.id ^ g.id;\n            if (f.id == g.id) return\
    \ terminal0();\n\n            if (f.top() < g.top()) std::swap(f, g);\n\n    \
    \        using namespace internal::zdd;\n            static std::unordered_map<std::tuple<zdd_t,\
    \ zdd_t>, ZDD> cache;\n            if (auto it = check_cache(cache, f.id, g.id);\
    \ it != cache.end()) return it->second;\n            \n            ZDD res = f.top()\
    \ > g.top() ? create_zdd(f[0] ^ g, f[1], f.top()) : create_zdd(f[0] ^ g[0], f[1]\
    \ ^ g[1], f.top());\n            return register_result(cache, res, f.id, g.id);\n\
    \        }\n\n        static ZDD restrict(ZDD f, ZDD g) {\n            if (f.is_terminal0()\
    \ or g.is_terminal0()) return terminal0();\n            if (g.is_terminal1())\
    \ return f;\n\n            using namespace internal::zdd;\n            static\
    \ std::unordered_map<std::tuple<zdd_t, zdd_t>, ZDD> cache;\n            if (auto\
    \ it = check_cache(cache, f.id, g.id); it != cache.end()) return it->second;\n\
    \n            ZDD res;\n            if (f.top() > g.top()) {\n               \
    \ res = create_zdd(restrict(f[0], g), restrict(f[1], g), f.top());\n         \
    \   } else if (f.top() == g.top()) {\n                res = create_zdd(restrict(f[0],\
    \ g[0]), restrict(f[1], g[0]) + restrict(f[1], g[1]), f.top());\n            }\
    \ else {\n                res = restrict(f, g[0]);\n            }\n          \
    \  return register_result(cache, res, f.id, g.id);\n        }\n\n        static\
    \ ZDD permit(ZDD f, ZDD g) {\n            if (f.is_terminal0() or g.is_terminal0())\
    \ return terminal0();\n            if (f.is_terminal1()) return f;\n\n       \
    \     using namespace internal::zdd;\n            static std::unordered_map<std::tuple<zdd_t,\
    \ zdd_t>, ZDD> cache;\n            if (auto it = check_cache(cache, f.id, g.id);\
    \ it != cache.end()) return it->second;\n\n            ZDD res;\n            if\
    \ (f.top() > g.top()) {\n                res = create_zdd(permit(f[0], g), terminal0(),\
    \ f.top());\n            } else if (f.top() == g.top()) {\n                res\
    \ = create_zdd(permit(f[0], g[0]) + permit(f[0], g[1]), permit(f[1], g[1]), f.top());\n\
    \            } else {\n                res = permit(f, g[0]) + permit(f, g[1]);\n\
    \            }\n            return register_result(cache, res, f.id, g.id);\n\
    \        }\n\n        template <typename T>\n        static T card(ZDD f) {\n\
    \            if (f.is_terminal0()) return 0;\n            if (f.is_terminal1())\
    \ return 1;\n\n            using namespace internal::zdd;\n            static\
    \ std::unordered_map<std::tuple<zdd_t>, T> cache;\n            if (auto it = check_cache(cache,\
    \ f.id); it != cache.end()) return it->second;\n\n            return register_result(cache,\
    \ card<T>(f[0]) + card<T>(f[1]), f.id);\n        }\n\n        static int32_t len(ZDD\
    \ f) {\n            if (f.is_terminal0()) return std::numeric_limits<int32_t>::min();\n\
    \            if (f.is_terminal1()) return 0;\n\n            using namespace internal::zdd;\n\
    \            static std::unordered_map<std::tuple<zdd_t>, int> cache;\n      \
    \      if (auto it = check_cache(cache, f.id); it != cache.end()) return it->second;\n\
    \n            return register_result(cache, std::max(len(f[0]), 1 + len(f[1])),\
    \ f.id);\n        }\n\n        static std::optional<std::vector<int32_t>> max_len_item(ZDD\
    \ f) {\n            if (f.is_terminal0()) return std::nullopt;\n            if\
    \ (f.is_terminal1()) return std::vector<int32_t>{};\n\n            using namespace\
    \ internal::zdd;\n            static std::unordered_map<std::tuple<zdd_t>, std::optional<std::vector<int32_t>>>\
    \ cache;\n            if (auto it = check_cache(cache, f.id); it != cache.end())\
    \ return it->second;\n\n            auto res0 = max_len_item(f[0]);\n        \
    \    auto res1 = max_len_item(f[1]);\n            if (res0.has_value() and res1.has_value())\
    \ {\n                res1->push_back(f.top());\n                return register_result(cache,\
    \ res0->size() > res1->size() ? res0 : res1, f.id);\n            } else if (res0.has_value())\
    \ {\n                return register_result(cache, res0, f.id);\n            }\
    \ else if (res1.has_value()) {\n                return register_result(cache,\
    \ res1, f.id);\n            } else {\n                return register_result(cache,\
    \ std::nullopt, f.id);\n            }\n        }\n\n        static int32_t size(ZDD\
    \ f) {\n            if (f.is_terminal0() or f.is_terminal1()) return 0;\n    \
    \        auto comp = [](ZDD f, ZDD g) { return f.top() < g.top(); };\n       \
    \     std::priority_queue<ZDD, std::vector<ZDD>, decltype(comp)> pq { comp };\n\
    \            std::set vis { f.id };\n            pq.push(f);\n            while\
    \ (pq.size()) {\n                ZDD g = pq.top();\n                pq.pop();\n\
    \                for (int i : { 0, 1 }) {\n                    if (g[i].is_terminal0()\
    \ or g[i].is_terminal1()) continue;\n                    if (vis.count(g[i].id))\
    \ continue;\n                    vis.insert(g[i].id);\n                    pq.push(g[i]);\n\
    \                }\n            }\n            return vis.size();\n        }\n\
    \n    private:\n        internal::zdd::zdd_t id;\n    };\n} // namespace suisen\n\
    \n\n\n#line 6 \"test/src/datastructure/ZDD/maximum_independent_set.test.cpp\"\n\
    using namespace suisen;\n\nint main() {\n    int n, m;\n    std::cin >> n >> m;\n\
    \n    std::vector<int> lvl(n);\n    for (int i = 0; i < n; ++i) {\n        lvl[i]\
    \ = ZDD::new_level();\n    }\n\n    auto F = [&](int u, int v) {\n        if (u\
    \ > v) std::swap(u, v);\n        ZDD f = ZDD::create_zdd(ZDD::create_zdd(ZDD::terminal1(),\
    \ ZDD::terminal1(), lvl[u]), ZDD::terminal1(), lvl[v]);\n        for (int i =\
    \ 0; i < n; ++i) {\n            if (i == u or i == v) continue;\n            f\
    \ = ZDD::change(f, lvl[i]) + f;\n        }\n        return f;\n    };\n\n    ZDD\
    \ U = ZDD::terminal1();\n    for (int i = 0; i < n; ++i) U = ZDD::change(U, lvl[i])\
    \ + U;\n\n    for (int i = 0; i < m; ++i) {\n        int u, v;\n        std::cin\
    \ >> u >> v;\n        auto Fuv = F(u, v);\n        U = U & Fuv;\n    }\n\n   \
    \ auto ans = *ZDD::max_len_item(U);\n\n    std::cout << ans.size() << std::endl;\n\
    \    for (int e : ans) std::cout << e - 1 << ' ';\n    std::cout << std::endl;\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/maximum_independent_set\"\
    \n\n#include <iostream>\n\n#include \"library/datastructure/ZDD.hpp\"\nusing namespace\
    \ suisen;\n\nint main() {\n    int n, m;\n    std::cin >> n >> m;\n\n    std::vector<int>\
    \ lvl(n);\n    for (int i = 0; i < n; ++i) {\n        lvl[i] = ZDD::new_level();\n\
    \    }\n\n    auto F = [&](int u, int v) {\n        if (u > v) std::swap(u, v);\n\
    \        ZDD f = ZDD::create_zdd(ZDD::create_zdd(ZDD::terminal1(), ZDD::terminal1(),\
    \ lvl[u]), ZDD::terminal1(), lvl[v]);\n        for (int i = 0; i < n; ++i) {\n\
    \            if (i == u or i == v) continue;\n            f = ZDD::change(f, lvl[i])\
    \ + f;\n        }\n        return f;\n    };\n\n    ZDD U = ZDD::terminal1();\n\
    \    for (int i = 0; i < n; ++i) U = ZDD::change(U, lvl[i]) + U;\n\n    for (int\
    \ i = 0; i < m; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n     \
    \   auto Fuv = F(u, v);\n        U = U & Fuv;\n    }\n\n    auto ans = *ZDD::max_len_item(U);\n\
    \n    std::cout << ans.size() << std::endl;\n    for (int e : ans) std::cout <<\
    \ e - 1 << ' ';\n    std::cout << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/datastructure/ZDD.hpp
  - library/util/tuple_hash.hpp
  isVerificationFile: true
  path: test/src/datastructure/ZDD/maximum_independent_set.test.cpp
  requiredBy: []
  timestamp: '2022-01-15 02:41:24+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/ZDD/maximum_independent_set.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/ZDD/maximum_independent_set.test.cpp
- /verify/test/src/datastructure/ZDD/maximum_independent_set.test.cpp.html
title: test/src/datastructure/ZDD/maximum_independent_set.test.cpp
---
