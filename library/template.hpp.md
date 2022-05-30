---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
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
    \ = typename safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line\
    \ 10 \"library/template.hpp\"\n\n// ! type aliases\nusing i128 = __int128_t;\n\
    using u128 = __uint128_t;\n\ntemplate <typename T>\nusing pq_greater = std::priority_queue<T,\
    \ std::vector<T>, std::greater<T>>;\ntemplate <typename T, typename U>\nusing\
    \ umap = std::unordered_map<T, U>;\n\n// ! macros (capital: internal macro)\n\
    #define OVERLOAD2(_1,_2,name,...) name\n#define OVERLOAD3(_1,_2,_3,name,...) name\n\
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
    \ std::begin(iterable), std::end(iterable)\n#define input(type, ...) type __VA_ARGS__;\
    \ read(__VA_ARGS__)\n\n#ifdef LOCAL\n#  define debug(...) debug_internal(#__VA_ARGS__,\
    \ __VA_ARGS__)\n\ntemplate <class T, class... Args>\nvoid debug_internal(const\
    \ char* s, T&& first, Args&&... args) {\n    constexpr const char* prefix = \"\
    [\\033[32mDEBUG\\033[m] \";\n    constexpr const char* open_brakets = sizeof...(args)\
    \ == 0 ? \"\" : \"(\";\n    constexpr const char* close_brakets = sizeof...(args)\
    \ == 0 ? \"\" : \")\";\n    std::cerr << prefix << open_brakets << s << close_brakets\
    \ << \": \" << open_brakets << std::forward<T>(first);\n    ((std::cerr << \"\
    , \" << std::forward<Args>(args)), ...);\n    std::cerr << close_brakets << \"\
    \\n\";\n}\n\n#else\n#  define debug(...) void(0)\n#endif\n\n// ! I/O utilities\n\
    \n// __int128_t\nstd::ostream& operator<<(std::ostream& dest, __int128_t value)\
    \ {\n    std::ostream::sentry s(dest);\n    if (s) {\n        __uint128_t tmp\
    \ = value < 0 ? -value : value;\n        char buffer[128];\n        char* d =\
    \ std::end(buffer);\n        do {\n            --d;\n            *d = \"0123456789\"\
    [tmp % 10];\n            tmp /= 10;\n        } while (tmp != 0);\n        if (value\
    \ < 0) {\n            --d;\n            *d = '-';\n        }\n        int len\
    \ = std::end(buffer) - d;\n        if (dest.rdbuf()->sputn(d, len) != len) {\n\
    \            dest.setstate(std::ios_base::badbit);\n        }\n    }\n    return\
    \ dest;\n}\n// __uint128_t\nstd::ostream& operator<<(std::ostream& dest, __uint128_t\
    \ value) {\n    std::ostream::sentry s(dest);\n    if (s) {\n        char buffer[128];\n\
    \        char* d = std::end(buffer);\n        do {\n            --d;\n       \
    \     *d = \"0123456789\"[value % 10];\n            value /= 10;\n        } while\
    \ (value != 0);\n        int len = std::end(buffer) - d;\n        if (dest.rdbuf()->sputn(d,\
    \ len) != len) {\n            dest.setstate(std::ios_base::badbit);\n        }\n\
    \    }\n    return dest;\n}\n\n// pair\ntemplate <typename T, typename U>\nstd::ostream&\
    \ operator<<(std::ostream& out, const std::pair<T, U>& a) {\n    return out <<\
    \ a.first << ' ' << a.second;\n}\n// tuple\ntemplate <unsigned int N = 0, typename\
    \ ...Args>\nstd::ostream& operator<<(std::ostream& out, const std::tuple<Args...>&\
    \ a) {\n    if constexpr (N >= std::tuple_size_v<std::tuple<Args...>>) {\n   \
    \     return out;\n    } else {\n        out << std::get<N>(a);\n        if constexpr\
    \ (N + 1 < std::tuple_size_v<std::tuple<Args...>>) {\n            out << ' ';\n\
    \        }\n        return operator<<<N + 1>(out, a);\n    }\n}\n// vector\ntemplate\
    \ <typename T>\nstd::ostream& operator<<(std::ostream& out, const std::vector<T>&\
    \ a) {\n    for (auto it = a.begin(); it != a.end();) {\n        out << *it;\n\
    \        if (++it != a.end()) out << ' ';\n    }\n    return out;\n}\n// array\n\
    template <typename T, size_t N>\nstd::ostream& operator<<(std::ostream& out, const\
    \ std::array<T, N>& a) {\n    for (auto it = a.begin(); it != a.end();) {\n  \
    \      out << *it;\n        if (++it != a.end()) out << ' ';\n    }\n    return\
    \ out;\n}\ninline void print() { std::cout << '\\n'; }\ntemplate <typename Head,\
    \ typename... Tail>\ninline void print(const Head& head, const Tail &...tails)\
    \ {\n    std::cout << head;\n    if (sizeof...(tails)) std::cout << ' ';\n   \
    \ print(tails...);\n}\ntemplate <typename Iterable>\nauto print_all(const Iterable&\
    \ v, std::string sep = \" \", std::string end = \"\\n\") -> decltype(std::cout\
    \ << *v.begin(), void()) {\n    for (auto it = v.begin(); it != v.end();) {\n\
    \        std::cout << *it;\n        if (++it != v.end()) std::cout << sep;\n \
    \   }\n    std::cout << end;\n}\n\n__int128_t parse_i128(std::string& s) {\n \
    \   __int128_t ret = 0;\n    for (int i = 0; i < int(s.size()); i++) if ('0' <=\
    \ s[i] and s[i] <= '9') ret = 10 * ret + s[i] - '0';\n    if (s[0] == '-') ret\
    \ = -ret;\n    return ret;\n}\n__uint128_t parse_u128(std::string& s) {\n    __uint128_t\
    \ ret = 0;\n    for (int i = 0; i < int(s.size()); i++) if ('0' <= s[i] and s[i]\
    \ <= '9') ret = 10 * ret + s[i] - '0';\n    return ret;\n}\n// __int128_t\nstd::istream&\
    \ operator>>(std::istream& in, __int128_t& v) {\n    std::string s;\n    in >>\
    \ s;\n    v = parse_i128(s);\n    return in;\n}\n// __uint128_t\nstd::istream&\
    \ operator>>(std::istream& in, __uint128_t& v) {\n    std::string s;\n    in >>\
    \ s;\n    v = parse_u128(s);\n    return in;\n}\n// pair\ntemplate <typename T,\
    \ typename U>\nstd::istream& operator>>(std::istream& in, std::pair<T, U>& a)\
    \ {\n    return in >> a.first >> a.second;\n}\n// tuple\ntemplate <unsigned int\
    \ N = 0, typename ...Args>\nstd::istream& operator>>(std::istream& in, std::tuple<Args...>&\
    \ a) {\n    if constexpr (N >= std::tuple_size_v<std::tuple<Args...>>) {\n   \
    \     return in;\n    } else {\n        return operator>><N + 1>(in >> std::get<N>(a),\
    \ a);\n    }\n}\n// vector\ntemplate <typename T>\nstd::istream& operator>>(std::istream&\
    \ in, std::vector<T>& a) {\n    for (auto it = a.begin(); it != a.end(); ++it)\
    \ in >> *it;\n    return in;\n}\n// array\ntemplate <typename T, size_t N>\nstd::istream&\
    \ operator>>(std::istream& in, std::array<T, N>& a) {\n    for (auto it = a.begin();\
    \ it != a.end(); ++it) in >> *it;\n    return in;\n}\ntemplate <typename ...Args>\n\
    void read(Args &...args) {\n    (std::cin >> ... >> args);\n}\n\n// ! integral\
    \ utilities\n\n// Returns pow(-1, n)\ntemplate <typename T>\nconstexpr inline\
    \ int pow_m1(T n) {\n    return -(n & 1) | 1;\n}\n// Returns pow(-1, n)\ntemplate\
    \ <>\nconstexpr inline int pow_m1<bool>(bool n) {\n    return -int(n) | 1;\n}\n\
    \n// Returns floor(x / y)\ntemplate <typename T>\nconstexpr inline T fld(const\
    \ T x, const T y) {\n    return (x ^ y) >= 0 ? x / y : (x - (y + pow_m1(y >= 0)))\
    \ / y;\n}\ntemplate <typename T>\nconstexpr inline T cld(const T x, const T y)\
    \ {\n    return (x ^ y) <= 0 ? x / y : (x + (y + pow_m1(y >= 0))) / y;\n}\n\n\
    template <typename T, suisen::constraints_t<suisen::is_nbit<T, 16>> = nullptr>\n\
    __attribute__((target(\"popcnt\"))) constexpr inline int popcount(const T x) {\
    \ return _mm_popcnt_u32(x); }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 32>> = nullptr>\n__attribute__((target(\"popcnt\"))) constexpr inline int popcount(const\
    \ T x) { return _mm_popcnt_u32(x); }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 64>> = nullptr>\n__attribute__((target(\"popcnt\"))) constexpr inline int popcount(const\
    \ T x) { return _mm_popcnt_u64(x); }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 16>> = nullptr>\nconstexpr inline int count_lz(const T x) { return x ? __builtin_clz(x)\
    \ : suisen::bit_num<T>; }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 32>> = nullptr>\nconstexpr inline int count_lz(const T x) { return x ? __builtin_clz(x)\
    \ : suisen::bit_num<T>; }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 64>> = nullptr>\nconstexpr inline int count_lz(const T x) { return x ? __builtin_clzll(x)\
    \ : suisen::bit_num<T>; }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 16>> = nullptr>\nconstexpr inline int count_tz(const T x) { return x ? __builtin_ctz(x)\
    \ : suisen::bit_num<T>; }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 32>> = nullptr>\nconstexpr inline int count_tz(const T x) { return x ? __builtin_ctz(x)\
    \ : suisen::bit_num<T>; }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 64>> = nullptr>\nconstexpr inline int count_tz(const T x) { return x ? __builtin_ctzll(x)\
    \ : suisen::bit_num<T>; }\ntemplate <typename T>\nconstexpr inline int floor_log2(const\
    \ T x) { return suisen::bit_num<T> -1 - count_lz(x); }\ntemplate <typename T>\n\
    constexpr inline int ceil_log2(const T x) { return floor_log2(x) + ((x & -x) !=\
    \ x); }\ntemplate <typename T>\nconstexpr inline int kth_bit(const T x, const\
    \ unsigned int k) { return (x >> k) & 1; }\ntemplate <typename T>\nconstexpr inline\
    \ int parity(const T x) { return popcount(x) & 1; }\n\n// ! container\n\ntemplate\
    \ <typename T, typename Comparator, suisen::constraints_t<suisen::is_comparator<Comparator,\
    \ T>> = nullptr>\nauto priqueue_comp(const Comparator comparator) {\n    return\
    \ std::priority_queue<T, std::vector<T>, Comparator>(comparator);\n}\n\ntemplate\
    \ <typename Iterable>\nauto isize(const Iterable& iterable) -> decltype(int(iterable.size()))\
    \ {\n    return iterable.size();\n}\n\ntemplate <typename T, typename Gen, suisen::constraints_t<suisen::is_same_as_invoke_result<T,\
    \ Gen, int>> = nullptr>\nauto generate_vector(int n, Gen generator) {\n    std::vector<T>\
    \ v(n);\n    for (int i = 0; i < n; ++i) v[i] = generator(i);\n    return v;\n\
    }\ntemplate <typename T>\nauto generate_range_vector(T l, T r) {\n    return generate_vector(r\
    \ - l, [l](int i) { return l + i; });\n}\ntemplate <typename T>\nauto generate_range_vector(T\
    \ n) {\n    return generate_range_vector(0, n);\n}\n\ntemplate <typename T>\n\
    void sort_unique_erase(std::vector<T>& a) {\n    std::sort(a.begin(), a.end());\n\
    \    a.erase(std::unique(a.begin(), a.end()), a.end());\n}\n\ntemplate <typename\
    \ InputIterator, typename BiConsumer>\nauto foreach_adjacent_values(InputIterator\
    \ first, InputIterator last, BiConsumer f) -> decltype(f(*first++, *last), void())\
    \ {\n    if (first != last) for (auto itr = first, itl = itr++; itr != last; itl\
    \ = itr++) f(*itl, *itr);\n}\ntemplate <typename Container, typename BiConsumer>\n\
    auto foreach_adjacent_values(Container c, BiConsumer f) -> decltype(c.begin(),\
    \ c.end(), void()) {\n    foreach_adjacent_values(c.begin(), c.end(), f);\n}\n\
    \n\n// ! other utilities\n\n// x <- min(x, y). returns true iff `x` has chenged.\n\
    template <typename T>\ninline bool chmin(T& x, const T& y) {\n    if (y >= x)\
    \ return false;\n    x = y;\n    return true;\n}\n// x <- max(x, y). returns true\
    \ iff `x` has chenged.\ntemplate <typename T>\ninline bool chmax(T& x, const T&\
    \ y) {\n    if (y <= x) return false;\n    x = y;\n    return true;\n}\n\ntemplate\
    \ <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n\
    std::string bin(T val, int bit_num = -1) {\n    std::string res;\n    if (bit_num\
    \ >= 0) {\n        for (int bit = bit_num; bit-- > 0;) res += '0' + ((val >> bit)\
    \ & 1);\n    } else {\n        for (; val; val >>= 1) res += '0' + (val & 1);\n\
    \        std::reverse(res.begin(), res.end());\n    }\n    return res;\n}\n\n\
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\nstd::vector<T> digits_low_to_high(T val, T base = 10) {\n    std::vector<T>\
    \ res;\n    for (; val; val /= base) res.push_back(val % base);\n    if (res.empty())\
    \ res.push_back(T{ 0 });\n    return res;\n}\ntemplate <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\nstd::vector<T> digits_high_to_low(T val, T base\
    \ = 10) {\n    auto res = digits_low_to_high(val, base);\n    std::reverse(res.begin(),\
    \ res.end());\n    return res;\n}\n\ntemplate <typename T>\nstd::string join(const\
    \ std::vector<T>& v, const std::string& sep, const std::string& end) {\n    std::ostringstream\
    \ ss;\n    for (auto it = v.begin(); it != v.end();) {\n        ss << *it;\n \
    \       if (++it != v.end()) ss << sep;\n    }\n    ss << end;\n    return ss.str();\n\
    }\n\nnamespace suisen {}\nusing namespace suisen;\nusing namespace std;\n"
  code: "#include <bits/stdc++.h>\n\n#ifdef _MSC_VER\n#  include <intrin.h>\n#else\n\
    #  include <x86intrin.h>\n#endif\n\n#include \"library/type_traits/type_traits.hpp\"\
    \n\n// ! type aliases\nusing i128 = __int128_t;\nusing u128 = __uint128_t;\n\n\
    template <typename T>\nusing pq_greater = std::priority_queue<T, std::vector<T>,\
    \ std::greater<T>>;\ntemplate <typename T, typename U>\nusing umap = std::unordered_map<T,\
    \ U>;\n\n// ! macros (capital: internal macro)\n#define OVERLOAD2(_1,_2,name,...)\
    \ name\n#define OVERLOAD3(_1,_2,_3,name,...) name\n#define OVERLOAD4(_1,_2,_3,_4,name,...)\
    \ name\n\n#define REP4(i,l,r,s)  for(std::remove_reference_t<std::remove_const_t<decltype(r)>>i=(l);i<(r);i+=(s))\n\
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
    \ std::begin(iterable), std::end(iterable)\n#define input(type, ...) type __VA_ARGS__;\
    \ read(__VA_ARGS__)\n\n#ifdef LOCAL\n#  define debug(...) debug_internal(#__VA_ARGS__,\
    \ __VA_ARGS__)\n\ntemplate <class T, class... Args>\nvoid debug_internal(const\
    \ char* s, T&& first, Args&&... args) {\n    constexpr const char* prefix = \"\
    [\\033[32mDEBUG\\033[m] \";\n    constexpr const char* open_brakets = sizeof...(args)\
    \ == 0 ? \"\" : \"(\";\n    constexpr const char* close_brakets = sizeof...(args)\
    \ == 0 ? \"\" : \")\";\n    std::cerr << prefix << open_brakets << s << close_brakets\
    \ << \": \" << open_brakets << std::forward<T>(first);\n    ((std::cerr << \"\
    , \" << std::forward<Args>(args)), ...);\n    std::cerr << close_brakets << \"\
    \\n\";\n}\n\n#else\n#  define debug(...) void(0)\n#endif\n\n// ! I/O utilities\n\
    \n// __int128_t\nstd::ostream& operator<<(std::ostream& dest, __int128_t value)\
    \ {\n    std::ostream::sentry s(dest);\n    if (s) {\n        __uint128_t tmp\
    \ = value < 0 ? -value : value;\n        char buffer[128];\n        char* d =\
    \ std::end(buffer);\n        do {\n            --d;\n            *d = \"0123456789\"\
    [tmp % 10];\n            tmp /= 10;\n        } while (tmp != 0);\n        if (value\
    \ < 0) {\n            --d;\n            *d = '-';\n        }\n        int len\
    \ = std::end(buffer) - d;\n        if (dest.rdbuf()->sputn(d, len) != len) {\n\
    \            dest.setstate(std::ios_base::badbit);\n        }\n    }\n    return\
    \ dest;\n}\n// __uint128_t\nstd::ostream& operator<<(std::ostream& dest, __uint128_t\
    \ value) {\n    std::ostream::sentry s(dest);\n    if (s) {\n        char buffer[128];\n\
    \        char* d = std::end(buffer);\n        do {\n            --d;\n       \
    \     *d = \"0123456789\"[value % 10];\n            value /= 10;\n        } while\
    \ (value != 0);\n        int len = std::end(buffer) - d;\n        if (dest.rdbuf()->sputn(d,\
    \ len) != len) {\n            dest.setstate(std::ios_base::badbit);\n        }\n\
    \    }\n    return dest;\n}\n\n// pair\ntemplate <typename T, typename U>\nstd::ostream&\
    \ operator<<(std::ostream& out, const std::pair<T, U>& a) {\n    return out <<\
    \ a.first << ' ' << a.second;\n}\n// tuple\ntemplate <unsigned int N = 0, typename\
    \ ...Args>\nstd::ostream& operator<<(std::ostream& out, const std::tuple<Args...>&\
    \ a) {\n    if constexpr (N >= std::tuple_size_v<std::tuple<Args...>>) {\n   \
    \     return out;\n    } else {\n        out << std::get<N>(a);\n        if constexpr\
    \ (N + 1 < std::tuple_size_v<std::tuple<Args...>>) {\n            out << ' ';\n\
    \        }\n        return operator<<<N + 1>(out, a);\n    }\n}\n// vector\ntemplate\
    \ <typename T>\nstd::ostream& operator<<(std::ostream& out, const std::vector<T>&\
    \ a) {\n    for (auto it = a.begin(); it != a.end();) {\n        out << *it;\n\
    \        if (++it != a.end()) out << ' ';\n    }\n    return out;\n}\n// array\n\
    template <typename T, size_t N>\nstd::ostream& operator<<(std::ostream& out, const\
    \ std::array<T, N>& a) {\n    for (auto it = a.begin(); it != a.end();) {\n  \
    \      out << *it;\n        if (++it != a.end()) out << ' ';\n    }\n    return\
    \ out;\n}\ninline void print() { std::cout << '\\n'; }\ntemplate <typename Head,\
    \ typename... Tail>\ninline void print(const Head& head, const Tail &...tails)\
    \ {\n    std::cout << head;\n    if (sizeof...(tails)) std::cout << ' ';\n   \
    \ print(tails...);\n}\ntemplate <typename Iterable>\nauto print_all(const Iterable&\
    \ v, std::string sep = \" \", std::string end = \"\\n\") -> decltype(std::cout\
    \ << *v.begin(), void()) {\n    for (auto it = v.begin(); it != v.end();) {\n\
    \        std::cout << *it;\n        if (++it != v.end()) std::cout << sep;\n \
    \   }\n    std::cout << end;\n}\n\n__int128_t parse_i128(std::string& s) {\n \
    \   __int128_t ret = 0;\n    for (int i = 0; i < int(s.size()); i++) if ('0' <=\
    \ s[i] and s[i] <= '9') ret = 10 * ret + s[i] - '0';\n    if (s[0] == '-') ret\
    \ = -ret;\n    return ret;\n}\n__uint128_t parse_u128(std::string& s) {\n    __uint128_t\
    \ ret = 0;\n    for (int i = 0; i < int(s.size()); i++) if ('0' <= s[i] and s[i]\
    \ <= '9') ret = 10 * ret + s[i] - '0';\n    return ret;\n}\n// __int128_t\nstd::istream&\
    \ operator>>(std::istream& in, __int128_t& v) {\n    std::string s;\n    in >>\
    \ s;\n    v = parse_i128(s);\n    return in;\n}\n// __uint128_t\nstd::istream&\
    \ operator>>(std::istream& in, __uint128_t& v) {\n    std::string s;\n    in >>\
    \ s;\n    v = parse_u128(s);\n    return in;\n}\n// pair\ntemplate <typename T,\
    \ typename U>\nstd::istream& operator>>(std::istream& in, std::pair<T, U>& a)\
    \ {\n    return in >> a.first >> a.second;\n}\n// tuple\ntemplate <unsigned int\
    \ N = 0, typename ...Args>\nstd::istream& operator>>(std::istream& in, std::tuple<Args...>&\
    \ a) {\n    if constexpr (N >= std::tuple_size_v<std::tuple<Args...>>) {\n   \
    \     return in;\n    } else {\n        return operator>><N + 1>(in >> std::get<N>(a),\
    \ a);\n    }\n}\n// vector\ntemplate <typename T>\nstd::istream& operator>>(std::istream&\
    \ in, std::vector<T>& a) {\n    for (auto it = a.begin(); it != a.end(); ++it)\
    \ in >> *it;\n    return in;\n}\n// array\ntemplate <typename T, size_t N>\nstd::istream&\
    \ operator>>(std::istream& in, std::array<T, N>& a) {\n    for (auto it = a.begin();\
    \ it != a.end(); ++it) in >> *it;\n    return in;\n}\ntemplate <typename ...Args>\n\
    void read(Args &...args) {\n    (std::cin >> ... >> args);\n}\n\n// ! integral\
    \ utilities\n\n// Returns pow(-1, n)\ntemplate <typename T>\nconstexpr inline\
    \ int pow_m1(T n) {\n    return -(n & 1) | 1;\n}\n// Returns pow(-1, n)\ntemplate\
    \ <>\nconstexpr inline int pow_m1<bool>(bool n) {\n    return -int(n) | 1;\n}\n\
    \n// Returns floor(x / y)\ntemplate <typename T>\nconstexpr inline T fld(const\
    \ T x, const T y) {\n    return (x ^ y) >= 0 ? x / y : (x - (y + pow_m1(y >= 0)))\
    \ / y;\n}\ntemplate <typename T>\nconstexpr inline T cld(const T x, const T y)\
    \ {\n    return (x ^ y) <= 0 ? x / y : (x + (y + pow_m1(y >= 0))) / y;\n}\n\n\
    template <typename T, suisen::constraints_t<suisen::is_nbit<T, 16>> = nullptr>\n\
    __attribute__((target(\"popcnt\"))) constexpr inline int popcount(const T x) {\
    \ return _mm_popcnt_u32(x); }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 32>> = nullptr>\n__attribute__((target(\"popcnt\"))) constexpr inline int popcount(const\
    \ T x) { return _mm_popcnt_u32(x); }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 64>> = nullptr>\n__attribute__((target(\"popcnt\"))) constexpr inline int popcount(const\
    \ T x) { return _mm_popcnt_u64(x); }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 16>> = nullptr>\nconstexpr inline int count_lz(const T x) { return x ? __builtin_clz(x)\
    \ : suisen::bit_num<T>; }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 32>> = nullptr>\nconstexpr inline int count_lz(const T x) { return x ? __builtin_clz(x)\
    \ : suisen::bit_num<T>; }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 64>> = nullptr>\nconstexpr inline int count_lz(const T x) { return x ? __builtin_clzll(x)\
    \ : suisen::bit_num<T>; }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 16>> = nullptr>\nconstexpr inline int count_tz(const T x) { return x ? __builtin_ctz(x)\
    \ : suisen::bit_num<T>; }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 32>> = nullptr>\nconstexpr inline int count_tz(const T x) { return x ? __builtin_ctz(x)\
    \ : suisen::bit_num<T>; }\ntemplate <typename T, suisen::constraints_t<suisen::is_nbit<T,\
    \ 64>> = nullptr>\nconstexpr inline int count_tz(const T x) { return x ? __builtin_ctzll(x)\
    \ : suisen::bit_num<T>; }\ntemplate <typename T>\nconstexpr inline int floor_log2(const\
    \ T x) { return suisen::bit_num<T> -1 - count_lz(x); }\ntemplate <typename T>\n\
    constexpr inline int ceil_log2(const T x) { return floor_log2(x) + ((x & -x) !=\
    \ x); }\ntemplate <typename T>\nconstexpr inline int kth_bit(const T x, const\
    \ unsigned int k) { return (x >> k) & 1; }\ntemplate <typename T>\nconstexpr inline\
    \ int parity(const T x) { return popcount(x) & 1; }\n\n// ! container\n\ntemplate\
    \ <typename T, typename Comparator, suisen::constraints_t<suisen::is_comparator<Comparator,\
    \ T>> = nullptr>\nauto priqueue_comp(const Comparator comparator) {\n    return\
    \ std::priority_queue<T, std::vector<T>, Comparator>(comparator);\n}\n\ntemplate\
    \ <typename Iterable>\nauto isize(const Iterable& iterable) -> decltype(int(iterable.size()))\
    \ {\n    return iterable.size();\n}\n\ntemplate <typename T, typename Gen, suisen::constraints_t<suisen::is_same_as_invoke_result<T,\
    \ Gen, int>> = nullptr>\nauto generate_vector(int n, Gen generator) {\n    std::vector<T>\
    \ v(n);\n    for (int i = 0; i < n; ++i) v[i] = generator(i);\n    return v;\n\
    }\ntemplate <typename T>\nauto generate_range_vector(T l, T r) {\n    return generate_vector(r\
    \ - l, [l](int i) { return l + i; });\n}\ntemplate <typename T>\nauto generate_range_vector(T\
    \ n) {\n    return generate_range_vector(0, n);\n}\n\ntemplate <typename T>\n\
    void sort_unique_erase(std::vector<T>& a) {\n    std::sort(a.begin(), a.end());\n\
    \    a.erase(std::unique(a.begin(), a.end()), a.end());\n}\n\ntemplate <typename\
    \ InputIterator, typename BiConsumer>\nauto foreach_adjacent_values(InputIterator\
    \ first, InputIterator last, BiConsumer f) -> decltype(f(*first++, *last), void())\
    \ {\n    if (first != last) for (auto itr = first, itl = itr++; itr != last; itl\
    \ = itr++) f(*itl, *itr);\n}\ntemplate <typename Container, typename BiConsumer>\n\
    auto foreach_adjacent_values(Container c, BiConsumer f) -> decltype(c.begin(),\
    \ c.end(), void()) {\n    foreach_adjacent_values(c.begin(), c.end(), f);\n}\n\
    \n\n// ! other utilities\n\n// x <- min(x, y). returns true iff `x` has chenged.\n\
    template <typename T>\ninline bool chmin(T& x, const T& y) {\n    if (y >= x)\
    \ return false;\n    x = y;\n    return true;\n}\n// x <- max(x, y). returns true\
    \ iff `x` has chenged.\ntemplate <typename T>\ninline bool chmax(T& x, const T&\
    \ y) {\n    if (y <= x) return false;\n    x = y;\n    return true;\n}\n\ntemplate\
    \ <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n\
    std::string bin(T val, int bit_num = -1) {\n    std::string res;\n    if (bit_num\
    \ >= 0) {\n        for (int bit = bit_num; bit-- > 0;) res += '0' + ((val >> bit)\
    \ & 1);\n    } else {\n        for (; val; val >>= 1) res += '0' + (val & 1);\n\
    \        std::reverse(res.begin(), res.end());\n    }\n    return res;\n}\n\n\
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\nstd::vector<T> digits_low_to_high(T val, T base = 10) {\n    std::vector<T>\
    \ res;\n    for (; val; val /= base) res.push_back(val % base);\n    if (res.empty())\
    \ res.push_back(T{ 0 });\n    return res;\n}\ntemplate <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\nstd::vector<T> digits_high_to_low(T val, T base\
    \ = 10) {\n    auto res = digits_low_to_high(val, base);\n    std::reverse(res.begin(),\
    \ res.end());\n    return res;\n}\n\ntemplate <typename T>\nstd::string join(const\
    \ std::vector<T>& v, const std::string& sep, const std::string& end) {\n    std::ostringstream\
    \ ss;\n    for (auto it = v.begin(); it != v.end();) {\n        ss << *it;\n \
    \       if (++it != v.end()) ss << sep;\n    }\n    ss << end;\n    return ss.str();\n\
    }\n\nnamespace suisen {}\nusing namespace suisen;\nusing namespace std;\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/template.hpp
  requiredBy:
  - library/template.cpp
  timestamp: '2022-05-30 16:24:36+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/template.hpp
layout: document
title: Template
---
## Template