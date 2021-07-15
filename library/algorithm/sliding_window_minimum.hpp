#include <cassert>
#include <vector>
#include <queue>
#include "library/type_traits/type_traits.hpp"

namespace suisen {
namespace prioritizing_mode {
    template <typename T>
    using left_most_min  = std::greater<T>;
    template <typename T>
    using right_most_min = std::greater_equal<T>;
    template <typename T>
    using left_most_max  = std::less<T>;
    template <typename T>
    using right_most_max = std::less_equal<T>;
}

template <typename T, typename Comparator = prioritizing_mode::left_most_min<T>, constraints_t<is_comparator<Comparator, T>> = nullptr>
class sliding_window_minimum {
    public:
        template <typename Gen, constraints_t<is_same_as_invoke_result<T, Gen, int>> = nullptr>
        sliding_window_minimum(int n, Gen gen) : _n(n), _a(n) {
            for (int i = 0; i < _n; ++i) _a[i] = gen(i);
        }
        void proc_right() {
            assert(_r < _n);
            T v = _a[_r];
            while (not _dq.empty() and _cmp(_a[_dq.back()], v)) _dq.pop_back();
            _dq.push_back(_r++);
        }
        void proc_right(int to_index) {
            while (_r < to_index) proc_right();
        }
        void proc_left() {
            assert(_l < _r);
            if (_dq.front() == _l) _dq.pop_front();
            ++_l;
        }
        void proc_left(int to_index) {
            while (_l < to_index) proc_left();
        }
        void proc(int new_l, int new_r) {
            proc_right(new_r), proc_left(new_l);
        }
        int arg_query() const {
            assert(_l < _r);
            return _dq.front();
        }
        T query() const {
            return _a[arg_query()];
        }

        int get_left() const {
            return _l;
        }
        int get_right() const {
            return _r;
        }
        int get_window_size() const {
            return _r - _l;
        }
    private:
        const int _n;
        int _l = 0, _r = 0;
        std::vector<T> _a;
        std::deque<int> _dq;
        Comparator _cmp;
};
} // namespace suisen