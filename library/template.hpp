#include <bits/stdc++.h>
#include <library/type_traits/type_traits.hpp>

#pragma region

// ! type aliases
using int128 = __int128_t;
using uint128 = __uint128_t;
using ll = long long;
using uint = unsigned int;
using ull  = unsigned long long;

template <typename T> using vec  = std::vector<T>;
template <typename T> using vec2 = vec<vec <T>>;
template <typename T> using vec3 = vec<vec2<T>>;
template <typename T> using vec4 = vec<vec3<T>>;

template <typename T>
using pq_greater = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template <typename T, typename U>
using umap = std::unordered_map<T, U>;

// ! macros
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

#define all(iterable) (iterable).begin(), (iterable).end()
#define range_iter(iterable, l, r) ((iterable).begin() + (l)), ((iterable).begin() + (r))
#define input(type, ...) type __VA_ARGS__; read(__VA_ARGS__)

// ! constants
constexpr int dx4[4] = {1, 0, -1, 0};
constexpr int dy4[4] = {0, 1, 0, -1};

constexpr int dx8[8] = {1, 1, 0, -1, -1, -1, 0, 1};
constexpr int dy8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

// ! I/O utilities
template <typename T, typename U>
std::ostream& operator<<(std::ostream& out, const std::pair<T, U> &a) { return out << a.first << ' ' << a.second; }
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T> &a) {
    for (auto it = a.begin(); it != a.end();) {
        out << *it;
        if (++it != a.end()) out << ' ';
    }
    return out;
}
inline void print() { std::cout << '\n'; }
template <typename Head, typename... Tail>
inline void print(const Head& head, const Tail&... tails) {
    std::cout << head;
    if (sizeof...(tails)) std::cout << ' ';
    print(tails...);
}
template <typename Iterable>
void print_iterable(const Iterable& v, const std::string sep = " ", const std::string end = "\n") {
    int n = v.size();
    rep(i, n) {
        std::cout << v[i];
        if (i < n - 1) std::cout << sep;
    }
    std::cout << end;
}

template <typename T, typename U>
std::istream& operator>>(std::istream& in, std::pair<T, U> &a) { return in >> a.first >> a.second; }
template <typename T>
std::istream& operator>>(std::istream& in, std::vector<T> &a) {
    for (auto it = a.begin(); it != a.end(); ++it) in >> *it;
    return in;
}
constexpr void read() {}
template <typename Head, typename... Tail>
inline void read(Head& head, Tail& ...tails) {
    std::cin >> head;
    read(tails...);
}

// ! primitive utilities

template <typename T>
bool chmin(T &x, const T &y) {
    if (y >= x) return false;
    x = y;
    return true;
}
template <typename T>
bool chmin(T &x, const T &&y) {
    if (y >= x) return false;
    x = y;
    return true;
}
template <typename T>
bool chmax(T &x, const T &y) {
    if (y <= x) return false;
    x = y;
    return true;
}
template <typename T>
bool chmax(T &x, const T &&y) {
    if (y <= x) return false;
    x = y;
    return true;
}

template <typename T>
constexpr T fld(const T x, const T y) {
    return y < 0 ? fld(-x, -y) : (x >= 0 ? x / y : -((-x + y - 1) / y));
}
template <typename T>
constexpr T cld(const T x, const T y) {
    return y < 0 ? cld(-x, -y) : (x >= 0 ? (x + y - 1) / y : -(-x / y));
}

template <typename T, suisen::constraints_t<suisen::is_nbit<T, 32>> = nullptr>
constexpr int popcount(const T x) { return __builtin_popcount(x); }
template <typename T, suisen::constraints_t<suisen::is_nbit<T, 64>> = nullptr>
constexpr int popcount(const T x) { return __builtin_popcountll(x); }
template <typename T, suisen::constraints_t<suisen::is_nbit<T, 32>> = nullptr>
constexpr int count_lz(const T x) { return x ? __builtin_clz(x)   : suisen::bit_num<T>; }
template <typename T, suisen::constraints_t<suisen::is_nbit<T, 64>> = nullptr>
constexpr int count_lz(const T x) { return x ? __builtin_clzll(x) : suisen::bit_num<T>; }
template <typename T, suisen::constraints_t<suisen::is_nbit<T, 32>> = nullptr>
constexpr int count_tz(const T x) { return x ? __builtin_ctz(x)   : suisen::bit_num<T>; }
template <typename T, suisen::constraints_t<suisen::is_nbit<T, 64>> = nullptr>
constexpr int count_tz(const T x) { return x ? __builtin_ctzll(x) : suisen::bit_num<T>; }
template <typename T>
constexpr int floor_log2(const T x) { return suisen::bit_num<T> - 1 - count_lz(x); }
template <typename T>
constexpr int ceil_log2(const T x)  { return floor_log2(x) + ((x & -x) != x); }
template <typename T>
constexpr int kth_bit(const T x, const unsigned int k) { return (x >> k) & 1; }
template <typename T>
constexpr int parity(const T x) { return popcount(x) & 1; }

// ! container

template <typename T, typename Comparator, suisen::constraints_t<suisen::is_comparator<Comparator, T>> = nullptr>
auto priqueue_comp(const Comparator comparator) {
    return std::priority_queue<T, std::vector<T>, Comparator>(comparator);
}

template <typename Iterable>
auto isize(const Iterable &iterable) -> decltype(int(iterable.size())) { return iterable.size(); }

namespace suisen {}
using namespace suisen;
using namespace std;

#pragma endregion
