---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: library/io/input_stream.hpp
    title: library/io/input_stream.hpp
  - icon: ':warning:'
    path: library/io/output_stream.hpp
    title: library/io/output_stream.hpp
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
  bundledCode: "#line 1 \"library/template.hpp\"\n#include <bits/stdc++.h>\nnamespace\
    \ suisen {\n    template <class T> bool chmin(T& x, const T& y) { return y >=\
    \ x ? false : (x = y, true); }\n    template <class T> bool chmax(T& x, const\
    \ T& y) { return y <= x ? false : (x = y, true); }\n    template <class T> constexpr\
    \ int pow_m1(T n) { return -(n & 1) | 1; }\n    template <class T> constexpr T\
    \ fld(const T x, const T y) { T q = x / y, r = x % y; return q - ((x ^ y) < 0\
    \ and (r != 0)); }\n    template <class T> constexpr T cld(const T x, const T\
    \ y) { T q = x / y, r = x % y; return q + ((x ^ y) > 0 and (r != 0)); }\n}\nnamespace\
    \ suisen::macro {\n#define IMPL_REPITER(cond) auto& begin() { return *this; }\
    \ auto end() { return nullptr; } auto& operator*() { return _val; } auto& operator++()\
    \ { return _val += _step, *this; } bool operator!=(std::nullptr_t) { return cond;\
    \ }\n    template <class Int, class IntL = Int, class IntStep = Int, std::enable_if_t<(std::is_signed_v<Int>\
    \ == std::is_signed_v<IntL>), std::nullptr_t> = nullptr> struct rep_impl {\n \
    \       Int _val; const Int _end, _step;\n        rep_impl(Int n) : rep_impl(0,\
    \ n) {}\n        rep_impl(IntL l, Int r, IntStep step = 1) : _val(l), _end(r),\
    \ _step(step) {}\n        IMPL_REPITER((_val < _end))\n    };\n    template <class\
    \ Int, class IntL = Int, class IntStep = Int, std::enable_if_t<(std::is_signed_v<Int>\
    \ == std::is_signed_v<IntL>), std::nullptr_t> = nullptr> struct rrep_impl {\n\
    \        Int _val; const Int _end, _step;\n        rrep_impl(Int n) : rrep_impl(0,\
    \ n) {}\n        rrep_impl(IntL l, Int r) : _val(r - 1), _end(l), _step(-1) {}\n\
    \        rrep_impl(IntL l, Int r, IntStep step) : _val(l + fld<Int>(r - l - 1,\
    \ step) * step), _end(l), _step(-step) {}\n        IMPL_REPITER((_val >= _end))\n\
    \    };\n    template <class Int, class IntStep = Int> struct repinf_impl {\n\
    \        Int _val; const Int _step;\n        repinf_impl(Int l, IntStep step =\
    \ 1) : _val(l), _step(step) {}\n        IMPL_REPITER((true))\n    };\n#undef IMPL_REPITER\n\
    }\n#line 1 \"library/io/input_stream.hpp\"\n\n\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#line 5 \"library/type_traits/type_traits.hpp\"\n#include <type_traits>\n\
    namespace suisen {\n    template <typename ...Constraints> using constraints_t\
    \ = std::enable_if_t<std::conjunction_v<Constraints...>, std::nullptr_t>;\n\n\
    \    template <typename T, typename = std::nullptr_t> struct bitnum { static constexpr\
    \ int value = 0; };\n    template <typename T> struct bitnum<T, constraints_t<std::is_integral<T>>>\
    \ { static constexpr int value = std::numeric_limits<std::make_unsigned_t<T>>::digits;\
    \ };\n    template <typename T> static constexpr int bitnum_v = bitnum<T>::value;\n\
    \    template <typename T, size_t n> struct is_nbit { static constexpr bool value\
    \ = bitnum_v<T> == n; };\n    template <typename T, size_t n> static constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n    template <typename T, typename\
    \ = std::nullptr_t> struct safely_multipliable { using type = T; };\n    template\
    \ <typename T> struct safely_multipliable<T, constraints_t<std::is_signed<T>,\
    \ is_nbit<T, 32>>> { using type = long long; };\n    template <typename T> struct\
    \ safely_multipliable<T, constraints_t<std::is_signed<T>, is_nbit<T, 64>>> { using\
    \ type = __int128_t; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_unsigned<T>, is_nbit<T, 32>>> { using type = unsigned\
    \ long long; };\n    template <typename T> struct safely_multipliable<T, constraints_t<std::is_unsigned<T>,\
    \ is_nbit<T, 64>>> { using type = __uint128_t; };\n    template <typename T> using\
    \ safely_multipliable_t = typename safely_multipliable<T>::type;\n\n    template\
    \ <typename T, typename = void> struct rec_value_type { using type = T; };\n \
    \   template <typename T> struct rec_value_type<T, std::void_t<typename T::value_type>>\
    \ {\n        using type = typename rec_value_type<typename T::value_type>::type;\n\
    \    };\n    template <typename T> using rec_value_type_t = typename rec_value_type<T>::type;\n\
    \n    template <typename T> class is_iterable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(e.begin(), e.end(), std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_iterable_v = is_iterable<T>::value;\n\
    \    template <typename T> class is_writable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(std::declval<std::ostream&>() << e, std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_writable_v = is_writable<T>::value;\n\
    \    template <typename T> class is_readable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(std::declval<std::istream&>() >> e, std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_readable_v = is_readable<T>::value;\n\
    } // namespace suisen\n\n#line 6 \"library/io/input_stream.hpp\"\nnamespace suisen::io\
    \ {\n    template <typename IStream, std::enable_if_t<std::conjunction_v<std::is_base_of<std::istream,\
    \ std::remove_reference_t<IStream>>, std::negation<std::is_const<std::remove_reference_t<IStream>>>>,\
    \ std::nullptr_t> = nullptr>\n    struct InputStream {\n    private:\n       \
    \ using istream_type = std::remove_reference_t<IStream>;\n        IStream is;\n\
    \        struct { InputStream* is; template <typename T> operator T() { T e; *is\
    \ >> e; return e; } } _reader{ this };\n    public:\n        template <typename\
    \ IStream_> InputStream(IStream_ &&is) : is(std::move(is)) {}\n        template\
    \ <typename IStream_> InputStream(IStream_ &is) : is(is) {}\n        template\
    \ <typename T> InputStream& operator>>(T& e) {\n            if constexpr (suisen::is_readable_v<T>)\
    \ is >> e; else _read(e);\n            return *this;\n        }\n        auto\
    \ read() { return _reader; }\n        template <typename Head, typename... Tail>\n\
    \        void read(Head& head, Tail &...tails) { ((*this >> head) >> ... >> tails);\
    \ }\n        istream_type& get_stream() { return is; }\n    private:\n       \
    \ static __uint128_t _stou128(const std::string& s) {\n            __uint128_t\
    \ ret = 0;\n            for (char c : s) if ('0' <= c and c <= '9') ret = 10 *\
    \ ret + c - '0';\n            return ret;\n        }\n        static __int128_t\
    \ _stoi128(const std::string& s) { return (s[0] == '-' ? -1 : +1) * _stou128(s);\
    \ }\n\n        void _read(__uint128_t& v) { v = _stou128(std::string(_reader));\
    \ }\n        void _read(__int128_t& v) { v = _stoi128(std::string(_reader)); }\n\
    \        template <typename T, typename U>\n        void _read(std::pair<T, U>&\
    \ a) { *this >> a.first >> a.second; }\n        template <size_t N = 0, typename\
    \ ...Args>\n        void _read(std::tuple<Args...>& a) { if constexpr (N < sizeof...(Args))\
    \ *this >> std::get<N>(a), _read<N + 1>(a); }\n        template <typename Iterable,\
    \ std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>\n\
    \        void _read(Iterable& a) { for (auto& e : a) *this >> e; }\n    };\n \
    \   template <typename IStream>\n    InputStream(IStream &&) -> InputStream<IStream>;\n\
    \    template <typename IStream>\n    InputStream(IStream &) -> InputStream<IStream&>;\n\
    \n    InputStream cin{ std::cin };\n\n    auto read() { return cin.read(); }\n\
    \    template <typename Head, typename... Tail>\n    void read(Head& head, Tail\
    \ &...tails) { cin.read(head, tails...); }\n} // namespace suisen::io\nnamespace\
    \ suisen { using io::read; } // namespace suisen\n\n#line 1 \"library/io/output_stream.hpp\"\
    \n\n\n\n#line 6 \"library/io/output_stream.hpp\"\nnamespace suisen::io {\n   \
    \ template <typename OStream, std::enable_if_t<std::conjunction_v<std::is_base_of<std::ostream,\
    \ std::remove_reference_t<OStream>>, std::negation<std::is_const<std::remove_reference_t<OStream>>>>,\
    \ std::nullptr_t> = nullptr>\n    struct OutputStream {\n    private:\n      \
    \  using ostream_type = std::remove_reference_t<OStream>;\n        OStream os;\n\
    \    public:\n        template <typename OStream_> OutputStream(OStream_ &&os)\
    \ : os(std::move(os)) {}\n        template <typename OStream_> OutputStream(OStream_\
    \ &os) : os(os) {}\n        template <typename T> OutputStream& operator<<(const\
    \ T& e) {\n            if constexpr (suisen::is_writable_v<T>) os << e; else _print(e);\n\
    \            return *this;\n        }\n        void print() { *this << '\\n';\
    \ }\n        template <typename Head, typename... Tail>\n        void print(const\
    \ Head& head, const Tail &...tails) { *this << head, ((*this << ' ' << tails),\
    \ ...), *this << '\\n'; }\n        template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\n        void print_all(const Iterable& v, std::string\
    \ sep = \" \", std::string end = \"\\n\") {\n            for (auto it = v.begin();\
    \ it != v.end();) if (*this << *it; ++it != v.end()) *this << sep;\n         \
    \   *this << end;\n        }\n        ostream_type& get_stream() { return os;\
    \ }\n    private:\n        void _print(__uint128_t value) {\n            char\
    \ buffer[41], *d = std::end(buffer);\n            do *--d = '0' + (value % 10),\
    \ value /= 10; while (value);\n            os.rdbuf()->sputn(d, std::end(buffer)\
    \ - d);\n        }\n        void _print(__int128_t value) {\n            if (value\
    \ < 0) *this << '-';\n            _print(__uint128_t(value < 0 ? -value : value));\n\
    \        }\n        template <typename T, typename U>\n        void _print(const\
    \ std::pair<T, U>& a) { *this << a.first << ' ' << a.second; }\n        template\
    \ <size_t N = 0, typename ...Args>\n        void _print(const std::tuple<Args...>&\
    \ a) {\n            if constexpr (N < std::tuple_size_v<std::tuple<Args...>>)\
    \ {\n                if constexpr (N) *this << ' ';\n                *this <<\
    \ std::get<N>(a), _print<N + 1>(a);\n            }\n        }\n        template\
    \ <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t>\
    \ = nullptr>\n        void _print(const Iterable& a) { print_all(a, \" \", \"\"\
    ); }\n    };\n    template <typename OStream_>\n    OutputStream(OStream_ &&)\
    \ -> OutputStream<OStream_>;\n    template <typename OStream_>\n    OutputStream(OStream_\
    \ &) -> OutputStream<OStream_&>;\n\n    OutputStream cout{ std::cout }, cerr{\
    \ std::cerr };\n\n    template <typename... Args>\n    void print(const Args &...\
    \ args) { cout.print(args...); }\n    template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\n    void print_all(const Iterable& v, const std::string&\
    \ sep = \" \", const std::string& end = \"\\n\") { cout.print_all(v, sep, end);\
    \ }\n} // namespace suisen::io\nnamespace suisen { using io::print, io::print_all;\
    \ } // namespace suisen\n\n#line 33 \"library/template.hpp\"\n\nnamespace suisen\
    \ {\n    template <class T, class ToKey, class CompKey = std::less<>, std::enable_if_t<std::conjunction_v<std::is_invocable<ToKey,\
    \ T>, std::is_invocable_r<bool, CompKey, std::invoke_result_t<ToKey, T>, std::invoke_result_t<ToKey,\
    \ T>>>, std::nullptr_t> = nullptr>\n    auto comparator(const ToKey& to_key, const\
    \ CompKey& comp_key = std::less<>()) {\n        return [=](const T& x, const T&\
    \ y) { return comp_key(to_key(x), to_key(y)); };\n    }\n    template <class Compare,\
    \ std::enable_if_t<std::is_invocable_r_v<bool, Compare, int, int>, std::nullptr_t>\
    \ = nullptr>\n    std::vector<int> sorted_indices(int n, const Compare& compare)\
    \ {\n        std::vector<int> p(n);\n        return std::iota(p.begin(), p.end(),\
    \ 0), std::sort(p.begin(), p.end(), compare), p;\n    }\n    template <class ToKey,\
    \ std::enable_if_t<std::is_invocable_v<ToKey, int>, std::nullptr_t> = nullptr>\n\
    \    std::vector<int> sorted_indices(int n, const ToKey& to_key) { return sorted_indices(n,\
    \ comparator<int>(to_key)); }\n    template <class T, class Comparator>\n    auto\
    \ priority_queue_with_comparator(const Comparator& comparator) { return std::priority_queue<T,\
    \ std::vector<T>, Comparator>{ comparator }; }\n    template <class Iterable,\
    \ std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>\n\
    \    void sort_unique_erase(Iterable& a) { std::sort(a.begin(), a.end()), a.erase(std::unique(a.begin(),\
    \ a.end()), a.end()); }\n\n    template <size_t D> struct Dim : std::array<int,\
    \ D> {\n        template <typename ...Ints> Dim(const Ints& ...ns) : std::array<int,\
    \ D>::array{ static_cast<int>(ns)... } {}\n    };\n    template <typename ...Ints>\
    \ Dim(const Ints& ...) -> Dim<sizeof...(Ints)>;\n    template <class T, size_t\
    \ D, size_t I = 0>\n    auto ndvec(const Dim<D> &ns, const T& value = {}) {\n\
    \        if constexpr (I + 1 < D) {\n            return std::vector(ns[I], ndvec<T,\
    \ D, I + 1>(ns, value));\n        } else {\n            return std::vector<T>(ns[I],\
    \ value);\n        }\n    }\n}\nnamespace suisen {\n    using int128 = __int128_t;\n\
    \    using uint128 = __uint128_t;\n    template <class T> using min_priority_queue\
    \ = std::priority_queue<T, std::vector<T>, std::greater<T>>;\n    template <class\
    \ T> using max_priority_queue = std::priority_queue<T, std::vector<T>, std::less<T>>;\n\
    }\nnamespace suisen { const std::string Yes = \"Yes\", No = \"No\", YES = \"YES\"\
    , NO = \"NO\"; }\n\n#ifdef LOCAL\n#  define debug(...) debug_impl(#__VA_ARGS__,\
    \ __VA_ARGS__)\ntemplate <class H, class... Ts> void debug_impl(const char* s,\
    \ const H& h, const Ts&... t) {\n    suisen::io::cerr << \"[\\033[32mDEBUG\\033[m]\
    \ \" << s << \": \" << h, ((suisen::io::cerr << \", \" << t), ..., (suisen::io::cerr\
    \ << \"\\n\"));\n}\n#else\n#  define debug(...) void(0)\n#endif\n#define FOR(e,\
    \ v) for (auto &&e : v)\n#define CFOR(e, v) for (const auto &e : v)\n#define REP(i,\
    \ ...) CFOR(i, suisen::macro::rep_impl(__VA_ARGS__))\n#define RREP(i, ...) CFOR(i,\
    \ suisen::macro::rrep_impl(__VA_ARGS__))\n#define REPINF(i, ...) CFOR(i, suisen::macro::repinf_impl(__VA_ARGS__))\n\
    #define LOOP(n) for ([[maybe_unused]] const auto& _ : suisen::macro::rep_impl(n))\n\
    #define ALL(iterable) std::begin(iterable), std::end(iterable)\n"
  code: "#include <bits/stdc++.h>\nnamespace suisen {\n    template <class T> bool\
    \ chmin(T& x, const T& y) { return y >= x ? false : (x = y, true); }\n    template\
    \ <class T> bool chmax(T& x, const T& y) { return y <= x ? false : (x = y, true);\
    \ }\n    template <class T> constexpr int pow_m1(T n) { return -(n & 1) | 1; }\n\
    \    template <class T> constexpr T fld(const T x, const T y) { T q = x / y, r\
    \ = x % y; return q - ((x ^ y) < 0 and (r != 0)); }\n    template <class T> constexpr\
    \ T cld(const T x, const T y) { T q = x / y, r = x % y; return q + ((x ^ y) >\
    \ 0 and (r != 0)); }\n}\nnamespace suisen::macro {\n#define IMPL_REPITER(cond)\
    \ auto& begin() { return *this; } auto end() { return nullptr; } auto& operator*()\
    \ { return _val; } auto& operator++() { return _val += _step, *this; } bool operator!=(std::nullptr_t)\
    \ { return cond; }\n    template <class Int, class IntL = Int, class IntStep =\
    \ Int, std::enable_if_t<(std::is_signed_v<Int> == std::is_signed_v<IntL>), std::nullptr_t>\
    \ = nullptr> struct rep_impl {\n        Int _val; const Int _end, _step;\n   \
    \     rep_impl(Int n) : rep_impl(0, n) {}\n        rep_impl(IntL l, Int r, IntStep\
    \ step = 1) : _val(l), _end(r), _step(step) {}\n        IMPL_REPITER((_val < _end))\n\
    \    };\n    template <class Int, class IntL = Int, class IntStep = Int, std::enable_if_t<(std::is_signed_v<Int>\
    \ == std::is_signed_v<IntL>), std::nullptr_t> = nullptr> struct rrep_impl {\n\
    \        Int _val; const Int _end, _step;\n        rrep_impl(Int n) : rrep_impl(0,\
    \ n) {}\n        rrep_impl(IntL l, Int r) : _val(r - 1), _end(l), _step(-1) {}\n\
    \        rrep_impl(IntL l, Int r, IntStep step) : _val(l + fld<Int>(r - l - 1,\
    \ step) * step), _end(l), _step(-step) {}\n        IMPL_REPITER((_val >= _end))\n\
    \    };\n    template <class Int, class IntStep = Int> struct repinf_impl {\n\
    \        Int _val; const Int _step;\n        repinf_impl(Int l, IntStep step =\
    \ 1) : _val(l), _step(step) {}\n        IMPL_REPITER((true))\n    };\n#undef IMPL_REPITER\n\
    }\n#include \"library/io/input_stream.hpp\"\n#include \"library/io/output_stream.hpp\"\
    \n\nnamespace suisen {\n    template <class T, class ToKey, class CompKey = std::less<>,\
    \ std::enable_if_t<std::conjunction_v<std::is_invocable<ToKey, T>, std::is_invocable_r<bool,\
    \ CompKey, std::invoke_result_t<ToKey, T>, std::invoke_result_t<ToKey, T>>>, std::nullptr_t>\
    \ = nullptr>\n    auto comparator(const ToKey& to_key, const CompKey& comp_key\
    \ = std::less<>()) {\n        return [=](const T& x, const T& y) { return comp_key(to_key(x),\
    \ to_key(y)); };\n    }\n    template <class Compare, std::enable_if_t<std::is_invocable_r_v<bool,\
    \ Compare, int, int>, std::nullptr_t> = nullptr>\n    std::vector<int> sorted_indices(int\
    \ n, const Compare& compare) {\n        std::vector<int> p(n);\n        return\
    \ std::iota(p.begin(), p.end(), 0), std::sort(p.begin(), p.end(), compare), p;\n\
    \    }\n    template <class ToKey, std::enable_if_t<std::is_invocable_v<ToKey,\
    \ int>, std::nullptr_t> = nullptr>\n    std::vector<int> sorted_indices(int n,\
    \ const ToKey& to_key) { return sorted_indices(n, comparator<int>(to_key)); }\n\
    \    template <class T, class Comparator>\n    auto priority_queue_with_comparator(const\
    \ Comparator& comparator) { return std::priority_queue<T, std::vector<T>, Comparator>{\
    \ comparator }; }\n    template <class Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\n    void sort_unique_erase(Iterable& a) { std::sort(a.begin(),\
    \ a.end()), a.erase(std::unique(a.begin(), a.end()), a.end()); }\n\n    template\
    \ <size_t D> struct Dim : std::array<int, D> {\n        template <typename ...Ints>\
    \ Dim(const Ints& ...ns) : std::array<int, D>::array{ static_cast<int>(ns)...\
    \ } {}\n    };\n    template <typename ...Ints> Dim(const Ints& ...) -> Dim<sizeof...(Ints)>;\n\
    \    template <class T, size_t D, size_t I = 0>\n    auto ndvec(const Dim<D> &ns,\
    \ const T& value = {}) {\n        if constexpr (I + 1 < D) {\n            return\
    \ std::vector(ns[I], ndvec<T, D, I + 1>(ns, value));\n        } else {\n     \
    \       return std::vector<T>(ns[I], value);\n        }\n    }\n}\nnamespace suisen\
    \ {\n    using int128 = __int128_t;\n    using uint128 = __uint128_t;\n    template\
    \ <class T> using min_priority_queue = std::priority_queue<T, std::vector<T>,\
    \ std::greater<T>>;\n    template <class T> using max_priority_queue = std::priority_queue<T,\
    \ std::vector<T>, std::less<T>>;\n}\nnamespace suisen { const std::string Yes\
    \ = \"Yes\", No = \"No\", YES = \"YES\", NO = \"NO\"; }\n\n#ifdef LOCAL\n#  define\
    \ debug(...) debug_impl(#__VA_ARGS__, __VA_ARGS__)\ntemplate <class H, class...\
    \ Ts> void debug_impl(const char* s, const H& h, const Ts&... t) {\n    suisen::io::cerr\
    \ << \"[\\033[32mDEBUG\\033[m] \" << s << \": \" << h, ((suisen::io::cerr << \"\
    , \" << t), ..., (suisen::io::cerr << \"\\n\"));\n}\n#else\n#  define debug(...)\
    \ void(0)\n#endif\n#define FOR(e, v) for (auto &&e : v)\n#define CFOR(e, v) for\
    \ (const auto &e : v)\n#define REP(i, ...) CFOR(i, suisen::macro::rep_impl(__VA_ARGS__))\n\
    #define RREP(i, ...) CFOR(i, suisen::macro::rrep_impl(__VA_ARGS__))\n#define REPINF(i,\
    \ ...) CFOR(i, suisen::macro::repinf_impl(__VA_ARGS__))\n#define LOOP(n) for ([[maybe_unused]]\
    \ const auto& _ : suisen::macro::rep_impl(n))\n#define ALL(iterable) std::begin(iterable),\
    \ std::end(iterable)"
  dependsOn:
  - library/io/input_stream.hpp
  - library/type_traits/type_traits.hpp
  - library/io/output_stream.hpp
  isVerificationFile: false
  path: library/template.hpp
  requiredBy:
  - library/template.cpp
  timestamp: '2023-09-06 20:34:22+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/template.hpp
layout: document
title: Template
---
## Template