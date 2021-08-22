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
            delete this->root;
            this->root = other.root;
            other.root = nullptr;
            return *this;
        }
        void insert(const Key &key) {
            return this->insert_if_absent(key, nullptr);
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
};
};

#endif // SUISEN_SPLAY_TREE_SET
