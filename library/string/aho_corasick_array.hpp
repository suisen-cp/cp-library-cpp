#ifndef SUISEN_ARRAY_AHO_CORASICK
#define SUISEN_ARRAY_AHO_CORASICK

#include <array>
#include <cassert>
#include <deque>
#include <vector>

#include "library/string/trie_array.hpp"

namespace suisen {
    template <int alphabet_size, int offset>
    struct AhoCorasickArrayNode : ArrayTrieNode<alphabet_size, offset> {
        int count;
        int failure;
    };

    template <int alphabet_size, int offset>
    struct AhoCorasickArray : private ArrayTrie<AhoCorasickArrayNode<alphabet_size, offset>> {
        using base_type = ArrayTrie<AhoCorasickArrayNode<alphabet_size, offset>>;
        using node_type = typename base_type::node_type;
        using key_type = typename base_type::key_type;

        using base_type::base_type;

        template <typename Container, std::enable_if_t<std::is_constructible_v<key_type, typename Container::value_type>, std::nullptr_t> = nullptr>
        void add(const Container& s) {
            ++base_type::add(s).count;
        }

        void build() {
            this->nodes[0].failure = init_state();
            std::deque<int> dq{ init_state() };
            while (dq.size()) {
                const int cur = dq.front();
                dq.pop_front();
                const auto& links = this->nodes[this->nodes[cur].failure];
                for (int i = 0; i < alphabet_size; ++i) {
                    const int link = cur ? links[i] : init_state();
                    if (int& nxt = this->nodes[cur][i]; nxt != node_type::none) {
                        this->nodes[nxt].failure = link;
                        this->nodes[nxt].count += this->nodes[link].count;
                        dq.push_back(nxt);
                    } else {
                        nxt = link;
                    }
                }
            }
            _built = true;
        }


        int state_num() const {
            return this->nodes.size();
        }

        int init_state() const {
            return 0;
        }
        int next_state(int state, key_type c) const {
            assert(_built);
            return this->nodes[state][c - offset];
        }
        int count_suffix_matching(int state) const {
            assert(_built);
            return this->nodes[state].count;
        }
    private:
        bool _built = false;
    };

} // namespace suisen


#endif // SUISEN_ARRAY_AHO_CORASICK
