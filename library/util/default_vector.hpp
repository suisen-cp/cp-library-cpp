#ifndef SUISEN_DEFAULT_VECTOR
#define SUISEN_DEFAULT_VECTOR

#include <iostream>
#include <initializer_list>
#include <vector>

namespace suisen {
template <typename T>
class default_vector {
    public:
        default_vector() {}
        explicit default_vector(const T default_value) : _default_value(default_value) {}
        explicit default_vector(const T default_value, int n) : _default_value(default_value), _data(n, default_value) {}
        explicit default_vector(const T default_value, const std::initializer_list<T> list) : _default_value(default_value), _data(list) {}

        int size() const {
            return _data.size();
        }
        void reserve(int n) {
            _data.reserve(n);
        }
        const T& operator[](int i) const {
            ensure_size(i);
            return _data[i];
        }
        T& operator[](int i) {
            ensure_size(i);
            return _data[i];
        }
        const T& front() const { return _data.front(); }
        T& front()             { return _data.front(); }
        const T& back() const  { return _data.back(); }
        T& back()              { return _data.back(); }
    
        auto begin()   { return _data.begin(); }
        auto end()     { return _data.end(); }
        auto rbegin()  { return _data.rbegin(); }
        auto rend()    { return _data.rend(); }
        auto cbegin()  { return _data.cbegin(); }
        auto cend()    { return _data.cend(); }
        auto crbegin() { return _data.crbegin(); }
        auto crend()   { return _data.crend(); }
    
        void push_back(const T &element) {
            _data.push_back(element);
        }
        void push_back(const T &&element) {
            _data.push_back(element);
        }
        template <typename ...Args>
        void emplace_back(Args &&...args) {
            _data.emplace_back(std::forward<Args>(args)...);
        }

        void pop_back() {
            _data.pop_back();
        }

        void erase(const typename std::vector<T>::const_iterator position) {
            _data.erase(position);
        }
        void erase(const typename std::vector<T>::const_iterator first, const typename std::vector<T>::const_iterator last) {
            _data.erase(first, last);
        }
        void clear() {
            _data.clear();
        }
        void insert(const typename std::vector<T>::const_iterator position, const T &element) {
            _data.insert(position, element);
        }
        void insert(const typename std::vector<T>::const_iterator position, const T &&element) {
            _data.insert(position, element);
        }
        void insert(const typename std::vector<T>::const_iterator position, const std::initializer_list<T> list) {
            _data.insert(position, list);
        }
        template <typename InputIterator>
        void insert(const typename std::vector<T>::const_iterator position, const InputIterator first, const InputIterator last) {
            _data.insert(position, first, last);
        }

        void swap(default_vector<T> &other) {
            _data.swap(other._data);
        }

        friend std::istream& operator>>(std::ostream& in, const default_vector<T> &a) {
            return in >> a._data;
        }
        friend std::ostream& operator<<(std::ostream& out, const default_vector<T> &a) {
            return out << a._data;
        }
    private:
        const T _default_value;
        std::vector<T> _data;
        void ensure_size(int n) {
            if (int(_data.size()) < n + 1) {
                _data.resize(n + 1, _default_value);
            }
        }
};
} // namespace suisen

#endif // SUISEN_DEFAULT_VECTOR