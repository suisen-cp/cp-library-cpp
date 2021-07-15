#include <vector>

namespace suisen {
template <typename Container>
class run_length_encoder {
    public:
        using content_type   = typename Container::value_type;
        using value_type     = std::pair<content_type, int>;
        using iterator       = typename std::vector<value_type>::iterator;
        using const_iterator = typename std::vector<value_type>::const_iterator;

        run_length_encoder(const Container &c) noexcept {
            compress(c, comp);
        }

        static void compress(const Container &c, std::vector<value_type> &res) {
            res.clear();
            for (auto it_l = c.begin(), it_r = c.begin(); it_l != c.end(); it_l = it_r) {
                while (it_r != c.end() and *it_l == *it_r) ++it_r;
                res.emplace_back(*it_l, it_r - it_l);
            }
        }
        static std::vector<value_type> compress(const Container &c) {
            std::vector<value_type> res;
            compress(std::forward<Container>(c), res);
            return res;
        }
        static std::vector<value_type> compress(const Container &&c) {
            std::vector<value_type> res;
            compress(std::forward<Container>(c), res);
            return res;
        }

        const auto& cdata() const noexcept { return comp; }
              auto   data() const noexcept { return comp; }

        int max_size() const noexcept { return comp.max_size(); }
        int capacity() const noexcept { return comp.capacity(); }
        int size()     const noexcept { return comp.size(); }
        void reserve(int n) { comp.reserve(n); }
        void shrink_to_fit() { comp.shrink_to_fit(); }
        void resize(int n) { comp.resize(); }
        void resize(int n, const value_type  &x) { comp.resize(n, x); }
        void resize(int n, const value_type &&x) { comp.resize(n, x); }
        void assign(int n, const value_type  &x) { comp.assign(n, x); }
        void assign(int n, const value_type &&x) { comp.assign(n, x); }
        template <typename InputIterator>
        void assign(const InputIterator first, const InputIterator last) { comp.assign(first, last); }
        void swap(run_length_encoder<Container>  &other) { comp.swap(other.comp); }
        void swap(run_length_encoder<Container> &&other) { comp.swap(other.comp); }
        void clear() { comp.clear(); }

        auto begin()   const noexcept { return comp.begin();   }
        auto end()     const noexcept { return comp.end();     }
        auto rbegin()  const noexcept { return comp.rbegin();  }
        auto rend()    const noexcept { return comp.rend();    }
        auto cbegin()  const noexcept { return comp.cbegin();  }
        auto cend()    const noexcept { return comp.cend();    }
        auto crbegin() const noexcept { return comp.crbegin(); }
        auto crend()   const noexcept { return comp.crend();   }

        const auto& operator[](const int i) const { return comp[i]; }
              auto& operator[](const int i)       { return comp[i]; }
        const auto& at(const int i) const { return comp.at(i); }
              auto& at(const int i)       { return comp.at(i); }
        const auto& front() const { return comp.front(); }
              auto& front()       { return comp.front(); }
        const auto& back()  const { return comp.back(); }
              auto& back()        { return comp.back(); }

        void erase(const const_iterator pos) { comp.erase(pos); }
        void erase(const const_iterator first, const const_iterator last) { comp.erase(first, last); }
        void pop_back() { comp.pop_back(); }
        void insert(const const_iterator pos, value_type  &entry) { comp.insert(pos, std::forward<value_type>(entry)); }
        void insert(const const_iterator pos, value_type &&entry) { comp.insert(pos, std::forward<value_type>(entry)); }
        void push_back(value_type  &entry) { comp.push_back(std::forward<value_type>(entry)); }
        void push_back(value_type &&entry) { comp.push_back(std::forward<value_type>(entry)); }
        template <typename ...Args>
        void emplace(const const_iterator pos, Args  &...args) { comp.emplace(pos, std::forward<Args>(args)...); }
        template <typename ...Args>
        void emplace(const const_iterator pos, Args &&...args) { comp.emplace(pos, std::forward<Args>(args)...); }
        template <typename ...Args>
        void emplace_back(Args  &...args) { comp.emplace_back(std::forward<Args>(args)...); }
        template <typename ...Args>
        void emplace_back(Args &&...args) { comp.emplace_back(std::forward<Args>(args)...); }
    private:
        std::vector<value_type> comp;
};
} // namespace suisen