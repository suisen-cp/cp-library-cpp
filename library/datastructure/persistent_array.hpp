#ifndef SUISEN_PERSISTENT_ARRAY
#define SUISEN_PERSISTENT_ARRAY

#include <utility>
#include "library/util/object_pool.hpp"

namespace suisen {
    template <typename T, int lg_ary = 4>
    struct PersistentArray {
        struct Node;
        using node_type = Node;
        using node_pointer_type = node_type*;
        using value_type = T;
        using pool_type = ObjectPool<node_type>;
        struct Node {
            static inline pool_type pool{};
            static constexpr int mask = (1 << lg_ary) - 1;

            node_pointer_type _ch[1 << lg_ary]{};
            value_type _val;
            Node(const value_type& val = value_type{}) : _val(val) {}

            static node_pointer_type clone(node_pointer_type node) {
                return &(*pool.alloc() = *node);
            }
            static node_pointer_type new_node(const value_type& val) {
                return &(*pool.alloc() = node_type(val));
            }
            static value_type& get(node_pointer_type node, int id) {
                for (; id; --id >>= lg_ary) node = node->_ch[id & mask];
                return node->_val;
            }
            static node_pointer_type set(node_pointer_type node, int id, const value_type& val) {
                node_pointer_type res = clone(node), cur = res;
                for (; id; --id >>= lg_ary) cur = cur->_ch[id & mask] = clone(cur->_ch[id & mask]);
                cur->_val = val;
                return res;
            }
            static value_type mut_set(node_pointer_type node, int id, const value_type& val) {
                return std::exchange(get(node, id), val);
            }
            static node_pointer_type build(const std::vector<value_type>& init) {
                const int n = init.size();
                if (n == 0) return nullptr;
                auto dfs = [&](auto dfs, node_pointer_type cur, int id, int p) -> void {
                    int np = p << lg_ary, nid = id + p;
                    for (int d = 1; d < 1 << lg_ary; ++d, nid += p) {
                        if (nid < n) dfs(dfs, cur->_ch[d] = new_node(init[nid]), nid, np);
                        else return;
                    }
                    if (nid < n) dfs(dfs, cur->_ch[0] = new_node(init[nid]), nid, np);
                };
                node_pointer_type root = new_node(init[0]);
                dfs(dfs, root, 0, 1);
                return root;
            }
            static std::vector<value_type> dump(node_pointer_type node) {
                if (not node) return {};
                std::vector<value_type> res;
                auto dfs = [&](auto dfs, node_pointer_type cur, int id, int p) -> void {
                    if (int(res.size()) <= id) res.resize(id + 1);
                    res[id] = node->_val;
                    int np = p << lg_ary, nid = id + p;
                    for (int d = 1; d < 1 << lg_ary; ++d, nid += p) {
                        if (cur->_ch[d]) dfs(dfs, cur->_ch[d], nid, np);
                        else return;
                    }
                    if (cur->_ch[0]) dfs(dfs, cur->_ch[0], nid, np);
                };
                dfs(dfs, node, 0, 1);
                return res;
            }
        };

        static void init_pool(int capacity) {
            node_type::pool = pool_type(capacity);
        }

        PersistentArray() {}
        explicit PersistentArray(int n, const value_type& val = value_type{}) : PersistentArray(std::vector<value_type>(n, val)) {}
        PersistentArray(const std::vector<value_type>& init) : _n(init.size()), _root(node_type::build(init)) {}

        int size() const {
            return _n;
        }
        const value_type& get(int id) {
            return node_type::get(_root, id);
        }
        PersistentArray set(int id, const value_type& new_val) {
            return PersistentArray{ _n, node_type::set(_root, id, new_val) };
        }
        value_type mut_set(int id, const value_type& new_val) {
            return node_type::mut_set(_root, id, new_val);
        }
        PersistentArray clone() {
            if (not _root) return PersistentArray { _n, _root };
            return PersistentArray{ _n, node_type::clone(_root) };
        }
        std::vector<value_type> dump() {
            return node_type::dump(_root);
        }
    private:
        int _n;
        node_pointer_type _root;
        explicit PersistentArray(int n, node_pointer_type root) : _n(n), _root(root) {}
    };
} // namespace suisen

#endif // SUISEN_PERSISTENT_ARRAY
