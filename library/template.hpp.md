---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/template.cpp
    title: library/template.cpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/template.hpp\"\n#include <bits/stdc++.h>\n\n#line\
    \ 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#line 5 \"library/type_traits/type_traits.hpp\"\
    \n#include <type_traits>\n\nnamespace suisen {\n// ! utility\ntemplate <typename\
    \ ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\n\n// ! function\ntemplate <typename ReturnType, typename Callable,\
    \ typename ...Args>\nusing is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable,\
    \ Args...>, ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op =\
    \ is_same_as_invoke_result<T, F, T>;\ntemplate <typename F, typename T>\nusing\
    \ is_bin_op = is_same_as_invoke_result<T, F, T, T>;\n\ntemplate <typename Comparator,\
    \ typename T>\nusing is_comparator = std::is_same<std::invoke_result_t<Comparator,\
    \ T, T>, bool>;\n\n// ! integral\ntemplate <typename T, typename = constraints_t<std::is_integral<T>>>\n\
    constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\n\
    template <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool\
    \ value = bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n} // namespace suisen\n\n\n#line 4 \"\
    library/template.hpp\"\n\n// ! type aliases\nusing i128 = __int128_t;\nusing u128\
    \ = __uint128_t;\nusing ll = long long;\nusing uint = unsigned int;\nusing ull\
    \  = unsigned long long;\n\ntemplate <typename T> using vec  = std::vector<T>;\n\
    template <typename T> using vec2 = vec<vec <T>>;\ntemplate <typename T> using\
    \ vec3 = vec<vec2<T>>;\ntemplate <typename T> using vec4 = vec<vec3<T>>;\n\ntemplate\
    \ <typename T>\nusing pq_greater = std::priority_queue<T, std::vector<T>, std::greater<T>>;\n\
    template <typename T, typename U>\nusing umap = std::unordered_map<T, U>;\n\n\
    // ! macros\n#define OVERLOAD2(_1,_2,name,...) name\n#define OVERLOAD3(_1,_2,_3,name,...)\
    \ name\n#define OVERLOAD4(_1,_2,_3,_4,name,...) name\n\n#define REP4(i,l,r,s)\
    \  for(std::remove_reference_t<std::remove_const_t<decltype(r)>>i=(l);i<(r);i+=(s))\n\
    #define REP3(i,l,r)    REP4(i,l,r,1)\n#define REP2(i,n)      REP3(i,0,n)\n#define\
    \ REPINF3(i,l,s) for(std::remove_reference_t<std::remove_const_t<decltype(l)>>i=(l);;i+=(s))\n\
    #define REPINF2(i,l)   REPINF3(i,l,1)\n#define REPINF1(i)     REPINF2(i,0)\n#define\
    \ RREP4(i,l,r,s) for(std::remove_reference_t<std::remove_const_t<decltype(r)>>i=(l)+fld((r)-(l)-1,s)*(s);i>=(l);i-=(s))\n\
    #define RREP3(i,l,r)   RREP4(i,l,r,1)\n#define RREP2(i,n)     RREP3(i,0,n)\n\n\
    #define rep(...)    OVERLOAD4(__VA_ARGS__, REP4   , REP3   , REP2   )(__VA_ARGS__)\n\
    #define rrep(...)   OVERLOAD4(__VA_ARGS__, RREP4  , RREP3  , RREP2  )(__VA_ARGS__)\n\
    #define repinf(...) OVERLOAD3(__VA_ARGS__, REPINF3, REPINF2, REPINF1)(__VA_ARGS__)\n\
    \n#define CAT_I(a, b) a##b\n#define CAT(a, b) CAT_I(a, b)\n#define UNIQVAR(tag)\
    \ CAT(tag, __LINE__)\n#define loop(n) for (std::remove_reference_t<std::remove_const_t<decltype(n)>>\
    \ UNIQVAR(loop_variable) = n; UNIQVAR(loop_variable) --> 0;)\n\n#define all(iterable)\
    \ (iterable).begin(), (iterable).end()\n#define range_iter(iterable, l, r) ((iterable).begin()\
    \ + (l)), ((iterable).begin() + (r))\n#define input(type, ...) type __VA_ARGS__;\
    \ read(__VA_ARGS__)\n\n// ! constants\nconstexpr int dx4[4] = {1, 0, -1, 0};\n\
    constexpr int dy4[4] = {0, 1, 0, -1};\n\nconstexpr int dx8[8] = {1, 1, 0, -1,\
    \ -1, -1, 0, 1};\nconstexpr int dy8[8] = {0, 1, 1, 1, 0, -1, -1, -1};\n\n// !\
    \ I/O utilities\ntemplate <typename T, typename U>\nstd::ostream& operator<<(std::ostream&\
    \ out, const std::pair<T, U> &a) { return out << a.first << ' ' << a.second; }\n\
    template <typename T>\nstd::ostream& operator<<(std::ostream& out, const std::vector<T>\
    \ &a) {\n    for (auto it = a.begin(); it != a.end();) {\n        out << *it;\n\
    \        if (++it != a.end()) out << ' ';\n    }\n    return out;\n}\ninline void\
    \ print() { std::cout << '\\n'; }\ntemplate <typename Head, typename... Tail>\n\
    inline void print(const Head& head, const Tail&... tails) {\n    std::cout <<\
    \ head;\n    if (sizeof...(tails)) std::cout << ' ';\n    print(tails...);\n}\n\
    template <typename Iterable>\nvoid print_iterable(const Iterable& v, const std::string\
    \ sep = \" \", const std::string end = \"\\n\") {\n    for (auto it = v.begin();\
    \ it != v.end();) {\n        std::cout << *it;\n        if (++it != v.end()) std::cout\
    \ << ' ';\n    }\n    std::cout << end;\n}\n\ntemplate <typename T, typename U>\n\
    std::istream& operator>>(std::istream& in, std::pair<T, U> &a) { return in >>\
    \ a.first >> a.second; }\ntemplate <typename T>\nstd::istream& operator>>(std::istream&\
    \ in, std::vector<T> &a) {\n    for (auto it = a.begin(); it != a.end(); ++it)\
    \ in >> *it;\n    return in;\n}\nconstexpr void read() {}\ntemplate <typename\
    \ Head, typename... Tail>\ninline void read(Head& head, Tail& ...tails) {\n  \
    \  std::cin >> head;\n    read(tails...);\n}\n\n// ! primitive utilities\n\ntemplate\
    \ <typename T>\nbool chmin(T &x, const T &y) {\n    if (y >= x) return false;\n\
    \    x = y;\n    return true;\n}\ntemplate <typename T>\nbool chmin(T &x, const\
    \ T &&y) {\n    if (y >= x) return false;\n    x = y;\n    return true;\n}\ntemplate\
    \ <typename T>\nbool chmax(T &x, const T &y) {\n    if (y <= x) return false;\n\
    \    x = y;\n    return true;\n}\ntemplate <typename T>\nbool chmax(T &x, const\
    \ T &&y) {\n    if (y <= x) return false;\n    x = y;\n    return true;\n}\n\n\
    template <typename T>\nconstexpr T fld(const T x, const T y) {\n    return y <\
    \ 0 ? fld(-x, -y) : (x >= 0 ? x / y : -((-x + y - 1) / y));\n}\ntemplate <typename\
    \ T>\nconstexpr T cld(const T x, const T y) {\n    return y < 0 ? cld(-x, -y)\
    \ : (x >= 0 ? (x + y - 1) / y : -(-x / y));\n}\n\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 32>> = nullptr>\nconstexpr int popcount(const T x) { return __builtin_popcount(x);\
    \ }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T, 64>> = nullptr>\n\
    constexpr int popcount(const T x) { return __builtin_popcountll(x); }\ntemplate\
    \ <typename T, suisen::constraints_t<suisen::is_nbit<T, 32>> = nullptr>\nconstexpr\
    \ int count_lz(const T x) { return x ? __builtin_clz(x)   : suisen::bit_num<T>;\
    \ }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T, 64>> = nullptr>\n\
    constexpr int count_lz(const T x) { return x ? __builtin_clzll(x) : suisen::bit_num<T>;\
    \ }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T, 32>> = nullptr>\n\
    constexpr int count_tz(const T x) { return x ? __builtin_ctz(x)   : suisen::bit_num<T>;\
    \ }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T, 64>> = nullptr>\n\
    constexpr int count_tz(const T x) { return x ? __builtin_ctzll(x) : suisen::bit_num<T>;\
    \ }\ntemplate <typename T>\nconstexpr int floor_log2(const T x) { return suisen::bit_num<T>\
    \ - 1 - count_lz(x); }\ntemplate <typename T>\nconstexpr int ceil_log2(const T\
    \ x)  { return floor_log2(x) + ((x & -x) != x); }\ntemplate <typename T>\nconstexpr\
    \ int kth_bit(const T x, const unsigned int k) { return (x >> k) & 1; }\ntemplate\
    \ <typename T>\nconstexpr int parity(const T x) { return popcount(x) & 1; }\n\n\
    // ! container\n\ntemplate <typename T, typename Comparator, suisen::constraints_t<suisen::is_comparator<Comparator,\
    \ T>> = nullptr>\nauto priqueue_comp(const Comparator comparator) {\n    return\
    \ std::priority_queue<T, std::vector<T>, Comparator>(comparator);\n}\n\ntemplate\
    \ <typename Iterable>\nauto isize(const Iterable &iterable) -> decltype(int(iterable.size()))\
    \ { return iterable.size(); }\n\nnamespace suisen {}\nusing namespace suisen;\n\
    using namespace std;\n"
  code: "#include <bits/stdc++.h>\n\n#include \"library/type_traits/type_traits.hpp\"\
    \n\n// ! type aliases\nusing i128 = __int128_t;\nusing u128 = __uint128_t;\nusing\
    \ ll = long long;\nusing uint = unsigned int;\nusing ull  = unsigned long long;\n\
    \ntemplate <typename T> using vec  = std::vector<T>;\ntemplate <typename T> using\
    \ vec2 = vec<vec <T>>;\ntemplate <typename T> using vec3 = vec<vec2<T>>;\ntemplate\
    \ <typename T> using vec4 = vec<vec3<T>>;\n\ntemplate <typename T>\nusing pq_greater\
    \ = std::priority_queue<T, std::vector<T>, std::greater<T>>;\ntemplate <typename\
    \ T, typename U>\nusing umap = std::unordered_map<T, U>;\n\n// ! macros\n#define\
    \ OVERLOAD2(_1,_2,name,...) name\n#define OVERLOAD3(_1,_2,_3,name,...) name\n\
    #define OVERLOAD4(_1,_2,_3,_4,name,...) name\n\n#define REP4(i,l,r,s)  for(std::remove_reference_t<std::remove_const_t<decltype(r)>>i=(l);i<(r);i+=(s))\n\
    #define REP3(i,l,r)    REP4(i,l,r,1)\n#define REP2(i,n)      REP3(i,0,n)\n#define\
    \ REPINF3(i,l,s) for(std::remove_reference_t<std::remove_const_t<decltype(l)>>i=(l);;i+=(s))\n\
    #define REPINF2(i,l)   REPINF3(i,l,1)\n#define REPINF1(i)     REPINF2(i,0)\n#define\
    \ RREP4(i,l,r,s) for(std::remove_reference_t<std::remove_const_t<decltype(r)>>i=(l)+fld((r)-(l)-1,s)*(s);i>=(l);i-=(s))\n\
    #define RREP3(i,l,r)   RREP4(i,l,r,1)\n#define RREP2(i,n)     RREP3(i,0,n)\n\n\
    #define rep(...)    OVERLOAD4(__VA_ARGS__, REP4   , REP3   , REP2   )(__VA_ARGS__)\n\
    #define rrep(...)   OVERLOAD4(__VA_ARGS__, RREP4  , RREP3  , RREP2  )(__VA_ARGS__)\n\
    #define repinf(...) OVERLOAD3(__VA_ARGS__, REPINF3, REPINF2, REPINF1)(__VA_ARGS__)\n\
    \n#define CAT_I(a, b) a##b\n#define CAT(a, b) CAT_I(a, b)\n#define UNIQVAR(tag)\
    \ CAT(tag, __LINE__)\n#define loop(n) for (std::remove_reference_t<std::remove_const_t<decltype(n)>>\
    \ UNIQVAR(loop_variable) = n; UNIQVAR(loop_variable) --> 0;)\n\n#define all(iterable)\
    \ (iterable).begin(), (iterable).end()\n#define range_iter(iterable, l, r) ((iterable).begin()\
    \ + (l)), ((iterable).begin() + (r))\n#define input(type, ...) type __VA_ARGS__;\
    \ read(__VA_ARGS__)\n\n// ! constants\nconstexpr int dx4[4] = {1, 0, -1, 0};\n\
    constexpr int dy4[4] = {0, 1, 0, -1};\n\nconstexpr int dx8[8] = {1, 1, 0, -1,\
    \ -1, -1, 0, 1};\nconstexpr int dy8[8] = {0, 1, 1, 1, 0, -1, -1, -1};\n\n// !\
    \ I/O utilities\ntemplate <typename T, typename U>\nstd::ostream& operator<<(std::ostream&\
    \ out, const std::pair<T, U> &a) { return out << a.first << ' ' << a.second; }\n\
    template <typename T>\nstd::ostream& operator<<(std::ostream& out, const std::vector<T>\
    \ &a) {\n    for (auto it = a.begin(); it != a.end();) {\n        out << *it;\n\
    \        if (++it != a.end()) out << ' ';\n    }\n    return out;\n}\ninline void\
    \ print() { std::cout << '\\n'; }\ntemplate <typename Head, typename... Tail>\n\
    inline void print(const Head& head, const Tail&... tails) {\n    std::cout <<\
    \ head;\n    if (sizeof...(tails)) std::cout << ' ';\n    print(tails...);\n}\n\
    template <typename Iterable>\nvoid print_iterable(const Iterable& v, const std::string\
    \ sep = \" \", const std::string end = \"\\n\") {\n    for (auto it = v.begin();\
    \ it != v.end();) {\n        std::cout << *it;\n        if (++it != v.end()) std::cout\
    \ << ' ';\n    }\n    std::cout << end;\n}\n\ntemplate <typename T, typename U>\n\
    std::istream& operator>>(std::istream& in, std::pair<T, U> &a) { return in >>\
    \ a.first >> a.second; }\ntemplate <typename T>\nstd::istream& operator>>(std::istream&\
    \ in, std::vector<T> &a) {\n    for (auto it = a.begin(); it != a.end(); ++it)\
    \ in >> *it;\n    return in;\n}\nconstexpr void read() {}\ntemplate <typename\
    \ Head, typename... Tail>\ninline void read(Head& head, Tail& ...tails) {\n  \
    \  std::cin >> head;\n    read(tails...);\n}\n\n// ! primitive utilities\n\ntemplate\
    \ <typename T>\nbool chmin(T &x, const T &y) {\n    if (y >= x) return false;\n\
    \    x = y;\n    return true;\n}\ntemplate <typename T>\nbool chmin(T &x, const\
    \ T &&y) {\n    if (y >= x) return false;\n    x = y;\n    return true;\n}\ntemplate\
    \ <typename T>\nbool chmax(T &x, const T &y) {\n    if (y <= x) return false;\n\
    \    x = y;\n    return true;\n}\ntemplate <typename T>\nbool chmax(T &x, const\
    \ T &&y) {\n    if (y <= x) return false;\n    x = y;\n    return true;\n}\n\n\
    template <typename T>\nconstexpr T fld(const T x, const T y) {\n    return y <\
    \ 0 ? fld(-x, -y) : (x >= 0 ? x / y : -((-x + y - 1) / y));\n}\ntemplate <typename\
    \ T>\nconstexpr T cld(const T x, const T y) {\n    return y < 0 ? cld(-x, -y)\
    \ : (x >= 0 ? (x + y - 1) / y : -(-x / y));\n}\n\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 32>> = nullptr>\nconstexpr int popcount(const T x) { return __builtin_popcount(x);\
    \ }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T, 64>> = nullptr>\n\
    constexpr int popcount(const T x) { return __builtin_popcountll(x); }\ntemplate\
    \ <typename T, suisen::constraints_t<suisen::is_nbit<T, 32>> = nullptr>\nconstexpr\
    \ int count_lz(const T x) { return x ? __builtin_clz(x)   : suisen::bit_num<T>;\
    \ }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T, 64>> = nullptr>\n\
    constexpr int count_lz(const T x) { return x ? __builtin_clzll(x) : suisen::bit_num<T>;\
    \ }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T, 32>> = nullptr>\n\
    constexpr int count_tz(const T x) { return x ? __builtin_ctz(x)   : suisen::bit_num<T>;\
    \ }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T, 64>> = nullptr>\n\
    constexpr int count_tz(const T x) { return x ? __builtin_ctzll(x) : suisen::bit_num<T>;\
    \ }\ntemplate <typename T>\nconstexpr int floor_log2(const T x) { return suisen::bit_num<T>\
    \ - 1 - count_lz(x); }\ntemplate <typename T>\nconstexpr int ceil_log2(const T\
    \ x)  { return floor_log2(x) + ((x & -x) != x); }\ntemplate <typename T>\nconstexpr\
    \ int kth_bit(const T x, const unsigned int k) { return (x >> k) & 1; }\ntemplate\
    \ <typename T>\nconstexpr int parity(const T x) { return popcount(x) & 1; }\n\n\
    // ! container\n\ntemplate <typename T, typename Comparator, suisen::constraints_t<suisen::is_comparator<Comparator,\
    \ T>> = nullptr>\nauto priqueue_comp(const Comparator comparator) {\n    return\
    \ std::priority_queue<T, std::vector<T>, Comparator>(comparator);\n}\n\ntemplate\
    \ <typename Iterable>\nauto isize(const Iterable &iterable) -> decltype(int(iterable.size()))\
    \ { return iterable.size(); }\n\nnamespace suisen {}\nusing namespace suisen;\n\
    using namespace std;\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/template.hpp
  requiredBy:
  - library/template.cpp
  timestamp: '2021-07-20 14:25:15+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/template.hpp
layout: document
redirect_from:
- /library/library/template.hpp
- /library/library/template.hpp.html
title: library/template.hpp
---
