#ifndef SUISEN_SPLAY_TREE_MAP
#define SUISEN_SPLAY_TREE_MAP

#include <cassert>
#include <cstddef>
#include <vector>
#include <utility>

namespace suisen {
namespace internal::splay_tree_map {

template <typename Key, typename Val, typename Derived>
struct MapNodeBase {
    using node_ptr_t = Derived *;

    Key key;
    Val val;
    int siz;
    node_ptr_t ch[2] {nullptr, nullptr};

    MapNodeBase() : key(), val(), siz(1) {}
    MapNodeBase(const Key &key, const Val &val) : key(key), val(val), siz(1) {}

    ~MapNodeBase() {
        delete ch[0];
        delete ch[1];
    }

    void update() {
        siz = 1 + size(ch[0]) + size(ch[1]);
    }
    void push() {}

    static int size(node_ptr_t node) {
        return node == nullptr ? 0 : node->siz;
    }

    static node_ptr_t rotate(node_ptr_t node, bool is_right) {
        node_ptr_t root = node->ch[is_right ^ true];
        node->ch[is_right ^ true] = root->ch[is_right];
        root->ch[is_right] = node;
        node->update(), root->update();
        return root;
    }

    static node_ptr_t splay_by_index(node_ptr_t node, int index) {
        std::vector<node_ptr_t> path;
        node_ptr_t work_root = new Derived();
        node_ptr_t work_leaf[2] { work_root, work_root };
        while (true) {
            node->push();
            int size_l = size(node->ch[0]);
            bool is_right = index > size_l;
            node_ptr_t next_node = node->ch[is_right];
            if (index == size_l or next_node == nullptr) { // found the target node
                break;
            }
            if (is_right) {
                index -= size_l + 1;
            }
            int size_l_ch = size(next_node->ch[0]);
            if (index != size_l_ch) {
                bool is_right_ch = index > size_l_ch;
                if (is_right_ch == is_right) { // zig-zig
                    if (is_right_ch) {
                        index -= size_l_ch + 1;
                    }
                    next_node->push();
                    node = rotate(node, is_right ^ true);
                    next_node = node->ch[is_right];
                    if (next_node == nullptr) { // found the target node
                        break;
                    }
                }
            }
            path.push_back(node);
            work_leaf[is_right]->ch[is_right] = node;
            work_leaf[is_right] = node;
            node = next_node;
        }
        work_leaf[0]->ch[0] = node->ch[1];
        work_leaf[1]->ch[1] = node->ch[0];
        node->ch[0] = work_root->ch[1];
        node->ch[1] = work_root->ch[0];
    
        work_root->ch[0] = work_root->ch[1] = nullptr;
        delete work_root;

        while (path.size()) {
            path.back()->update(), path.pop_back();
        }
        node->update();

        return node;
    }

