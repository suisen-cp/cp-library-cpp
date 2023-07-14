---
data:
  _extendedDependsOn:
  - icon: ':question:'
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
    \n#include <type_traits>\n\nnamespace suisen {\ntemplate <typename ...Types>\n\
    using constraints_t = std::enable_if_t<std::conjunction_v<Types...>, std::nullptr_t>;\n\
    template <bool cond_v, typename Then, typename OrElse>\nconstexpr decltype(auto)\
    \ constexpr_if(Then&& then, OrElse&& or_else) {\n    if constexpr (cond_v) return\
    \ std::forward<Then>(then);\n    else return std::forward<OrElse>(or_else);\n\
    }\n\n// ! function\ntemplate <typename ReturnType, typename Callable, typename\
    \ ...Args>\nusing is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable,\
    \ Args...>, ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op =\
    \ is_same_as_invoke_result<T, F, T>;\ntemplate <typename F, typename T>\nusing\
    \ is_bin_op = is_same_as_invoke_result<T, F, T, T>;\n\ntemplate <typename Comparator,\
    \ typename T>\nusing is_comparator = std::is_same<std::invoke_result_t<Comparator,\
    \ T, T>, bool>;\n\n// ! integral\ntemplate <typename T, typename = constraints_t<std::is_integral<T>>>\n\
    constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\n\
    template <typename T, size_t n> struct is_nbit { static constexpr bool value =\
    \ bit_num<T> == n; };\ntemplate <typename T, size_t n> static constexpr bool is_nbit_v\
    \ = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T> struct safely_multipliable\
    \ {};\ntemplate <> struct safely_multipliable<int> { using type = long long; };\n\
    template <> struct safely_multipliable<long long> { using type = __int128_t; };\n\
    template <> struct safely_multipliable<unsigned int> { using type = unsigned long\
    \ long; };\ntemplate <> struct safely_multipliable<unsigned long int> { using\
    \ type = __uint128_t; };\ntemplate <> struct safely_multipliable<unsigned long\
    \ long> { using type = __uint128_t; };\ntemplate <> struct safely_multipliable<float>\
    \ { using type = float; };\ntemplate <> struct safely_multipliable<double> { using\
    \ type = double; };\ntemplate <> struct safely_multipliable<long double> { using\
    \ type = long double; };\ntemplate <typename T> using safely_multipliable_t =\
    \ typename safely_multipliable<T>::type;\n\ntemplate <typename T, typename = void>\
    \ struct rec_value_type { using type = T; };\ntemplate <typename T> struct rec_value_type<T,\
    \ std::void_t<typename T::value_type>> {\n    using type = typename rec_value_type<typename\
    \ T::value_type>::type;\n};\ntemplate <typename T> using rec_value_type_t = typename\
    \ rec_value_type<T>::type;\n\ntemplate <typename T> class is_iterable {\n    template\
    \ <typename T_>\n    static auto test(T_ e) -> decltype(e.begin(), e.end(), std::true_type{});\n\
    \    static std::false_type test(...);\npublic:\n    static constexpr bool value\
    \ = decltype(test(std::declval<T>()))::value;\n};\ntemplate <typename T> static\
    \ constexpr bool is_iterable_v = is_iterable<T>::value;\n\ntemplate <typename\
    \ T> class is_writable {\n    template <typename T_>\n    static auto test(T_\
    \ e) -> decltype(std::declval<std::ostream&>() << e, std::true_type{});\n    static\
    \ std::false_type test(...);\npublic:\n    static constexpr bool value = decltype(test(std::declval<T>()))::value;\n\
    };\ntemplate <typename T> static constexpr bool is_writable_v = is_writable<T>::value;\n\
    \ntemplate <typename T> class is_readable {\n    template <typename T_>\n    static\
    \ auto test(T_ e) -> decltype(std::declval<std::istream&>() >> e, std::true_type{});\n\
    \    static std::false_type test(...);\npublic:\n    static constexpr bool value\
    \ = decltype(test(std::declval<T>()))::value;\n};\ntemplate <typename T> static\
    \ constexpr bool is_readable_v = is_readable<T>::value;\n} // namespace suisen\n\
    \n\n#line 10 \"library/template.hpp\"\n\nnamespace suisen {\n    // ! type aliases\n\
    \    using int128 = __int128_t;\n    using uint128 = __uint128_t;\n\n    template\
    \ <typename T>\n    using priority_queue_greater = std::priority_queue<T, std::vector<T>,\
    \ std::greater<T>>;\n}\n\n// ! macros (internal)\n#define DETAIL_CAT_I(a, b) a##b\n\
    #define DETAIL_CAT(a, b) DETAIL_CAT_I(a, b)\n#define DETAIL_UNIQVAR(tag) DETAIL_CAT(tag,\
    \ __LINE__)\n\n// ! macros\n#define FOR(e, v) for (auto &&e : v)\n#define CFOR(e,\
    \ v) for (const auto &e : v)\n#define REP(i, ...) for (auto &&i : suisen::macro::rep_impl(__VA_ARGS__))\n\
    #define RREP(i, ...) for (auto &&i : suisen::macro::rrep_impl(__VA_ARGS__))\n\
    #define REPINF(i, ...) for (auto &&i : suisen::macro::repinf_impl(__VA_ARGS__))\n\
    #define CREP(i, ...) for (const auto &i : suisen::macro::rep_impl(__VA_ARGS__))\n\
    #define CRREP(i, ...) for (const auto &i : suisen::macro::rrep_impl(__VA_ARGS__))\n\
    #define CREPINF(i, ...) for (const auto &i : suisen::macro::repinf_impl(__VA_ARGS__))\n\
    #define LOOP(n) for ([[maybe_unused]] const auto& DETAIL_UNIQVAR(loop_variable)\
    \ : suisen::macro::rep_impl(n))\n\n#define ALL(iterable) std::begin(iterable),\
    \ std::end(iterable)\n#define INPUT(type, ...) type __VA_ARGS__; read(__VA_ARGS__)\n\
    \n// ! debug\n#ifdef LOCAL\n#  define debug(...) suisen::debug_internal(#__VA_ARGS__,\
    \ __VA_ARGS__)\n\nnamespace suisen {\n    template <class T, class... Args>\n\
    \    void debug_internal(const char* s, T&& first, Args&&... args) {\n       \
    \ constexpr const char* prefix = \"[\\033[32mDEBUG\\033[m] \";\n        constexpr\
    \ const char* open_brakets = sizeof...(args) == 0 ? \"\" : \"(\";\n        constexpr\
    \ const char* close_brakets = sizeof...(args) == 0 ? \"\" : \")\";\n        std::cerr\
    \ << prefix << open_brakets << s << close_brakets << \": \" << open_brakets <<\
    \ std::forward<T>(first);\n        ((std::cerr << \", \" << std::forward<Args>(args)),\
    \ ...);\n        std::cerr << close_brakets << \"\\n\";\n    }\n}\n\n#else\n#\
    \  define debug(...) void(0)\n#endif\n\n// ! string / container\nnamespace suisen\
    \ {\n    __int128_t stoi128(const std::string& s) {\n        __int128_t ret =\
    \ 0;\n        for (int i = 0; i < int(s.size()); i++) if ('0' <= s[i] and s[i]\
    \ <= '9') ret = 10 * ret + s[i] - '0';\n        if (s[0] == '-') ret = -ret;\n\
    \        return ret;\n    }\n    __uint128_t stou128(const std::string& s) {\n\
    \        __uint128_t ret = 0;\n        for (int i = 0; i < int(s.size()); i++)\
    \ if ('0' <= s[i] and s[i] <= '9') ret = 10 * ret + s[i] - '0';\n        return\
    \ ret;\n    }\n\n    template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\n    std::string join(const Iterable& v, const std::string&\
    \ sep, const std::string& end) {\n        std::ostringstream ss;\n        for\
    \ (auto it = v.begin(); it != v.end();) {\n            ss << *it;\n          \
    \  if (++it != v.end()) ss << sep;\n        }\n        ss << end;\n        return\
    \ ss.str();\n    }\n    template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\n    std::vector<Iterable> split(const Iterable s,\
    \ typename Iterable::value_type delim) {\n        std::vector<Iterable> res;\n\
    \        for (auto itl = std::begin(s), itr = itl;; itl = ++itr) {\n         \
    \   while (itr != std::end(s) and *itr != delim) ++itr;\n            res.emplace_back(itl,\
    \ itr);\n            if (itr == std::end(s)) return res;\n        }\n    }\n \
    \   template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\n    void concat(Iterable& s, const Iterable& t)\
    \ {\n        s.reserve(std::size(s) + std::size(t));\n        std::copy(std::begin(t),\
    \ std::end(t), std::back_inserter(s));\n    }\n    template <typename Iterable,\
    \ std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>\n\
    \    Iterable concatenated(Iterable s, const Iterable& t) { concat(s, t); return\
    \ s; }\n\n    template <typename Func, typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\n    auto mapped_vec(const Func& f, const Iterable&\
    \ s) {\n        std::vector<std::invoke_result_t<Func, typename Iterable::value_type>>\
    \ v;\n        v.reserve(std::size(s)), std::transform(std::begin(s), std::end(s),\
    \ std::back_inserter(v), f);\n        return v;\n    }\n    template <typename\
    \ T, typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t>\
    \ = nullptr>\n    auto copied_vec(const Iterable& s) {\n        std::vector<T>\
    \ v;\n        v.reserve(std::size(s)), std::copy(std::begin(s), std::end(s), std::back_inserter(v));\n\
    \        return v;\n    }\n\n    namespace charmap {\n        int fd(char c) {\
    \ return c - '0'; }\n        int fa(char c) { return c - 'a'; }\n        int fA(char\
    \ c) { return c - 'A'; }\n        int faA(char c) { return c <= 'Z' ? c - 'A'\
    \ : 26 + (c - 'a'); }\n    }\n\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    std::string bin(T val, int bit_num = -1) {\n\
    \        std::string res;\n        if (bit_num != -1) {\n            for (int\
    \ bit = bit_num; bit-- > 0;) res += '0' + ((val >> bit) & 1);\n        } else\
    \ {\n            for (; val; val >>= 1) res += '0' + (val & 1);\n            std::reverse(res.begin(),\
    \ res.end());\n        }\n        return res;\n    }\n\n    template <typename\
    \ T, typename U = int, std::enable_if_t<std::conjunction_v<std::is_integral<T>,\
    \ std::is_integral<U>>, std::nullptr_t> = nullptr>\n    std::vector<U> digits_low_to_high(T\
    \ val, U base = 10) {\n        std::vector<U> res;\n        for (; val; val /=\
    \ base) res.push_back(val % base);\n        if (res.empty()) res.push_back(T{\
    \ 0 });\n        return res;\n    }\n    template <typename T, typename U = int,\
    \ std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_integral<U>>,\
    \ std::nullptr_t> = nullptr>\n    std::vector<U> digits_high_to_low(T val, U base\
    \ = 10) {\n        auto res = digits_low_to_high(val, base);\n        std::reverse(res.begin(),\
    \ res.end());\n        return res;\n    }\n\n    template <typename T, typename\
    \ ToKey, typename CompareValue = std::less<>, std::enable_if_t<std::conjunction_v<std::is_invocable<ToKey,\
    \ T>, std::is_invocable_r<bool, CompareValue, std::invoke_result_t<ToKey, T>,\
    \ std::invoke_result_t<ToKey, T>>>, std::nullptr_t> = nullptr>\n    auto comparator(const\
    \ ToKey& to_key, const CompareValue& compare_value = std::less<>()) {\n      \
    \  return [to_key, compare_value](const T& x, const T& y) { return compare_value(to_key(x),\
    \ to_key(y)); };\n    }\n    template <typename ToKey, std::enable_if_t<std::is_invocable_v<ToKey,\
    \ int>, std::nullptr_t> = nullptr>\n    std::vector<int> sorted_indices(int n,\
    \ const ToKey& to_key) {\n        std::vector<int> p(n);\n        std::iota(p.begin(),\
    \ p.end(), 0);\n        std::sort(p.begin(), p.end(), comparator<int>(to_key));\n\
    \        return p;\n    }\n    template <typename Compare, std::enable_if_t<std::is_invocable_r_v<bool,\
    \ Compare, int, int>, std::nullptr_t> = nullptr>\n    std::vector<int> sorted_indices(int\
    \ n, const Compare& compare) {\n        std::vector<int> p(n);\n        std::iota(p.begin(),\
    \ p.end(), 0);\n        std::sort(p.begin(), p.end(), compare);\n        return\
    \ p;\n    }\n    template <typename T, typename Comparator>\n    auto priority_queue_with_comparator(const\
    \ Comparator comparator) { return std::priority_queue<T, std::vector<T>, Comparator>(comparator);\
    \ }\n    template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\n    void sort_unique_erase(Iterable& a) { std::sort(a.begin(),\
    \ a.end()), a.erase(std::unique(a.begin(), a.end()), a.end()); }\n}\n\n// ! IO\n\
    namespace suisen::io {\n    namespace details {\n        template <typename T>\n\
    \        void print_single(std::ostream&, const T&);\n\n        void print(std::ostream&\
    \ os, __int128_t value) {\n            std::ostream::sentry s(os);\n         \
    \   if (s) {\n                __uint128_t tmp = value < 0 ? -value : value;\n\
    \                char buffer[128];\n                char* d = std::end(buffer);\n\
    \                do {\n                    --d;\n                    *d = \"0123456789\"\
    [tmp % 10];\n                    tmp /= 10;\n                } while (tmp != 0);\n\
    \                if (value < 0) {\n                    --d;\n                \
    \    *d = '-';\n                }\n                int len = std::end(buffer)\
    \ - d;\n                if (os.rdbuf()->sputn(d, len) != len) {\n            \
    \        os.setstate(std::ios_base::badbit);\n                }\n            }\n\
    \        }\n        void print(std::ostream& os, __uint128_t value) {\n      \
    \      std::ostream::sentry s(os);\n            if (s) {\n                char\
    \ buffer[128];\n                char* d = std::end(buffer);\n                do\
    \ {\n                    --d;\n                    *d = \"0123456789\"[value %\
    \ 10];\n                    value /= 10;\n                } while (value != 0);\n\
    \                int len = std::end(buffer) - d;\n                if (os.rdbuf()->sputn(d,\
    \ len) != len) {\n                    os.setstate(std::ios_base::badbit);\n  \
    \              }\n            }\n        }\n\n        template <typename T, typename\
    \ U>\n        void print(std::ostream& os, const std::pair<T, U>& a) {\n     \
    \       print_single(os, a.first), print_single(os, ' '), print_single(os, a.second);\n\
    \        }\n        template <size_t N = 0, typename ...Args>\n        void print(std::ostream&\
    \ os, const std::tuple<Args...>& a) {\n            if constexpr (N == std::tuple_size_v<std::tuple<Args...>>)\
    \ return;\n            else {\n                if constexpr (N) print_single(os,\
    \ ' ');\n                print_single(os, std::get<N>(a));\n                print<N\
    \ + 1>(os, a);\n            }\n        }\n        template <typename Iterable,\n\
    \            std::enable_if_t<std::conjunction_v<suisen::is_iterable<Iterable>,\
    \ std::negation<suisen::is_writable<Iterable>>>, std::nullptr_t> = nullptr>\n\
    \        void print(std::ostream& os, const Iterable& a) {\n            for (auto\
    \ it = a.begin(); it != a.end();) {\n                print_single(os, *it);\n\
    \                if (++it != a.end()) print_single(os, ' ');\n            }\n\
    \        }\n\n        template <typename T>\n        void print_single(std::ostream&\
    \ os, const T& e) {\n            if constexpr (suisen::is_writable_v<T>) os <<\
    \ e;\n            else details::print(os, e);\n        }\n    }\n    void print()\
    \ { std::cout << '\\n'; }\n    template <typename Head, typename... Tail>\n  \
    \  void print(const Head& head, const Tail &...tails) {\n        details::print_single(std::cout,\
    \ head);\n        if constexpr (sizeof...(Tail)) details::print_single(std::cout,\
    \ ' ');\n        print(tails...);\n    }\n    template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\n    void print_all(const Iterable& v, std::string\
    \ sep = \" \", std::string end = \"\\n\") {\n        for (auto it = v.begin();\
    \ it != v.end();) {\n            details::print_single(std::cout, *it);\n    \
    \        if (++it != v.end()) details::print_single(std::cout, sep);\n       \
    \ }\n        details::print_single(std::cout, end);\n    }\n\n    namespace details\
    \ {\n        template <typename T>\n        void read_single(std::istream&, T&);\n\
    \n        void read(std::istream& is, __int128_t& v) { std::string s; is >> s;\
    \ v = stoi128(s); }\n        void read(std::istream& is, __uint128_t& v) { std::string\
    \ s; is >> s; v = stou128(s); }\n        template <typename T, typename U>\n \
    \       void read(std::istream& is, std::pair<T, U>& a) { read_single(is, a.first),\
    \ read_single(is, a.second); }\n        template <size_t N = 0, typename ...Args>\n\
    \        void read(std::istream& is, std::tuple<Args...>& a) { if constexpr (N\
    \ < sizeof...(Args)) read_single(is, std::get<N>(a)), read<N + 1>(is, a); }\n\n\
    \        template <typename Iterable,\n            std::enable_if_t<std::conjunction_v<suisen::is_iterable<Iterable>,\
    \ std::negation<suisen::is_readable<Iterable>>>, std::nullptr_t> = nullptr>\n\
    \        void read(std::istream& is, Iterable& a) { for (auto it = a.begin();\
    \ it != a.end(); ++it) read_single(is, *it); }\n\n        template <typename T>\n\
    \        void read_single(std::istream& is, T& e) {\n            if constexpr\
    \ (suisen::is_readable_v<T>) is >> e;\n            else details::read(is, e);\n\
    \        }\n\n        struct { template <typename T> operator T() const { T e;\
    \ read_single(std::cin, e); return e; } } constexpr reader;\n    }\n\n    auto\
    \ read() { return details::reader; }\n    template <typename Head, typename...\
    \ Tail>\n    void read(Head& head, Tail &...tails) {\n        details::read_single(std::cin,\
    \ head);\n        if constexpr (sizeof...(Tail)) read(tails...);\n    }\n}\nnamespace\
    \ suisen {\n    using io::print, io::print_all, io::read;\n}\n\n// ! numeric\n\
    namespace suisen {\n    // x <- min(x, y). returns true iff `x` has chenged.\n\
    \    template <typename T>\n    bool chmin(T& x, const T& y) { return y >= x ?\
    \ false : (x = y, true); }\n    // x <- max(x, y). returns true iff `x` has chenged.\n\
    \    template <typename T>\n    bool chmax(T& x, const T& y) { return y <= x ?\
    \ false : (x = y, true); }\n\n    // Returns pow(-1, n)\n    template <typename\
    \ T> constexpr int pow_m1(T n) { return -(n & 1) | 1; }\n    // Returns pow(-1,\
    \ n)\n    template <> constexpr int pow_m1<bool>(bool n) { return -int(n) | 1;\
    \ }\n\n    // Returns floor(x / y)\n    template <typename T> constexpr T fld(const\
    \ T x, const T y) {\n        T q = x / y, r = x % y;\n        return q - ((x ^\
    \ y) < 0 and (r != 0));\n    }\n    template <typename T> constexpr T cld(const\
    \ T x, const T y) {\n        T q = x / y, r = x % y;\n        return q + ((x ^\
    \ y) > 0 and (r != 0));\n    }\n}\n\n// ! bit\nnamespace suisen {\n    template\
    \ <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T, 64>>, std::nullptr_t>\
    \ = nullptr>\n    __attribute__((target(\"popcnt\"))) constexpr int popcount(const\
    \ T x) { return _mm_popcnt_u32(x); }\n    template <typename T, std::enable_if_t<suisen::is_nbit_v<T,\
    \ 64>, std::nullptr_t> = nullptr>\n    __attribute__((target(\"popcnt\"))) constexpr\
    \ int popcount(const T x) { return _mm_popcnt_u64(x); }\n    template <typename\
    \ T, std::enable_if_t<std::negation_v<suisen::is_nbit<T, 64>>, std::nullptr_t>\
    \ = nullptr>\n    constexpr int count_lz(const T x) { return x ? __builtin_clz(x)\
    \ : suisen::bit_num<T>; }\n    template <typename T, std::enable_if_t<suisen::is_nbit_v<T,\
    \ 64>, std::nullptr_t> = nullptr>\n    constexpr int count_lz(const T x) { return\
    \ x ? __builtin_clzll(x) : suisen::bit_num<T>; }\n    template <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T,\
    \ 64>>, std::nullptr_t> = nullptr>\n    constexpr int count_tz(const T x) { return\
    \ x ? __builtin_ctz(x) : suisen::bit_num<T>; }\n    template <typename T, std::enable_if_t<suisen::is_nbit_v<T,\
    \ 64>, std::nullptr_t> = nullptr>\n    constexpr int count_tz(const T x) { return\
    \ x ? __builtin_ctzll(x) : suisen::bit_num<T>; }\n    template <typename T> constexpr\
    \ int floor_log2(const T x) { return suisen::bit_num<T> -1 - count_lz(x); }\n\
    \    template <typename T> constexpr int ceil_log2(const T x) { return floor_log2(x)\
    \ + ((x & -x) != x); }\n    template <typename T> constexpr int kth_bit(const\
    \ T x, const unsigned int k) { return (x >> k) & 1; }\n    template <typename\
    \ T> constexpr int parity(const T x) { return popcount(x) & 1; }\n}\n\n// ! for\
    \ macro\nnamespace suisen::macro {\n    template <typename IntR, typename IntL\
    \ = IntR, typename IntStep = IntR>\n    struct rep_impl {\n        rep_impl(IntR\
    \ n) : rep_impl(0, n, 1) {}\n        rep_impl(IntL l, IntR r, IntStep step = 1)\
    \ : _begin(l, step), _end(r) {}\n        auto begin() const { return _begin; }\n\
    \        auto end() const { return _end; }\n    private:\n        struct iterator\
    \ {\n            IntR val, step;\n            iterator(const IntR& val, const\
    \ IntR& step) : val(val), step(step) {}\n            IntR& operator*() { return\
    \ val; }\n            bool operator!=(const IntR& endval) { return val < endval;\
    \ }\n            iterator& operator++() { return val += step, *this; }\n     \
    \   };\n        iterator _begin;\n        IntR _end;\n    };\n    template <typename\
    \ IntR, typename IntL = IntR, typename IntStep = IntR>\n    struct rrep_impl {\n\
    \        rrep_impl(IntR n) : rrep_impl(0, n, 1) {}\n        rrep_impl(IntL l,\
    \ IntR r, IntStep step = 1) : _begin(l + fld<IntR>(r - l - 1, step) * step, step),\
    \ _end(l) {}\n        auto begin() const { return _begin; }\n        auto end()\
    \ const { return _end; }\n    private:\n        struct iterator {\n          \
    \  IntR val, step;\n            iterator(const IntR& val, const IntR& step) :\
    \ val(val), step(step) {}\n            IntR& operator*() { return val; }\n   \
    \         bool operator!=(const IntR& endval) { return val >= endval; }\n    \
    \        iterator& operator++() { return val -= step, *this; }\n        };\n \
    \       iterator _begin;\n        IntR _end;\n    };\n    template <typename IntL,\
    \ typename IntStep = IntL>\n    struct repinf_impl {\n        repinf_impl(IntL\
    \ l, IntStep step = 1) : _begin(l, step) {}\n        auto begin() const { return\
    \ _begin; }\n        auto end() const { return nullptr; }\n    private:\n    \
    \    struct iterator {\n            IntL val, step;\n            iterator(const\
    \ IntL& val, const IntL& step) : val(val), step(step) {}\n            IntL& operator*()\
    \ { return val; }\n            bool operator!=(std::nullptr_t) { return true;\
    \ }\n            iterator& operator++() { return val += step, *this; }\n     \
    \   };\n        iterator _begin;\n    };\n}\n\n// ! misc\nnamespace suisen {\n\
    \    const std::string Yes = \"Yes\", No = \"No\", YES = \"YES\", NO = \"NO\"\
    ;\n}\n\nnamespace suisen {}\nusing namespace suisen;\nusing namespace std;\n"
  code: "#include <bits/stdc++.h>\n\n#ifdef _MSC_VER\n#  include <intrin.h>\n#else\n\
    #  include <x86intrin.h>\n#endif\n\n#include \"library/type_traits/type_traits.hpp\"\
    \n\nnamespace suisen {\n    // ! type aliases\n    using int128 = __int128_t;\n\
    \    using uint128 = __uint128_t;\n\n    template <typename T>\n    using priority_queue_greater\
    \ = std::priority_queue<T, std::vector<T>, std::greater<T>>;\n}\n\n// ! macros\
    \ (internal)\n#define DETAIL_CAT_I(a, b) a##b\n#define DETAIL_CAT(a, b) DETAIL_CAT_I(a,\
    \ b)\n#define DETAIL_UNIQVAR(tag) DETAIL_CAT(tag, __LINE__)\n\n// ! macros\n#define\
    \ FOR(e, v) for (auto &&e : v)\n#define CFOR(e, v) for (const auto &e : v)\n#define\
    \ REP(i, ...) for (auto &&i : suisen::macro::rep_impl(__VA_ARGS__))\n#define RREP(i,\
    \ ...) for (auto &&i : suisen::macro::rrep_impl(__VA_ARGS__))\n#define REPINF(i,\
    \ ...) for (auto &&i : suisen::macro::repinf_impl(__VA_ARGS__))\n#define CREP(i,\
    \ ...) for (const auto &i : suisen::macro::rep_impl(__VA_ARGS__))\n#define CRREP(i,\
    \ ...) for (const auto &i : suisen::macro::rrep_impl(__VA_ARGS__))\n#define CREPINF(i,\
    \ ...) for (const auto &i : suisen::macro::repinf_impl(__VA_ARGS__))\n#define\
    \ LOOP(n) for ([[maybe_unused]] const auto& DETAIL_UNIQVAR(loop_variable) : suisen::macro::rep_impl(n))\n\
    \n#define ALL(iterable) std::begin(iterable), std::end(iterable)\n#define INPUT(type,\
    \ ...) type __VA_ARGS__; read(__VA_ARGS__)\n\n// ! debug\n#ifdef LOCAL\n#  define\
    \ debug(...) suisen::debug_internal(#__VA_ARGS__, __VA_ARGS__)\n\nnamespace suisen\
    \ {\n    template <class T, class... Args>\n    void debug_internal(const char*\
    \ s, T&& first, Args&&... args) {\n        constexpr const char* prefix = \"[\\\
    033[32mDEBUG\\033[m] \";\n        constexpr const char* open_brakets = sizeof...(args)\
    \ == 0 ? \"\" : \"(\";\n        constexpr const char* close_brakets = sizeof...(args)\
    \ == 0 ? \"\" : \")\";\n        std::cerr << prefix << open_brakets << s << close_brakets\
    \ << \": \" << open_brakets << std::forward<T>(first);\n        ((std::cerr <<\
    \ \", \" << std::forward<Args>(args)), ...);\n        std::cerr << close_brakets\
    \ << \"\\n\";\n    }\n}\n\n#else\n#  define debug(...) void(0)\n#endif\n\n// !\
    \ string / container\nnamespace suisen {\n    __int128_t stoi128(const std::string&\
    \ s) {\n        __int128_t ret = 0;\n        for (int i = 0; i < int(s.size());\
    \ i++) if ('0' <= s[i] and s[i] <= '9') ret = 10 * ret + s[i] - '0';\n       \
    \ if (s[0] == '-') ret = -ret;\n        return ret;\n    }\n    __uint128_t stou128(const\
    \ std::string& s) {\n        __uint128_t ret = 0;\n        for (int i = 0; i <\
    \ int(s.size()); i++) if ('0' <= s[i] and s[i] <= '9') ret = 10 * ret + s[i] -\
    \ '0';\n        return ret;\n    }\n\n    template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\n    std::string join(const Iterable& v, const std::string&\
    \ sep, const std::string& end) {\n        std::ostringstream ss;\n        for\
    \ (auto it = v.begin(); it != v.end();) {\n            ss << *it;\n          \
    \  if (++it != v.end()) ss << sep;\n        }\n        ss << end;\n        return\
    \ ss.str();\n    }\n    template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\n    std::vector<Iterable> split(const Iterable s,\
    \ typename Iterable::value_type delim) {\n        std::vector<Iterable> res;\n\
    \        for (auto itl = std::begin(s), itr = itl;; itl = ++itr) {\n         \
    \   while (itr != std::end(s) and *itr != delim) ++itr;\n            res.emplace_back(itl,\
    \ itr);\n            if (itr == std::end(s)) return res;\n        }\n    }\n \
    \   template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\n    void concat(Iterable& s, const Iterable& t)\
    \ {\n        s.reserve(std::size(s) + std::size(t));\n        std::copy(std::begin(t),\
    \ std::end(t), std::back_inserter(s));\n    }\n    template <typename Iterable,\
    \ std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>\n\
    \    Iterable concatenated(Iterable s, const Iterable& t) { concat(s, t); return\
    \ s; }\n\n    template <typename Func, typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\n    auto mapped_vec(const Func& f, const Iterable&\
    \ s) {\n        std::vector<std::invoke_result_t<Func, typename Iterable::value_type>>\
    \ v;\n        v.reserve(std::size(s)), std::transform(std::begin(s), std::end(s),\
    \ std::back_inserter(v), f);\n        return v;\n    }\n    template <typename\
    \ T, typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t>\
    \ = nullptr>\n    auto copied_vec(const Iterable& s) {\n        std::vector<T>\
    \ v;\n        v.reserve(std::size(s)), std::copy(std::begin(s), std::end(s), std::back_inserter(v));\n\
    \        return v;\n    }\n\n    namespace charmap {\n        int fd(char c) {\
    \ return c - '0'; }\n        int fa(char c) { return c - 'a'; }\n        int fA(char\
    \ c) { return c - 'A'; }\n        int faA(char c) { return c <= 'Z' ? c - 'A'\
    \ : 26 + (c - 'a'); }\n    }\n\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    std::string bin(T val, int bit_num = -1) {\n\
    \        std::string res;\n        if (bit_num != -1) {\n            for (int\
    \ bit = bit_num; bit-- > 0;) res += '0' + ((val >> bit) & 1);\n        } else\
    \ {\n            for (; val; val >>= 1) res += '0' + (val & 1);\n            std::reverse(res.begin(),\
    \ res.end());\n        }\n        return res;\n    }\n\n    template <typename\
    \ T, typename U = int, std::enable_if_t<std::conjunction_v<std::is_integral<T>,\
    \ std::is_integral<U>>, std::nullptr_t> = nullptr>\n    std::vector<U> digits_low_to_high(T\
    \ val, U base = 10) {\n        std::vector<U> res;\n        for (; val; val /=\
    \ base) res.push_back(val % base);\n        if (res.empty()) res.push_back(T{\
    \ 0 });\n        return res;\n    }\n    template <typename T, typename U = int,\
    \ std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_integral<U>>,\
    \ std::nullptr_t> = nullptr>\n    std::vector<U> digits_high_to_low(T val, U base\
    \ = 10) {\n        auto res = digits_low_to_high(val, base);\n        std::reverse(res.begin(),\
    \ res.end());\n        return res;\n    }\n\n    template <typename T, typename\
    \ ToKey, typename CompareValue = std::less<>, std::enable_if_t<std::conjunction_v<std::is_invocable<ToKey,\
    \ T>, std::is_invocable_r<bool, CompareValue, std::invoke_result_t<ToKey, T>,\
    \ std::invoke_result_t<ToKey, T>>>, std::nullptr_t> = nullptr>\n    auto comparator(const\
    \ ToKey& to_key, const CompareValue& compare_value = std::less<>()) {\n      \
    \  return [to_key, compare_value](const T& x, const T& y) { return compare_value(to_key(x),\
    \ to_key(y)); };\n    }\n    template <typename ToKey, std::enable_if_t<std::is_invocable_v<ToKey,\
    \ int>, std::nullptr_t> = nullptr>\n    std::vector<int> sorted_indices(int n,\
    \ const ToKey& to_key) {\n        std::vector<int> p(n);\n        std::iota(p.begin(),\
    \ p.end(), 0);\n        std::sort(p.begin(), p.end(), comparator<int>(to_key));\n\
    \        return p;\n    }\n    template <typename Compare, std::enable_if_t<std::is_invocable_r_v<bool,\
    \ Compare, int, int>, std::nullptr_t> = nullptr>\n    std::vector<int> sorted_indices(int\
    \ n, const Compare& compare) {\n        std::vector<int> p(n);\n        std::iota(p.begin(),\
    \ p.end(), 0);\n        std::sort(p.begin(), p.end(), compare);\n        return\
    \ p;\n    }\n    template <typename T, typename Comparator>\n    auto priority_queue_with_comparator(const\
    \ Comparator comparator) { return std::priority_queue<T, std::vector<T>, Comparator>(comparator);\
    \ }\n    template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\n    void sort_unique_erase(Iterable& a) { std::sort(a.begin(),\
    \ a.end()), a.erase(std::unique(a.begin(), a.end()), a.end()); }\n}\n\n// ! IO\n\
    namespace suisen::io {\n    namespace details {\n        template <typename T>\n\
    \        void print_single(std::ostream&, const T&);\n\n        void print(std::ostream&\
    \ os, __int128_t value) {\n            std::ostream::sentry s(os);\n         \
    \   if (s) {\n                __uint128_t tmp = value < 0 ? -value : value;\n\
    \                char buffer[128];\n                char* d = std::end(buffer);\n\
    \                do {\n                    --d;\n                    *d = \"0123456789\"\
    [tmp % 10];\n                    tmp /= 10;\n                } while (tmp != 0);\n\
    \                if (value < 0) {\n                    --d;\n                \
    \    *d = '-';\n                }\n                int len = std::end(buffer)\
    \ - d;\n                if (os.rdbuf()->sputn(d, len) != len) {\n            \
    \        os.setstate(std::ios_base::badbit);\n                }\n            }\n\
    \        }\n        void print(std::ostream& os, __uint128_t value) {\n      \
    \      std::ostream::sentry s(os);\n            if (s) {\n                char\
    \ buffer[128];\n                char* d = std::end(buffer);\n                do\
    \ {\n                    --d;\n                    *d = \"0123456789\"[value %\
    \ 10];\n                    value /= 10;\n                } while (value != 0);\n\
    \                int len = std::end(buffer) - d;\n                if (os.rdbuf()->sputn(d,\
    \ len) != len) {\n                    os.setstate(std::ios_base::badbit);\n  \
    \              }\n            }\n        }\n\n        template <typename T, typename\
    \ U>\n        void print(std::ostream& os, const std::pair<T, U>& a) {\n     \
    \       print_single(os, a.first), print_single(os, ' '), print_single(os, a.second);\n\
    \        }\n        template <size_t N = 0, typename ...Args>\n        void print(std::ostream&\
    \ os, const std::tuple<Args...>& a) {\n            if constexpr (N == std::tuple_size_v<std::tuple<Args...>>)\
    \ return;\n            else {\n                if constexpr (N) print_single(os,\
    \ ' ');\n                print_single(os, std::get<N>(a));\n                print<N\
    \ + 1>(os, a);\n            }\n        }\n        template <typename Iterable,\n\
    \            std::enable_if_t<std::conjunction_v<suisen::is_iterable<Iterable>,\
    \ std::negation<suisen::is_writable<Iterable>>>, std::nullptr_t> = nullptr>\n\
    \        void print(std::ostream& os, const Iterable& a) {\n            for (auto\
    \ it = a.begin(); it != a.end();) {\n                print_single(os, *it);\n\
    \                if (++it != a.end()) print_single(os, ' ');\n            }\n\
    \        }\n\n        template <typename T>\n        void print_single(std::ostream&\
    \ os, const T& e) {\n            if constexpr (suisen::is_writable_v<T>) os <<\
    \ e;\n            else details::print(os, e);\n        }\n    }\n    void print()\
    \ { std::cout << '\\n'; }\n    template <typename Head, typename... Tail>\n  \
    \  void print(const Head& head, const Tail &...tails) {\n        details::print_single(std::cout,\
    \ head);\n        if constexpr (sizeof...(Tail)) details::print_single(std::cout,\
    \ ' ');\n        print(tails...);\n    }\n    template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\n    void print_all(const Iterable& v, std::string\
    \ sep = \" \", std::string end = \"\\n\") {\n        for (auto it = v.begin();\
    \ it != v.end();) {\n            details::print_single(std::cout, *it);\n    \
    \        if (++it != v.end()) details::print_single(std::cout, sep);\n       \
    \ }\n        details::print_single(std::cout, end);\n    }\n\n    namespace details\
    \ {\n        template <typename T>\n        void read_single(std::istream&, T&);\n\
    \n        void read(std::istream& is, __int128_t& v) { std::string s; is >> s;\
    \ v = stoi128(s); }\n        void read(std::istream& is, __uint128_t& v) { std::string\
    \ s; is >> s; v = stou128(s); }\n        template <typename T, typename U>\n \
    \       void read(std::istream& is, std::pair<T, U>& a) { read_single(is, a.first),\
    \ read_single(is, a.second); }\n        template <size_t N = 0, typename ...Args>\n\
    \        void read(std::istream& is, std::tuple<Args...>& a) { if constexpr (N\
    \ < sizeof...(Args)) read_single(is, std::get<N>(a)), read<N + 1>(is, a); }\n\n\
    \        template <typename Iterable,\n            std::enable_if_t<std::conjunction_v<suisen::is_iterable<Iterable>,\
    \ std::negation<suisen::is_readable<Iterable>>>, std::nullptr_t> = nullptr>\n\
    \        void read(std::istream& is, Iterable& a) { for (auto it = a.begin();\
    \ it != a.end(); ++it) read_single(is, *it); }\n\n        template <typename T>\n\
    \        void read_single(std::istream& is, T& e) {\n            if constexpr\
    \ (suisen::is_readable_v<T>) is >> e;\n            else details::read(is, e);\n\
    \        }\n\n        struct { template <typename T> operator T() const { T e;\
    \ read_single(std::cin, e); return e; } } constexpr reader;\n    }\n\n    auto\
    \ read() { return details::reader; }\n    template <typename Head, typename...\
    \ Tail>\n    void read(Head& head, Tail &...tails) {\n        details::read_single(std::cin,\
    \ head);\n        if constexpr (sizeof...(Tail)) read(tails...);\n    }\n}\nnamespace\
    \ suisen {\n    using io::print, io::print_all, io::read;\n}\n\n// ! numeric\n\
    namespace suisen {\n    // x <- min(x, y). returns true iff `x` has chenged.\n\
    \    template <typename T>\n    bool chmin(T& x, const T& y) { return y >= x ?\
    \ false : (x = y, true); }\n    // x <- max(x, y). returns true iff `x` has chenged.\n\
    \    template <typename T>\n    bool chmax(T& x, const T& y) { return y <= x ?\
    \ false : (x = y, true); }\n\n    // Returns pow(-1, n)\n    template <typename\
    \ T> constexpr int pow_m1(T n) { return -(n & 1) | 1; }\n    // Returns pow(-1,\
    \ n)\n    template <> constexpr int pow_m1<bool>(bool n) { return -int(n) | 1;\
    \ }\n\n    // Returns floor(x / y)\n    template <typename T> constexpr T fld(const\
    \ T x, const T y) {\n        T q = x / y, r = x % y;\n        return q - ((x ^\
    \ y) < 0 and (r != 0));\n    }\n    template <typename T> constexpr T cld(const\
    \ T x, const T y) {\n        T q = x / y, r = x % y;\n        return q + ((x ^\
    \ y) > 0 and (r != 0));\n    }\n}\n\n// ! bit\nnamespace suisen {\n    template\
    \ <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T, 64>>, std::nullptr_t>\
    \ = nullptr>\n    __attribute__((target(\"popcnt\"))) constexpr int popcount(const\
    \ T x) { return _mm_popcnt_u32(x); }\n    template <typename T, std::enable_if_t<suisen::is_nbit_v<T,\
    \ 64>, std::nullptr_t> = nullptr>\n    __attribute__((target(\"popcnt\"))) constexpr\
    \ int popcount(const T x) { return _mm_popcnt_u64(x); }\n    template <typename\
    \ T, std::enable_if_t<std::negation_v<suisen::is_nbit<T, 64>>, std::nullptr_t>\
    \ = nullptr>\n    constexpr int count_lz(const T x) { return x ? __builtin_clz(x)\
    \ : suisen::bit_num<T>; }\n    template <typename T, std::enable_if_t<suisen::is_nbit_v<T,\
    \ 64>, std::nullptr_t> = nullptr>\n    constexpr int count_lz(const T x) { return\
    \ x ? __builtin_clzll(x) : suisen::bit_num<T>; }\n    template <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T,\
    \ 64>>, std::nullptr_t> = nullptr>\n    constexpr int count_tz(const T x) { return\
    \ x ? __builtin_ctz(x) : suisen::bit_num<T>; }\n    template <typename T, std::enable_if_t<suisen::is_nbit_v<T,\
    \ 64>, std::nullptr_t> = nullptr>\n    constexpr int count_tz(const T x) { return\
    \ x ? __builtin_ctzll(x) : suisen::bit_num<T>; }\n    template <typename T> constexpr\
    \ int floor_log2(const T x) { return suisen::bit_num<T> -1 - count_lz(x); }\n\
    \    template <typename T> constexpr int ceil_log2(const T x) { return floor_log2(x)\
    \ + ((x & -x) != x); }\n    template <typename T> constexpr int kth_bit(const\
    \ T x, const unsigned int k) { return (x >> k) & 1; }\n    template <typename\
    \ T> constexpr int parity(const T x) { return popcount(x) & 1; }\n}\n\n// ! for\
    \ macro\nnamespace suisen::macro {\n    template <typename IntR, typename IntL\
    \ = IntR, typename IntStep = IntR>\n    struct rep_impl {\n        rep_impl(IntR\
    \ n) : rep_impl(0, n, 1) {}\n        rep_impl(IntL l, IntR r, IntStep step = 1)\
    \ : _begin(l, step), _end(r) {}\n        auto begin() const { return _begin; }\n\
    \        auto end() const { return _end; }\n    private:\n        struct iterator\
    \ {\n            IntR val, step;\n            iterator(const IntR& val, const\
    \ IntR& step) : val(val), step(step) {}\n            IntR& operator*() { return\
    \ val; }\n            bool operator!=(const IntR& endval) { return val < endval;\
    \ }\n            iterator& operator++() { return val += step, *this; }\n     \
    \   };\n        iterator _begin;\n        IntR _end;\n    };\n    template <typename\
    \ IntR, typename IntL = IntR, typename IntStep = IntR>\n    struct rrep_impl {\n\
    \        rrep_impl(IntR n) : rrep_impl(0, n, 1) {}\n        rrep_impl(IntL l,\
    \ IntR r, IntStep step = 1) : _begin(l + fld<IntR>(r - l - 1, step) * step, step),\
    \ _end(l) {}\n        auto begin() const { return _begin; }\n        auto end()\
    \ const { return _end; }\n    private:\n        struct iterator {\n          \
    \  IntR val, step;\n            iterator(const IntR& val, const IntR& step) :\
    \ val(val), step(step) {}\n            IntR& operator*() { return val; }\n   \
    \         bool operator!=(const IntR& endval) { return val >= endval; }\n    \
    \        iterator& operator++() { return val -= step, *this; }\n        };\n \
    \       iterator _begin;\n        IntR _end;\n    };\n    template <typename IntL,\
    \ typename IntStep = IntL>\n    struct repinf_impl {\n        repinf_impl(IntL\
    \ l, IntStep step = 1) : _begin(l, step) {}\n        auto begin() const { return\
    \ _begin; }\n        auto end() const { return nullptr; }\n    private:\n    \
    \    struct iterator {\n            IntL val, step;\n            iterator(const\
    \ IntL& val, const IntL& step) : val(val), step(step) {}\n            IntL& operator*()\
    \ { return val; }\n            bool operator!=(std::nullptr_t) { return true;\
    \ }\n            iterator& operator++() { return val += step, *this; }\n     \
    \   };\n        iterator _begin;\n    };\n}\n\n// ! misc\nnamespace suisen {\n\
    \    const std::string Yes = \"Yes\", No = \"No\", YES = \"YES\", NO = \"NO\"\
    ;\n}\n\nnamespace suisen {}\nusing namespace suisen;\nusing namespace std;\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/template.hpp
  requiredBy:
  - library/template.cpp
  timestamp: '2023-07-13 15:42:30+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/template.hpp
layout: document
title: Template
---
## Template