#ifndef SUISEN_TRIE_MAP
#define SUISEN_TRIE_MAP

#include <map>
#include <unordered_map>
#include <vector>

namespace suisen {
    template <typename T, bool use_ordered_map = true>
    struct MapTrieNode : std::conditional_t<use_ordered_map, std::map<T, int>, std::unordered_map<T, int>> {
        static constexpr int none = -1;
        static constexpr bool ordered = use_ordered_map;

        using key_type = T;

        int operator[](const key_type& c) const {
            auto it = this->find(c);
            return it == this->end() ? none : it->second;
        }
        int& operator[](const key_type& c) {
            return this->try_emplace(c, none).first->second;
        }
    };
    template <
        typename NodeType,
        std::enable_if_t<std::is_base_of_v<MapTrieNode<typename NodeType::key_type, NodeType::ordered>, NodeType>, std::nullptr_t> = nullptr
    >
    struct MapTrie {
        using node_type = NodeType;
        using key_type = typename node_type::key_type;
        using base_node_type = MapTrieNode<key_type>;

        static constexpr int none = node_type::none;

        std::vector<node_type> nodes;

        MapTrie() { nodes.emplace_back(); }

        void reserve(int capacity) {
            nodes.reserve(capacity);
        }

        template <typename Container, std::enable_if_t<std::is_constructible_v<key_type, typename Container::value_type>, std::nullptr_t> = nullptr>
        node_type& add(const Container& s, int start = 0) {
            int cur = start;
            for (key_type c : s) {
                auto [it, inserted] = nodes[cur].try_emplace(c, nodes.size());
                if (inserted) nodes.emplace_back();
                cur = it->second;
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


#endif // SUISEN_TRIE_MAP
