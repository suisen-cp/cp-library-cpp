#include <bits/stdc++.h>

#ifdef _MSC_VER
#  include <intrin.h>
#else
#  include <x86intrin.h>
#endif

#include "library/type_traits/type_traits.hpp"

namespace suisen {
    // ! type aliases
    using int128 = __int128_t;
    using uint128 = __uint128_t;

    template <typename T>
    using priority_queue_greater = std::priority_queue<T, std::vector<T>, std::greater<T>>;
}

// ! macros (internal)
#define DETAIL_CAT_I(a, b) a##b
#define DETAIL_CAT(a, b) DETAIL_CAT_I(a, b)
#define DETAIL_UNIQVAR(tag) DETAIL_CAT(tag, __LINE__)

// ! macros
#define FOR(e, v) for (auto &&e : v)
#define CFOR(e, v) for (const auto &e : v)
#define REP(i, ...) for (auto &&i : suisen::macro::rep_impl(__VA_ARGS__))
#define RREP(i, ...) for (auto &&i : suisen::macro::rrep_impl(__VA_ARGS__))
#define REPINF(i, ...) for (auto &&i : suisen::macro::repinf_impl(__VA_ARGS__))
#define CREP(i, ...) for (const auto &i : suisen::macro::rep_impl(__VA_ARGS__))
#define CRREP(i, ...) for (const auto &i : suisen::macro::rrep_impl(__VA_ARGS__))
#define CREPINF(i, ...) for (const auto &i : suisen::macro::repinf_impl(__VA_ARGS__))
#define LOOP(n) for ([[maybe_unused]] const auto& DETAIL_UNIQVAR(loop_variable) : suisen::macro::rep_impl(n))

#define ALL(iterable) std::begin(iterable), std::end(iterable)
#define INPUT(type, ...) type __VA_ARGS__; read(__VA_ARGS__)

// ! debug
#ifdef LOCAL
#  define debug(...) suisen::debug_internal(#__VA_ARGS__, __VA_ARGS__)

namespace suisen {
    template <class T, class... Args>
    void debug_internal(const char* s, T&& first, Args&&... args) {
        constexpr const char* prefix = "[\033[32mDEBUG\033[m] ";
        constexpr const char* open_brakets = sizeof...(args) == 0 ? "" : "(";
        constexpr const char* close_brakets = sizeof...(args) == 0 ? "" : ")";
        std::cerr << prefix << open_brakets << s << close_brakets << ": " << open_brakets << std::forward<T>(first);
        ((std::cerr << ", " << std::forward<Args>(args)), ...);
        std::cerr << close_brakets << "\n";
    }
}

#else
#  define debug(...) void(0)
#endif

// ! string / container
namespace suisen {
    __int128_t stoi128(const std::string& s) {
        __int128_t ret = 0;
        for (int i = 0; i < int(s.size()); i++) if ('0' <= s[i] and s[i] <= '9') ret = 10 * ret + s[i] - '0';
        if (s[0] == '-') ret = -ret;
        return ret;
    }
    __uint128_t stou128(const std::string& s) {
        __uint128_t ret = 0;
        for (int i = 0; i < int(s.size()); i++) if ('0' <= s[i] and s[i] <= '9') ret = 10 * ret + s[i] - '0';
        return ret;
    }

    template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
    std::string join(const Iterable& v, const std::string& sep, const std::string& end) {
        std::ostringstream ss;
        for (auto it = v.begin(); it != v.end();) {
            ss << *it;
            if (++it != v.end()) ss << sep;
        }
        ss << end;
        return ss.str();
    }
    template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
    std::vector<Iterable> split(const Iterable s, typename Iterable::value_type delim) {
        std::vector<Iterable> res;
        for (auto itl = std::begin(s), itr = itl;; itl = ++itr) {
            while (itr != std::end(s) and *itr != delim) ++itr;
            res.emplace_back(itl, itr);
            if (itr == std::end(s)) return res;
        }
    }
    template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
    void concat(Iterable& s, const Iterable& t) {
        s.reserve(std::size(s) + std::size(t));
        std::copy(std::begin(t), std::end(t), std::back_inserter(s));
    }
    template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
    Iterable concatenated(Iterable s, const Iterable& t) { concat(s, t); return s; }

