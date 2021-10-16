#ifndef SUISEN_RANGE_SET
#define SUISEN_RANGE_SET

#include <map>

namespace suisen {

template <typename T, bool merge_adjacent_segment = true>
struct RangeSet : public std::map<T, T> {
    public:
        RangeSet() : _size(0) {}

        // returns the number of intergers in this set (not the number of ranges). O(1)
        T size() const { return number_of_elements(); }
        // returns the number of intergers in this set (not the number of ranges). O(1)
        T number_of_elements() const { return _size; }
        // returns the number of ranges in this set (not the number of integers). O(1)
        int number_of_ranges() const { return std::map<T, T>::size(); }

        // returns whether the given integer is in this set or not. O(log N)
        bool contains(T x) const {
            auto it = this->upper_bound(x);
            return it != this->begin() and x <= std::prev(it)->second;
        }

        /**
         * returns the iterator pointing to the range [l, r] in this set s.t. l <= x <= r.
         * if such a range does not exist, returns `end()`.
         * O(log N)
         */
        auto find_range(T x) const {
            auto it = this->upper_bound(x);
            return it != this->begin() and x <= (--it)->second ? it : this->end();
        }

        // returns whether `x` and `y` is in this set and in the same range. O(log N)
        bool in_the_same_range(T x, T y) const {
            auto it = get_containing_range(x);
            return it != this->end() and it->first <= y and y <= it->second;
        }

        // inserts the range [x, x] and returns the number of integers inserted to this set. O(log N)
        T insert(T x) {
            return insert(x, x);
        }
        
        // inserts the range [l, r] and returns the number of integers inserted to this set. amortized O(log N)
        T insert(T l, T r) {
            if (l > r) return 0;
            auto it = this->upper_bound(l);
            if (it != this->begin() and is_mergeable(std::prev(it)->second, l)) {
                it = std::prev(it);
                l = std::min(l, it->first);
            }
            T inserted = 0;
            for (; it != this->end() and is_mergeable(r, it->first); it = std::map<T, T>::erase(it)) {
                auto [cl, cr] = *it; 
                r = std::max(r, cr);
                inserted -= cr - cl + 1;
            }
            inserted += r - l + 1;
            (*this)[l] = r;
            _size += inserted;
            return inserted;
        }

        // erases the range [x, x] and returns the number of intergers erased from this set. O(log N)
        T erase(T x) {
            return erase(x, x);
        }

        // erases the range [l, r] and returns the number of intergers erased from this set. amortized O(log N)
        T erase(T l, T r) {
            if (l > r) return 0;
            T tl = l, tr = r;
            auto it = this->upper_bound(l);
            if (it != this->begin() and l <= std::prev(it)->second) {
                it = std::prev(it);
                tl = it->first;
            }
            T erased = 0;
            for (; it != this->end() and it->first <= r; it = std::map<T, T>::erase(it)) {
                auto [cl, cr] = *it;
                tr = cr;
                erased += cr - cl + 1;
            }
            if (tl < l) {
                (*this)[tl] = l - 1;
                erased -= l - tl;
            }
            if (r < tr) {
                (*this)[r + 1] = tr;
                erased -= tr - r;
            }
            _size -= erased;
            return erased;
        }

        // returns minimum integer x s.t. x >= lower and x is NOT in this set
        T minimum_excluded(T lower = 0) const {
            static_assert(merge_adjacent_segment);
            auto it = find_range(lower);
            return it == this->end() ? lower : it->second + 1;
        }

        // returns maximum integer x s.t. x <= upper and x is NOT in this set
        T maximum_excluded(T upper) const {
            static_assert(merge_adjacent_segment);
            auto it = find_range(upper);
            return it == this->end() ? upper : it->first - 1;
        }

    private:
        T _size;

        bool is_mergeable(T cur_r, T next_l) {
            return next_l <= cur_r + merge_adjacent_segment;
        }
};

} // namespace suisen

#endif // SUISEN_RANGE_SET
