#ifndef SUISEN_DEFAULT_VECTOR
#define SUISEN_DEFAULT_VECTOR

#include <vector>

namespace suisen {
template <typename T>
class default_vector : public std::vector<T> {
    public:
        using std::vector<T>::vector;
        void set_default_value(const T &val) {
            default_value = val;
        }
        const T& operator[](int i) const {
            return index_out_of_bounds(i) ? default_value : std::vector<T>::operator[](i);
        }
        T& operator[](int i) {
            if (index_out_of_bounds(i)) resize(i + 1);
            return std::vector<T>::operator[](i);
        }
        const T& at(int i) const {
            return (*this)[i];
        }
        T& at(int i) {
            return (*this)[i];
        }
        T get_or_default(int i) const {
            return index_out_of_bounds(i) ? default_value : std::vector<T>::operator[](i);
        }
        T get_or_default(int i, T tmp_default_value) const {
            return index_out_of_bounds(i) ? tmp_default_value : std::vector<T>::operator[](i);
        }
        int size() {
            return std::vector<T>::size();
        }
        void resize(int n) {
            std::vector<T>::resize(n, default_value);
        }
    private:
        T default_value;
        bool index_out_of_bounds(unsigned int i) const {
            return i >= std::vector<T>::size();
        }
};
} // namespace suisen

#endif // SUISEN_DEFAULT_VECTOR