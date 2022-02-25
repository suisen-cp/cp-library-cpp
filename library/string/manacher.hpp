#ifndef SUISEN_MANACHER
#define SUISEN_MANACHER

#include <vector>

namespace suisen {
    struct Manacher {
        Manacher() {}
        template <typename Container>
        Manacher(const Container& container, const typename Container::value_type& dummy) : _n(container.size()), _r(2 * _n + 1) {
            std::vector v{ dummy };
            for (const auto& val : container) v.push_back(val), v.push_back(dummy);
            build(v);
        }

        int operator[](int i) const { return _r[i]; }
        int odd_length(int i) const { return _r[2 * i + 1]; }
        int even_length(int i) const { return _r[2 * i]; }
    private:
        int _n;
        std::vector<int> _r;

        template <typename T>
        void build(const std::vector<T>& v) {
            for (int i = 0, j = 0, siz = v.size(); i < siz;) {
                while (i - j >= 0 and i + j < siz and v[i - j] == v[i + j]) ++j;
                _r[i] = j;
                int k = 1;
                while (i - k >= 0 and k + _r[i - k] < j) _r[i + k] = _r[i - k], ++k;
                i += k, j -= k;
            }
            for (int& r : _r) --r;
        }
    };
} // namespace suisen


#endif // SUISEN_MANACHER
