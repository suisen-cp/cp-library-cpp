#ifndef SUISEN_ROOTED_TREE_ISOMORPHISM_CLASSIFICATION
#define SUISEN_ROOTED_TREE_ISOMORPHISM_CLASSIFICATION

#include <algorithm>
#include <cassert>
#include <deque>
#include <map>
#include <optional>
#include <random>
#include <utility>
#include <vector>

#include "library/string/trie_map.hpp"
#include "library/util/hashes.hpp"
#include "library/tree/find_centroid.hpp"

namespace suisen {
    namespace internal::tree_classification { struct IDHandlerBase {}; }

    struct IDHandlerNaive : internal::tree_classification::IDHandlerBase {
        using base_type = internal::tree_classification::IDHandlerBase;
        using key_type = std::vector<int>;
    private:
        static constexpr int None = -1;
        struct TrieNode : MapTrieNode<int> {
            int id = None;
        };
        std::vector<int> mp1{};
        MapTrie<TrieNode> mp{};
        int next_id = 0;

        void ensure_mp1(int id) {
            if (id >= int(mp1.size())) mp1.resize(id + 1, None);
        }
    public:
        IDHandlerNaive() = default;

        int get_id(key_type ch_ids) {
            if (const int siz = ch_ids.size(); siz == 1) {
                int ch = ch_ids[0];
                ensure_mp1(ch);
                return mp1[ch] != None ? mp1[ch] : (mp1[ch] = next_id++);
            } else {
                std::sort(ch_ids.begin(), ch_ids.end());
                TrieNode& node = mp.add(ch_ids);
                return node.id != None ? node.id : (node.id = next_id++);
            }
        }
        void add_child(key_type& key, int id) const {
            key.push_back(id);
        }
        void rem_child(key_type& key, int id) const {
            auto it = std::find(key.begin(), key.end(), id);
            assert(it != key.end());
            key.erase(it);
        }
    };

    template <std::size_t hash_num = 2>
    struct IDHandlerZobrist : internal::tree_classification::IDHandlerBase {
        using base_type = internal::tree_classification::IDHandlerBase;
        using key_type = std::array<uint64_t, hash_num>;
    private:
        std::mt19937_64 rng{ std::random_device{}() };
        std::vector<key_type> h{};
        std::map<key_type, int> mp{};
        int next_id = 0;
    public:
        IDHandlerZobrist() = default;

        int get_id(key_type key) {
            auto [it, inserted] = mp.try_emplace(key, next_id);
            if (inserted) {
                ++next_id;
                auto& x = h.emplace_back();
                for (std::size_t i = 0; i < hash_num; ++i) {
                    while ((x[i] = rng()) == 0);
                }
            }
            return it->second;
        }
        void add_child(key_type& key, int id) const {
            for (std::size_t i = 0; i < hash_num; ++i) key[i] += h[id][i];
        }
        void rem_child(key_type& key, int id) const {
            for (std::size_t i = 0; i < hash_num; ++i) key[i] -= h[id][i];
        }
    };

    template <
        typename IDHandler = IDHandlerNaive,
        std::enable_if_t<std::is_base_of_v<internal::tree_classification::IDHandlerBase, IDHandler>, std::nullptr_t> = nullptr
    >
    struct RootedTreeClassifier {
        using key_type = typename IDHandler::key_type;
    public:
        RootedTreeClassifier() = default;

        /**
         * @brief Classify subtrees by isomorphism in O(n log n) time.
         * @param g tree
         * @param root root of g
         * @return { number of distinct (rooted) subtrees, id of subtrees }
         */
        template <typename GraphType>
        std::vector<int> classify_subtrees(const GraphType& g, int root) {
            const int n = g.size();
            std::vector<int> ids(n), eid(n), par(n, -1);
            for (int cur = root; cur != -1;) {
                if (eid[cur] == int(g[cur].size())) {
                    key_type ch_ids{};
                    for (int v : g[cur]) if (v != par[cur]) {
                        _id_handler.add_child(ch_ids, ids[v]);
                    }
                    ids[cur] = classify(ch_ids);
                    cur = par[cur];
                } else if (int nxt = g[cur][eid[cur]++]; nxt != par[cur]) {
                    par[nxt] = cur;
                    cur = nxt;
                }
            }
            return ids;
        }

