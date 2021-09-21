#ifndef SUISEN_RANGE_FOLDABLE_DYNAMIC_SEQUENCE
#define SUISEN_RANGE_FOLDABLE_DYNAMIC_SEQUENCE

#include <cassert>
#include <tuple>

#include "library/util/update_proxy_object.hpp"
#include "library/datastructure/dynamic_sequence.hpp"

namespace suisen {
namespace internal::range_foldable_dynamic_sequence {

template <typename T, T(*op)(T, T), T (*e)(), typename Derived>
struct RangeFoldableDynamicSequenceNodeBase : public internal::dynamic_sequence::DynamicSequenceNodeBase<T, Derived> {
    using Base = internal::dynamic_sequence::DynamicSequenceNodeBase<T, Derived>;
    using node_ptr_t = typename Base::node_ptr_t;
    T dat;
    RangeFoldableDynamicSequenceNodeBase() : RangeFoldableDynamicSequenceNodeBase(e()) {}
    RangeFoldableDynamicSequenceNodeBase(const T &val) : Base::DynamicSequenceNodeBase(val), dat(val) {}
    void update() {
        Base::update();
        dat = op(op(prod_all(this->ch[0]), this->val), prod_all(this->ch[1]));
    }
    static T prod_all(node_ptr_t node) {
        return node == nullptr ? e() : node->dat;
    }
    static std::pair<node_ptr_t, T> prod(node_ptr_t node, int l, int r) {
        auto [tl, tm, tr] = Base::split(node, l, r);
        T res = prod_all(tm);
        return { Base::merge(tl, tm, tr), res };
    }
};

template <typename T, T(*op)(T, T), T (*e)()>
struct RangeFoldableDynamicSequenceNode : public RangeFoldableDynamicSequenceNodeBase<T, op, e, RangeFoldableDynamicSequenceNode<T, op, e>> {
    using Base = RangeFoldableDynamicSequenceNodeBase<T, op, e, RangeFoldableDynamicSequenceNode<T, op, e>>;
    using Base::RangeFoldableDynamicSequenceNodeBase;
    using node_ptr_t = typename Base::node_ptr_t;
};
}

template <typename T, T(*op)(T, T), T (*e)(), typename SplayNode>
class RangeFoldableDynamicSequenceBase : public DynamicSequenceBase<T, SplayNode> {
    using Base = DynamicSequenceBase<T, SplayNode>;
    using node_ptr_t = typename SplayNode::node_ptr_t;
    public:
        using value_type = T;
        using Base::DynamicSequenceBase;
        auto operator[](int k) {
            this->index_bounds_check(k, this->size());
            this->root = SplayNode::splay(this->root, k);
            return UpdateProxyObject { this->root->val, [this]{ this->root->update(); } };
        }
        T operator()(int l, int r) {
            return prod(l, r);
        }
        T prod(int l, int r) {
            this->range_bounds_check(l, r, this->size());
            auto [new_root, res] = SplayNode::prod(this->root, l, r);
            this->root = new_root;
            return res;
        }
        T prod_all() {
            return SplayNode::prod_all(this->root);
        }
};

template <typename T, T(*op)(T, T), T (*e)()>
class RangeFoldableDynamicSequence : public RangeFoldableDynamicSequenceBase<T, op, e, internal::range_foldable_dynamic_sequence::RangeFoldableDynamicSequenceNode<T, op, e>> {
    using Node = internal::range_foldable_dynamic_sequence::RangeFoldableDynamicSequenceNode<T, op, e>;
    using Base = RangeFoldableDynamicSequenceBase<T, op, e, Node>;
    using node_ptr_t = typename Node::node_ptr_t;
    public:
        using value_type = T;
        using Base::RangeFoldableDynamicSequenceBase;

        RangeFoldableDynamicSequence& operator=(RangeFoldableDynamicSequence&  other) = delete;
        RangeFoldableDynamicSequence& operator=(RangeFoldableDynamicSequence&& other) {
            if (other.root == this->root) return *this;
            delete this->root;
            this->root = other.root;
            other.root = nullptr;
            return *this;
        }

        RangeFoldableDynamicSequence& operator+=(RangeFoldableDynamicSequence &&right) {
            this->root = Node::merge(this->root, right.root);
            right.root = nullptr;
            return *this;
        }
        void concat(RangeFoldableDynamicSequence &&right) {
            *this += std::move(right);
        }
        void concat_left(RangeFoldableDynamicSequence &&left) {
            this->root = (left += std::move(*this)).root;
            left.root = nullptr;
        }
        // erases [k, size()) and returns [k, size())
        RangeFoldableDynamicSequence split(int k) {
            this->index_bounds_check(k, this->size() + 1);
            auto [l, r] = Node::split(this->root, k);
            this->root = l;
            return RangeFoldableDynamicSequence(r);
        }
        void swap(RangeFoldableDynamicSequence &r) {
            std::swap(this->root, r.root);
        }
};

}

#endif // SUISEN_RANGE_FOLDABLE_DYNAMIC_SEQUENCE
