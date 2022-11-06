#ifndef SUISEN_TRIE_ARRAY
#define SUISEN_TRIE_ARRAY

#include <array>
#include <cassert>
#include <vector>

namespace suisen {
    template <int _alphabet_size, int _offset>
    struct ArrayTrieNode : std::array<int, _alphabet_size> {
        using key_type = int;

        static constexpr int none = -1;
        static constexpr int alphabet_size = _alphabet_size;
        static constexpr int offset = _offset;

        ArrayTrieNode() { this->fill(none); }
    };
    template <int _alphabet_size, int _offset>
    struct ArrayTrieNodeWithParentLink : ArrayTrieNode<_alphabet_size, _offset> {
        using base_node_type = ArrayTrieNode<_alphabet_size, _offset>;
        using key_type = typename base_node_type::key_type;
        int par;
        key_type key;

        ArrayTrieNodeWithParentLink() : base_node_type() {}
        ArrayTrieNodeWithParentLink(int par, const key_type& key) : base_node_type(), par(par), key(key) {}
    };

    template <typename NodeType, std::enable_if_t<std::is_base_of_v<ArrayTrieNode<NodeType::alphabet_size, NodeType::offset>, NodeType>, std::nullptr_t> = nullptr>
    struct ArrayTrie {
        using node_type = NodeType;
        using key_type = typename node_type::key_type;

        static constexpr int none = node_type::none;
        static constexpr int alphabet_size = node_type::alphabet_size;
        static constexpr int offset = node_type::offset;

        static constexpr int root = 0;

        using base_node_type = ArrayTrieNode<alphabet_size, offset>;

        std::vector<node_type> nodes;

        ArrayTrie() {
            nodes.emplace_back();
        }

        void reserve(int capacity) {
            nodes.reserve(capacity);
        }

        template <typename Container, std::enable_if_t<std::is_constructible_v<key_type, typename Container::value_type>, std::nullptr_t> = nullptr>
        node_type& add(const Container& s, int start = 0) {
            int cur = start;
            for (key_type c : s) {
                c -= offset;
                if (nodes[cur][c] == none) {
                    nodes[cur][c] = nodes.size();
                    if constexpr (std::is_base_of_v<ArrayTrieNodeWithParentLink<alphabet_size, offset>, node_type>) {
                        nodes.emplace_back(cur, c);
                    } else {
                        nodes.emplace_back();
                    }
                }
                cur = nodes[cur][c];
            }
            return nodes[cur];
        }

        const node_type& operator[](int i) const {
            return nodes[i];
        }
        node_type& operator[](int i) {
            return nodes[i];
        }
    };
} // namespace suisen

#endif // SUISEN_TRIE_ARRAY
