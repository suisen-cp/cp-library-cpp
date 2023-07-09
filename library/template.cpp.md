---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: library/template.hpp
    title: Template
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/template.hpp\"\n#include <bits/stdc++.h>\n\n#ifdef\
    \ _MSC_VER\n#  include <intrin.h>\n#else\n#  include <x86intrin.h>\n#endif\n\n\
    #line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#line 5 \"library/type_traits/type_traits.hpp\"\
    \n#include <type_traits>\n\nnamespace suisen {\n// ! utility\ntemplate <typename\
    \ ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\ntemplate <bool cond_v, typename Then, typename OrElse>\nconstexpr\
    \ decltype(auto) constexpr_if(Then&& then, OrElse&& or_else) {\n    if constexpr\
    \ (cond_v) {\n        return std::forward<Then>(then);\n    } else {\n       \
    \ return std::forward<OrElse>(or_else);\n    }\n}\n\n// ! function\ntemplate <typename\
    \ ReturnType, typename Callable, typename ...Args>\nusing is_same_as_invoke_result\
    \ = std::is_same<std::invoke_result_t<Callable, Args...>, ReturnType>;\ntemplate\
    \ <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T, F, T>;\n\
    template <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
    \ F, T, T>;\n\ntemplate <typename Comparator, typename T>\nusing is_comparator\
    \ = std::is_same<std::invoke_result_t<Comparator, T, T>, bool>;\n\n// ! integral\n\
    template <typename T, typename = constraints_t<std::is_integral<T>>>\nconstexpr\
    \ int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\ntemplate\
    \ <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool value =\
    \ bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T>\nstruct\
    \ safely_multipliable {};\ntemplate <>\nstruct safely_multipliable<int> { using\
    \ type = long long; };\ntemplate <>\nstruct safely_multipliable<long long> { using\
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned int>\
    \ { using type = unsigned long long; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long int> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long long> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<float>\
    \ { using type = float; };\ntemplate <>\nstruct safely_multipliable<double> {\
    \ using type = double; };\ntemplate <>\nstruct safely_multipliable<long double>\
    \ { using type = long double; };\ntemplate <typename T>\nusing safely_multipliable_t\
    \ = typename safely_multipliable<T>::type;\n\ntemplate <typename T, typename =\
    \ void>\nstruct rec_value_type {\n    using type = T;\n};\ntemplate <typename\
    \ T>\nstruct rec_value_type<T, std::void_t<typename T::value_type>> {\n    using\
    \ type = typename rec_value_type<typename T::value_type>::type;\n};\ntemplate\
    \ <typename T>\nusing rec_value_type_t = typename rec_value_type<T>::type;\n\n\
    } // namespace suisen\n\n\n#line 10 \"library/template.hpp\"\n\n// ! type aliases\n\
    using i128 = __int128_t;\nusing u128 = __uint128_t;\n\ntemplate <typename T>\n\
    using pq_greater = std::priority_queue<T, std::vector<T>, std::greater<T>>;\n\n\
    // ! macros (internal)\n#define DETAIL_OVERLOAD2(_1,_2,name,...) name\n#define\
    \ DETAIL_OVERLOAD3(_1,_2,_3,name,...) name\n#define DETAIL_OVERLOAD4(_1,_2,_3,_4,name,...)\
    \ name\n\n#define DETAIL_REP4(i,l,r,s)  for(std::remove_reference_t<std::remove_const_t<decltype(r)>>i=(l);i<(r);i+=(s))\n\
    #define DETAIL_REP3(i,l,r)    DETAIL_REP4(i,l,r,1)\n#define DETAIL_REP2(i,n) \
    \     DETAIL_REP3(i,0,n)\n#define DETAIL_REPINF3(i,l,s) for(std::remove_reference_t<std::remove_const_t<decltype(l)>>i=(l);;i+=(s))\n\
    #define DETAIL_REPINF2(i,l)   DETAIL_REPINF3(i,l,1)\n#define DETAIL_REPINF1(i)\
    \     DETAIL_REPINF2(i,0)\n#define DETAIL_RREP4(i,l,r,s) for(std::remove_reference_t<std::remove_const_t<decltype(r)>>i=(l)+fld((r)-(l)-1,s)*(s);i>=(l);i-=(s))\n\
    #define DETAIL_RREP3(i,l,r)   DETAIL_RREP4(i,l,r,1)\n#define DETAIL_RREP2(i,n)\
    \     DETAIL_RREP3(i,0,n)\n\n#define DETAIL_CAT_I(a, b) a##b\n#define DETAIL_CAT(a,\
    \ b) DETAIL_CAT_I(a, b)\n#define DETAIL_UNIQVAR(tag) DETAIL_CAT(tag, __LINE__)\n\
    \n// ! macros\n#define REP(...)    DETAIL_OVERLOAD4(__VA_ARGS__, DETAIL_REP4 \
    \  , DETAIL_REP3   , DETAIL_REP2   )(__VA_ARGS__)\n#define RREP(...)   DETAIL_OVERLOAD4(__VA_ARGS__,\
    \ DETAIL_RREP4  , DETAIL_RREP3  , DETAIL_RREP2  )(__VA_ARGS__)\n#define REPINF(...)\
    \ DETAIL_OVERLOAD3(__VA_ARGS__, DETAIL_REPINF3, DETAIL_REPINF2, DETAIL_REPINF1)(__VA_ARGS__)\n\
    \n#define LOOP(n) for (std::remove_reference_t<std::remove_const_t<decltype(n)>>\
    \ DETAIL_UNIQVAR(loop_variable) = n; DETAIL_UNIQVAR(loop_variable) --> 0;)\n\n\
    #define ALL(iterable) std::begin(iterable), std::end(iterable)\n#define INPUT(type,\
    \ ...) type __VA_ARGS__; read(__VA_ARGS__)\n\n// ! debug\n\n#ifdef LOCAL\n#  define\
    \ debug(...) debug_internal(#__VA_ARGS__, __VA_ARGS__)\n\ntemplate <class T, class...\
    \ Args>\nvoid debug_internal(const char* s, T&& first, Args&&... args) {\n   \
    \ constexpr const char* prefix = \"[\\033[32mDEBUG\\033[m] \";\n    constexpr\
    \ const char* open_brakets = sizeof...(args) == 0 ? \"\" : \"(\";\n    constexpr\
    \ const char* close_brakets = sizeof...(args) == 0 ? \"\" : \")\";\n    std::cerr\
    \ << prefix << open_brakets << s << close_brakets << \": \" << open_brakets <<\
    \ std::forward<T>(first);\n    ((std::cerr << \", \" << std::forward<Args>(args)),\
    \ ...);\n    std::cerr << close_brakets << \"\\n\";\n}\n\n#else\n#  define debug(...)\
    \ void(0)\n#endif\n\n// ! I/O utilities\n\n// __int128_t\nstd::ostream& operator<<(std::ostream&\
    \ dest, __int128_t value) {\n    std::ostream::sentry s(dest);\n    if (s) {\n\
    \        __uint128_t tmp = value < 0 ? -value : value;\n        char buffer[128];\n\
    \        char* d = std::end(buffer);\n        do {\n            --d;\n       \
    \     *d = \"0123456789\"[tmp % 10];\n            tmp /= 10;\n        } while\
    \ (tmp != 0);\n        if (value < 0) {\n            --d;\n            *d = '-';\n\
    \        }\n        int len = std::end(buffer) - d;\n        if (dest.rdbuf()->sputn(d,\
    \ len) != len) {\n            dest.setstate(std::ios_base::badbit);\n        }\n\
    \    }\n    return dest;\n}\n// __uint128_t\nstd::ostream& operator<<(std::ostream&\
    \ dest, __uint128_t value) {\n    std::ostream::sentry s(dest);\n    if (s) {\n\
    \        char buffer[128];\n        char* d = std::end(buffer);\n        do {\n\
    \            --d;\n            *d = \"0123456789\"[value % 10];\n            value\
    \ /= 10;\n        } while (value != 0);\n        int len = std::end(buffer) -\
    \ d;\n        if (dest.rdbuf()->sputn(d, len) != len) {\n            dest.setstate(std::ios_base::badbit);\n\
    \        }\n    }\n    return dest;\n}\n\n// pair\ntemplate <typename T, typename\
    \ U>\nstd::ostream& operator<<(std::ostream& out, const std::pair<T, U>& a) {\n\
    \    return out << a.first << ' ' << a.second;\n}\n// tuple\ntemplate <unsigned\
    \ int N = 0, typename ...Args>\nstd::ostream& operator<<(std::ostream& out, const\
    \ std::tuple<Args...>& a) {\n    if constexpr (N >= std::tuple_size_v<std::tuple<Args...>>)\
    \ return out;\n    else {\n        out << std::get<N>(a);\n        if constexpr\
    \ (N + 1 < std::tuple_size_v<std::tuple<Args...>>) out << ' ';\n        return\
    \ operator<<<N + 1>(out, a);\n    }\n}\n// vector\ntemplate <typename T>\nstd::ostream&\
    \ operator<<(std::ostream& out, const std::vector<T>& a) {\n    for (auto it =\
    \ a.begin(); it != a.end();) {\n        out << *it;\n        if (++it != a.end())\
    \ out << ' ';\n    }\n    return out;\n}\n// array\ntemplate <typename T, size_t\
    \ N>\nstd::ostream& operator<<(std::ostream& out, const std::array<T, N>& a) {\n\
    \    for (auto it = a.begin(); it != a.end();) {\n        out << *it;\n      \
    \  if (++it != a.end()) out << ' ';\n    }\n    return out;\n}\ninline void print()\
    \ { std::cout << '\\n'; }\ntemplate <typename Head, typename... Tail>\ninline\
    \ void print(const Head& head, const Tail &...tails) {\n    std::cout << head;\n\
    \    if (sizeof...(tails)) std::cout << ' ';\n    print(tails...);\n}\ntemplate\
    \ <typename Iterable>\nauto print_all(const Iterable& v, std::string sep = \"\
    \ \", std::string end = \"\\n\") -> decltype(std::cout << *v.begin(), void())\
    \ {\n    for (auto it = v.begin(); it != v.end();) {\n        std::cout << *it;\n\
    \        if (++it != v.end()) std::cout << sep;\n    }\n    std::cout << end;\n\
    }\n\n__int128_t stoi128(const std::string& s) {\n    __int128_t ret = 0;\n   \
    \ for (int i = 0; i < int(s.size()); i++) if ('0' <= s[i] and s[i] <= '9') ret\
    \ = 10 * ret + s[i] - '0';\n    if (s[0] == '-') ret = -ret;\n    return ret;\n\
    }\n__uint128_t stou128(const std::string& s) {\n    __uint128_t ret = 0;\n   \
    \ for (int i = 0; i < int(s.size()); i++) if ('0' <= s[i] and s[i] <= '9') ret\
    \ = 10 * ret + s[i] - '0';\n    return ret;\n}\n// __int128_t\nstd::istream& operator>>(std::istream&\
    \ in, __int128_t& v) {\n    std::string s;\n    in >> s;\n    v = stoi128(s);\n\
    \    return in;\n}\n// __uint128_t\nstd::istream& operator>>(std::istream& in,\
    \ __uint128_t& v) {\n    std::string s;\n    in >> s;\n    v = stou128(s);\n \
    \   return in;\n}\n// pair\ntemplate <typename T, typename U>\nstd::istream& operator>>(std::istream&\
    \ in, std::pair<T, U>& a) {\n    return in >> a.first >> a.second;\n}\n// tuple\n\
    template <unsigned int N = 0, typename ...Args>\nstd::istream& operator>>(std::istream&\
    \ in, std::tuple<Args...>& a) {\n    if constexpr (N >= std::tuple_size_v<std::tuple<Args...>>)\
    \ return in;\n    else return operator>><N + 1>(in >> std::get<N>(a), a);\n}\n\
    // vector\ntemplate <typename T>\nstd::istream& operator>>(std::istream& in, std::vector<T>&\
    \ a) {\n    for (auto it = a.begin(); it != a.end(); ++it) in >> *it;\n    return\
    \ in;\n}\n// array\ntemplate <typename T, size_t N>\nstd::istream& operator>>(std::istream&\
    \ in, std::array<T, N>& a) {\n    for (auto it = a.begin(); it != a.end(); ++it)\
    \ in >> *it;\n    return in;\n}\ntemplate <typename ...Args>\nvoid read(Args &...args)\
    \ {\n    (std::cin >> ... >> args);\n}\n\n// ! integral utilities\n\n// Returns\
    \ pow(-1, n)\ntemplate <typename T> constexpr inline int pow_m1(T n) {\n    return\
    \ -(n & 1) | 1;\n}\n// Returns pow(-1, n)\ntemplate <> constexpr inline int pow_m1<bool>(bool\
    \ n) {\n    return -int(n) | 1;\n}\n\n// Returns floor(x / y)\ntemplate <typename\
    \ T> constexpr inline T fld(const T x, const T y) {\n    return (x ^ y) >= 0 ?\
    \ x / y : (x - (y + pow_m1(y >= 0))) / y;\n}\ntemplate <typename T> constexpr\
    \ inline T cld(const T x, const T y) {\n    return (x ^ y) <= 0 ? x / y : (x +\
    \ (y + pow_m1(y >= 0))) / y;\n}\n\ntemplate <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T,\
    \ 64>>, std::nullptr_t> = nullptr>\n__attribute__((target(\"popcnt\"))) constexpr\
    \ inline int popcount(const T x) { return _mm_popcnt_u32(x); }\ntemplate <typename\
    \ T, std::enable_if_t<suisen::is_nbit_v<T, 64>, std::nullptr_t> = nullptr>\n__attribute__((target(\"\
    popcnt\"))) constexpr inline int popcount(const T x) { return _mm_popcnt_u64(x);\
    \ }\ntemplate <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T,\
    \ 64>>, std::nullptr_t> = nullptr>\nconstexpr inline int count_lz(const T x) {\
    \ return x ? __builtin_clz(x) : suisen::bit_num<T>; }\ntemplate <typename T, std::enable_if_t<suisen::is_nbit_v<T,\
    \ 64>, std::nullptr_t> = nullptr>\nconstexpr inline int count_lz(const T x) {\
    \ return x ? __builtin_clzll(x) : suisen::bit_num<T>; }\ntemplate <typename T,\
    \ std::enable_if_t<std::negation_v<suisen::is_nbit<T, 64>>, std::nullptr_t> =\
    \ nullptr>\nconstexpr inline int count_tz(const T x) { return x ? __builtin_ctz(x)\
    \ : suisen::bit_num<T>; }\ntemplate <typename T, std::enable_if_t<suisen::is_nbit_v<T,\
    \ 64>, std::nullptr_t> = nullptr>\nconstexpr inline int count_tz(const T x) {\
    \ return x ? __builtin_ctzll(x) : suisen::bit_num<T>; }\ntemplate <typename T>\
    \ constexpr inline int floor_log2(const T x) { return suisen::bit_num<T> - 1 -\
    \ count_lz(x); }\ntemplate <typename T> constexpr inline int ceil_log2(const T\
    \ x) { return floor_log2(x) + ((x & -x) != x); }\ntemplate <typename T> constexpr\
    \ inline int kth_bit(const T x, const unsigned int k) { return (x >> k) & 1; }\n\
    template <typename T> constexpr inline int parity(const T x) { return popcount(x)\
    \ & 1; }\n\n// ! container\n\ntemplate <typename T, typename Comparator>\nauto\
    \ priqueue_comp(const Comparator comparator) {\n    return std::priority_queue<T,\
    \ std::vector<T>, Comparator>(comparator);\n}\n\ntemplate <typename Container>\n\
    void sort_unique_erase(Container& a) {\n    std::sort(a.begin(), a.end());\n \
    \   a.erase(std::unique(a.begin(), a.end()), a.end());\n}\n\ntemplate <typename\
    \ InputIterator, typename BiConsumer>\nauto foreach_adjacent_values(InputIterator\
    \ first, InputIterator last, BiConsumer f) -> decltype(f(*first++, *last), void())\
    \ {\n    if (first != last) for (auto itr = first, itl = itr++; itr != last; itl\
    \ = itr++) f(*itl, *itr);\n}\ntemplate <typename Container, typename BiConsumer>\n\
    auto foreach_adjacent_values(Container &&c, BiConsumer f) -> decltype(c.begin(),\
    \ c.end(), void()) {\n    foreach_adjacent_values(c.begin(), c.end(), f);\n}\n\
    \n\n// ! other utilities\n\n// x <- min(x, y). returns true iff `x` has chenged.\n\
    template <typename T>\ninline bool chmin(T& x, const T& y) {\n    return y >=\
    \ x ? false : (x = y, true);\n}\n// x <- max(x, y). returns true iff `x` has chenged.\n\
    template <typename T>\ninline bool chmax(T& x, const T& y) {\n    return y <=\
    \ x ? false : (x = y, true);\n}\n\ntemplate <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\nstd::string bin(T val, int bit_num = -1) {\n   \
    \ std::string res;\n    if (bit_num != -1) {\n        for (int bit = bit_num;\
    \ bit-- > 0;) res += '0' + ((val >> bit) & 1);\n    } else {\n        for (; val;\
    \ val >>= 1) res += '0' + (val & 1);\n        std::reverse(res.begin(), res.end());\n\
    \    }\n    return res;\n}\n\ntemplate <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\nstd::vector<T> digits_low_to_high(T val, T base\
    \ = 10) {\n    std::vector<T> res;\n    for (; val; val /= base) res.push_back(val\
    \ % base);\n    if (res.empty()) res.push_back(T{ 0 });\n    return res;\n}\n\
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\nstd::vector<T> digits_high_to_low(T val, T base = 10) {\n    auto\
    \ res = digits_low_to_high(val, base);\n    std::reverse(res.begin(), res.end());\n\
    \    return res;\n}\n\ntemplate <typename T>\nstd::string join(const std::vector<T>&\
    \ v, const std::string& sep, const std::string& end) {\n    std::ostringstream\
    \ ss;\n    for (auto it = v.begin(); it != v.end();) {\n        ss << *it;\n \
    \       if (++it != v.end()) ss << sep;\n    }\n    ss << end;\n    return ss.str();\n\
    }\n\ntemplate <typename Func, typename Seq>\nauto transform_to_vector(const Func\
    \ &f, const Seq &s) {\n    std::vector<std::invoke_result_t<Func, typename Seq::value_type>>\
    \ v;\n    v.reserve(std::size(s)), std::transform(std::begin(s), std::end(s),\
    \ std::back_inserter(v), f);\n    return v;\n}\ntemplate <typename T, typename\
    \ Seq>\nauto copy_to_vector(const Seq &s) {\n    std::vector<T> v;\n    v.reserve(std::size(s)),\
    \ std::copy(std::begin(s), std::end(s), std::back_inserter(v));\n    return v;\n\
    }\ntemplate <typename Seq>\nSeq concat(Seq s, const Seq &t) {\n    s.reserve(std::size(s)\
    \ + std::size(t));\n    std::copy(std::begin(t), std::end(t), std::back_inserter(s));\n\
    \    return s;\n}\ntemplate <typename Seq>\nstd::vector<Seq> split(const Seq s,\
    \ typename Seq::value_type delim) {\n    std::vector<Seq> res;\n    for (auto\
    \ itl = std::begin(s), itr = itl;; itl = ++itr) {\n        while (itr != std::end(s)\
    \ and *itr != delim) ++itr;\n        res.emplace_back(itl, itr);\n        if (itr\
    \ == std::end(s)) return res;\n    }\n}\n\nint digit_to_int(char c) { return c\
    \ - '0'; }\nint lowercase_to_int(char c) { return c - 'a'; }\nint uppercase_to_int(char\
    \ c) { return c - 'A'; }\n\nstd::vector<int> digit_str_to_ints(const std::string\
    \ &s) {\n    return transform_to_vector(digit_to_int, s);\n}\nstd::vector<int>\
    \ lowercase_str_to_ints(const std::string &s) {\n    return transform_to_vector(lowercase_to_int,\
    \ s);\n}\nstd::vector<int> uppercase_str_to_ints(const std::string &s) {\n   \
    \ return transform_to_vector(uppercase_to_int, s);\n}\n\ntemplate <typename T,\
    \ typename ToKey, typename CompareValue = std::less<>,\n    std::enable_if_t<\n\
    \        std::conjunction_v<\n            std::is_invocable<ToKey, T>,\n     \
    \       std::is_invocable_r<bool, CompareValue, std::invoke_result_t<ToKey, T>,\
    \ std::invoke_result_t<ToKey, T>\n        >\n    >, std::nullptr_t> = nullptr\n\
    >\nauto comparator(const ToKey &to_key, const CompareValue &compare_value = std::less<>())\
    \ {\n    return [to_key, compare_value](const T& x, const T& y) { return compare_value(to_key(x),\
    \ to_key(y)); };\n}\n\ntemplate <typename ToKey, std::enable_if_t<std::is_invocable_v<ToKey,\
    \ int>, std::nullptr_t> = nullptr>\nstd::vector<int> sorted_indices(int n, const\
    \ ToKey &to_key) {\n    std::vector<int> p(n);\n    std::iota(p.begin(), p.end(),\
    \ 0);\n    std::sort(p.begin(), p.end(), comparator<int>(to_key));\n    return\
    \ p;\n}\ntemplate <typename Compare, std::enable_if_t<std::is_invocable_r_v<bool,\
    \ Compare, int, int>, std::nullptr_t> = nullptr>\nstd::vector<int> sorted_indices(int\
    \ n, const Compare &compare) {\n    std::vector<int> p(n);\n    std::iota(p.begin(),\
    \ p.end(), 0);\n    std::sort(p.begin(), p.end(), compare);\n    return p;\n}\n\
    \nconst std::string Yes = \"Yes\", No = \"No\", YES = \"YES\", NO = \"NO\";\n\n\
    namespace suisen {}\nusing namespace suisen;\nusing namespace std;\n#line 2 \"\
    library/template.cpp\"\n\nstruct io_setup {\n    io_setup(int precision = 20)\
    \ {\n        std::ios::sync_with_stdio(false);\n        std::cin.tie(nullptr);\n\
    \        std::cout << std::fixed << std::setprecision(precision);\n    }\n} io_setup_\
    \ {};\n\n// ! code from here\n\nint main() {\n    \n    return 0;\n}\n"
  code: "#include \"library/template.hpp\"\n\nstruct io_setup {\n    io_setup(int\
    \ precision = 20) {\n        std::ios::sync_with_stdio(false);\n        std::cin.tie(nullptr);\n\
    \        std::cout << std::fixed << std::setprecision(precision);\n    }\n} io_setup_\
    \ {};\n\n// ! code from here\n\nint main() {\n    \n    return 0;\n}"
  dependsOn:
  - library/template.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/template.cpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/template.cpp
layout: document
redirect_from:
- /library/library/template.cpp
- /library/library/template.cpp.html
title: library/template.cpp
---
