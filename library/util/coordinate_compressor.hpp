#ifndef SUISEN_COORDINATE_COMPRESSOR
#define SUISEN_COORDINATE_COMPRESSOR

#include <algorithm>
#include <cassert>
#include <vector>

#include "library/type_traits/type_traits.hpp"

namespace suisen {
template <typename T>
class CoordinateCompressorBuilder {
    public:
        struct Compressor {
            public:
                static constexpr int absent = -1;

                // default constructor
                Compressor() : _xs(std::vector<T>{}) {}
                // Construct from strictly sorted vector
                Compressor(const std::vector<T> &xs) : _xs(xs) {
                    assert(is_strictly_sorted(xs));
                }

                // Return the number of distinct keys.
                int size() const {
                    return _xs.size();
                }
                // Check if the element is registered.
                bool has_key(const T &e) const {
                    return std::binary_search(_xs.begin(), _xs.end(), e);
                }
                // Compress the element. if not registered, returns `default_value`. (default: Compressor::absent)
                int comp(const T &e, int default_value = absent) const {
                    const int res = min_geq_index(e);
                    return res != size() and _xs[res] == e ? res : default_value;
                }
                // Restore the element from the index.
                T decomp(const int compressed_index) const {
                    return _xs[compressed_index];
                }
                // Compress the element. Equivalent to call `comp(e)`
                int operator[](const T &e) const {
                    return comp(e);
                }
                // Return the minimum registered value greater than `e`. if not exists, return `default_value`.
                T min_gt(const T &e, const T &default_value) const {
                    auto it = std::upper_bound(_xs.begin(), _xs.end(), e);
                    return it == _xs.end() ? default_value : *it;
                }
                // Return the minimum registered value greater than or equal to `e`. if not exists, return `default_value`.
                T min_geq(const T &e, const T &default_value) const {
                    auto it = std::lower_bound(_xs.begin(), _xs.end(), e);
                    return it == _xs.end() ? default_value : *it;
                }
                // Return the maximum registered value less than `e`. if not exists, return `default_value`
                T max_lt(const T &e, const T &default_value) const {
                    auto it = std::upper_bound(_xs.rbegin(), _xs.rend(), e, std::greater<T>());
                    return it == _xs.rend() ? default_value : *it;
                }
                // Return the maximum registered value less than or equal to `e`. if not exists, return `default_value`
                T max_leq(const T &e, const T &default_value) const {
                    auto it = std::lower_bound(_xs.rbegin(), _xs.rend(), e, std::greater<T>());
                    return it == _xs.rend() ? default_value : *it;
                }
                // Return the compressed index of the minimum registered value greater than `e`. if not exists, return `compressor.size()`.
                int min_gt_index(const T &e) const {
                    return std::upper_bound(_xs.begin(), _xs.end(), e) - _xs.begin();
                }
                // Return the compressed index of the minimum registered value greater than or equal to `e`. if not exists, return `compressor.size()`.
                int min_geq_index(const T &e) const {
                    return std::lower_bound(_xs.begin(), _xs.end(), e) - _xs.begin();
                }
                // Return the compressed index of the maximum registered value less than `e`. if not exists, return -1.
                int max_lt_index(const T &e) const {
                    return int(_xs.rend() - std::upper_bound(_xs.rbegin(), _xs.rend(), e, std::greater<T>())) - 1;
                }
                // Return the compressed index of the maximum registered value less than or equal to `e`. if not exists, return -1.
                int max_leq_index(const T &e) const {
                    return int(_xs.rend() - std::lower_bound(_xs.rbegin(), _xs.rend(), e, std::greater<T>())) - 1;
                }
            private:
                std::vector<T> _xs;
                static bool is_strictly_sorted(const std::vector<T> &v) {
                    return std::adjacent_find(v.begin(), v.end(), std::greater_equal<T>()) == v.end();
                }
        };
        CoordinateCompressorBuilder() : _xs(std::vector<T>{}) {}
        explicit CoordinateCompressorBuilder(const std::vector<T> &xs) : _xs(xs) {}
        explicit CoordinateCompressorBuilder(std::vector<T> &&xs) : _xs(std::move(xs)) {}
        template <typename Gen, constraints_t<std::is_invocable_r<T, Gen, int>> = nullptr>
        CoordinateCompressorBuilder(const int n, Gen generator) {
            reserve(n);
            for (int i = 0; i < n; ++i) push(generator(i));
        }
        // Attempt to preallocate enough memory for specified number of elements.
        void reserve(int n) {
            _xs.reserve(n);
        }
        // Add data.
        void push(const T &first) {
            _xs.push_back(first);
        }
        // Add data.
        void push(T &&first) {
            _xs.push_back(std::move(first));
        }
        // Add data in the range of [first, last). 
        template <typename Iterator>
        auto push(const Iterator &first, const Iterator &last) -> decltype(std::vector<T>{}.push_back(*first), void()) {
            for (auto it = first; it != last; ++it) _xs.push_back(*it);
        }
        // Add all data in the container. Equivalent to `push(iterable.begin(), iterable.end())`.
        template <typename Iterable>
        auto push(const Iterable &iterable) -> decltype(std::vector<T>{}.push_back(*iterable.begin()), void()) {
            push(iterable.begin(), iterable.end());
        }
        // Add data.
        template <typename ...Args>
        void emplace(Args &&...args) {
            _xs.emplace_back(std::forward<Args>(args)...);
        }
        // Build compressor.
        auto build() {
            std::sort(_xs.begin(), _xs.end()), _xs.erase(std::unique(_xs.begin(), _xs.end()), _xs.end());
            return Compressor {_xs};
        }
        // Build compressor from vector.
        static auto build(const std::vector<T> &xs) {
            return CoordinateCompressorBuilder(xs).build();
        }
        // Build compressor from vector.
        static auto build(std::vector<T> &&xs) {
            return CoordinateCompressorBuilder(std::move(xs)).build();
        }
        // Build compressor from generator.
        template <typename Gen, constraints_t<std::is_invocable_r<T, Gen, int>> = nullptr>
        static auto build(const int n, Gen generator) {
            return CoordinateCompressorBuilder<T>(n, generator).build();
        }
    private:
        std::vector<T> _xs;
};

} // namespace suisen

#endif // SUISEN_COORDINATE_COMPRESSOR
