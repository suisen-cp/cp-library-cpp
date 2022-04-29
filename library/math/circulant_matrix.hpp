#ifndef SUISEN_CIRCULANT_MATRIX
#define SUISEN_CIRCULANT_MATRIX

#include <cassert>
#include <iostream>
#include <vector>

namespace suisen {
    template <typename T>
    struct CirculantMatrix {
        using value_type = T;
        using convolution_t = std::vector<value_type>(*)(const std::vector<value_type>&, const std::vector<value_type>&);

        // empty matrix
        CirculantMatrix() : CirculantMatrix(std::vector<value_type>{}) {}

        /**
         * +-                        -+
         * | a[0] a[4] a[3] a[2] a[1] |
         * | a[1] a[0] a[4] a[3] a[2] |
         * | a[2] a[1] a[0] a[4] a[3] |
         * | a[3] a[2] a[1] a[0] a[4] |
         * | a[4] a[3] a[2] a[1] a[0] |
         * +-                        -+
         */
        explicit CirculantMatrix(const std::vector<value_type>& a) : _dat(a) {}

        static void set_multiplication(convolution_t multiplication) {
            convolve = multiplication;
        }

        static CirculantMatrix<value_type> e0(int n, const value_type& zero = value_type{ 0 }) {
            return CirculantMatrix<value_type>{ std::vector<value_type>(n, zero) };
        }
        static CirculantMatrix<value_type> e1(int n, const value_type& zero = value_type{ 0 }, const value_type& one = value_type{ 1 }) {
            auto dat = std::vector<value_type>(n, zero);
            dat[0] = one;
            return CirculantMatrix<value_type>{ dat };
        }

        int size() const {
            return _dat.size();
        }

        value_type get(int i, int j) const {
            const int n = size();
            int k = i - j;
            if (k < 0) k += n;
            return _dat[k];
        }
        value_type operator[](const std::pair<int, int> &p) const {
            return get(p.first, p.second);
        }

        friend CirculantMatrix<value_type> operator+(const CirculantMatrix<value_type>& mat) {
            return mat;
        }
        friend CirculantMatrix<value_type> operator-(const CirculantMatrix<value_type>& mat) {
            const int n = mat.size();
            std::vector<value_type> res(n);
            for (int i = 0; i < n; ++i) res[i] = -mat._dat[i];
            return CirculantMatrix<value_type> { std::move(res) };
        }
        friend CirculantMatrix<value_type> operator+(const CirculantMatrix<value_type>& lhs, const CirculantMatrix<value_type>& rhs) {
            const int n = lhs.size();
            assert(n == int(rhs.size()));
            std::vector<value_type> res(n);
            for (int i = 0; i < n; ++i) res[i] = lhs._dat[i] + rhs._dat[i];
            return CirculantMatrix<value_type> { std::move(res) };
        }
        friend CirculantMatrix<value_type> operator-(const CirculantMatrix<value_type>& lhs, const CirculantMatrix<value_type>& rhs) {
            const int n = lhs.size();
            assert(n == int(rhs.size()));
            std::vector<value_type> res(n);
            for (int i = 0; i < n; ++i) res[i] = lhs._dat[i] - rhs._dat[i];
            return CirculantMatrix<value_type> { std::move(res) };
        }
        friend CirculantMatrix<value_type> operator*(const CirculantMatrix<value_type>& lhs, const CirculantMatrix<value_type>& rhs) {
            const int n = lhs.size();
            assert(n == int(rhs.size()));
            std::vector<value_type> res = convolve(lhs._dat, rhs._dat);
            for (int i = n; i < int(res.size()); ++i) res[i - n] += res[i];
            res.resize(n);
            return CirculantMatrix<value_type> { std::move(res) };
        }
        friend std::vector<value_type> operator*(const CirculantMatrix<value_type>& mat, const std::vector<value_type>& x) {
            return std::move((mat * CirculantMatrix<value_type> { x })._dat);
        }
        friend CirculantMatrix<value_type> operator*(const CirculantMatrix<value_type>& mat, const value_type& coef) {
            const int n = mat.size();
            std::vector<value_type> res(n);
            for (int i = 0; i < n; ++i) res[i] = coef * mat._dat[i];
            return CirculantMatrix<value_type> { res };
        }
        friend CirculantMatrix<value_type> operator*(const value_type& coef, const CirculantMatrix<value_type>& mat) {
            return mat * coef;
        }

        CirculantMatrix<value_type>& operator+=(const CirculantMatrix<value_type>& rhs) {
            return *this = *this + rhs;
        }
        CirculantMatrix<value_type>& operator-=(const CirculantMatrix<value_type>& rhs) {
            return *this = *this - rhs;
        }
        CirculantMatrix<value_type>& operator*=(const CirculantMatrix<value_type>& rhs) {
            return *this = *this * rhs;
        }
        CirculantMatrix<value_type>& operator*=(const value_type& coef) {
            return *this = *this * coef;
        }

        CirculantMatrix<value_type> pow(long long b) {
            auto res = CirculantMatrix<value_type>::e1(size());
            for (auto p = *this; b; b >>= 1) {
                if (b & 1) res *= p;
                p *= p;
            }
            return res;
        }

    private:
        static inline convolution_t convolve{
            [](const auto&, const auto&) {
                std::cerr << "convolution function is not available." << std::endl;
                assert(false);
                return std::vector<value_type>{};
            }
        };

        std::vector<value_type> _dat;
    };
} // namespace suisen

#endif // SUISEN_CIRCULANT_MATRIX
