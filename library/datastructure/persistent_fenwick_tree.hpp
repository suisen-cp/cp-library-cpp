#ifndef SUISEN_PERSISTENT_FENWICK_TREE
#define SUISEN_PERSISTENT_FENWICK_TREE

#include <cassert>

#include "library/util/object_pool.hpp"

namespace suisen {
    template <typename T>
    struct PersistentFenwickTree {
        struct Node;

        using value_type = T;

        using node_type = Node;
        using node_pointer_type = node_type*;

        struct Node {
            static inline ObjectPool<node_type> _pool;

            node_pointer_type _ch[2]{ nullptr, nullptr };
            value_type _dat;

            Node() : _dat{} {}

            static node_pointer_type clone(node_pointer_type node) {
                return &(*_pool.alloc() = *node);
            }

            static node_pointer_type build(const std::vector<value_type> &dat, int p) {
                const int n = dat.size();
                std::vector<node_pointer_type> nodes(n + 1);
                auto rec = [&](auto rec, int p, int id) -> node_pointer_type {
                    if (p == 0) return nullptr;
                    const int np = p >> 1;
                    node_pointer_type res = _pool.alloc();
                    res->_ch[0] = rec(rec, np, id - np);
                    if (id + 1 <= n) res->_ch[1] = rec(rec, np, id + np);
                    if (id <= n) nodes[id] = res;
                    return res;
                };
                node_pointer_type res = rec(rec, p, p);
                for (int i = 1; i <= n; ++i) {
                    int par = i + (i & -i);
                    if (par <= n) nodes[par]->_dat += nodes[i]->_dat;
                }
                return res;
            }

            static value_type sum(node_pointer_type node, int p, int l, int r) {
                return sum(node, p, r) - sum(node, p, l);
            }

            static node_pointer_type add(node_pointer_type node, int p, int i, const value_type& val) {
                ++i;
                node_pointer_type res = clone(node);
                for (node_pointer_type cur = res;; p >>= 1) {
                    if (i & p) {
                        if (i ^= p) {
                            cur = cur->_ch[1] = clone(cur->_ch[1]);
                        } else {
                            cur->_dat += val;
                            return res;
                        }
                    } else {
                        cur->_dat += val;
                        cur = cur->_ch[0] = clone(cur->_ch[0]);
                    }
                }
            }
        private:
            static value_type sum(node_pointer_type node, int p, int r) {
                value_type res{};
                for (; r; p >>= 1) {
                    if (r & p) {
                        r ^= p;
                        res += node->_dat;
                        node = node->_ch[1];
                    } else {
                        node = node->_ch[0];
                    }
                }
                return res;
            }
        };

        PersistentFenwickTree() : _p(0), _root(nullptr) {}
        explicit PersistentFenwickTree(int n) : PersistentFenwickTree(std::vector<value_type>(n, T{})) {}
        PersistentFenwickTree(const std::vector<value_type>& dat) : _p(floor_pow2(dat.size())), _root(node_type::build(dat, _p)) {}

        static void init_pool(int siz) {
            node_type::_pool = ObjectPool<node_type>(siz);
        }
        static void clear_pool() {
            node_type::_pool.clear();
        }

        value_type sum(int l, int r) {
            return node_type::sum(_root, _p, l, r);
        }
        PersistentFenwickTree add(int i, const value_type &val) {
            return PersistentFenwickTree(_p, node_type::add(_root, _p, i, val));
        }

    private:
        int _p;
        node_pointer_type _root;
        PersistentFenwickTree(int p, node_pointer_type root) : _p(p), _root(root) {}

        static constexpr int floor_pow2(int n) {
            int x = 31 - __builtin_clz(n);
            return x < 0 ? 0 : 1 << x;
        }
    };
}

#endif // SUISEN_PERSISTENT_FENWICK_TREE