    template <typename Func, typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
    auto mapped_vec(const Func& f, const Iterable& s) {
        std::vector<std::invoke_result_t<Func, typename Iterable::value_type>> v;
        v.reserve(std::size(s)), std::transform(std::begin(s), std::end(s), std::back_inserter(v), f);
        return v;
    }
    template <typename T, typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
    auto copied_vec(const Iterable& s) {
        std::vector<T> v;
        v.reserve(std::size(s)), std::copy(std::begin(s), std::end(s), std::back_inserter(v));
        return v;
    }

    namespace charmap {
        int fd(char c) { return c - '0'; }
        int fa(char c) { return c - 'a'; }
        int fA(char c) { return c - 'A'; }
        int faA(char c) { return c <= 'Z' ? c - 'A' : 26 + (c - 'a'); }
    }

    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    std::string bin(T val, int bit_num = -1) {
        std::string res;
        if (bit_num != -1) {
            for (int bit = bit_num; bit-- > 0;) res += '0' + ((val >> bit) & 1);
        } else {
            for (; val; val >>= 1) res += '0' + (val & 1);
            std::reverse(res.begin(), res.end());
        }
        return res;
    }

    template <typename T, typename U = int, std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_integral<U>>, std::nullptr_t> = nullptr>
    std::vector<U> digits_low_to_high(T val, U base = 10) {
        std::vector<U> res;
        for (; val; val /= base) res.push_back(val % base);
        if (res.empty()) res.push_back(T{ 0 });
        return res;
    }
    template <typename T, typename U = int, std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_integral<U>>, std::nullptr_t> = nullptr>
    std::vector<U> digits_high_to_low(T val, U base = 10) {
        auto res = digits_low_to_high(val, base);
        std::reverse(res.begin(), res.end());
        return res;
    }

    template <typename T, typename ToKey, typename CompareValue = std::less<>, std::enable_if_t<std::conjunction_v<std::is_invocable<ToKey, T>, std::is_invocable_r<bool, CompareValue, std::invoke_result_t<ToKey, T>, std::invoke_result_t<ToKey, T>>>, std::nullptr_t> = nullptr>
    auto comparator(const ToKey& to_key, const CompareValue& compare_value = std::less<>()) {
        return [to_key, compare_value](const T& x, const T& y) { return compare_value(to_key(x), to_key(y)); };
    }
    template <typename ToKey, std::enable_if_t<std::is_invocable_v<ToKey, int>, std::nullptr_t> = nullptr>
    std::vector<int> sorted_indices(int n, const ToKey& to_key) {
        std::vector<int> p(n);
        std::iota(p.begin(), p.end(), 0);
        std::sort(p.begin(), p.end(), comparator<int>(to_key));
        return p;
    }
    template <typename Compare, std::enable_if_t<std::is_invocable_r_v<bool, Compare, int, int>, std::nullptr_t> = nullptr>
    std::vector<int> sorted_indices(int n, const Compare& compare) {
        std::vector<int> p(n);
        std::iota(p.begin(), p.end(), 0);
        std::sort(p.begin(), p.end(), compare);
        return p;
    }
    template <typename T, typename Comparator>
    auto priority_queue_with_comparator(const Comparator comparator) { return std::priority_queue<T, std::vector<T>, Comparator>(comparator); }
    template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
    void sort_unique_erase(Iterable& a) { std::sort(a.begin(), a.end()), a.erase(std::unique(a.begin(), a.end()), a.end()); }
}

// ! IO
namespace suisen::io {
    namespace details {
        template <typename T>
        void print_single(std::ostream&, const T&);

        void print(std::ostream& os, __int128_t value) {
            std::ostream::sentry s(os);
            if (s) {
                __uint128_t tmp = value < 0 ? -value : value;
                char buffer[128];
                char* d = std::end(buffer);
                do {
                    --d;
                    *d = "0123456789"[tmp % 10];
                    tmp /= 10;
                } while (tmp != 0);
                if (value < 0) {
                    --d;
                    *d = '-';
                }
                int len = std::end(buffer) - d;
                if (os.rdbuf()->sputn(d, len) != len) {
                    os.setstate(std::ios_base::badbit);
                }
            }
        }
        void print(std::ostream& os, __uint128_t value) {
            std::ostream::sentry s(os);
            if (s) {
                char buffer[128];
                char* d = std::end(buffer);
                do {
                    --d;
                    *d = "0123456789"[value % 10];
                    value /= 10;
                } while (value != 0);
                int len = std::end(buffer) - d;
                if (os.rdbuf()->sputn(d, len) != len) {
                    os.setstate(std::ios_base::badbit);
                }
            }
        }

