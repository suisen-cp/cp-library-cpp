#ifndef SUISEN_XOR_BASE
#define SUISEN_XOR_BASE

#include <vector>

namespace suisen {
    template <typename T>
    struct XorBase {
        XorBase() = default;
        XorBase(const std::vector<T> &a) : XorBase() {
            for (const auto &v : a) add(v);
        }

        bool add(T v) {
            for (const auto &e : _basis) if (T w = e ^ v; w < v) v = std::move(w);
            return v ? (_basis.push_back(v), true) : false;
        }
        XorBase<T>& operator+=(const XorBase<T> &rhs) {
            for (const T &e : rhs._basis) add(e);
            return *this;
        }
        XorBase<T>& operator+=(const T &v) {
            add(v);
            return *this;
        }
        XorBase<T> operator+(const XorBase<T> &rhs) const {
            XorBase<T> res;
            res._basis = _basis;
            return res += rhs;
        }
        XorBase<T> operator+(const T &v) const {
            return *this + XorBase<T>({ v });
        }

        XorBase<T> intersection(const XorBase<T> &rhs) const {
            std::vector<std::pair<T, T>> basis;
            for (const T &e : _basis) basis.emplace_back(e, e);
            XorBase<T> res;
            for (T e : rhs._basis) {
                T s;
                if constexpr (std::is_integral_v<T>) s = 0;
                for (const auto &[v, t] : basis) if (T w = e ^ v; w < e) e = std::move(w), s ^= t;
                if (e) basis.emplace_back(e, s);
                else res.add(s);
            }
            return res;
        }
        XorBase<T>& operator&=(const XorBase<T> &rhs) {
            return *this = intersection(rhs);
        }
        XorBase<T> operator&(const XorBase<T> &rhs) const {
            return intersection(rhs);
        }

        int dim() const { return _basis.size(); }

        const std::vector<T>& get_basis() const { return _basis; }
    private:
        std::vector<T> _basis;
    };
} // namespace suisen


#endif // SUISEN_XOR_BASE
