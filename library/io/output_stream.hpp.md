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
  bundledCode: "#line 1 \"library/io/output_stream.hpp\"\n\n\n\n#include <iostream>\n\
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
    } // namespace suisen\n\n#line 6 \"library/io/output_stream.hpp\"\nnamespace suisen::io\
    \ {\n    template <typename OStream, std::enable_if_t<std::conjunction_v<std::is_base_of<std::ostream,\
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
    \ } // namespace suisen\n\n"
  code: "#ifndef SUISEN_OUTPUT_STREAM\n#define SUISEN_OUTPUT_STREAM\n\n#include <iostream>\n\
    #include \"library/type_traits/type_traits.hpp\"\nnamespace suisen::io {\n   \
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
    \ } // namespace suisen\n#endif // SUISEN_OUTPUT_STREAM\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/io/output_stream.hpp
  requiredBy:
  - library/template.cpp
  - library/template.hpp
  - library/util/container_utils.hpp
  timestamp: '2023-09-15 20:02:25+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/io/output_stream.hpp
layout: document
redirect_from:
- /library/library/io/output_stream.hpp
- /library/library/io/output_stream.hpp.html
title: library/io/output_stream.hpp
---
