#include <bits/stdc++.h>

#ifdef _MSC_VER
#  include <intrin.h>
#else
#  include <x86intrin.h>
#endif

#include "library/type_traits/type_traits.hpp"

// ! type aliases
using i128 = __int128_t;
using u128 = __uint128_t;

template <typename T>
using pq_greater = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template <typename T, typename U>
using umap = std::unordered_map<T, U>;

// ! macros (capital: internal macro)
#define OVERLOAD2(_1,_2,name,...) name
#define OVERLOAD3(_1,_2,_3,name,...) name
#define OVERLOAD4(_1,_2,_3,_4,name,...) name

#define REP4(i,l,r,s)  for(std::remove_reference_t<std::remove_const_t<decltype(r)>>i=(l);i<(r);i+=(s))
#define REP3(i,l,r)    REP4(i,l,r,1)
#define REP2(i,n)      REP3(i,0,n)
#define REPINF3(i,l,s) for(std::remove_reference_t<std::remove_const_t<decltype(l)>>i=(l);;i+=(s))
#define REPINF2(i,l)   REPINF3(i,l,1)
#define REPINF1(i)     REPINF2(i,0)
#define RREP4(i,l,r,s) for(std::remove_reference_t<std::remove_const_t<decltype(r)>>i=(l)+fld((r)-(l)-1,s)*(s);i>=(l);i-=(s))
#define RREP3(i,l,r)   RREP4(i,l,r,1)
#define RREP2(i,n)     RREP3(i,0,n)

#define rep(...)    OVERLOAD4(__VA_ARGS__, REP4   , REP3   , REP2   )(__VA_ARGS__)
#define rrep(...)   OVERLOAD4(__VA_ARGS__, RREP4  , RREP3  , RREP2  )(__VA_ARGS__)
#define repinf(...) OVERLOAD3(__VA_ARGS__, REPINF3, REPINF2, REPINF1)(__VA_ARGS__)

#define CAT_I(a, b) a##b
#define CAT(a, b) CAT_I(a, b)
#define UNIQVAR(tag) CAT(tag, __LINE__)
#define loop(n) for (std::remove_reference_t<std::remove_const_t<decltype(n)>> UNIQVAR(loop_variable) = n; UNIQVAR(loop_variable) --> 0;)

#define all(iterable) std::begin(iterable), std::end(iterable)
#define input(type, ...) type __VA_ARGS__; read(__VA_ARGS__)

#ifdef LOCAL
#  define debug(...) debug_internal(#__VA_ARGS__, __VA_ARGS__)

template <class T, class... Args>
void debug_internal(const char* s, T&& first, Args&&... args) {
    constexpr const char* prefix = "[\033[32mDEBUG\033[m] ";
    constexpr const char* open_brakets = sizeof...(args) == 0 ? "" : "(";
    constexpr const char* close_brakets = sizeof...(args) == 0 ? "" : ")";
    std::cerr << prefix << open_brakets << s << close_brakets << ": " << open_brakets << std::forward<T>(first);
    ((std::cerr << ", " << std::forward<Args>(args)), ...);
    std::cerr << close_brakets << "\n";
}

#else
#  define debug(...) void(0)
#endif

// ! I/O utilities

// __int128_t
std::ostream& operator<<(std::ostream& dest, __int128_t value) {
    std::ostream::sentry s(dest);
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
        if (dest.rdbuf()->sputn(d, len) != len) {
            dest.setstate(std::ios_base::badbit);
        }
    }
    return dest;
}
// __uint128_t
std::ostream& operator<<(std::ostream& dest, __uint128_t value) {
    std::ostream::sentry s(dest);
    if (s) {
        char buffer[128];
        char* d = std::end(buffer);
        do {
            --d;
            *d = "0123456789"[value % 10];
            value /= 10;
        } while (value != 0);
        int len = std::end(buffer) - d;
        if (dest.rdbuf()->sputn(d, len) != len) {
            dest.setstate(std::ios_base::badbit);
        }
    }
    return dest;
}

