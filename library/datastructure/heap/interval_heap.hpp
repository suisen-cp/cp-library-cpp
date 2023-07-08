#ifndef SUISEN_INTERVAL_HEAP
#define SUISEN_INTERVAL_HEAP

#include <cassert>
#include <vector>
#include <functional>
#include <type_traits>
#include <utility>

namespace suisen {
    template <
        typename T, typename Comp = std::less<T>,
        std::enable_if_t<std::is_invocable_r_v<bool, Comp, T, T>, std::nullptr_t> = nullptr
    >
    struct IntervalHeap {
        using value_type = T;

        IntervalHeap() = default;
        IntervalHeap(const Comp& comp) : _comp(comp) {}

        void reserve(int capacity) { _dat.reserve(capacity); }

        bool empty() const { return _dat.empty(); }
        int size() const { return _dat.size(); }

        void push(const value_type& v) {
            _dat.push_back(v);
            fix_up(_dat.size() - 1);
        }
        template <typename ...Args>
        void emplace(Args &&...args) {
            push(value_type(std::forward<Args>(args)...));
        }

        const value_type& max() const {
            assert(_dat.size());
            return _dat[max_heap_top_index()];
        }
        const value_type& min() const {
            assert(_dat.size());
            return _dat[min_heap_top_index()];
        }

        value_type pop_max() {
            assert(_dat.size());
            const int idx = max_heap_top_index();
            std::swap(_dat[idx], _dat.back());
            value_type res = std::move(_dat.back());
            _dat.pop_back();
            fix_max_heap_down(idx);
            return res;
        }
        value_type pop_min() {
            assert(_dat.size());
            const int idx = min_heap_top_index();
            std::swap(_dat[idx], _dat.back());
            value_type res = std::move(_dat.back());
            _dat.pop_back();
            fix_min_heap_down(idx);
            return res;
        }
        const auto& data() const { return _dat; }
        auto &data() { return _dat; }

        // for debug
        void check_heap_property() const {
            const int siz = size();
            for (int i = 0; i < siz; ++i) {
                if (i % 2 == 0) {
                    int lch = min_heap_child_l(i), rch = min_heap_child_r(i);
                    if (lch < siz) assert(not _comp(_dat[lch], _dat[i]));
                    if (rch < siz) assert(not _comp(_dat[rch], _dat[i]));
                    if (i + 1 < siz) assert(not _comp(_dat[i + 1], _dat[i]));
                } else {
                    int lch = max_heap_child_l(i), rch = max_heap_child_r(i);
                    lch -= lch >= siz, rch -= rch >= siz;
                    if (lch < siz) assert(not _comp(_dat[i], _dat[lch]));
                    if (rch < siz) assert(not _comp(_dat[i], _dat[rch]));
                }
            }
        }
    private:
        // even : min_heap, odd : max_heap
        std::vector<value_type> _dat;
        Comp _comp;

        int min_heap_top_index() const { return 0; }
        int max_heap_top_index() const { return _dat.size() >= 2; }

        void fix_up(int idx) {
            if (const int l = idx & ~0b1, r = l | 1; r < int(_dat.size())) {
                if (_comp(_dat[r], _dat[l])) std::swap(_dat[l], _dat[r]), idx ^= 1;
                fix_min_heap_up(l), fix_max_heap_up(r);
            } else {
                fix_min_heap_up(l), fix_max_heap_up(l);
            }
        }
        void fix_min_heap_up(int idx) {
            while (idx >= 2) {
                if (int par = min_heap_parent(idx); _comp(_dat[idx], _dat[par])) std::swap(_dat[std::exchange(idx, par)], _dat[par]);
                else return;
            }
        }
        void fix_max_heap_up(int idx) {
            while (idx >= 2) {
                if (int par = max_heap_parent(idx); _comp(_dat[par], _dat[idx])) std::swap(_dat[std::exchange(idx, par)], _dat[par]);
                else return;
            }
        }
        void fix_min_heap_down(int idx) {
            const int siz = _dat.size();
            while (true) {
                int lch = min_heap_child_l(idx), rch = min_heap_child_r(idx);
                if (lch >= siz) {
                    fix_up(idx);
                    break;
                }
                int ch = rch < siz and _comp(_dat[rch], _dat[lch]) ? rch : lch;
                if (_comp(_dat[ch], _dat[idx])) std::swap(_dat[std::exchange(idx, ch)], _dat[ch]);
                else break;
            }
        }
        void fix_max_heap_down(int idx) {
            const int siz = _dat.size();
            while (true) {
                int lch = max_heap_child_l(idx), rch = max_heap_child_r(idx);
                lch -= lch >= siz, rch -= rch >= siz;
                if (lch >= siz) {
                    fix_up(idx);
                    break;
                }
                int ch = rch < siz and _comp(_dat[lch], _dat[rch]) ? rch : lch;
                if (_comp(_dat[idx], _dat[ch])) std::swap(_dat[std::exchange(idx, ch)], _dat[ch]);
                else break;
            }
        }

        static constexpr int min_heap_parent(int idx) { return (idx - 2) >> 2 << 1; }
        static constexpr int max_heap_parent(int idx) { return min_heap_parent(idx) | 1; }
        static constexpr int min_heap_child_l(int idx) { return (idx + 1) << 1; }
        static constexpr int min_heap_child_r(int idx) { return (idx + 2) << 1; }
        static constexpr int max_heap_child_l(int idx) { return min_heap_child_l(idx - 1) | 1; }
        static constexpr int max_heap_child_r(int idx) { return min_heap_child_r(idx - 1) | 1; }
    };
} // namespace suisen


#endif // SUISEN_INTERVAL_HEAP
