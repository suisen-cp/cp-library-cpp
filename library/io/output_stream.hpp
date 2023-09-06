#ifndef SUISEN_OUTPUT_STREAM
#define SUISEN_OUTPUT_STREAM

#include <iostream>
#include "library/type_traits/type_traits.hpp"
namespace suisen::io {
    template <typename OStream, std::enable_if_t<std::conjunction_v<std::is_base_of<std::ostream, std::remove_reference_t<OStream>>, std::negation<std::is_const<std::remove_reference_t<OStream>>>>, std::nullptr_t> = nullptr>
    struct OutputStream {
    private:
        using ostream_type = std::remove_reference_t<OStream>;
        OStream os;
    public:
        template <typename OStream_> OutputStream(OStream_ &&os) : os(std::move(os)) {}
        template <typename OStream_> OutputStream(OStream_ &os) : os(os) {}
        template <typename T> OutputStream& operator<<(const T& e) {
            if constexpr (suisen::is_writable_v<T>) os << e; else _print(e);
            return *this;
        }
        void print() { *this << '\n'; }
        template <typename Head, typename... Tail>
        void print(const Head& head, const Tail &...tails) { *this << head, ((*this << ' ' << tails), ...), *this << '\n'; }
        template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
        void print_all(const Iterable& v, std::string sep = " ", std::string end = "\n") {
            for (auto it = v.begin(); it != v.end();) if (*this << *it; ++it != v.end()) *this << sep;
            *this << end;
        }
        ostream_type& get_stream() { return os; }
    private:
        void _print(__uint128_t value) {
            char buffer[41], *d = std::end(buffer);
            do *--d = '0' + (value % 10), value /= 10; while (value);
            os.rdbuf()->sputn(d, std::end(buffer) - d);
        }
        void _print(__int128_t value) {
            if (value < 0) *this << '-';
            _print(__uint128_t(value < 0 ? -value : value));
        }
        template <typename T, typename U>
        void _print(const std::pair<T, U>& a) { *this << a.first << ' ' << a.second; }
        template <size_t N = 0, typename ...Args>
        void _print(const std::tuple<Args...>& a) {
            if constexpr (N < std::tuple_size_v<std::tuple<Args...>>) {
                if constexpr (N) *this << ' ';
                *this << std::get<N>(a), _print<N + 1>(a);
            }
        }
        template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
        void _print(const Iterable& a) { print_all(a, " ", ""); }
    };
    template <typename OStream_>
    OutputStream(OStream_ &&) -> OutputStream<OStream_>;
    template <typename OStream_>
    OutputStream(OStream_ &) -> OutputStream<OStream_&>;

    OutputStream cout{ std::cout }, cerr{ std::cerr };

    template <typename... Args>
    void print(const Args &... args) { cout.print(args...); }
    template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
    void print_all(const Iterable& v, const std::string& sep = " ", const std::string& end = "\n") { cout.print_all(v, sep, end); }
} // namespace suisen::io
namespace suisen { using io::print, io::print_all; } // namespace suisen
#endif // SUISEN_OUTPUT_STREAM
