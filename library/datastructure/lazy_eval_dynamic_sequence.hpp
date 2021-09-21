#ifndef SUISEN_LAZY_EVAL_DYNAMIC_SEQUENCE
#define SUISEN_LAZY_EVAL_DYNAMIC_SEQUENCE

#include <cassert>
#include <tuple>

#include "library/util/update_proxy_object.hpp"
#include "library/datastructure/range_foldable_dynamic_sequence.hpp"

namespace suisen {
namespace internal::lazy_eval_dynamic_sequence {

template <typename T, T(*op)(T, T), T (*e)(), typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)(), typename Derived>
struct LazyEvalDynamicSequenceNodeBase : public internal::range_foldable_dynamic_sequence::RangeFoldableDynamicSequenceNodeBase<T, op, e, Derived> {
    using Base = internal::range_foldable_dynamic_sequence::RangeFoldableDynamicSequenceNodeBase<T, op, e, Derived>;
    using node_ptr_t = typename Base::node_ptr_t;
    F laz;

    LazyEvalDynamicSequenceNodeBase() : LazyEvalDynamicSequenceNodeBase(e()) {}
    LazyEvalDynamicSequenceNodeBase(const T &val) : Base::RangeFoldableDynamicSequenceNodeBase(val), laz(id()) {}

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
    static node_ptr_t apply(node_ptr_t node, int l, int r, const F &f) {
        auto [tl, tm, tr] = Base::split(node, l, r);
        apply_all(tm, f);
        return Base::merge(tl, tm, tr);
    }
};

template <typename T, T(*op)(T, T), T (*e)(), typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
struct LazyEvalDynamicSequenceNode : public LazyEvalDynamicSequenceNodeBase<T, op, e, F, mapping, composition, id, LazyEvalDynamicSequenceNode<T, op, e, F, mapping, composition, id>> {
    using Base = LazyEvalDynamicSequenceNodeBase<T, op, e, F, mapping, composition, id, LazyEvalDynamicSequenceNode<T, op, e, F, mapping, composition, id>>;
    using Base::LazyEvalDynamicSequenceNodeBase;
    using node_ptr_t = typename Base::node_ptr_t;
};
}

template <typename T, T(*op)(T, T), T (*e)(), typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)(), typename SplayNode>
class LazyEvalDynamicSequenceBase : public RangeFoldableDynamicSequenceBase<T, op, e, SplayNode> {
    using Base = RangeFoldableDynamicSequenceBase<T, op, e, SplayNode>;
    using node_ptr_t = typename SplayNode::node_ptr_t;
    public:
        using value_type = T;
        using Base::RangeFoldableDynamicSequenceBase;
        void apply(int l, int r, const F &f) {
            this->range_bounds_check(l, r, this->size());
            this->root = SplayNode::apply(this->root, l, r, f);
        }
        void apply_all(const F &f) {
            SplayNode::apply_all(this->root, f);
        }
};

template <typename T, T(*op)(T, T), T (*e)(), typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
class LazyEvalDynamicSequence : public LazyEvalDynamicSequenceBase<T, op, e, F, mapping, composition, id, internal::lazy_eval_dynamic_sequence::LazyEvalDynamicSequenceNode<T, op, e, F, mapping, composition, id>> {
    using Node = internal::lazy_eval_dynamic_sequence::LazyEvalDynamicSequenceNode<T, op, e, F, mapping, composition, id>;
    using Base = LazyEvalDynamicSequenceBase<T, op, e, F, mapping, composition, id, Node>;
    using node_ptr_t = typename Node::node_ptr_t;
    public:
        using value_type = T;
        using Base::LazyEvalDynamicSequenceBase;

        LazyEvalDynamicSequence& operator=(LazyEvalDynamicSequence&  other) = delete;
        LazyEvalDynamicSequence& operator=(LazyEvalDynamicSequence&& other) {
            if (other.root == this->root) return *this;
            delete this->root;
            this->root = other.root;
            other.root = nullptr;
            return *this;
        }

        LazyEvalDynamicSequence& operator+=(LazyEvalDynamicSequence &&right) {
            this->root = Node::merge(this->root, right.root);
            right.root = nullptr;
            return *this;
        }
        void concat(LazyEvalDynamicSequence &&right) {
            *this += std::move(right);
        }
        void concat_left(LazyEvalDynamicSequence &&left) {
            this->root = (left += std::move(*this)).root;
            left.root = nullptr;
        }
        // erases [k, size()) and returns [k, size())
        LazyEvalDynamicSequence split(int k) {
            this->index_bounds_check(k, this->size() + 1);
            auto [l, r] = Node::split(this->root, k);
            this->root = l;
            return LazyEvalDynamicSequence(r);
        }
        void swap(LazyEvalDynamicSequence &r) {
            std::swap(this->root, r.root);
        }
};
}

#endif // SUISEN_LAZY_EVAL_DYNAMIC_SEQUENCE