        template <typename GraphType>
        int classify(const GraphType& g, int root) {
            return classify_subtrees(g, root)[root];
        }
        int classify(const key_type& ch_ids) {
            return _id_handler.get_id(ch_ids);
        }

        template <typename GraphType>
        std::vector<int> classify_rerooting(const GraphType& g) {
            const int n = g.size();
            std::vector<key_type> ch_ids(n);
            std::vector<int> sub_ids(n), eid(n), par(n, -1);
            std::vector<int> pre(n);
            std::vector<int>::iterator it = pre.begin();
            for (int cur = 0; cur != -1;) {
                if (eid[cur] == 0) *it++ = cur;
                if (eid[cur] == int(g[cur].size())) {
                    for (int v : g[cur]) if (v != par[cur]) {
                        _id_handler.add_child(ch_ids[cur], sub_ids[v]);
                    }
                    sub_ids[cur] = classify(ch_ids[cur]);
                    cur = par[cur];
                } else if (int nxt = g[cur][eid[cur]++]; nxt != par[cur]) {
                    par[nxt] = cur;
                    cur = nxt;
                }
            }
            std::vector<int> ids(n);
            ids[0] = sub_ids[0];
            for (int u : pre) {
                for (int v : g[u]) if (v != par[u]) {
                    key_type ku = ch_ids[u];
                    int iu = ids[u];
                    reroot(ku, iu, ch_ids[v], sub_ids[v]);
                    ids[v] = sub_ids[v];
                }
            }
            return ids;
        }

        void reroot(key_type& ch_ids_old_par, int& id_old_par, key_type& ch_ids_new_par, int& id_new_par) {
            _id_handler.rem_child(ch_ids_old_par, id_new_par);
            id_old_par = classify(ch_ids_old_par);
            _id_handler.add_child(ch_ids_new_par, id_old_par);
            id_new_par = classify(ch_ids_new_par);
        }

        template <typename GraphType>
        std::optional<std::pair<int, int>> is_isomorphic(const GraphType& g1, const GraphType& g2) {
            std::vector<int> cs1 = find_centroids(g1);
            std::vector<int> cs2 = find_centroids(g2);
            const int cnum1 = cs1.size(), cnum2 = cs2.size();

            std::vector<int> ids10 = classify_subtrees(g1, cs1[0]);
            std::vector<int> ids20 = classify_subtrees(g2, cs2[0]);

            if (ids10[cs1[0]] == ids20[cs2[0]]) return std::pair{ cs1[0], cs2[0] };

            int id11 = -1, id21 = -2;
            if (cnum1 == 2) {
                key_type ch_ids_old_par{};
                int id_old_par = ids10[cs1[0]];
                key_type ch_ids_new_par{};
                int id_new_par = ids10[cs1[1]];
                for (int v : g1[cs1[0]]) {
                    _id_handler.add_child(ch_ids_old_par, ids10[v]);
                }
                for (int v : g1[cs1[1]]) if (v != cs1[0]) {
                    _id_handler.add_child(ch_ids_new_par, ids10[v]);
                }
                reroot(ch_ids_old_par, id_old_par, ch_ids_new_par, id_new_par);
                id11 = id_new_par;
            }
            if (cnum2 == 2) {
                key_type ch_ids_old_par{};
                int id_old_par = ids20[cs2[0]];
                key_type ch_ids_new_par{};
                int id_new_par = ids20[cs2[1]];
                for (int v : g2[cs2[0]]) {
                    _id_handler.add_child(ch_ids_old_par, ids20[v]);
                }
                for (int v : g2[cs2[1]]) if (v != cs2[0]) {
                    _id_handler.add_child(ch_ids_new_par, ids20[v]);
                }
                reroot(ch_ids_old_par, id_old_par, ch_ids_new_par, id_new_par);
                id21 = id_new_par;
            }
            if (id11 == ids20[cs2[0]]) return std::pair{ cs1[1], cs2[0] };
            if (ids20[cs2[1]] == id21) return std::pair{ cs1[0], cs2[1] };
            if (id11 == id21) return std::pair{ cs1[1], cs2[1] };
            return std::nullopt;
        }
        template <typename GraphType>
        bool is_isomorphic_rooted(const GraphType& g1, int root1, const GraphType& g2, int root2) {
            return classify(g1, root1) == classify(g2, root2);
        }
    private:
        IDHandler _id_handler;
    };
} // namespace suisen

#endif // SUISEN_ROOTED_TREE_ISOMORPHISM_CLASSIFICATION
