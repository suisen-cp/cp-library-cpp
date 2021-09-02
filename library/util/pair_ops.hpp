#ifndef SUISEN_PAIR_OPS
#define SUISEN_PAIR_OPS

#include <utility>

namespace suisen {
template <typename T, typename U>
std::pair<T, U>& operator+=(std::pair<T, U> &p1, const std::pair<T, U> &p2) {
    p1.first += p2.first, p1.second += p2.second;
    return p1;
}
template <typename T, typename U>
std::pair<T, U> operator+(const std::pair<T, U> &p1, const std::pair<T, U> &p2) {
    return {p1.first + p2.first, p1.second + p2.second};
}
template <typename T, typename U>
std::pair<T, U>& operator-=(std::pair<T, U> &p1, const std::pair<T, U> &p2) {
    p1.first -= p2.first, p1.second -= p2.second;
    return p1;
}
template <typename T, typename U>
std::pair<T, U> operator-(const std::pair<T, U> &p1, const std::pair<T, U> &p2) {
    return {p1.first - p2.first, p1.second - p2.second};
}
template <typename T, typename U, typename V>
std::pair<T, U>& operator*=(std::pair<T, U> &p, const V m) {
    p.first *= m, p.second *= m;
    return p;
}
template <typename T, typename U, typename V>
std::pair<T, U> operator*(const std::pair<T, U> &p, const V m) {
    return {p.first * m, p.second * m};
}
template <typename T, typename U, typename V>
std::pair<T, U> operator*(const V m, const std::pair<T, U> &p) {
    return {p.first * m, p.second * m};
}
} // namespace suisen

#endif // SUISEN_PAIR_OPS
