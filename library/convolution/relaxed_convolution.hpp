#ifndef SUISEN_RELAXED_CONVOLUTION
#define SUISEN_RELAXED_CONVOLUTION

#include <vector>

namespace suisen {
    // reference: https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c
    template <typename T>
    struct RelaxedConvolution {
        using value_type = T;
        using polynomial_type = std::vector<value_type>;
        using convolution_type = polynomial_type(*)(const polynomial_type&, const polynomial_type&);

        RelaxedConvolution() = default;
        RelaxedConvolution(const convolution_type &convolve) : _convolve(convolve), _n(0), _f{}, _g{}, _h{} {}

        void set_convolve_function(const convolution_type &convolve) {
            _convolve = convolve;
        }

        value_type append(const value_type &fi, const value_type &gi) {
            ++_n;
            _f.push_back(fi), _g.push_back(gi);
            for (int p = 1;; p <<= 1) {
                int l1 = _n - p, r1 = _n, l2 = p - 1, r2 = l2 + p;
                add(l1 + l2, range_convolve(l1, r1, l2, r2));
                if (l1 == l2) break;
                add(l1 + l2, range_convolve(l2, r2, l1, r1));
                if (not (_n & p)) break;
            }
            return _h[_n - 1];
        }

        const value_type& operator[](int i) const {
            return _h[i];
        }
        polynomial_type get() const {
            return _h;
        }

    private:
        convolution_type _convolve = [](const polynomial_type&, const polynomial_type&) -> polynomial_type { assert(false); };
        int _n;
        polynomial_type _f, _g, _h;

        polynomial_type range_convolve(int l1, int r1, int l2, int r2) {
            return _convolve(polynomial_type(_f.begin() + l1, _f.begin() + r1), polynomial_type(_g.begin() + l2, _g.begin() + r2));
        }

        void add(std::size_t bias, const polynomial_type &h) {
            if (_h.size() < bias + h.size()) _h.resize(bias + h.size());
            for (std::size_t i = 0; i < h.size(); ++i) _h[bias + i] += h[i];
        }
    };
} // namespace suisen


#endif // SUISEN_RELAXED_CONVOLUTION