        template <typename T, typename U>
        void print(std::ostream& os, const std::pair<T, U>& a) {
            print_single(os, a.first), print_single(os, ' '), print_single(os, a.second);
        }
        template <size_t N = 0, typename ...Args>
        void print(std::ostream& os, const std::tuple<Args...>& a) {
            if constexpr (N == std::tuple_size_v<std::tuple<Args...>>) return;
            else {
                if constexpr (N) print_single(os, ' ');
                print_single(os, std::get<N>(a));
                print<N + 1>(os, a);
            }
        }
        template <typename Iterable,
            std::enable_if_t<std::conjunction_v<suisen::is_iterable<Iterable>, std::negation<suisen::is_writable<Iterable>>>, std::nullptr_t> = nullptr>
        void print(std::ostream& os, const Iterable& a) {
            for (auto it = a.begin(); it != a.end();) {
                print_single(os, *it);
                if (++it != a.end()) print_single(os, ' ');
            }
        }

        template <typename T>
        void print_single(std::ostream& os, const T& e) {
            if constexpr (suisen::is_writable_v<T>) os << e;
            else details::print(os, e);
        }
    }
    void print() { std::cout << '\n'; }
    template <typename Head, typename... Tail>
    void print(const Head& head, const Tail &...tails) {
        details::print_single(std::cout, head);
        if constexpr (sizeof...(Tail)) details::print_single(std::cout, ' ');
        print(tails...);
    }
    template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
    void print_all(const Iterable& v, std::string sep = " ", std::string end = "\n") {
        for (auto it = v.begin(); it != v.end();) {
            details::print_single(std::cout, *it);
            if (++it != v.end()) details::print_single(std::cout, sep);
        }
        details::print_single(std::cout, end);
    }

    namespace details {
        template <typename T>
        void read_single(std::istream&, T&);

        void read(std::istream& is, __int128_t& v) { std::string s; is >> s; v = stoi128(s); }
        void read(std::istream& is, __uint128_t& v) { std::string s; is >> s; v = stou128(s); }
        template <typename T, typename U>
        void read(std::istream& is, std::pair<T, U>& a) { read_single(is, a.first), read_single(is, a.second); }
        template <size_t N = 0, typename ...Args>
        void read(std::istream& is, std::tuple<Args...>& a) { if constexpr (N < sizeof...(Args)) read_single(is, std::get<N>(a)), read<N + 1>(is, a); }

        template <typename Iterable,
            std::enable_if_t<std::conjunction_v<suisen::is_iterable<Iterable>, std::negation<suisen::is_readable<Iterable>>>, std::nullptr_t> = nullptr>
        void read(std::istream& is, Iterable& a) { for (auto it = a.begin(); it != a.end(); ++it) read_single(is, *it); }

        template <typename T>
        void read_single(std::istream& is, T& e) {
            if constexpr (suisen::is_readable_v<T>) is >> e;
            else details::read(is, e);
        }

        struct { template <typename T> operator T() const { T e; read_single(std::cin, e); return e; } } constexpr reader;
    }

    auto read() { return details::reader; }
    template <typename Head, typename... Tail>
    void read(Head& head, Tail &...tails) {
        details::read_single(std::cin, head);
        if constexpr (sizeof...(Tail)) read(tails...);
    }
}
namespace suisen {
    using io::print, io::print_all, io::read;
}

// ! numeric
namespace suisen {
    // x <- min(x, y). returns true iff `x` has chenged.
    template <typename T>
    bool chmin(T& x, const T& y) { return y >= x ? false : (x = y, true); }
    // x <- max(x, y). returns true iff `x` has chenged.
    template <typename T>
    bool chmax(T& x, const T& y) { return y <= x ? false : (x = y, true); }

    // Returns pow(-1, n)
    template <typename T> constexpr int pow_m1(T n) { return -(n & 1) | 1; }
    // Returns pow(-1, n)
    template <> constexpr int pow_m1<bool>(bool n) { return -int(n) | 1; }

