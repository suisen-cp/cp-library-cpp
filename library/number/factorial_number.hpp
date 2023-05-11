#ifndef SUISEN_FACTORIAL_NUMBER
#define SUISEN_FACTORIAL_NUMBER

#include <algorithm>
#include <cassert>
#include <vector>

#include "library/datastructure/fenwick_tree/fenwick_tree_set.hpp"

namespace suisen {
    struct factorial_number {
        factorial_number(): factorial_number(1) {}
        explicit factorial_number(int n, long long val = 0): _n(n), _d(_n - 1) {
            bool neg = val < 0;
            val = std::abs(val);
            for (int i = 0; val and i < _n - 1; ++i) {
                _d[i] = val % (i + 2);
                val /= i + 2;
            }
            if (neg) *this = -*this;
        }
        explicit factorial_number(const std::vector<int>& perm): factorial_number(perm.size()) {
            fenwick_tree_set st(_n, true);
            for (int i = 0; i < _n - 1; ++i) {
                int v = perm[i];
                _d[_n - 2 - i] = st.index_of(v);
                st.erase(v);
            }
        }

        int size() const {
            return _n;
        }
        void resize(int n) {
            _n = n;
            _d.resize(_n - 1);
        }

        factorial_number operator-() const {
            factorial_number res(_n);
            res -= *this;
            return res;
        }

        factorial_number& operator++() {
            for (int i = 0; i < _n - 1; ++i) {
                if (++_d[i] > i + 1) {
                    _d[i] = 0;
                } else {
                    break;
                }
            }
            return *this;
        }
        factorial_number& operator--() {
            for (int i = 0; i < _n - 1; ++i) {
                if (--_d[i] < 0) {
                    _d[i] = i + 1;
                } else {
                    break;
                }
            }
            return *this;
        }

        factorial_number operator++(int) {
            factorial_number res = *this;
            ++* this;
            return res;
        }
        factorial_number operator--(int) {
            factorial_number res = *this;
            --* this;
            return res;
        }

        factorial_number& operator+=(const factorial_number& x) {
            assert(size() == x.size());
            add(x, 0);
            return *this;
        }
        factorial_number& operator-=(factorial_number x) {
            assert(size() == x.size());
            for (int i = 0; i < _n - 1; ++i) {
                x._d[i] = (i + 1) - x._d[i];
            }
            add(x, 1);
            return *this;
        }

        friend factorial_number operator+(const factorial_number& x, const factorial_number& y) {
            factorial_number z = x;
            z += y;
            return z;
        }
        friend factorial_number operator-(const factorial_number& x, const factorial_number& y) {
            factorial_number z = x;
            z -= y;
            return z;
        }

        factorial_number& operator+=(long long val) {
            return *this += factorial_number(_n, val);
        }
        factorial_number& operator-=(long long val) {
            return *this -= factorial_number(_n, val);
        }

        friend factorial_number operator+(const factorial_number& x, long long val) {
            return x + factorial_number(x._n, val);
        }
        friend factorial_number operator-(const factorial_number& x, long long val) {
            return x - factorial_number(x._n, val);
        }
        friend factorial_number operator+(long long val, const factorial_number& x) {
            return factorial_number(x._n, val) + x;
        }
        friend factorial_number operator-(long long val, const factorial_number& x) {
            return factorial_number(x._n, val) - x;
        }

        factorial_number& operator*=(long long val) {
            bool neg = val < 0;
            val = std::abs(val);
            __int128_t carry = 0;
            for (int i = 0; i < _n - 1; ++i) {
                __int128_t x = __int128_t(_d[i]) * val + carry;
                _d[i] = x % (i + 2);
                carry = x / (i + 2);
            }
            if (neg) *this = -*this;
            return *this;
        }
        friend factorial_number operator*(const factorial_number& x, long long val) {
            factorial_number z = x;
            z *= val;
            return z;
        }
        friend factorial_number operator*(long long val, const factorial_number& x) {
            return x * val;
        }

        std::vector<int> to_permutation() const {
            fenwick_tree_set st(_n, true);
            std::vector<int> p(_n);
            for (int i = 0; i < _n; ++i) {
                int v = st.kth_element(i < _n - 1 ? _d[_n - 2 - i] : 0);
                p[i] = v;
                st.erase(v);
            }
            return p;
        }
        unsigned long long to_ull() const {
            unsigned long long res = 0;
            for (int i = _n - 2; i >= 0; --i) {
                res = res * (i + 2) + _d[i];
            }
            return res;
        }

        friend bool operator==(const factorial_number &x, const factorial_number &y) {
            return x._d == y._d;
        }
        friend bool operator!=(const factorial_number &x, const factorial_number &y) {
            return x._d != y._d;
        }
        friend bool operator<(const factorial_number &x, const factorial_number &y) {
            assert(x._n == y._n);
            for (int i = x._n - 2; i >= 0; --i) if (x._d[i] != y._d[i]) {
                return x._d[i] < y._d[i];
            }
            return false;
        }
        friend bool operator<=(const factorial_number &x, const factorial_number &y) {
            return not (y < x);
        }
        friend bool operator>(const factorial_number &x, const factorial_number &y) {
            return y < x;
        }
        friend bool operator>=(const factorial_number &x, const factorial_number &y) {
            return not (x < y);
        }
    private:
        // Sum[i=0,_n-2] _d[i] * (i+1)!
        int _n;
        std::vector<int> _d;

        void add(const factorial_number& x, int carry) {
            for (int i = 0; i < _n - 1; ++i) {
                _d[i] += x._d[i] + carry;
                if (_d[i] > i + 1) {
                    _d[i] -= i + 2;
                    carry = 1;
                } else {
                    carry = 0;
                }
            }
        }
        static int floor_log2(int x) {
            int l = 0;
            while (1 << (l + 1) <= x) ++l;
            return l;
        }
    };
} // namespace suisen


#endif // SUISEN_FACTORIAL_NUMBER