// pair
template <typename T, typename U>
std::ostream& operator<<(std::ostream& out, const std::pair<T, U>& a) {
    return out << a.first << ' ' << a.second;
}
// tuple
template <unsigned int N = 0, typename ...Args>
std::ostream& operator<<(std::ostream& out, const std::tuple<Args...>& a) {
    if constexpr (N >= std::tuple_size_v<std::tuple<Args...>>) {
        return out;
    } else {
        out << std::get<N>(a);
        if constexpr (N + 1 < std::tuple_size_v<std::tuple<Args...>>) {
            out << ' ';
        }
        return operator<<<N + 1>(out, a);
    }
}
// vector
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& a) {
    for (auto it = a.begin(); it != a.end();) {
        out << *it;
        if (++it != a.end()) out << ' ';
    }
    return out;
}
// array
template <typename T, size_t N>
std::ostream& operator<<(std::ostream& out, const std::array<T, N>& a) {
    for (auto it = a.begin(); it != a.end();) {
        out << *it;
        if (++it != a.end()) out << ' ';
    }
    return out;
}
inline void print() { std::cout << '\n'; }
template <typename Head, typename... Tail>
inline void print(const Head& head, const Tail &...tails) {
    std::cout << head;
    if (sizeof...(tails)) std::cout << ' ';
    print(tails...);
}
template <typename Iterable>
auto print_all(const Iterable& v, std::string sep = " ", std::string end = "\n") -> decltype(std::cout << *v.begin(), void()) {
    for (auto it = v.begin(); it != v.end();) {
        std::cout << *it;
        if (++it != v.end()) std::cout << sep;
    }
    std::cout << end;
}

__int128_t parse_i128(std::string& s) {
    __int128_t ret = 0;
    for (int i = 0; i < int(s.size()); i++) if ('0' <= s[i] and s[i] <= '9') ret = 10 * ret + s[i] - '0';
    if (s[0] == '-') ret = -ret;
    return ret;
}
__uint128_t parse_u128(std::string& s) {
    __uint128_t ret = 0;
    for (int i = 0; i < int(s.size()); i++) if ('0' <= s[i] and s[i] <= '9') ret = 10 * ret + s[i] - '0';
    return ret;
}
// __int128_t
std::istream& operator>>(std::istream& in, __int128_t& v) {
    std::string s;
    in >> s;
    v = parse_i128(s);
    return in;
}
// __uint128_t
std::istream& operator>>(std::istream& in, __uint128_t& v) {
    std::string s;
    in >> s;
    v = parse_u128(s);
    return in;
}
// pair
template <typename T, typename U>
std::istream& operator>>(std::istream& in, std::pair<T, U>& a) {
    return in >> a.first >> a.second;
}
// tuple
template <unsigned int N = 0, typename ...Args>
std::istream& operator>>(std::istream& in, std::tuple<Args...>& a) {
    if constexpr (N >= std::tuple_size_v<std::tuple<Args...>>) {
        return in;
    } else {
        return operator>><N + 1>(in >> std::get<N>(a), a);
    }
}
// vector
template <typename T>
std::istream& operator>>(std::istream& in, std::vector<T>& a) {
    for (auto it = a.begin(); it != a.end(); ++it) in >> *it;
    return in;
}
// array
template <typename T, size_t N>
std::istream& operator>>(std::istream& in, std::array<T, N>& a) {
    for (auto it = a.begin(); it != a.end(); ++it) in >> *it;
    return in;
}
template <typename ...Args>
void read(Args &...args) {
    (std::cin >> ... >> args);
}

// ! integral utilities

// Returns pow(-1, n)
template <typename T>
constexpr inline int pow_m1(T n) {
    return -(n & 1) | 1;
}
// Returns pow(-1, n)
template <>
constexpr inline int pow_m1<bool>(bool n) {
    return -int(n) | 1;
}

// Returns floor(x / y)
template <typename T>
constexpr inline T fld(const T x, const T y) {
    return (x ^ y) >= 0 ? x / y : (x - (y + pow_m1(y >= 0))) / y;
}
template <typename T>
constexpr inline T cld(const T x, const T y) {
    return (x ^ y) <= 0 ? x / y : (x + (y + pow_m1(y >= 0))) / y;
}

