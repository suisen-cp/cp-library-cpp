#ifndef SUISEN_PRIORITY_SUM
#define SUISEN_PRIORITY_SUM

#include <queue>
#include <utility>

namespace suisen {
    namespace internal::priority_sum {
        template <typename T, typename Comparator, typename RevComparator>
        struct PrioritySum {
            using value_type = T;
            using comparator_type = Comparator;
            using reverse_comparator_type = RevComparator;

            PrioritySum() : PrioritySum(0) {}
            PrioritySum(int k) : _k(k), _sum(0), _cmp(), _rev_cmp(), _head_k(_cmp), _del_head_k(_cmp), _tail(_rev_cmp), _del_tail(_rev_cmp) {}

            value_type get_sum() const {
                return _sum;
            }

            void insert(const value_type &v) {
                _sum += v;
                _head_k.push(v);
                fix();
            }

            void erase(const value_type &v) {
                if (_head_k.size() and v == _head_k.top()) {
                    _sum -= v;
                    _head_k.pop();
                } else if (_head_k.size() and _rev_cmp(v, _head_k.top())) {
                    _sum -= v;
                    _del_head_k.push(v);
                } else {
                    _del_tail.push(v);
                }
                fix();
            }

            int get_k() const { return _k; }

            void set_k(int new_k) { _k = new_k, fix(); }
            void incr_k() { set_k(get_k() + 1); }
            void decr_k() { set_k(get_k() - 1); }

            int size() const {
                return int((_head_k.size() + _tail.size()) - (_del_head_k.size() + _del_tail.size()));
            }

        private:
            int _k;
            value_type _sum;
            comparator_type _cmp;
            reverse_comparator_type _rev_cmp;
            std::priority_queue<value_type, std::vector<value_type>, comparator_type> _head_k, _del_head_k;
            std::priority_queue<value_type, std::vector<value_type>, reverse_comparator_type> _tail, _del_tail;

            void fix() {
                while (int(_head_k.size() - _del_head_k.size()) < _k and _tail.size()) {
                    value_type v = std::move(_tail.top());
                    _tail.pop();
                    if (_del_tail.size() and _del_tail.top() == v) {
                        _del_tail.pop();
                    } else {
                        _sum += v;
                        _head_k.push(std::move(v));
                    }
                }
                while (int(_head_k.size() - _del_head_k.size()) > _k) {
                    value_type v = std::move(_head_k.top());
                    _head_k.pop();
                    if (_del_head_k.size() and _del_head_k.top() == v) {
                        _del_head_k.pop();
                    } else {
                        _sum -= v;
                        _tail.push(std::move(v));
                    }
                }
            }
        };
    } // internal::priority_sum

    template <typename T>
    using MaximumPrioritySum = internal::priority_sum::PrioritySum<T, std::less<T>, std::greater<T>>;
    template <typename T>
    using MinimumPrioritySum = internal::priority_sum::PrioritySum<T, std::greater<T>, std::less<T>>;
} // namespace suisen


#endif // SUISEN_PRIORITY_SUM
