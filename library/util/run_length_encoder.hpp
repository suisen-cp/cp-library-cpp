#ifndef SUISEN_RUN_LENGTH_ENCODER
#define SUISEN_RUN_LENGTH_ENCODER

#include <vector>

namespace suisen {
template <typename Container>
class RunLengthEncoder {
    public:
        using content_type   = typename Container::value_type;
        using value_type     = std::pair<content_type, long long>;
        using iterator       = typename std::vector<value_type>::iterator;
        using const_iterator = typename std::vector<value_type>::const_iterator;

        RunLengthEncoder() noexcept : _length(0), comp() {}
        RunLengthEncoder(const Container &c) noexcept {
            compress(c, comp);
            _length = c.size();
        }
        long long length() const noexcept {
            return _length;
        }
        void swap(RunLengthEncoder<Container>  &other) { comp.swap(other.comp); }
        void swap(RunLengthEncoder<Container> &&other) { comp.swap(other.comp); }
        void clear() { comp.clear(); }
        auto begin()   const noexcept { return comp.begin();   }
        auto end()     const noexcept { return comp.end();     }
        auto rbegin()  const noexcept { return comp.rbegin();  }
        auto rend()    const noexcept { return comp.rend();    }
        auto cbegin()  const noexcept { return comp.cbegin();  }
        auto cend()    const noexcept { return comp.cend();    }
        auto crbegin() const noexcept { return comp.crbegin(); }
        auto crend()   const noexcept { return comp.crend();   }

        const auto& front() const { return comp.front(); }
        const auto& back()  const { return comp.back(); }

        void push_back(const content_type &val, const long long num = 1) {
            if (comp.size() and comp.back().first == val) {
                comp.back().second += num;
            } else {
                comp.emplace_back(val, num);
            }
            _length += num;
        }

        long long pop_back(long long num = 1) {
            long long rem = 0;
            while (comp.size()) {
                long long cnt = comp.back().second;
                if (cnt > num) {
                    comp.back.second -= num;
                    return rem + num;
                }
                num -= cnt, rem += cnt;
                comp.pop_back();
            }
            _length -= rem;
            return rem;
        }

    private:
        long long _length;
        std::vector<value_type> comp;

        static void compress(const Container &c, std::vector<value_type> &res) {
            res.clear();
            for (auto it_l = c.begin(), it_r = c.begin(); it_l != c.end(); it_l = it_r) {
                while (it_r != c.end() and *it_l == *it_r) ++it_r;
                res.emplace_back(*it_l, it_r - it_l);
            }
        }
        static std::vector<value_type> compress(const Container &c) {
            std::vector<value_type> res;
            compress(c, res);
            return res;
        }
};
} // namespace suisen

#endif // SUISEN_RUN_LENGTH_ENCODER