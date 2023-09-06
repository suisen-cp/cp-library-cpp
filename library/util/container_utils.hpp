#ifndef SUISEN_CONTAINER_UTILS
#define SUISEN_CONTAINER_UTILS

#include <vector>
#include <optional>
#include <sstream>

#include "library/io/input_stream.hpp"
#include "library/io/output_stream.hpp"
#include "library/type_traits/type_traits.hpp"

namespace suisen {
template <typename T>
int count_leq(const std::vector<T> &v, const T &key) { return std::upper_bound(v.begin(), v.end(), key) - v.begin();  }
template <typename T>
int count_lt(const std::vector<T> &v, const T &key) { return std::lower_bound(v.begin(), v.end(), key) - v.begin();  }
template <typename T>
int count_geq(const std::vector<T> &v, const T &key) { return v.size() - count_lt(v, key); }
template <typename T>
int count_gt(const std::vector<T> &v, const T &key) { return v.size() - count_leq(v, key); }

template <typename Container, typename Key>
auto min_geq(const Container &container, const Key &key) -> decltype(std::make_optional(*container.lower_bound(key))) {
    if (auto it = container.lower_bound(key); it == container.end()) return std::nullopt;
    else return std::make_optional(*it);
}
template <typename Container, typename Key>
auto min_gt(const Container &container, const Key &key) -> decltype(std::make_optional(*container.upper_bound(key))) {
    if (auto it = container.upper_bound(key); it == container.end()) return std::nullopt;
    else return std::make_optional(*it);
}
template <typename Container, typename Key>
auto max_leq(const Container &container, const Key &key) -> decltype(std::make_optional(*container.upper_bound(key))) {
    if (auto it = container.upper_bound(key); it == container.begin()) return std::nullopt;
    else return std::make_optional(*--it);
}
template <typename Container, typename Key>
auto max_lt(const Container &container, const Key &key) -> decltype(std::make_optional(*container.lower_bound(key))) {
    if (auto it = container.lower_bound(key); it == container.begin()) return std::nullopt;
    else return std::make_optional(*--it);
}
template <typename T>
std::optional<T> min_geq(const std::vector<T> &v, const T &key) {
    auto it = std::lower_bound(v.begin(), v.end(), key);
    return it == v.end() ? std::nullopt : std::make_optional(*it);
}
template <typename T>
std::optional<T> min_gt(const std::vector<T> &v, const T &key) {
    auto it = std::upper_bound(v.begin(), v.end(), key);
    return it == v.end() ? std::nullopt : std::make_optional(*it);
}
template <typename T>
std::optional<T> max_leq(const std::vector<T> &v, const T &key) {
    auto it = std::upper_bound(v.begin(), v.end(), key);
    return it == v.begin() ? std::nullopt : std::make_optional(*--it);
}
template <typename T>
std::optional<T> max_lt(const std::vector<T> &v, const T &key) {
    auto it = std::lower_bound(v.begin(), v.end(), key);
    return it == v.begin() ? std::nullopt : std::make_optional(*--it);
}

__int128_t stoi128(const std::string& s) {
    __int128_t res;
    io::InputStream{std::istringstream{s}} >> res;
    return res;
}
__uint128_t stou128(const std::string& s) {
    __uint128_t res;
    io::InputStream{std::istringstream{s}} >> res;
    return res;
}
template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
std::string join(const Iterable& v, const std::string& sep, const std::string& end) {
    io::OutputStream os{ std::ostringstream{} };
    os.print_all(v, sep, end);
    return os.get_stream().str();
}
template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
std::vector<Iterable> split(const Iterable &s, const typename Iterable::value_type &delim) {
    std::vector<Iterable> res;
    for (auto itl = s.begin(), itr = itl;; itl = ++itr) {
        while (itr != s.end() and *itr != delim) ++itr;
        res.emplace_back(itl, itr);
        if (itr == s.end()) return res;
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
    v.reserve(std::size(s)), std::transform(s.begin(), s.end(), std::back_inserter(v), f);
    return v;
}
template <typename T, typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
auto copied_vec(const Iterable& s) {
    std::vector<T> v;
    v.reserve(std::size(s)), std::copy(s.begin(), s.end(), std::back_inserter(v));
    return v;
}

namespace charmap {
    int fd(char c) { return c - '0'; }
    int fa(char c) { return c - 'a'; }
    int fA(char c) { return c - 'A'; }
    int faA(char c) { return c <= 'Z' ? c - 'A' : 26 + (c - 'a'); }
}

// val = Sum_i res[i] * base^i
template <int base = 2, typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
std::string digits_str(T val, size_t width = 0) {
    static_assert(2 <= base and base <= 10);
    std::string res;
    for (; val or res.size() < width; val /= base) res += '0' + (val % base);
    return res;
}
// val = Sum_i res[i] * base^i
template <typename T, typename U = int, std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_integral<U>>, std::nullptr_t> = nullptr>
std::vector<U> digits(T val, U base = 10) {
    std::vector<U> res;
    for (; val; val /= base) res.push_back(val % base);
    if (res.empty()) res.push_back(T{ 0 });
    return res;
}
} // namespace suisen

#endif // SUISEN_CONTAINER_UTILS