template <typename T, suisen::constraints_t<suisen::is_nbit<T, 16>> = nullptr>
__attribute__((target("popcnt"))) constexpr inline int popcount(const T x) { return _mm_popcnt_u32(x); }
template <typename T, suisen::constraints_t<suisen::is_nbit<T, 32>> = nullptr>
__attribute__((target("popcnt"))) constexpr inline int popcount(const T x) { return _mm_popcnt_u32(x); }
template <typename T, suisen::constraints_t<suisen::is_nbit<T, 64>> = nullptr>
__attribute__((target("popcnt"))) constexpr inline int popcount(const T x) { return _mm_popcnt_u64(x); }
template <typename T, suisen::constraints_t<suisen::is_nbit<T, 16>> = nullptr>
constexpr inline int count_lz(const T x) { return x ? __builtin_clz(x) : suisen::bit_num<T>; }
template <typename T, suisen::constraints_t<suisen::is_nbit<T, 32>> = nullptr>
constexpr inline int count_lz(const T x) { return x ? __builtin_clz(x) : suisen::bit_num<T>; }
template <typename T, suisen::constraints_t<suisen::is_nbit<T, 64>> = nullptr>
constexpr inline int count_lz(const T x) { return x ? __builtin_clzll(x) : suisen::bit_num<T>; }
template <typename T, suisen::constraints_t<suisen::is_nbit<T, 16>> = nullptr>
constexpr inline int count_tz(const T x) { return x ? __builtin_ctz(x) : suisen::bit_num<T>; }
template <typename T, suisen::constraints_t<suisen::is_nbit<T, 32>> = nullptr>
constexpr inline int count_tz(const T x) { return x ? __builtin_ctz(x) : suisen::bit_num<T>; }
template <typename T, suisen::constraints_t<suisen::is_nbit<T, 64>> = nullptr>
constexpr inline int count_tz(const T x) { return x ? __builtin_ctzll(x) : suisen::bit_num<T>; }
template <typename T>
constexpr inline int floor_log2(const T x) { return suisen::bit_num<T> -1 - count_lz(x); }
template <typename T>
constexpr inline int ceil_log2(const T x) { return floor_log2(x) + ((x & -x) != x); }
template <typename T>
constexpr inline int kth_bit(const T x, const unsigned int k) { return (x >> k) & 1; }
template <typename T>
constexpr inline int parity(const T x) { return popcount(x) & 1; }

// ! container

template <typename T, typename Comparator, suisen::constraints_t<suisen::is_comparator<Comparator, T>> = nullptr>
auto priqueue_comp(const Comparator comparator) {
    return std::priority_queue<T, std::vector<T>, Comparator>(comparator);
}

template <typename Iterable>
auto isize(const Iterable& iterable) -> decltype(int(iterable.size())) {
    return iterable.size();
}

template <typename T, typename Gen, suisen::constraints_t<suisen::is_same_as_invoke_result<T, Gen, int>> = nullptr>
auto generate_vector(int n, Gen generator) {
    std::vector<T> v(n);
    for (int i = 0; i < n; ++i) v[i] = generator(i);
    return v;
}
template <typename T>
auto generate_range_vector(T l, T r) {
    return generate_vector(r - l, [l](int i) { return l + i; });
}
template <typename T>
auto generate_range_vector(T n) {
    return generate_range_vector(0, n);
}

template <typename T>
void sort_unique_erase(std::vector<T>& a) {
    std::sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());
}

template <typename InputIterator, typename BiConsumer>
auto foreach_adjacent_values(InputIterator first, InputIterator last, BiConsumer f) -> decltype(f(*first++, *last), void()) {
    if (first != last) for (auto itr = first, itl = itr++; itr != last; itl = itr++) f(*itl, *itr);
}
template <typename Container, typename BiConsumer>
auto foreach_adjacent_values(Container c, BiConsumer f) -> decltype(c.begin(), c.end(), void()) {
    foreach_adjacent_values(c.begin(), c.end(), f);
}


// ! other utilities

// x <- min(x, y). returns true iff `x` has chenged.
template <typename T>
inline bool chmin(T& x, const T& y) {
    if (y >= x) return false;
    x = y;
    return true;
}
// x <- max(x, y). returns true iff `x` has chenged.
template <typename T>
inline bool chmax(T& x, const T& y) {
    if (y <= x) return false;
    x = y;
    return true;
}

template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
std::string bin(T val, int bit_num = -1) {
    std::string res;
    if (bit_num >= 0) {
        for (int bit = bit_num; bit-- > 0;) res += '0' + ((val >> bit) & 1);
    } else {
        for (; val; val >>= 1) res += '0' + (val & 1);
        std::reverse(res.begin(), res.end());
    }
    return res;
}

template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
std::vector<T> digits_low_to_high(T val, T base = 10) {
    std::vector<T> res;
    for (; val; val /= base) res.push_back(val % base);
    if (res.empty()) res.push_back(T{ 0 });
    return res;
}
template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
std::vector<T> digits_high_to_low(T val, T base = 10) {
    auto res = digits_low_to_high(val, base);
    std::reverse(res.begin(), res.end());
    return res;
}

template <typename T>
std::string join(const std::vector<T>& v, const std::string& sep, const std::string& end) {
    std::ostringstream ss;
    for (auto it = v.begin(); it != v.end();) {
        ss << *it;
        if (++it != v.end()) ss << sep;
    }
    ss << end;
    return ss.str();
}

namespace suisen {}
using namespace suisen;
using namespace std;
