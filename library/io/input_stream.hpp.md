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
  - icon: ':warning:'
    path: library/template.hpp
    title: Template
  - icon: ':warning:'
    path: library/util/container_utils.hpp
    title: Container Utils
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/io/input_stream.hpp\"\n\n\n\n#include <iostream>\n\
    #line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n#line\
    \ 6 \"library/type_traits/type_traits.hpp\"\n#include <type_traits>\n\nnamespace\
    \ suisen {\n    template <typename ...Constraints> using constraints_t = std::enable_if_t<std::conjunction_v<Constraints...>,\
    \ std::nullptr_t>;\n\n    template <typename T, typename = std::nullptr_t> struct\
    \ bitnum { static constexpr int value = 0; };\n    template <typename T> struct\
    \ bitnum<T, constraints_t<std::is_integral<T>>> { static constexpr int value =\
    \ std::numeric_limits<std::make_unsigned_t<T>>::digits; };\n    template <typename\
    \ T> static constexpr int bitnum_v = bitnum<T>::value;\n    template <typename\
    \ T, size_t n> struct is_nbit { static constexpr bool value = bitnum_v<T> == n;\
    \ };\n    template <typename T, size_t n> static constexpr bool is_nbit_v = is_nbit<T,\
    \ n>::value;\n\n    template <typename T, typename = std::nullptr_t> struct safely_multipliable\
    \ { using type = T; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_signed<T>, is_nbit<T, 32>>> { using type = long long;\
    \ };\n    template <typename T> struct safely_multipliable<T, constraints_t<std::is_signed<T>,\
    \ is_nbit<T, 64>>> { using type = __int128_t; };\n    template <typename T> struct\
    \ safely_multipliable<T, constraints_t<std::is_unsigned<T>, is_nbit<T, 32>>> {\
    \ using type = unsigned long long; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_unsigned<T>, is_nbit<T, 64>>> { using type = __uint128_t;\
    \ };\n    template <typename T> using safely_multipliable_t = typename safely_multipliable<T>::type;\n\
    \n    template <typename T, typename = void> struct rec_value_type { using type\
    \ = T; };\n    template <typename T> struct rec_value_type<T, std::void_t<typename\
    \ T::value_type>> {\n        using type = typename rec_value_type<typename T::value_type>::type;\n\
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
    \ suisen { using io::read; } // namespace suisen\n\n"
  code: "#ifndef SUISEN_INPUT_STREAM\n#define SUISEN_INPUT_STREAM\n\n#include <iostream>\n\
    #include \"library/type_traits/type_traits.hpp\"\nnamespace suisen::io {\n   \
    \ template <typename IStream, std::enable_if_t<std::conjunction_v<std::is_base_of<std::istream,\
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
    \ suisen { using io::read; } // namespace suisen\n#endif // SUISEN_INPUT_STREAM\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/io/input_stream.hpp
  requiredBy:
  - library/template.cpp
  - library/util/container_utils.hpp
  - library/template.hpp
  timestamp: '2023-09-15 20:02:25+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/io/input_stream.hpp
layout: document
redirect_from:
- /library/library/io/input_stream.hpp
- /library/library/io/input_stream.hpp.html
title: library/io/input_stream.hpp
---
