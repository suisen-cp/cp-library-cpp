---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/string/trie_map.hpp
    title: Trie Map
  - icon: ':heavy_check_mark:'
    path: library/tree/find_centroid.hpp
    title: Find Centroid
  - icon: ':heavy_check_mark:'
    path: library/util/hashes.hpp
    title: Hashes
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/tree/tree_isomorphism_classification/rooted_tree_isomorphism_classification.test.cpp
    title: test/src/tree/tree_isomorphism_classification/rooted_tree_isomorphism_classification.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Classify subtrees by isomorphism in O(n log n) time.
    links: []
  bundledCode: "#line 1 \"library/tree/tree_isomorphism_classification.hpp\"\n\n\n\
    \n#include <algorithm>\n#include <cassert>\n#include <deque>\n#include <map>\n\
    #include <optional>\n#include <random>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"library/string/trie_map.hpp\"\n\n\n\n#line 5 \"library/string/trie_map.hpp\"\
    \n#include <unordered_map>\n#line 7 \"library/string/trie_map.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, bool use_ordered_map = true>\n    struct\
    \ MapTrieNode : std::conditional_t<use_ordered_map, std::map<T, int>, std::unordered_map<T,\
    \ int>> {\n        static constexpr int none = -1;\n        static constexpr bool\
    \ ordered = use_ordered_map;\n\n        using key_type = T;\n\n        int operator[](const\
    \ key_type& c) const {\n            auto it = this->find(c);\n            return\
    \ it == this->end() ? none : it->second;\n        }\n        int& operator[](const\
    \ key_type& c) {\n            return this->try_emplace(c, none).first->second;\n\
    \        }\n    };\n    template <\n        typename NodeType,\n        std::enable_if_t<std::is_base_of_v<MapTrieNode<typename\
    \ NodeType::key_type, NodeType::ordered>, NodeType>, std::nullptr_t> = nullptr\n\
    \    >\n    struct MapTrie {\n        using node_type = NodeType;\n        using\
    \ key_type = typename node_type::key_type;\n        using base_node_type = MapTrieNode<key_type>;\n\
    \n        static constexpr int none = node_type::none;\n\n        std::vector<node_type>\
    \ nodes;\n\n        MapTrie() { nodes.emplace_back(); }\n\n        void reserve(int\
    \ capacity) {\n            nodes.reserve(capacity);\n        }\n\n        template\
    \ <typename Container, std::enable_if_t<std::is_constructible_v<key_type, typename\
    \ Container::value_type>, std::nullptr_t> = nullptr>\n        node_type& add(const\
    \ Container& s, int start = 0) {\n            int cur = start;\n            for\
    \ (key_type c : s) {\n                auto [it, inserted] = nodes[cur].try_emplace(c,\
    \ nodes.size());\n                if (inserted) nodes.emplace_back();\n      \
    \          cur = it->second;\n            }\n            return nodes[cur];\n\
    \        }\n        const node_type& operator[](int i) const {\n            return\
    \ nodes[i];\n        }\n        node_type& operator[](int i) {\n            return\
    \ nodes[i];\n        }\n    };\n} // namespace suisen\n\n\n\n#line 1 \"library/util/hashes.hpp\"\
    \n\n\n\n#include <array>\n#include <cstdint>\n#include <tuple>\n#line 8 \"library/util/hashes.hpp\"\
    \n\nnamespace std {\n    namespace {\n        template <class T>\n        inline\
    \ void hash_combine(std::size_t& seed, T const& v) {\n            seed ^= hash<T>()(v)\
    \ + 0x9e3779b9 + (seed << 6) + (seed >> 2);\n        }\n\n        template <class\
    \ Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>\n        struct HashValueImpl\
    \ {\n            static void apply(size_t& seed, Tuple const& t) {\n         \
    \       HashValueImpl<Tuple, Index - 1>::apply(seed, t);\n                hash_combine(seed,\
    \ get<Index>(t));\n            }\n        };\n\n        template <class Tuple>\n\
    \        struct HashValueImpl<Tuple, 0> {\n            static void apply(size_t&\
    \ seed, Tuple const& t) {\n                hash_combine(seed, get<0>(t));\n  \
    \          }\n        };\n    }\n\n    template <typename T, typename U>\n   \
    \ struct hash<std::pair<T, U>> {\n        size_t operator()(std::pair<T, U> const&\
    \ tt) const {\n            size_t seed = 0;\n            HashValueImpl<std::pair<T,\
    \ U>>::apply(seed, tt);\n            return seed;\n        }\n    };\n    template\
    \ <typename ...Args>\n    struct hash<std::tuple<Args...>> {\n        size_t operator()(std::tuple<Args...>\
    \ const& tt) const {\n            size_t seed = 0;\n            HashValueImpl<std::tuple<Args...>>::apply(seed,\
    \ tt);\n            return seed;\n        }\n    };\n    template <typename T,\
    \ std::size_t N>\n    struct hash<std::array<T, N>> {\n        size_t operator()(std::array<T,\
    \ N> const& tt) const {\n            size_t seed = 0;\n            HashValueImpl<std::array<T,\
    \ N>>::apply(seed, tt);\n            return seed;\n        }\n    };\n}\n\n\n\
    #line 1 \"library/tree/find_centroid.hpp\"\n\n\n\n#line 7 \"library/tree/find_centroid.hpp\"\
    \n\nnamespace suisen {\n    template <typename GraphType>\n    std::vector<int>\
    \ find_centroids(const GraphType& g) {\n        const int n = g.size();\n    \
    \    std::vector<int> res;\n        std::vector<int8_t> is_centroid(n, true);\n\
    \        std::vector<int> eid(n), par(n, -1), sub(n, 1);\n        for (int cur\
    \ = 0; cur >= 0;) {\n            if (eid[cur] == int(g[cur].size())) {\n     \
    \           if (par[cur] >= 0) {\n                    sub[par[cur]] += sub[cur];\n\
    \                    is_centroid[par[cur]] &= 2 * sub[cur] <= n;\n           \
    \     }\n                if (is_centroid[cur] and 2 * sub[cur] >= n) {\n     \
    \               res.push_back(cur);\n                }\n                cur =\
    \ par[cur];\n            } else {\n                int nxt = g[cur][eid[cur]++];\n\
    \                if (nxt == par[cur]) continue;\n                par[nxt] = cur;\n\
    \                cur = nxt;\n            }\n        }\n        assert(res.size()\
    \ == 1 or res.size() == 2);\n        return res;\n    }\n} // namespace suisen\n\
    \n\n\n#line 16 \"library/tree/tree_isomorphism_classification.hpp\"\n\nnamespace\
    \ suisen {\n    namespace internal::tree_classification { struct IDHandlerBase\
    \ {}; }\n\n    struct IDHandlerNaive : internal::tree_classification::IDHandlerBase\
    \ {\n        using base_type = internal::tree_classification::IDHandlerBase;\n\
    \        using key_type = std::vector<int>;\n    private:\n        static constexpr\
    \ int None = -1;\n        struct TrieNode : MapTrieNode<int> {\n            int\
    \ id = None;\n        };\n        std::vector<int> mp1{};\n        MapTrie<TrieNode>\
    \ mp{};\n        int next_id = 0;\n\n        void ensure_mp1(int id) {\n     \
    \       if (id >= int(mp1.size())) mp1.resize(id + 1, None);\n        }\n    public:\n\
    \        IDHandlerNaive() = default;\n\n        int get_id(key_type ch_ids) {\n\
    \            if (const int siz = ch_ids.size(); siz == 1) {\n                int\
    \ ch = ch_ids[0];\n                ensure_mp1(ch);\n                return mp1[ch]\
    \ != None ? mp1[ch] : (mp1[ch] = next_id++);\n            } else {\n         \
    \       std::sort(ch_ids.begin(), ch_ids.end());\n                TrieNode& node\
    \ = mp.add(ch_ids);\n                return node.id != None ? node.id : (node.id\
    \ = next_id++);\n            }\n        }\n        void add_child(key_type& key,\
    \ int id) const {\n            key.push_back(id);\n        }\n        void rem_child(key_type&\
    \ key, int id) const {\n            auto it = std::find(key.begin(), key.end(),\
    \ id);\n            assert(it != key.end());\n            key.erase(it);\n   \
    \     }\n    };\n\n    template <std::size_t hash_num = 2>\n    struct IDHandlerZobrist\
    \ : internal::tree_classification::IDHandlerBase {\n        using base_type =\
    \ internal::tree_classification::IDHandlerBase;\n        using key_type = std::array<uint64_t,\
    \ hash_num>;\n    private:\n        std::mt19937_64 rng{ std::random_device{}()\
    \ };\n        std::vector<key_type> h{};\n        std::map<key_type, int> mp{};\n\
    \        int next_id = 0;\n    public:\n        IDHandlerZobrist() = default;\n\
    \n        int get_id(key_type key) {\n            auto [it, inserted] = mp.try_emplace(key,\
    \ next_id);\n            if (inserted) {\n                ++next_id;\n       \
    \         auto& x = h.emplace_back();\n                for (std::size_t i = 0;\
    \ i < hash_num; ++i) {\n                    while ((x[i] = rng()) == 0);\n   \
    \             }\n            }\n            return it->second;\n        }\n  \
    \      void add_child(key_type& key, int id) const {\n            for (std::size_t\
    \ i = 0; i < hash_num; ++i) key[i] += h[id][i];\n        }\n        void rem_child(key_type&\
    \ key, int id) const {\n            for (std::size_t i = 0; i < hash_num; ++i)\
    \ key[i] -= h[id][i];\n        }\n    };\n\n    template <\n        typename IDHandler\
    \ = IDHandlerNaive,\n        std::enable_if_t<std::is_base_of_v<internal::tree_classification::IDHandlerBase,\
    \ IDHandler>, std::nullptr_t> = nullptr\n    >\n    struct RootedTreeClassifier\
    \ {\n        using key_type = typename IDHandler::key_type;\n    public:\n   \
    \     RootedTreeClassifier() = default;\n\n        /**\n         * @brief Classify\
    \ subtrees by isomorphism in O(n log n) time.\n         * @param g tree\n    \
    \     * @param root root of g\n         * @return { number of distinct (rooted)\
    \ subtrees, id of subtrees }\n         */\n        template <typename GraphType>\n\
    \        std::vector<int> classify_subtrees(const GraphType& g, int root) {\n\
    \            const int n = g.size();\n            std::vector<int> ids(n), eid(n),\
    \ par(n, -1);\n            for (int cur = root; cur != -1;) {\n              \
    \  if (eid[cur] == int(g[cur].size())) {\n                    key_type ch_ids{};\n\
    \                    for (int v : g[cur]) if (v != par[cur]) {\n             \
    \           _id_handler.add_child(ch_ids, ids[v]);\n                    }\n  \
    \                  ids[cur] = classify(ch_ids);\n                    cur = par[cur];\n\
    \                } else if (int nxt = g[cur][eid[cur]++]; nxt != par[cur]) {\n\
    \                    par[nxt] = cur;\n                    cur = nxt;\n       \
    \         }\n            }\n            return ids;\n        }\n\n        template\
    \ <typename GraphType>\n        int classify(const GraphType& g, int root) {\n\
    \            return classify_subtrees(g, root)[root];\n        }\n        int\
    \ classify(const key_type& ch_ids) {\n            return _id_handler.get_id(ch_ids);\n\
    \        }\n\n        template <typename GraphType>\n        std::vector<int>\
    \ classify_rerooting(const GraphType& g) {\n            const int n = g.size();\n\
    \            std::vector<key_type> ch_ids(n);\n            std::vector<int> sub_ids(n),\
    \ eid(n), par(n, -1);\n            std::vector<int> pre(n);\n            std::vector<int>::iterator\
    \ it = pre.begin();\n            for (int cur = 0; cur != -1;) {\n           \
    \     if (eid[cur] == 0) *it++ = cur;\n                if (eid[cur] == int(g[cur].size()))\
    \ {\n                    for (int v : g[cur]) if (v != par[cur]) {\n         \
    \               _id_handler.add_child(ch_ids[cur], sub_ids[v]);\n            \
    \        }\n                    sub_ids[cur] = classify(ch_ids[cur]);\n      \
    \              cur = par[cur];\n                } else if (int nxt = g[cur][eid[cur]++];\
    \ nxt != par[cur]) {\n                    par[nxt] = cur;\n                  \
    \  cur = nxt;\n                }\n            }\n            std::vector<int>\
    \ ids(n);\n            ids[0] = sub_ids[0];\n            for (int u : pre) {\n\
    \                for (int v : g[u]) if (v != par[u]) {\n                    key_type\
    \ ku = ch_ids[u];\n                    int iu = ids[u];\n                    reroot(ku,\
    \ iu, ch_ids[v], sub_ids[v]);\n                    ids[v] = sub_ids[v];\n    \
    \            }\n            }\n            return ids;\n        }\n\n        void\
    \ reroot(key_type& ch_ids_old_par, int& id_old_par, key_type& ch_ids_new_par,\
    \ int& id_new_par) {\n            _id_handler.rem_child(ch_ids_old_par, id_new_par);\n\
    \            id_old_par = classify(ch_ids_old_par);\n            _id_handler.add_child(ch_ids_new_par,\
    \ id_old_par);\n            id_new_par = classify(ch_ids_new_par);\n        }\n\
    \n        template <typename GraphType>\n        std::optional<std::pair<int,\
    \ int>> is_isomorphic(const GraphType& g1, const GraphType& g2) {\n          \
    \  std::vector<int> cs1 = find_centroids(g1);\n            std::vector<int> cs2\
    \ = find_centroids(g2);\n            const int cnum1 = cs1.size(), cnum2 = cs2.size();\n\
    \n            std::vector<int> ids10 = classify_subtrees(g1, cs1[0]);\n      \
    \      std::vector<int> ids20 = classify_subtrees(g2, cs2[0]);\n\n           \
    \ if (ids10[cs1[0]] == ids20[cs2[0]]) return std::pair{ cs1[0], cs2[0] };\n\n\
    \            int id11 = -1, id21 = -2;\n            if (cnum1 == 2) {\n      \
    \          key_type ch_ids_old_par{};\n                int id_old_par = ids10[cs1[0]];\n\
    \                key_type ch_ids_new_par{};\n                int id_new_par =\
    \ ids10[cs1[1]];\n                for (int v : g1[cs1[0]]) {\n               \
    \     _id_handler.add_child(ch_ids_old_par, ids10[v]);\n                }\n  \
    \              for (int v : g1[cs1[1]]) if (v != cs1[0]) {\n                 \
    \   _id_handler.add_child(ch_ids_new_par, ids10[v]);\n                }\n    \
    \            reroot(ch_ids_old_par, id_old_par, ch_ids_new_par, id_new_par);\n\
    \                id11 = id_new_par;\n            }\n            if (cnum2 == 2)\
    \ {\n                key_type ch_ids_old_par{};\n                int id_old_par\
    \ = ids20[cs2[0]];\n                key_type ch_ids_new_par{};\n             \
    \   int id_new_par = ids20[cs2[1]];\n                for (int v : g2[cs2[0]])\
    \ {\n                    _id_handler.add_child(ch_ids_old_par, ids20[v]);\n  \
    \              }\n                for (int v : g2[cs2[1]]) if (v != cs2[0]) {\n\
    \                    _id_handler.add_child(ch_ids_new_par, ids20[v]);\n      \
    \          }\n                reroot(ch_ids_old_par, id_old_par, ch_ids_new_par,\
    \ id_new_par);\n                id21 = id_new_par;\n            }\n          \
    \  if (id11 == ids20[cs2[0]]) return std::pair{ cs1[1], cs2[0] };\n          \
    \  if (ids20[cs2[1]] == id21) return std::pair{ cs1[0], cs2[1] };\n          \
    \  if (id11 == id21) return std::pair{ cs1[1], cs2[1] };\n            return std::nullopt;\n\
    \        }\n        template <typename GraphType>\n        bool is_isomorphic_rooted(const\
    \ GraphType& g1, int root1, const GraphType& g2, int root2) {\n            return\
    \ classify(g1, root1) == classify(g2, root2);\n        }\n    private:\n     \
    \   IDHandler _id_handler;\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_ROOTED_TREE_ISOMORPHISM_CLASSIFICATION\n#define SUISEN_ROOTED_TREE_ISOMORPHISM_CLASSIFICATION\n\
    \n#include <algorithm>\n#include <cassert>\n#include <deque>\n#include <map>\n\
    #include <optional>\n#include <random>\n#include <utility>\n#include <vector>\n\
    \n#include \"library/string/trie_map.hpp\"\n#include \"library/util/hashes.hpp\"\
    \n#include \"library/tree/find_centroid.hpp\"\n\nnamespace suisen {\n    namespace\
    \ internal::tree_classification { struct IDHandlerBase {}; }\n\n    struct IDHandlerNaive\
    \ : internal::tree_classification::IDHandlerBase {\n        using base_type =\
    \ internal::tree_classification::IDHandlerBase;\n        using key_type = std::vector<int>;\n\
    \    private:\n        static constexpr int None = -1;\n        struct TrieNode\
    \ : MapTrieNode<int> {\n            int id = None;\n        };\n        std::vector<int>\
    \ mp1{};\n        MapTrie<TrieNode> mp{};\n        int next_id = 0;\n\n      \
    \  void ensure_mp1(int id) {\n            if (id >= int(mp1.size())) mp1.resize(id\
    \ + 1, None);\n        }\n    public:\n        IDHandlerNaive() = default;\n\n\
    \        int get_id(key_type ch_ids) {\n            if (const int siz = ch_ids.size();\
    \ siz == 1) {\n                int ch = ch_ids[0];\n                ensure_mp1(ch);\n\
    \                return mp1[ch] != None ? mp1[ch] : (mp1[ch] = next_id++);\n \
    \           } else {\n                std::sort(ch_ids.begin(), ch_ids.end());\n\
    \                TrieNode& node = mp.add(ch_ids);\n                return node.id\
    \ != None ? node.id : (node.id = next_id++);\n            }\n        }\n     \
    \   void add_child(key_type& key, int id) const {\n            key.push_back(id);\n\
    \        }\n        void rem_child(key_type& key, int id) const {\n          \
    \  auto it = std::find(key.begin(), key.end(), id);\n            assert(it !=\
    \ key.end());\n            key.erase(it);\n        }\n    };\n\n    template <std::size_t\
    \ hash_num = 2>\n    struct IDHandlerZobrist : internal::tree_classification::IDHandlerBase\
    \ {\n        using base_type = internal::tree_classification::IDHandlerBase;\n\
    \        using key_type = std::array<uint64_t, hash_num>;\n    private:\n    \
    \    std::mt19937_64 rng{ std::random_device{}() };\n        std::vector<key_type>\
    \ h{};\n        std::map<key_type, int> mp{};\n        int next_id = 0;\n    public:\n\
    \        IDHandlerZobrist() = default;\n\n        int get_id(key_type key) {\n\
    \            auto [it, inserted] = mp.try_emplace(key, next_id);\n           \
    \ if (inserted) {\n                ++next_id;\n                auto& x = h.emplace_back();\n\
    \                for (std::size_t i = 0; i < hash_num; ++i) {\n              \
    \      while ((x[i] = rng()) == 0);\n                }\n            }\n      \
    \      return it->second;\n        }\n        void add_child(key_type& key, int\
    \ id) const {\n            for (std::size_t i = 0; i < hash_num; ++i) key[i] +=\
    \ h[id][i];\n        }\n        void rem_child(key_type& key, int id) const {\n\
    \            for (std::size_t i = 0; i < hash_num; ++i) key[i] -= h[id][i];\n\
    \        }\n    };\n\n    template <\n        typename IDHandler = IDHandlerNaive,\n\
    \        std::enable_if_t<std::is_base_of_v<internal::tree_classification::IDHandlerBase,\
    \ IDHandler>, std::nullptr_t> = nullptr\n    >\n    struct RootedTreeClassifier\
    \ {\n        using key_type = typename IDHandler::key_type;\n    public:\n   \
    \     RootedTreeClassifier() = default;\n\n        /**\n         * @brief Classify\
    \ subtrees by isomorphism in O(n log n) time.\n         * @param g tree\n    \
    \     * @param root root of g\n         * @return { number of distinct (rooted)\
    \ subtrees, id of subtrees }\n         */\n        template <typename GraphType>\n\
    \        std::vector<int> classify_subtrees(const GraphType& g, int root) {\n\
    \            const int n = g.size();\n            std::vector<int> ids(n), eid(n),\
    \ par(n, -1);\n            for (int cur = root; cur != -1;) {\n              \
    \  if (eid[cur] == int(g[cur].size())) {\n                    key_type ch_ids{};\n\
    \                    for (int v : g[cur]) if (v != par[cur]) {\n             \
    \           _id_handler.add_child(ch_ids, ids[v]);\n                    }\n  \
    \                  ids[cur] = classify(ch_ids);\n                    cur = par[cur];\n\
    \                } else if (int nxt = g[cur][eid[cur]++]; nxt != par[cur]) {\n\
    \                    par[nxt] = cur;\n                    cur = nxt;\n       \
    \         }\n            }\n            return ids;\n        }\n\n        template\
    \ <typename GraphType>\n        int classify(const GraphType& g, int root) {\n\
    \            return classify_subtrees(g, root)[root];\n        }\n        int\
    \ classify(const key_type& ch_ids) {\n            return _id_handler.get_id(ch_ids);\n\
    \        }\n\n        template <typename GraphType>\n        std::vector<int>\
    \ classify_rerooting(const GraphType& g) {\n            const int n = g.size();\n\
    \            std::vector<key_type> ch_ids(n);\n            std::vector<int> sub_ids(n),\
    \ eid(n), par(n, -1);\n            std::vector<int> pre(n);\n            std::vector<int>::iterator\
    \ it = pre.begin();\n            for (int cur = 0; cur != -1;) {\n           \
    \     if (eid[cur] == 0) *it++ = cur;\n                if (eid[cur] == int(g[cur].size()))\
    \ {\n                    for (int v : g[cur]) if (v != par[cur]) {\n         \
    \               _id_handler.add_child(ch_ids[cur], sub_ids[v]);\n            \
    \        }\n                    sub_ids[cur] = classify(ch_ids[cur]);\n      \
    \              cur = par[cur];\n                } else if (int nxt = g[cur][eid[cur]++];\
    \ nxt != par[cur]) {\n                    par[nxt] = cur;\n                  \
    \  cur = nxt;\n                }\n            }\n            std::vector<int>\
    \ ids(n);\n            ids[0] = sub_ids[0];\n            for (int u : pre) {\n\
    \                for (int v : g[u]) if (v != par[u]) {\n                    key_type\
    \ ku = ch_ids[u];\n                    int iu = ids[u];\n                    reroot(ku,\
    \ iu, ch_ids[v], sub_ids[v]);\n                    ids[v] = sub_ids[v];\n    \
    \            }\n            }\n            return ids;\n        }\n\n        void\
    \ reroot(key_type& ch_ids_old_par, int& id_old_par, key_type& ch_ids_new_par,\
    \ int& id_new_par) {\n            _id_handler.rem_child(ch_ids_old_par, id_new_par);\n\
    \            id_old_par = classify(ch_ids_old_par);\n            _id_handler.add_child(ch_ids_new_par,\
    \ id_old_par);\n            id_new_par = classify(ch_ids_new_par);\n        }\n\
    \n        template <typename GraphType>\n        std::optional<std::pair<int,\
    \ int>> is_isomorphic(const GraphType& g1, const GraphType& g2) {\n          \
    \  std::vector<int> cs1 = find_centroids(g1);\n            std::vector<int> cs2\
    \ = find_centroids(g2);\n            const int cnum1 = cs1.size(), cnum2 = cs2.size();\n\
    \n            std::vector<int> ids10 = classify_subtrees(g1, cs1[0]);\n      \
    \      std::vector<int> ids20 = classify_subtrees(g2, cs2[0]);\n\n           \
    \ if (ids10[cs1[0]] == ids20[cs2[0]]) return std::pair{ cs1[0], cs2[0] };\n\n\
    \            int id11 = -1, id21 = -2;\n            if (cnum1 == 2) {\n      \
    \          key_type ch_ids_old_par{};\n                int id_old_par = ids10[cs1[0]];\n\
    \                key_type ch_ids_new_par{};\n                int id_new_par =\
    \ ids10[cs1[1]];\n                for (int v : g1[cs1[0]]) {\n               \
    \     _id_handler.add_child(ch_ids_old_par, ids10[v]);\n                }\n  \
    \              for (int v : g1[cs1[1]]) if (v != cs1[0]) {\n                 \
    \   _id_handler.add_child(ch_ids_new_par, ids10[v]);\n                }\n    \
    \            reroot(ch_ids_old_par, id_old_par, ch_ids_new_par, id_new_par);\n\
    \                id11 = id_new_par;\n            }\n            if (cnum2 == 2)\
    \ {\n                key_type ch_ids_old_par{};\n                int id_old_par\
    \ = ids20[cs2[0]];\n                key_type ch_ids_new_par{};\n             \
    \   int id_new_par = ids20[cs2[1]];\n                for (int v : g2[cs2[0]])\
    \ {\n                    _id_handler.add_child(ch_ids_old_par, ids20[v]);\n  \
    \              }\n                for (int v : g2[cs2[1]]) if (v != cs2[0]) {\n\
    \                    _id_handler.add_child(ch_ids_new_par, ids20[v]);\n      \
    \          }\n                reroot(ch_ids_old_par, id_old_par, ch_ids_new_par,\
    \ id_new_par);\n                id21 = id_new_par;\n            }\n          \
    \  if (id11 == ids20[cs2[0]]) return std::pair{ cs1[1], cs2[0] };\n          \
    \  if (ids20[cs2[1]] == id21) return std::pair{ cs1[0], cs2[1] };\n          \
    \  if (id11 == id21) return std::pair{ cs1[1], cs2[1] };\n            return std::nullopt;\n\
    \        }\n        template <typename GraphType>\n        bool is_isomorphic_rooted(const\
    \ GraphType& g1, int root1, const GraphType& g2, int root2) {\n            return\
    \ classify(g1, root1) == classify(g2, root2);\n        }\n    private:\n     \
    \   IDHandler _id_handler;\n    };\n} // namespace suisen\n\n#endif // SUISEN_ROOTED_TREE_ISOMORPHISM_CLASSIFICATION\n"
  dependsOn:
  - library/string/trie_map.hpp
  - library/util/hashes.hpp
  - library/tree/find_centroid.hpp
  isVerificationFile: false
  path: library/tree/tree_isomorphism_classification.hpp
  requiredBy: []
  timestamp: '2022-10-23 23:59:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/tree/tree_isomorphism_classification/rooted_tree_isomorphism_classification.test.cpp
documentation_of: library/tree/tree_isomorphism_classification.hpp
layout: document
title: Tree Isomorphism Classification
---
## Tree Isomorphism Classification
