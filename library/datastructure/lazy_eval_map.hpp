#ifndef SUISEN_LAZY_EVAL_MAP
#define SUISEN_LAZY_EVAL_MAP

#include <cassert>
#include <tuple>

#include "library/util/update_proxy_object.hpp"
#include "library/datastructure/range_foldable_map.hpp"

namespace suisen {
namespace internal::lazy_eval_map {

template <typename Key, typename Val, Val(*op)(Val, Val), Val (*e)(), typename F, Val(*mapping)(F, Val), F(*composition)(F, F), F(*id)(), typename Derived>
struct LazyEvalMapNodeBase : public internal::range_foldable_map::RangeFoldableMapNodeBase<Key, Val, op, e, Derived> {
    using Base = internal::range_foldable_map::RangeFoldableMapNodeBase<Key, Val, op, e, Derived>;
    using node_ptr_t = typename Base::node_ptr_t;
    F laz;

    LazyEvalMapNodeBase() : LazyEvalMapNodeBase(Key{}, e()) {}
    LazyEvalMapNodeBase(const Key &key, const Val &val) : Base::RangeFoldableMapNodeBase(key, val), laz(id()) {}

    void push() {
        Base::push();
        apply_all(this->ch[0], laz), apply_all(this->ch[1], laz);
        laz = id();
    }
    static void apply_all(node_ptr_t node, const F &f) {
        if (node == nullptr) return;
        node->val = mapping(f, node->val);
        node->dat = mapping(f, node->dat);
        node->laz = composition(f, node->laz);
    }
    static node_ptr_t apply_by_key(node_ptr_t node, const Key &l, const Key &r, const F &f) {
        auto [tl, tm, tr] = Base::split_by_key(node, l, r);
        apply_all(tm, f);
        return Base::merge(tl, tm, tr);
    }
    static node_ptr_t apply_by_index(node_ptr_t node, int l, int r, const F &f) {
        auto [tl, tm, tr] = Base::split_by_index(node, l, r);
        apply_all(tm, f);
        return Base::merge(tl, tm, tr);
    }
};

template <typename Key, typename Val, Val(*op)(Val, Val), Val (*e)(), typename F, Val(*mapping)(F, Val), F(*composition)(F, F), F(*id)()>
struct LazyEvalMapNode : public LazyEvalMapNodeBase<Key, Val, op, e, F, mapping, composition, id, LazyEvalMapNode<Key, Val, op, e, F, mapping, composition, id>> {
    using Base = LazyEvalMapNodeBase<Key, Val, op, e, F, mapping, composition, id, LazyEvalMapNode<Key, Val, op, e, F, mapping, composition, id>>;
    using Base::LazyEvalMapNodeBase;
    using node_ptr_t = typename Base::node_ptr_t;
};
}

template <typename Key, typename Val, Val(*op)(Val, Val), Val (*e)(), typename F, Val(*mapping)(F, Val), F(*composition)(F, F), F(*id)()>
class LazyEvalMap {
    using Node = internal::lazy_eval_map::LazyEvalMapNode<Key, Val, op, e, F, mapping, composition, id>;
    using node_ptr_t = typename Node::node_ptr_t;
    public:
        LazyEvalMap() : root(nullptr) {}
        ~LazyEvalMap() {
            delete root;
        }

        LazyEvalMap& operator=(const LazyEvalMap&) = delete;
        LazyEvalMap& operator=(LazyEvalMap&& other) {
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

        auto operator[](const Key &key) {
            get_or_create(key, e());
            return UpdateProxyObject { root->val, [this]{ root->update(); } };
        }
        Val operator()(const Key &l, const Key &r) {
            return prod(l, r);
        }
        Val prod_by_key(const Key &l, const Key &r) {
            auto [new_root, res] = Node::prod_by_key(root, l, r);
            root = new_root;
            return res;
        }
        Val prod_by_index(int l, int r) {
            auto [new_root, res] = Node::prod_by_index(root, l, r);
            root = new_root;
            return res;
        }
        Val prod_all() {
            return Node::prod_all(root);
        }
        void apply_by_key(const Key &l, const Key &r, const F &f) {
            root = Node::apply_by_key(root, l, r, f);
        }
        void apply_by_index(int l, int r, const F &f) {
            root = Node::apply_by_index(root, l, r, f);
        }
        void apply_all(const F &f) {
            Node::apply_all(root, f);
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
        LazyEvalMap split_by_index(int k) {
            index_bounds_check(k, size() + 1);
            auto [l, r] = Node::split_by_index(root, k);
            root = l;
            return LazyEvalMap(r);
        }
        LazyEvalMap split_by_key(const Key &key) {
            auto [l, r] = Node::split_by_key(root, key);
            root = l;
            return LazyEvalMap(r);
        }
    protected:
        Node *root;

        LazyEvalMap(node_ptr_t root) : root(root) {}
    
        static void index_bounds_check(unsigned int k, unsigned int n) {
            assert(k < n);
        }
        static void range_bounds_check(unsigned int l, unsigned int r, unsigned int n) {
            assert(l <= r and r <= n);
        }
};

}


#endif // SUISEN_LAZY_EVAL_MAP
