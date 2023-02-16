#ifndef SUISEN_STEP_VIEW
#define SUISEN_STEP_VIEW

#include <iterator>

namespace suisen {
    template <typename RandomAccessIterator>
    struct StepIterator {
        using difference_type   = typename std::iterator_traits<RandomAccessIterator>::difference_type;
        using value_type        = typename std::iterator_traits<RandomAccessIterator>::value_type;
        using pointer           = typename std::iterator_traits<RandomAccessIterator>::pointer;
        using reference         = typename std::iterator_traits<RandomAccessIterator>::reference;
        using iterator_category = typename std::iterator_traits<RandomAccessIterator>::iterator_category;
        static_assert(std::is_same_v<iterator_category, std::random_access_iterator_tag>);

        StepIterator(const RandomAccessIterator &it, int step) : _it(it), _step(step) {}
        StepIterator& operator++() { return _it += _step, *this; }
        StepIterator& operator--() { return _it -= _step, *this; }
        StepIterator operator++(int) { StepIterator ret = *this; ++(*this); return ret; }
        StepIterator operator--(int) { StepIterator ret = *this; --(*this); return ret; }
        StepIterator& operator+=(difference_type dif) { return _it += dif * _step, *this; }
        StepIterator& operator-=(difference_type dif) { return _it -= dif * _step, *this; }
        friend StepIterator operator+(StepIterator it, difference_type dif) { it += dif; return it; }
        friend StepIterator operator+(difference_type dif, StepIterator it) { it += dif; return it; }
        friend StepIterator operator-(StepIterator it, difference_type dif) { it -= dif; return it; }
        friend difference_type operator-(const StepIterator &lhs, const StepIterator &rhs) { return (lhs._it - rhs._it) / lhs._step; }
        reference operator[](difference_type i) const { return _it[i * _step]; }
        reference operator*() const { return *_it; }
        friend bool operator==(const StepIterator &lhs, const StepIterator &rhs) { return lhs._it == rhs._it; }
        friend bool operator!=(const StepIterator &lhs, const StepIterator &rhs) { return lhs._it != rhs._it; }
        friend bool operator< (const StepIterator &lhs, const StepIterator &rhs) { return lhs._it <  rhs._it; }
        friend bool operator<=(const StepIterator &lhs, const StepIterator &rhs) { return lhs._it <= rhs._it; }
        friend bool operator> (const StepIterator &lhs, const StepIterator &rhs) { return lhs._it >  rhs._it; }
        friend bool operator>=(const StepIterator &lhs, const StepIterator &rhs) { return lhs._it >= rhs._it; }
    private:
        RandomAccessIterator _it;
        int _step;
    };

    template <typename RandomAccesibleContainer>
    struct StepView {
        using iterator   = typename RandomAccesibleContainer::iterator;
        using value_type = typename RandomAccesibleContainer::value_type;
        using reference  = typename RandomAccesibleContainer::reference;
        
        StepView(RandomAccesibleContainer& dat, int start, int step, int size) : _start(dat.begin() + start, step), _size(size) {}
        std::size_t size() const { return _size; }
        reference operator[](std::size_t k) const { return _start[k]; }
    private:
        StepIterator<iterator> _start;
        std::size_t _size;
    };
} // namespace suisen


#endif // SUISEN_STEP_VIEW
