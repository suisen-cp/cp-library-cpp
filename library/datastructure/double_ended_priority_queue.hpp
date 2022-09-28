#ifndef SUISEN_DOUBLE_ENDED_PRIORITY_QUEUE
#define SUISEN_DOUBLE_ENDED_PRIORITY_QUEUE

#include <cassert>
#include <vector>
#include <functional>

namespace suisen {
    template <typename T, typename Comp = std::less<T>>
    struct DoubleEndedPriorityQueue {
        DoubleEndedPriorityQueue() {}
        DoubleEndedPriorityQueue(const Comp& comp) : _comp(comp) {}

        void push(const T& v) {
            _dat.push_back(v);
            fix_up(_dat.size() - 1);
        }
        template <typename ...Args>
        void emplace(Args &&...args) {
            push(T(std::forward<Args>(args)...));
        }

        const T& max() const {
            assert(_dat.size());
            return _dat[_dat.size() >= 2];
        }
        const T& min() const {
            assert(_dat.size());
            return _dat[0];
        }

        T pop_max() {
            assert(_dat.size());
            int idx = _dat.size() >= 2;
            T res = std::move(_dat[idx]);
            if (_dat.size() == 1) {
                _dat.pop_back();
                return res;
            }
            _dat[idx] = std::move(_dat.back());
            _dat.pop_back();

            const int siz = _dat.size();
            while (true) {
                int lch = max_heap_child_l(idx), rch = max_heap_child_r(idx);
                lch -= lch >= siz;
                rch -= rch >= siz;
                if (lch >= siz) {
                    fix_up(idx);
                    break;
                }
                int ch = rch < siz and _comp(_dat[lch], _dat[rch]) ? rch : lch;
                if (_comp(_dat[idx], _dat[ch])) {
                    std::swap(_dat[idx], _dat[ch]);
                    idx = ch;
                } else break;
            }
            return res;
        }
        T pop_min() {
            assert(_dat.size());
            int idx = 0;
            T res = std::move(_dat[idx]);
            if (_dat.size() == 1) {
                _dat.pop_back();
                return res;
            }
            _dat[idx] = std::move(_dat.back());
            _dat.pop_back();

            const int siz = _dat.size();
            while (true) {
                int lch = min_heap_child_l(idx), rch = min_heap_child_r(idx);
                if (lch >= siz) {
                    fix_up(idx);
                    break;
                }
                int ch = rch < siz and _comp(_dat[rch], _dat[lch]) ? rch : lch;
                if (_comp(_dat[ch], _dat[idx])) {
                    std::swap(_dat[idx], _dat[ch]);
                    idx = ch;
                } else break;
            }
            return res;
        }

        const std::vector<T>& data() const {
            return _dat;
        }
    private:
        // even : min_heap
        // odd  : max_heap
        std::vector<T> _dat;
        Comp _comp;

        void fix_up(int idx) {
            int l = idx & ~0b1, r = l | 1;
            if (r < int(_dat.size())) {
                if (_comp(_dat[r], _dat[l])) {
                    std::swap(_dat[l], _dat[r]);
                    idx ^= 1;
                }
                fix_min_heap_up(l), fix_max_heap_up(r);
            } else {
                fix_min_heap_up(l), fix_max_heap_up(l);
            }
        }
        void fix_min_heap_up(int idx) {
            while (idx >= 2) {
                int par = min_heap_parent(idx);
                if (_comp(_dat[idx], _dat[par])) {
                    std::swap(_dat[idx], _dat[par]);
                    idx = par;
                } else return;
            }
        }
        void fix_max_heap_up(int idx) {
            while (idx >= 2) {
                int par = max_heap_parent(idx);
                if (_comp(_dat[par], _dat[idx])) {
                    std::swap(_dat[idx], _dat[par]);
                    idx = par;
                } else return;
            }
        }

        static constexpr int min_heap_parent(int idx) {
            return (idx - 2) >> 2 << 1;
        }
        static constexpr int max_heap_parent(int idx) {
            return min_heap_parent(idx) | 1;
        }
        static constexpr int min_heap_child_l(int idx) {
            return (idx + 1) << 1;
        }
        static constexpr int min_heap_child_r(int idx) {
            return (idx + 2) << 1;
        }
        static constexpr int max_heap_child_l(int idx) {
            return min_heap_child_l(idx - 1) | 1;
        }
        static constexpr int max_heap_child_r(int idx) {
            return min_heap_child_r(idx - 1) | 1;
        }
    };
} // namespace suisen


#endif // SUISEN_DOUBLE_ENDED_PRIORITY_QUEUE
