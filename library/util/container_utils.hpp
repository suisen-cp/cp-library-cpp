#include <vector>
#include <optional>

namespace suisen {
template <typename T>
void unique_erase(std::vector<T> &v) {
    v.erase(std::unique(v.begin(), v.end()), v.end());
}

template <typename T>
int count_leq(const std::vector<T> &v, const T &&key) {
    return std::upper_bound(v.begin(), v.end(), key) - v.begin(); 
}
template <typename T>
int count_lt(const std::vector<T> &v, const T &&key) {
    return std::lower_bound(v.begin(), v.end(), key) - v.begin(); 
}
template <typename T>
int count_geq(const std::vector<T> &v, const T &&key) {
    return v.size() - count_lt(v, key);
}
template <typename T>
int count_gt(const std::vector<T> &v, const T &&key) {
    return v.size() - count_leq(v, key);
}

template <typename _Container, typename _Key>
auto min_geq(const _Container &container, const _Key &&key) -> decltype(std::make_optional(*container.lower_bound(key))) {
    auto it = container.lower_bound(key);
    return it == container.end() ? std::nullopt : std::make_optional(*it);
}
template <typename _Container, typename _Key>
auto min_geq(const _Container &container, const _Key &key) -> decltype(std::make_optional(*container.lower_bound(key))) {
    auto it = container.lower_bound(key);
    return it == container.end() ? std::nullopt : std::make_optional(*it);
}
template <typename _Container, typename _Key>
auto min_gt(const _Container &container, const _Key &&key) -> decltype(std::make_optional(*container.upper_bound(key))) {
    auto it = container.upper_bound(key);
    return it == container.end() ? std::nullopt : std::make_optional(*it);
}
template <typename _Container, typename _Key>
auto min_gt(const _Container &container, const _Key &key) -> decltype(std::make_optional(*container.upper_bound(key))) {
    auto it = container.upper_bound(key);
    return it == container.end() ? std::nullopt : std::make_optional(*it);
}
template <typename _Container, typename _Key>
auto max_leq(const _Container &container, const _Key &&key) -> decltype(std::make_optional(*container.upper_bound(key))) {
    auto it = container.upper_bound(key);
    return it == container.begin() ? std::nullopt : std::make_optional(*--it);
}
template <typename _Container, typename _Key>
auto max_leq(const _Container &container, const _Key &key) -> decltype(std::make_optional(*container.upper_bound(key))) {
    auto it = container.upper_bound(key);
    return it == container.begin() ? std::nullopt : std::make_optional(*--it);
}
template <typename _Container, typename _Key>
auto max_lt(const _Container &container, const _Key &&key) -> decltype(std::make_optional(*container.lower_bound(key))) {
    auto it = container.lower_bound(key);
    return it == container.begin() ? std::nullopt : std::make_optional(*--it);
}
template <typename _Container, typename _Key>
auto max_lt(const _Container &container, const _Key &key) -> decltype(std::make_optional(*container.lower_bound(key))) {
    auto it = container.lower_bound(key);
    return it == container.begin() ? std::nullopt : std::make_optional(*--it);
}

template <typename T>
std::optional<T> min_geq(const std::vector<T> &v, const T &&key) {
    auto it = std::lower_bound(v.begin(), v.end(), key);
    return it == v.end() ? std::nullopt : std::make_optional(*it);
}
template <typename T>
std::optional<T> min_geq(const std::vector<T> &v, const T &key) {
    auto it = std::lower_bound(v.begin(), v.end(), key);
    return it == v.end() ? std::nullopt : std::make_optional(*it);
}
template <typename T>
std::optional<T> min_gt(const std::vector<T> &v, const T &&key) {
    auto it = std::upper_bound(v.begin(), v.end(), key);
    return it == v.end() ? std::nullopt : std::make_optional(*it);
}
template <typename T>
std::optional<T> min_gt(const std::vector<T> &v, const T &key) {
    auto it = std::upper_bound(v.begin(), v.end(), key);
    return it == v.end() ? std::nullopt : std::make_optional(*it);
}
template <typename T>
std::optional<T> max_leq(const std::vector<T> &v, const T &&key) {
    auto it = std::upper_bound(v.begin(), v.end(), key);
    return it == v.begin() ? std::nullopt : std::make_optional(*--it);
}
template <typename T>
std::optional<T> max_leq(const std::vector<T> &v, const T &key) {
    auto it = std::upper_bound(v.begin(), v.end(), key);
    return it == v.begin() ? std::nullopt : std::make_optional(*--it);
}
template <typename T>
std::optional<T> max_lt(const std::vector<T> &v, const T &&key) {
    auto it = std::lower_bound(v.begin(), v.end(), key);
    return it == v.begin() ? std::nullopt : std::make_optional(*--it);
}
template <typename T>
std::optional<T> max_lt(const std::vector<T> &v, const T &key) {
    auto it = std::lower_bound(v.begin(), v.end(), key);
    return it == v.begin() ? std::nullopt : std::make_optional(*--it);
}
} // namespace suisen
