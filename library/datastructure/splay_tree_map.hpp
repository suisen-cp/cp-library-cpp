#ifndef SUISEN_SPLAY_TREE_MAP
#define SUISEN_SPLAY_TREE_MAP

#include "library/datastructure/internal_splay_tree.hpp"

namespace suisen {

template <typename Key, typename Val>
class SplayTreeMap {
    using Node = internal::splay_tree::Node<Key, Val>;
    public:
        SplayTreeMap() : root(nullptr) {}
        ~SplayTreeMap() {
            delete root;
        }
        bool contains(const Key &key) {
            auto [new_root, found] = Node::search(root, key);
            root = new_root;
            return found;
        }
        void insert(const Key &key, const Val &val) {
            root = Node::insert(root, key, val, true);
        }
        void insert_if_absent(const Key &key, const Val &val) {
            root = Node::insert(root, key, val, false);
        }
        bool erase(const Key &key) {
            auto [new_root, is_erased] = Node::erase(root, key);
            root = new_root;
            return is_erased;
        }
        Val& get_or_create(const Key &key, const Val &val) {
            root = Node::insert(root, key, val, false);
            return root->val;
        }
        Val& operator[](const Key &key) {
            return get_or_create(key, Val{});
        }
        Val get_or_default(const Key &key, const Val &val) {
            auto [new_root, res] = Node::get_or_default(root, key, val);
            root = new_root;
            return res;
        }
        std::pair<Key, Val> kth_entry(int k) {
            return Node::kth_entry(root, k);
        }
        int size() {
            return Node::size(root);
        }
    private:
        Node *root;
};

};

#endif // SUISEN_SPLAY_TREE_MAP
