#ifndef SUISEN_SPLAY_TREE_SET
#define SUISEN_SPLAY_TREE_SET

#include "library/datastructure/splay_tree_map.hpp"

namespace suisen {
template <typename Key>
class SplayTreeSet : protected SplayTreeMap<Key, std::nullptr_t> {
    using Base = SplayTreeMap<Key, std::nullptr_t>;
    using Node = typename Base::Node;
    public:
        using Base::SplayTreeMap;
        SplayTreeSet& operator=(const SplayTreeSet&) = delete;
        SplayTreeSet& operator=(SplayTreeSet&& other) {
            if (other.root == this->root) return *this;
            delete this->root;
            this->root = other.root;
            other.root = nullptr;
            return *this;
        }
        int size() {
            return Node::size(this->root);
        }
        bool contains(const Key &key) {
            auto [new_root, found] = Node::find_key(this->root, key);
            this->root = new_root;
            return found;
        }
        void insert(const Key &key) {
            return this->insert_if_absent(key, nullptr);
        }
        bool erase(const Key &key) {
            return this->erase_key(key);
        }
        Key operator[](int k) {
            return this->kth_entry(k).first;
        }
        Key kth_element(int k) {
            return (*this)[k];
        }
        SplayTreeSet split_by_index(int k) {
            Base::index_bounds_check(k, this->size() + 1);
            auto [l, r] = Node::split_by_index(this->root, k);
            this->root = l;
            return SplayTreeSet<Key>(r);
        }
        SplayTreeSet split_by_key(const Key &key) {
            auto [l, r] = Node::split_by_key(this->root, key);
            this->root = l;
            return SplayTreeSet<Key>(r);
        }
        void merge(SplayTreeSet &&r) {
            assert(this->root != r.root);
            this->root = Node::merge(this->root, r.root);
            r.root = nullptr;
        }
        void swap(SplayTreeSet &r) {
            std::swap(this->root, r.root);
        }
};
};

#endif // SUISEN_SPLAY_TREE_SET
