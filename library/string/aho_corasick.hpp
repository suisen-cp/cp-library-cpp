#ifndef SUISEN_AHO_CORASICK
#define SUISEN_AHO_CORASICK

#include <cassert>
#include <deque>
#include <map>
#include <vector>

namespace suisen {
    template <typename T = char>
    struct AhoCorasick {
        using value_type = T;

        AhoCorasick() : _next(1) {}

        template <typename Container, std::enable_if_t<std::is_constructible_v<value_type, typename Container::value_type>, std::nullptr_t> = nullptr>
        void add(const Container& s) {
            int cur = 0;
            for (value_type c : s) {
                auto [it, inserted] = _next[cur].try_emplace(c, _next.size());
                if (inserted) _next.emplace_back();
                cur = it->second;
            }
            _marks.push_back(cur);
            _built = false;
        }

        void build() {
            _built = true;
            const int n = _next.size();
            _failure.resize(n, 0);
            _count.resize(n, 0);
            for (int mark : _marks) ++_count[mark];
            std::deque<int> dq{ 0 };
            while (dq.size()) {
                const int cur = dq.front();
                dq.pop_front();
                for (const auto& [c, nxt] : _next[cur]) {
                    if (cur) {
                        _failure[nxt] = next_state(_failure[cur], c);
                        _count[nxt] += _count[_failure[nxt]];
                    }
                    dq.push_back(nxt);
                }
            }
        }

        int init_state() const {
            return 0;
        }
        int next_state(int state, value_type c) const {
            assert(_built);
            while (true) {
                if (auto it = _next[state].find(c); it == _next[state].end()) {
                    if (state == 0) return 0;
                    state = _failure[state];
                } else {
                    return it->second;
                }
            }
        }
        int match_count(int state) const {
            assert(_built);
            return _count[state];
        }
    private:
        std::vector<int> _failure;
        std::vector<std::map<value_type, int>> _next;
        std::vector<int> _marks;
        std::vector<int> _count;
        bool _built = true;
    };
} // namespace suisen


#endif // SUISEN_AHO_CORASICK
