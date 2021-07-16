#ifndef SUISEN_ITER_UTILS
#define SUISEN_ITER_UTILS

#include <algorithm>
#include <array>
#include <initializer_list>
#include <numeric>
#include <limits>
#include <vector>

namespace suisen {
namespace internal {

template <typename T>
const auto true_pred = [](const T){ return true; };

template <typename Container, bool ascending, bool (*f)(typename Container::iterator, typename Container::iterator)>
class internal_permutations {
    private:
        struct permutations_iterator {
            Container p;
            bool next;
            permutations_iterator(const Container &&container) : p(std::move(container)), next(p.size()) { next = p.size(); }
            permutations_iterator() {
                if (ascending) std::iota(p. begin(), p. end(), 0);
                else           std::iota(p.rbegin(), p.rend(), 0);
                next = p.size();
            }
            Container operator*() const {
                return p;
            }
            bool operator!=(const permutations_iterator) const {
                return next;
            }
            permutations_iterator& operator++() {
                next = f(p.begin(), p.end());
                return *this;
            }
        };
        Container container;
        bool init;
    public:
        internal_permutations() : container(), init(false) {}
        internal_permutations(const Container  &container) : container(container), init(true) {}
        internal_permutations(const Container &&container) : container(std::move(container)), init(true) {}
        permutations_iterator begin() const { return init ? permutations_iterator(std::move(container)) : end(); }
        permutations_iterator end()   const { return permutations_iterator{}; }
};

template <int n>
using permutations      = internal_permutations<std::array<int, n>, true,  std::next_permutation<typename std::array<int, n>::iterator>>;
template <int n>
using permutations_desc = internal_permutations<std::array<int, n>, false, std::prev_permutation<typename std::array<int, n>::iterator>>;
using vec_permutations      = internal_permutations<std::vector<int>, true,  std::next_permutation<typename std::vector<int>::iterator>>;
using vec_permutations_desc = internal_permutations<std::vector<int>, false, std::prev_permutation<typename std::vector<int>::iterator>>;

} // namespace internal

template <
    typename F, typename Iterable,
    typename Iterator = typename Iterable::const_iterator, typename value_type = typename Iterable::value_type
>
class enumerate_if {
    private:
        struct enumerate_iterator {
            F pred;
            Iterator it;
            int num;
            int i;
            enumerate_iterator(const F pred, const Iterator iterator, int num) : pred(pred), it(iterator), num(num), i(0) {}
            std::pair<int, value_type> operator*() const {
                return {i, *it};
            }
            bool operator!=(const enumerate_iterator &other) {
                if (i == num) return false;
                while (it != other.it and not pred(*it)) ++it;
                return it != other.it;
            }
            enumerate_iterator& operator++() {
                ++i, ++it;
                return *this;
            }
        };
        const F pred;
        const Iterable &iterable;
        const int max_iterate_num;
    public:
        enumerate_if(const F pred, const Iterable &iterable, const int max_iterate_num = std::numeric_limits<int>::max())
            : pred(pred), iterable(iterable), max_iterate_num(max_iterate_num) {}
        auto begin() const {
            return enumerate_iterator(pred, iterable.begin(), max_iterate_num);
        }
        auto end() const {
            return enumerate_iterator(pred, iterable.end(), max_iterate_num);
        }
};

template <typename Iterable, typename Iterator = typename Iterable::const_iterator, typename value_type = typename Iterable::value_type>
struct enumerate : public enumerate_if<decltype(internal::true_pred<value_type>), Iterable> {
    enumerate(const Iterable &iterable, const int max_iterate_num = std::numeric_limits<int>::max()) :
        enumerate_if<decltype(internal::true_pred<value_type>), Iterable>(internal::true_pred<value_type>, iterable, max_iterate_num) {}
};

template <typename T>
class range {
    private:
        struct range_iterator {
            T cur;
            const T r, step;
            range_iterator(T l, T r, T step) : cur(l), r(r), step(step) {}
            range_iterator() : range_iterator(0, 0, 0) {}
            T operator*() const {
                return cur;
            }
            bool operator!=(const range_iterator) const {
                return cur < r;
            }
            range_iterator& operator++() {
                cur += step;
                return *this;
            }
        };
        const T l, r, step;
    public:
        range(T l, T r, T step) : l(l), r(r), step(step) {}
        range(T l, T r) : range(l, r, 1) {}
        range(T r) : range(0, r) {}
        auto begin() const { return range_iterator{l, r, step}; }
        auto end()   const { return range_iterator{}; }
};

template <int n>
auto all_permutations() { return internal::permutations<n>{}; }
template <int n>
auto all_permutations(const std::array<int, n>  &a) { return internal::permutations<n>(a); }
template <int n>
auto all_permutations(const std::array<int, n> &&a) { return internal::permutations<n>(std::move(a)); }
template <int n>
auto all_permutations_desc() { return internal::permutations_desc<n>{}; }
template <int n>
auto all_permutations_desc(const std::array<int, n>  &a) { return internal::permutations_desc<n>(a); }
template <int n>
auto all_permutations_desc(const std::array<int, n> &&a) { return internal::permutations_desc<n>(std::move(a)); }
auto all_permutations(int n) {
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    return internal::vec_permutations(std::move(p));
}
auto all_permutations(const std::vector<int>  &p) { return internal::vec_permutations(p); }
auto all_permutations(const std::vector<int> &&p) { return internal::vec_permutations(std::move(p)); }
auto all_permutations_desc(int n) {
    std::vector<int> p(n);
    std::iota(p.rbegin(), p.rend(), 0);
    return internal::vec_permutations_desc(std::move(p));
}
auto all_permutations_desc(const std::vector<int>  &p) { return internal::vec_permutations_desc(p); }
auto all_permutations_desc(const std::vector<int> &&p) { return internal::vec_permutations_desc(std::move(p)); }

} // namespace suisen

#endif // SUISEN_ITER_UTILS
