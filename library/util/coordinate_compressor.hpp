#ifndef SUISEN_COORDINATE_COMPRESSOR
#define SUISEN_COORDINATE_COMPRESSOR

#include <algorithm>
#include <cassert>
#include <vector>

namespace suisen {
template <typename T>
class coordinate_compressor {
    public:
        explicit coordinate_compressor() noexcept {}

        void reserve(int n) { _xs.reserve(n); }
    
        void push(const T  &first) { _xs.push_back(first), _built = false; }
        void push(const T &&first) { _xs.push_back(first), _built = false; }
        template <typename Iterator>
        auto push(const Iterator first, const Iterator last) -> decltype(std::vector<T>{}.push_back(*first), void()) {
            for (auto it = first; it != last; ++it) _xs.push_back(*it);
            _built = false;
        }
        template <typename Iterable>
        auto push(const Iterable &iterable) -> decltype(std::vector<T>{}.push_back(*iterable.begin()), void()) {
            push(iterable.begin(), iterable.end());
        }
        template <typename ...Args>
        void emplace(Args  &...args) { _xs.emplace_back(std::forward<Args>(args)...), _built = false; }
        template <typename ...Args>
        void emplace(Args &&...args) { _xs.emplace_back(std::forward<Args>(args)...), _built = false; }
    
        void build() {
            std::sort(_xs.begin(), _xs.end());
            _xs.erase(std::unique(_xs.begin(), _xs.end()), _xs.end());
            _built = true;
        }
    
        inline int size() const {
            assert(_built);
            return _xs.size();
        }
        inline int comp(const T e) const {
            const int res = lower_bound(e);
            assert(res < int(_xs.size()) and _xs[res] == e);
            return res;
        }
        inline T decomp(const int compressed) const {
            assert(_built);
            return _xs[compressed];
        }
        inline int operator[](const T e) const {
            return comp(e);
        }
        inline int lower_bound(const T e) const {
            assert(_built);
            return std::lower_bound(_xs.begin(), _xs.end(), e) - _xs.begin();
        }
        inline int upper_bound(const T e) const {
            assert(_built);
            return std::upper_bound(_xs.begin(), _xs.end(), e) - _xs.begin();
        }
        inline bool has_key(const T e) const {
            assert(_built);
            int index = lower_bound(e);
            return index < size() and _xs[index] == e;
        }
    private:
        std::vector<T> _xs;
        bool _built = true;
};
} // namespace suisen

#endif // SUISEN_COORDINATE_COMPRESSOR
