#ifndef SUISEN_FENWICK_TREE
#define SUISEN_FENWICK_TREE

#include <vector>
#include <map>
#include <unordered_map>

#include "library/type_traits/type_traits.hpp"

namespace suisen {
    namespace internal {
        template <typename T, typename index_t = int, typename Container = std::vector<T>>
        class FenwickTreeBase {
        public:
            FenwickTreeBase() {}
            explicit FenwickTreeBase(index_t n) : n(n) {}

            int size() const {
                return n;
            }
            void add(index_t i, T v) {
                for (++i; i <= n; i += (i & -i)) data[i - 1] += v;
            }
            T sum(index_t l, index_t r) const {
                return sum(r) - sum(l);
            }
            auto operator[](int i) {
                struct {
                    int i;
                    FenwickTreeBase& ft;
                    operator T() const { return ft.sum(i, i + 1); }
                    auto& operator++() { return *this += 1; }
                    auto& operator--() { return *this -= 1; }
                    auto& operator+=(T val) { ft.add(i, val); return *this; }
                    auto& operator-=(T val) { ft.add(i, -val); return *this; }
                    auto& operator*=(T val) { T cur = ft.sum(i, i + 1); ft.add(i, cur * val - cur); return *this; }
                    auto& operator/=(T val) { T cur = ft.sum(i, i + 1); ft.add(i, cur / val - cur); return *this; }
                    auto& operator%=(T val) { T cur = ft.sum(i, i + 1); ft.add(i, cur % val - cur); return *this; }
                    auto& operator =(T val) { T cur = ft.sum(i, i + 1); ft.add(i, val - cur); return *this; }
                } obj{ i, *this };
                return obj;
            }
            T operator()(int l, int r) const { return sum(l, r); }

            Container& get_internal_container() { return data; }
        protected:
            index_t n;
            Container data;
            template <typename ...Args>
            FenwickTreeBase(index_t n, Args &&...args) : n(n), data(std::forward<Args>(args)...) {}
        private:
            T sum(int r) const {
                T s{};
                for (; r; r -= r & -r) s += data[r - 1];
                return s;
            }
        };

        template <typename Key, typename Value, bool unordered>
        using cond_map_t = std::conditional_t<unordered, std::unordered_map<Key, Value>, std::map<Key, Value>>;

    } // namespace internal

    template <typename T>
    struct FenwickTree : public internal::FenwickTreeBase<T> {
        FenwickTree() : FenwickTree(0) {}
        explicit FenwickTree(int n) : internal::FenwickTreeBase<T>::FenwickTreeBase(n, n, T{}) {}
        explicit FenwickTree(std::vector<T>&& a) : internal::FenwickTreeBase<T>::FenwickTreeBase(a.size(), std::move(a)) {
            for (int i = 1; i <= this->n; ++i) {
                int p = i + (i & -i);
                if (p <= this->n) this->data[p - 1] += this->data[i - 1];
            }
        }
        explicit FenwickTree(const std::vector<T>& a) : FenwickTree(std::vector<T>(a)) {}
    };

    template <typename T, typename index_t, bool use_unordered_map = false>
    using MapFenwickTree = internal::FenwickTreeBase<T, index_t, internal::cond_map_t<index_t, T, use_unordered_map>>;

} // namespace suisen

#endif // SUISEN_FENWICK_TREE