    // Returns floor(x / y)
    template <typename T> constexpr T fld(const T x, const T y) {
        T q = x / y, r = x % y;
        return q - ((x ^ y) < 0 and (r != 0));
    }
    template <typename T> constexpr T cld(const T x, const T y) {
        T q = x / y, r = x % y;
        return q + ((x ^ y) > 0 and (r != 0));
    }
}

// ! bit
namespace suisen {
    template <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T, 64>>, std::nullptr_t> = nullptr>
    __attribute__((target("popcnt"))) constexpr int popcount(const T x) { return _mm_popcnt_u32(x); }
    template <typename T, std::enable_if_t<suisen::is_nbit_v<T, 64>, std::nullptr_t> = nullptr>
    __attribute__((target("popcnt"))) constexpr int popcount(const T x) { return _mm_popcnt_u64(x); }
    template <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T, 64>>, std::nullptr_t> = nullptr>
    constexpr int count_lz(const T x) { return x ? __builtin_clz(x) : suisen::bit_num<T>; }
    template <typename T, std::enable_if_t<suisen::is_nbit_v<T, 64>, std::nullptr_t> = nullptr>
    constexpr int count_lz(const T x) { return x ? __builtin_clzll(x) : suisen::bit_num<T>; }
    template <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T, 64>>, std::nullptr_t> = nullptr>
    constexpr int count_tz(const T x) { return x ? __builtin_ctz(x) : suisen::bit_num<T>; }
    template <typename T, std::enable_if_t<suisen::is_nbit_v<T, 64>, std::nullptr_t> = nullptr>
    constexpr int count_tz(const T x) { return x ? __builtin_ctzll(x) : suisen::bit_num<T>; }
    template <typename T> constexpr int floor_log2(const T x) { return suisen::bit_num<T> -1 - count_lz(x); }
    template <typename T> constexpr int ceil_log2(const T x) { return floor_log2(x) + ((x & -x) != x); }
    template <typename T> constexpr int kth_bit(const T x, const unsigned int k) { return (x >> k) & 1; }
    template <typename T> constexpr int parity(const T x) { return popcount(x) & 1; }
}

// ! for macro
namespace suisen::macro {
    template <typename IntR, typename IntL = IntR, typename IntStep = IntR>
    struct rep_impl {
        rep_impl(IntR n) : rep_impl(0, n, 1) {}
        rep_impl(IntL l, IntR r, IntStep step = 1) : _begin(l, step), _end(r) {}
        auto begin() const { return _begin; }
        auto end() const { return _end; }
    private:
        struct iterator {
            IntR val, step;
            iterator(const IntR& val, const IntR& step) : val(val), step(step) {}
            IntR& operator*() { return val; }
            bool operator!=(const IntR& endval) { return val < endval; }
            iterator& operator++() { return val += step, *this; }
        };
        iterator _begin;
        IntR _end;
    };
    template <typename IntR, typename IntL = IntR, typename IntStep = IntR>
    struct rrep_impl {
        rrep_impl(IntR n) : rrep_impl(0, n, 1) {}
        rrep_impl(IntL l, IntR r, IntStep step = 1) : _begin(l + fld<IntR>(r - l - 1, step) * step, step), _end(l) {}
        auto begin() const { return _begin; }
        auto end() const { return _end; }
    private:
        struct iterator {
            IntR val, step;
            iterator(const IntR& val, const IntR& step) : val(val), step(step) {}
            IntR& operator*() { return val; }
            bool operator!=(const IntR& endval) { return val >= endval; }
            iterator& operator++() { return val -= step, *this; }
        };
        iterator _begin;
        IntR _end;
    };
    template <typename IntL, typename IntStep = IntL>
    struct repinf_impl {
        repinf_impl(IntL l, IntStep step = 1) : _begin(l, step) {}
        auto begin() const { return _begin; }
        auto end() const { return nullptr; }
    private:
        struct iterator {
            IntL val, step;
            iterator(const IntL& val, const IntL& step) : val(val), step(step) {}
            IntL& operator*() { return val; }
            bool operator!=(std::nullptr_t) { return true; }
            iterator& operator++() { return val += step, *this; }
        };
        iterator _begin;
    };
}

// ! misc
namespace suisen {
    const std::string Yes = "Yes", No = "No", YES = "YES", NO = "NO";
}

namespace suisen {}
using namespace suisen;
using namespace std;
