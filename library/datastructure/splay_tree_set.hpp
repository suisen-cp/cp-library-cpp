#ifndef SUISEN_SPLAY_TREE_SET
#define SUISEN_SPLAY_TREE_SET

#include "library/datastructure/splay_tree_map.hpp"

namespace suisen {
template <typename Key>
class SplayTreeSet {
    public:
        bool contains(const Key &key) { return mp.contains(key); }
        void insert(const Key &key) { return mp.insert_if_absent(key, nullptr); }
        bool erase(const Key &key) { return mp.erase(key); }
        Key operator[](int k) { return mp.kth_entry(k).first; }
        Key kth_element(int k) { return (*this)[k]; }
        int size() { return mp.size(); }
    private:
        SplayTreeMap<Key, std::nullptr_t> mp;
};
};

#endif // SUISEN_SPLAY_TREE_SET
