---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: library/io/input_stream.hpp
    title: library/io/input_stream.hpp
  - icon: ':warning:'
    path: library/io/output_stream.hpp
    title: library/io/output_stream.hpp
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/container_utils.hpp\"\n\n\n\n#include <vector>\n\
    #include <optional>\n#include <sstream>\n\n#line 1 \"library/io/input_stream.hpp\"\
    \n\n\n\n#include <iostream>\n#line 1 \"library/type_traits/type_traits.hpp\"\n\
    \n\n\n#include <limits>\n#line 6 \"library/type_traits/type_traits.hpp\"\n#include\
    \ <type_traits>\n\nnamespace suisen {\n    template <typename ...Constraints>\
    \ using constraints_t = std::enable_if_t<std::conjunction_v<Constraints...>, std::nullptr_t>;\n\
    \n    template <typename T, typename = std::nullptr_t> struct bitnum { static\
    \ constexpr int value = 0; };\n    template <typename T> struct bitnum<T, constraints_t<std::is_integral<T>>>\
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
    \ } // namespace suisen\n\n#line 11 \"library/util/container_utils.hpp\"\n\nnamespace\
    \ suisen {\ntemplate <typename T>\nint count_leq(const std::vector<T> &v, const\
    \ T &key) { return std::upper_bound(v.begin(), v.end(), key) - v.begin();  }\n\
    template <typename T>\nint count_lt(const std::vector<T> &v, const T &key) { return\
    \ std::lower_bound(v.begin(), v.end(), key) - v.begin();  }\ntemplate <typename\
    \ T>\nint count_geq(const std::vector<T> &v, const T &key) { return v.size() -\
    \ count_lt(v, key); }\ntemplate <typename T>\nint count_gt(const std::vector<T>\
    \ &v, const T &key) { return v.size() - count_leq(v, key); }\n\ntemplate <typename\
    \ Container, typename Key>\nauto min_geq(const Container &container, const Key\
    \ &key) -> decltype(std::make_optional(*container.lower_bound(key))) {\n    if\
    \ (auto it = container.lower_bound(key); it == container.end()) return std::nullopt;\n\
    \    else return std::make_optional(*it);\n}\ntemplate <typename Container, typename\
    \ Key>\nauto min_gt(const Container &container, const Key &key) -> decltype(std::make_optional(*container.upper_bound(key)))\
    \ {\n    if (auto it = container.upper_bound(key); it == container.end()) return\
    \ std::nullopt;\n    else return std::make_optional(*it);\n}\ntemplate <typename\
    \ Container, typename Key>\nauto max_leq(const Container &container, const Key\
    \ &key) -> decltype(std::make_optional(*container.upper_bound(key))) {\n    if\
    \ (auto it = container.upper_bound(key); it == container.begin()) return std::nullopt;\n\
    \    else return std::make_optional(*--it);\n}\ntemplate <typename Container,\
    \ typename Key>\nauto max_lt(const Container &container, const Key &key) -> decltype(std::make_optional(*container.lower_bound(key)))\
    \ {\n    if (auto it = container.lower_bound(key); it == container.begin()) return\
    \ std::nullopt;\n    else return std::make_optional(*--it);\n}\ntemplate <typename\
    \ T>\nstd::optional<T> min_geq(const std::vector<T> &v, const T &key) {\n    auto\
    \ it = std::lower_bound(v.begin(), v.end(), key);\n    return it == v.end() ?\
    \ std::nullopt : std::make_optional(*it);\n}\ntemplate <typename T>\nstd::optional<T>\
    \ min_gt(const std::vector<T> &v, const T &key) {\n    auto it = std::upper_bound(v.begin(),\
    \ v.end(), key);\n    return it == v.end() ? std::nullopt : std::make_optional(*it);\n\
    }\ntemplate <typename T>\nstd::optional<T> max_leq(const std::vector<T> &v, const\
    \ T &key) {\n    auto it = std::upper_bound(v.begin(), v.end(), key);\n    return\
    \ it == v.begin() ? std::nullopt : std::make_optional(*--it);\n}\ntemplate <typename\
    \ T>\nstd::optional<T> max_lt(const std::vector<T> &v, const T &key) {\n    auto\
    \ it = std::lower_bound(v.begin(), v.end(), key);\n    return it == v.begin()\
    \ ? std::nullopt : std::make_optional(*--it);\n}\n\n__int128_t stoi128(const std::string&\
    \ s) {\n    __int128_t res;\n    io::InputStream{std::istringstream{s}} >> res;\n\
    \    return res;\n}\n__uint128_t stou128(const std::string& s) {\n    __uint128_t\
    \ res;\n    io::InputStream{std::istringstream{s}} >> res;\n    return res;\n\
    }\ntemplate <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\nstd::string join(const Iterable& v, const std::string&\
    \ sep, const std::string& end) {\n    io::OutputStream os{ std::ostringstream{}\
    \ };\n    os.print_all(v, sep, end);\n    return os.get_stream().str();\n}\ntemplate\
    \ <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t>\
    \ = nullptr>\nstd::vector<Iterable> split(const Iterable &s, const typename Iterable::value_type\
    \ &delim) {\n    std::vector<Iterable> res;\n    for (auto itl = s.begin(), itr\
    \ = itl;; itl = ++itr) {\n        while (itr != s.end() and *itr != delim) ++itr;\n\
    \        res.emplace_back(itl, itr);\n        if (itr == s.end()) return res;\n\
    \    }\n}\ntemplate <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\nvoid concat(Iterable& s, const Iterable& t) {\n\
    \    s.reserve(std::size(s) + std::size(t));\n    std::copy(std::begin(t), std::end(t),\
    \ std::back_inserter(s));\n}\ntemplate <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\nIterable concatenated(Iterable s, const Iterable&\
    \ t) { concat(s, t); return s; }\n\ntemplate <typename Func, typename Iterable,\
    \ std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>\n\
    auto mapped_vec(const Func& f, const Iterable& s) {\n    std::vector<std::invoke_result_t<Func,\
    \ typename Iterable::value_type>> v;\n    v.reserve(std::size(s)), std::transform(s.begin(),\
    \ s.end(), std::back_inserter(v), f);\n    return v;\n}\ntemplate <typename T,\
    \ typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t>\
    \ = nullptr>\nauto copied_vec(const Iterable& s) {\n    std::vector<T> v;\n  \
    \  v.reserve(std::size(s)), std::copy(s.begin(), s.end(), std::back_inserter(v));\n\
    \    return v;\n}\n\nnamespace charmap {\n    int fd(char c) { return c - '0';\
    \ }\n    int fa(char c) { return c - 'a'; }\n    int fA(char c) { return c - 'A';\
    \ }\n    int faA(char c) { return c <= 'Z' ? c - 'A' : 26 + (c - 'a'); }\n}\n\n\
    // val = Sum_i res[i] * base^i\ntemplate <int base = 2, typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\nstd::string digits_str(T val, size_t width = 0)\
    \ {\n    static_assert(2 <= base and base <= 10);\n    std::string res;\n    for\
    \ (; val or res.size() < width; val /= base) res += '0' + (val % base);\n    return\
    \ res;\n}\n// val = Sum_i res[i] * base^i\ntemplate <typename T, typename U =\
    \ int, std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_integral<U>>,\
    \ std::nullptr_t> = nullptr>\nstd::vector<U> digits(T val, U base = 10) {\n  \
    \  std::vector<U> res;\n    for (; val; val /= base) res.push_back(val % base);\n\
    \    if (res.empty()) res.push_back(T{ 0 });\n    return res;\n}\n} // namespace\
    \ suisen\n\n\n"
  code: "#ifndef SUISEN_CONTAINER_UTILS\n#define SUISEN_CONTAINER_UTILS\n\n#include\
    \ <vector>\n#include <optional>\n#include <sstream>\n\n#include \"library/io/input_stream.hpp\"\
    \n#include \"library/io/output_stream.hpp\"\n#include \"library/type_traits/type_traits.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename T>\nint count_leq(const std::vector<T>\
    \ &v, const T &key) { return std::upper_bound(v.begin(), v.end(), key) - v.begin();\
    \  }\ntemplate <typename T>\nint count_lt(const std::vector<T> &v, const T &key)\
    \ { return std::lower_bound(v.begin(), v.end(), key) - v.begin();  }\ntemplate\
    \ <typename T>\nint count_geq(const std::vector<T> &v, const T &key) { return\
    \ v.size() - count_lt(v, key); }\ntemplate <typename T>\nint count_gt(const std::vector<T>\
    \ &v, const T &key) { return v.size() - count_leq(v, key); }\n\ntemplate <typename\
    \ Container, typename Key>\nauto min_geq(const Container &container, const Key\
    \ &key) -> decltype(std::make_optional(*container.lower_bound(key))) {\n    if\
    \ (auto it = container.lower_bound(key); it == container.end()) return std::nullopt;\n\
    \    else return std::make_optional(*it);\n}\ntemplate <typename Container, typename\
    \ Key>\nauto min_gt(const Container &container, const Key &key) -> decltype(std::make_optional(*container.upper_bound(key)))\
    \ {\n    if (auto it = container.upper_bound(key); it == container.end()) return\
    \ std::nullopt;\n    else return std::make_optional(*it);\n}\ntemplate <typename\
    \ Container, typename Key>\nauto max_leq(const Container &container, const Key\
    \ &key) -> decltype(std::make_optional(*container.upper_bound(key))) {\n    if\
    \ (auto it = container.upper_bound(key); it == container.begin()) return std::nullopt;\n\
    \    else return std::make_optional(*--it);\n}\ntemplate <typename Container,\
    \ typename Key>\nauto max_lt(const Container &container, const Key &key) -> decltype(std::make_optional(*container.lower_bound(key)))\
    \ {\n    if (auto it = container.lower_bound(key); it == container.begin()) return\
    \ std::nullopt;\n    else return std::make_optional(*--it);\n}\ntemplate <typename\
    \ T>\nstd::optional<T> min_geq(const std::vector<T> &v, const T &key) {\n    auto\
    \ it = std::lower_bound(v.begin(), v.end(), key);\n    return it == v.end() ?\
    \ std::nullopt : std::make_optional(*it);\n}\ntemplate <typename T>\nstd::optional<T>\
    \ min_gt(const std::vector<T> &v, const T &key) {\n    auto it = std::upper_bound(v.begin(),\
    \ v.end(), key);\n    return it == v.end() ? std::nullopt : std::make_optional(*it);\n\
    }\ntemplate <typename T>\nstd::optional<T> max_leq(const std::vector<T> &v, const\
    \ T &key) {\n    auto it = std::upper_bound(v.begin(), v.end(), key);\n    return\
    \ it == v.begin() ? std::nullopt : std::make_optional(*--it);\n}\ntemplate <typename\
    \ T>\nstd::optional<T> max_lt(const std::vector<T> &v, const T &key) {\n    auto\
    \ it = std::lower_bound(v.begin(), v.end(), key);\n    return it == v.begin()\
    \ ? std::nullopt : std::make_optional(*--it);\n}\n\n__int128_t stoi128(const std::string&\
    \ s) {\n    __int128_t res;\n    io::InputStream{std::istringstream{s}} >> res;\n\
    \    return res;\n}\n__uint128_t stou128(const std::string& s) {\n    __uint128_t\
    \ res;\n    io::InputStream{std::istringstream{s}} >> res;\n    return res;\n\
    }\ntemplate <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\nstd::string join(const Iterable& v, const std::string&\
    \ sep, const std::string& end) {\n    io::OutputStream os{ std::ostringstream{}\
    \ };\n    os.print_all(v, sep, end);\n    return os.get_stream().str();\n}\ntemplate\
    \ <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t>\
    \ = nullptr>\nstd::vector<Iterable> split(const Iterable &s, const typename Iterable::value_type\
    \ &delim) {\n    std::vector<Iterable> res;\n    for (auto itl = s.begin(), itr\
    \ = itl;; itl = ++itr) {\n        while (itr != s.end() and *itr != delim) ++itr;\n\
    \        res.emplace_back(itl, itr);\n        if (itr == s.end()) return res;\n\
    \    }\n}\ntemplate <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\nvoid concat(Iterable& s, const Iterable& t) {\n\
    \    s.reserve(std::size(s) + std::size(t));\n    std::copy(std::begin(t), std::end(t),\
    \ std::back_inserter(s));\n}\ntemplate <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>,\
    \ std::nullptr_t> = nullptr>\nIterable concatenated(Iterable s, const Iterable&\
    \ t) { concat(s, t); return s; }\n\ntemplate <typename Func, typename Iterable,\
    \ std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>\n\
    auto mapped_vec(const Func& f, const Iterable& s) {\n    std::vector<std::invoke_result_t<Func,\
    \ typename Iterable::value_type>> v;\n    v.reserve(std::size(s)), std::transform(s.begin(),\
    \ s.end(), std::back_inserter(v), f);\n    return v;\n}\ntemplate <typename T,\
    \ typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t>\
    \ = nullptr>\nauto copied_vec(const Iterable& s) {\n    std::vector<T> v;\n  \
    \  v.reserve(std::size(s)), std::copy(s.begin(), s.end(), std::back_inserter(v));\n\
    \    return v;\n}\n\nnamespace charmap {\n    int fd(char c) { return c - '0';\
    \ }\n    int fa(char c) { return c - 'a'; }\n    int fA(char c) { return c - 'A';\
    \ }\n    int faA(char c) { return c <= 'Z' ? c - 'A' : 26 + (c - 'a'); }\n}\n\n\
    // val = Sum_i res[i] * base^i\ntemplate <int base = 2, typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\nstd::string digits_str(T val, size_t width = 0)\
    \ {\n    static_assert(2 <= base and base <= 10);\n    std::string res;\n    for\
    \ (; val or res.size() < width; val /= base) res += '0' + (val % base);\n    return\
    \ res;\n}\n// val = Sum_i res[i] * base^i\ntemplate <typename T, typename U =\
    \ int, std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_integral<U>>,\
    \ std::nullptr_t> = nullptr>\nstd::vector<U> digits(T val, U base = 10) {\n  \
    \  std::vector<U> res;\n    for (; val; val /= base) res.push_back(val % base);\n\
    \    if (res.empty()) res.push_back(T{ 0 });\n    return res;\n}\n} // namespace\
    \ suisen\n\n#endif // SUISEN_CONTAINER_UTILS\n"
  dependsOn:
  - library/io/input_stream.hpp
  - library/type_traits/type_traits.hpp
  - library/io/output_stream.hpp
  isVerificationFile: false
  path: library/util/container_utils.hpp
  requiredBy: []
  timestamp: '2023-09-15 20:02:25+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/container_utils.hpp
layout: document
title: Container Utils
---
## Container Utils