    static node_ptr_t splay_by_key(node_ptr_t node, const Key &x) {
        if (node == nullptr) return node;
        std::vector<node_ptr_t> path;
        node_ptr_t work_root = new Derived();
        node_ptr_t work_leaf[2] { work_root, work_root };
        while (true) {
            node->push();
            if (x == node->key) {
                break;
            }
            bool is_right = x > node->key;
            node_ptr_t next_node = node->ch[is_right];
            if (next_node == nullptr) {
                break;
            }
            if (x != next_node->key) {
                bool is_right_ch = x > next_node->key;
                if (is_right_ch == is_right) { // zig-zig
                    next_node->push();
                    node = rotate(node, is_right ^ true);
                    next_node = node->ch[is_right];
                    if (next_node == nullptr) { // found the target node
                        break;
                    }
                }
            }
            path.push_back(node);
            work_leaf[is_right]->ch[is_right] = node;
            work_leaf[is_right] = node;
            node = next_node;
        }
        work_leaf[0]->ch[0] = node->ch[1];
        work_leaf[1]->ch[1] = node->ch[0];
        node->ch[0] = work_root->ch[1];
        node->ch[1] = work_root->ch[0];

        work_root->ch[0] = work_root->ch[1] = nullptr;
        delete work_root;

        while (path.size()) {
            path.back()->update(), path.pop_back();
        }
        node->update();

        return node;
    }
    static std::pair<node_ptr_t, bool> find_key(node_ptr_t node, const Key &key) {
        if (node == nullptr) return { node, false };
        node = splay_by_key(node, key);
        return { node, node->key == key };
    }
    static std::pair<node_ptr_t, node_ptr_t> split_by_index(node_ptr_t node, int k) {
        if (k == 0) return { nullptr, node };
        if (k == size(node)) return { node, nullptr };
        node_ptr_t r = splay_by_index(node, k);
        node_ptr_t l = r->ch[0];
        r->ch[0] = nullptr;
        r->update();
        return { l, r };
    }
    static std::tuple<node_ptr_t, node_ptr_t, node_ptr_t> split_by_index(node_ptr_t node, int l, int r) {
        auto [tl, tmr] = split_by_index(node, l);
        auto [tm, tr] = split_by_index(tmr, r - l);
        return { tl, tm, tr };
    }
    static std::pair<node_ptr_t, node_ptr_t> split_by_key(node_ptr_t node, const Key &key) {
        if (node == nullptr) return { nullptr, nullptr };
        node_ptr_t r = splay_by_key(node, key);
        if (r->key >= key) {
            node_ptr_t l = r->ch[0];
            r->ch[0] = nullptr;
            r->update();
            return { l, r };
        } else {
            node_ptr_t l = r->ch[1];
            r->ch[1] = nullptr;
            r->update();
            return { r, l };
        }
    }
    static std::tuple<node_ptr_t, node_ptr_t, node_ptr_t> split_by_key(node_ptr_t node, const Key &l, const Key &r) {
        auto [tl, tmr] = split_by_key(node, l);
        auto [tm, tr] = split_by_key(tmr, r);
        return { tl, tm, tr };
    }
    static node_ptr_t merge(node_ptr_t l, node_ptr_t r) {
        if (l == nullptr) return r;
        if (r == nullptr) return l;
        node_ptr_t new_root = splay_by_index(r, 0);
        new_root->ch[0] = l;
        new_root->update();
        return new_root;
    }
    static node_ptr_t merge(node_ptr_t tl, node_ptr_t tm, node_ptr_t tr) {
        return merge(merge(tl, tm), tr);
    }
    static node_ptr_t insert(node_ptr_t node, const Key &key, const Val &val, bool overwrite = true) {
        auto [l, r] = split_by_key(node, key);
        if (r != nullptr and r->key == key) {
            if (overwrite) {
                r->val = val;
                r->update();
            }
            return merge(l, r);
        }
        node_ptr_t new_node = new Derived(key, val);
        new_node->ch[0] = l;
        new_node->ch[1] = r;
        new_node->update();
        return new_node;
    }
    static node_ptr_t erase_index(node_ptr_t node, int index) {
        auto [l, r] = split(index ? node : splay(node, 0), index);
        assert(r->ch[0] == nullptr);
        node_ptr_t res = merge(l, r->ch[1]);
        r->ch[1] = nullptr;
        delete r;
        return res;
    }
    static std::pair<node_ptr_t, bool> erase_key(node_ptr_t node, const Key &key) {
        auto [l, r] = split_by_key(node, key);
        if (r == nullptr or r->key != key) return { merge(l, r), false };
        assert(r->ch[0] == nullptr);
        node_ptr_t res = merge(l, r->ch[1]);
        r->ch[1] = nullptr;
        delete r;
        return { res, true };
    }
    static Val get_or_default(node_ptr_t node, const Key &key, const Val &default_value) {
        auto [new_root, found] = find_key(node, key);
        node = new_root;
        return found ? new_root->val : default_value;
    }
};

template <typename Key, typename Val>
struct SplayTreeMapNode : public MapNodeBase<Key, Val, SplayTreeMapNode<Key, Val>> {
    using Base = MapNodeBase<Key, Val, SplayTreeMapNode<Key, Val>>;
    using Base::MapNodeBase;
    using node_ptr_t = typename Base::node_ptr_t;
};
}

template <typename Key, typename Val>
class SplayTreeMap {
    using Node = internal::splay_tree_map::SplayTreeMapNode<Key, Val>;
    using node_ptr_t = typename Node::node_ptr_t;
    public:
        SplayTreeMap() : root(nullptr) {}
        ~SplayTreeMap() {
            delete root;
        }

        SplayTreeMap& operator=(const SplayTreeMap&) = delete;
        SplayTreeMap& operator=(SplayTreeMap&& other) {
            delete root;
            root = other.root;
            other.root = nullptr;
            return *this;
        }

        int size() {
            return Node::size(root);
        }
        bool contains(const Key &key) {
            auto [new_root, found] = Node::find_key(root, key);
            root = new_root;
            return found;
        }
        void insert(const Key &key, const Val &val) {
            root = Node::insert(root, key, val, true);
        }
        void insert_if_absent(const Key &key, const Val &val) {
            root = Node::insert(root, key, val, false);
        }
        bool erase_key(const Key &key) {
            auto [new_root, is_erased] = Node::erase_key(root, key);
            root = new_root;
            return is_erased;
        }
        void erase_index(int k) {
            index_bounds_check(k, size() + 1);
            root = Node::erase_index(root, k);
        }
        Val& get_or_create(const Key &key, const Val &val) {
            root = Node::insert(root, key, val, false);
            return root->val;
        }
        Val& operator[](const Key &key) {
            return get_or_create(key, Val{});
        }
        Val get_or_default(const Key &key, const Val &default_value) {
            auto [new_root, res] = Node::get_or_default(root, key, default_value);
            root = new_root;
            return res;
        }
        std::pair<Key, Val> kth_entry(int k) {
            index_bounds_check(k, size());
            root = Node::splay_by_index(root, k);
            return { root->key, root->val };
        }
        SplayTreeMap split_by_index(int k) {
            index_bounds_check(k, size() + 1);
            auto [l, r] = Node::split_by_index(root, k);
            root = l;
            return SplayTreeMap(r);
        }
        SplayTreeMap split_by_key(const Key &key) {
            auto [l, r] = Node::split_by_key(root, key);
            root = l;
            return SplayTreeMap(r);
        }
    protected:
        Node *root;

        SplayTreeMap(node_ptr_t root) : root(root) {}
    
        static void index_bounds_check(unsigned int k, unsigned int n) {
            assert(k < n);
        }
        static void range_bounds_check(unsigned int l, unsigned int r, unsigned int n) {
            assert(l <= r and r <= n);
        }
};

}

#endif // SUISEN_SPLAY_TREE_MAP
