#ifndef SUISEN_IMPLICIT_TREAP_BASE
#define SUISEN_IMPLICIT_TREAP_BASE

#include <cassert>
#include <cstdint>
#include <string>
#include <random>
#include <tuple>
#include <utility>

namespace suisen::internal::implicit_treap {
    template <typename T, typename Derived>
    struct Node {
        using value_type = T;
        using node_type = Derived;
        using node_pointer = uint32_t;

        static inline std::mt19937 rng{ std::random_device{}() };
        static inline std::vector<node_type> _nodes{};
        static inline std::vector<node_pointer> _erased{};

        static constexpr node_pointer null = ~node_pointer(0);

        node_pointer _ch[2]{ null, null };
        value_type _val;
        uint32_t _size;
        uint32_t _priority;

        bool _rev = false;

        Node(const value_type val = {}): _val(val), _size(1), _priority(rng()) {}

        static void reserve(uint32_t capacity) {
            _nodes.reserve(capacity);
        }

        static node_type& node(node_pointer t) {
            return _nodes[t];
        }
        static const node_type& const_node(node_pointer t) {
            return _nodes[t];
        }

        static value_type& value(node_pointer t) {
            return node(t)._val;
        }
        static value_type set_value(node_pointer t, const value_type& new_val) {
            return std::exchange(value(t), new_val);
        }

        static bool empty(node_pointer t) {
            return t == null;
        }
        static uint32_t& size(node_pointer t) {
            return node(t)._size;
        }
        static uint32_t safe_size(node_pointer t) {
            return empty(t) ? 0 : size(t);
        }

        static uint32_t priority(node_pointer t) {
            return const_node(t)._priority;
        }

        static node_pointer& child0(node_pointer t) {
            return node(t)._ch[0];
        }
        static node_pointer& child1(node_pointer t) {
            return node(t)._ch[1];
        }
        static node_pointer child(node_pointer t, bool b) {
            return node(t)._ch[b];
        }
        static node_pointer set_child0(node_pointer t, node_pointer cid) {
            return std::exchange(child0(t), cid);
        }
        static node_pointer set_child1(node_pointer t, node_pointer cid) {
            return std::exchange(child1(t), cid);
        }

        static bool& reversed(node_pointer t) {
            return node(t)._rev;
        }

        static node_pointer update(node_pointer t) { // t : not null
            size(t) = safe_size(child0(t)) + safe_size(child1(t)) + 1;
            return t;
        }
        static bool push(node_pointer t) { // t : not null
            bool rev = t != null and std::exchange(reversed(t), false);
            if (rev) {
                reverse_all(child0(t));
                reverse_all(child1(t));
            }
            return rev;
        }

        static node_pointer empty_node() {
            return null;
        }
        template <typename ...Args>
        static node_pointer create_node(Args &&...args) {
            if (_erased.size()) {
                node_pointer res = _erased.back();
                _erased.pop_back();
                node(res) = node_type(std::forward<Args>(args)...);
                return res;
            } else {
                node_pointer res = _nodes.size();
                _nodes.emplace_back(std::forward<Args>(args)...);
                return res;
            }
        }
        static void delete_node(node_pointer t) {
            _erased.push_back(t);
        }
        static void delete_tree(node_pointer t) {
            if (t == null) return;
            delete_tree(child0(t));
            delete_tree(child1(t));
            delete_node(t);
        }

        template <typename ...Args>
        static node_pointer build(Args &&... args) {
            node_pointer res = empty_node();
            for (auto&& e : std::vector<value_type>(std::forward<Args>(args)...)) {
                res = push_back(res, std::move(e));
            }
            return res;
        }

        static std::pair<node_pointer, node_pointer> split(node_pointer t, uint32_t k) {
            if (t == null) {
                return { null, null };
            }
            node_type::push(t);
            if (const uint32_t lsiz = safe_size(child0(t)); k <= lsiz) {
                auto [ll, lr] = split(child0(t), k);
                set_child0(t, lr);
                return { ll, node_type::update(t) };
            } else {
                auto [rl, rr] = split(child1(t), k - (lsiz + 1));
                set_child1(t, rl);
                return { node_type::update(t), rr };
            }
        }
        static std::tuple<node_pointer, node_pointer, node_pointer> split(node_pointer t, uint32_t l, uint32_t r) {
            auto [tlm, tr] = split(t, r);
            auto [tl, tm] = split(tlm, l);
            return { tl, tm, tr };
        }
        static node_pointer merge(node_pointer tl, node_pointer tr) {
            if (tl == null or tr == null) {
                return tl ^ tr ^ null;
            }
            if (priority(tl) < priority(tr)) {
                node_type::push(tr);
                set_child0(tr, merge(tl, child0(tr)));
                return node_type::update(tr);
            } else {
                node_type::push(tl);
                set_child1(tl, merge(child1(tl), tr));
                return node_type::update(tl);
            }
        }
        static node_pointer merge(node_pointer tl, node_pointer tm, node_pointer tr) {
            return merge(merge(tl, tm), tr);
        }
        static node_pointer insert_impl(node_pointer t, uint32_t k, node_pointer new_node) {
            if (t == null) {
                return new_node;
            }
            if (priority(new_node) > priority(t)) {
                auto [tl, tr] = split(t, k);
                set_child0(new_node, tl);
                set_child1(new_node, tr);
                return node_type::update(new_node);
            } else {
                node_type::push(t);
                if (const uint32_t lsiz = safe_size(child0(t)); k <= lsiz) {
                    set_child0(t, insert_impl(child0(t), k, new_node));
                } else {
                    set_child1(t, insert_impl(child1(t), k - (lsiz + 1), new_node));
                }
                return node_type::update(t);
            }
        }
        template <typename ...Args>
        static node_pointer insert(node_pointer t, uint32_t k, Args &&...args) {
            return insert_impl(t, k, create_node(std::forward<Args>(args)...));
        }
        template <typename ...Args>
        static node_pointer push_front(node_pointer t, Args &&...args) {
            return insert(t, 0, std::forward<Args>(args)...);
        }
        template <typename ...Args>
        static node_pointer push_back(node_pointer t, Args &&...args) {
            return insert(t, safe_size(t), std::forward<Args>(args)...);
        }

        static node_pointer erase(node_pointer t, uint32_t k) {
            node_type::push(t);
            if (const uint32_t lsiz = safe_size(child0(t)); k == lsiz) {
                delete_node(t);
                return merge(child0(t), child1(t));
            } else if (k < lsiz) {
                set_child0(t, erase(child0(t), k));
                return node_type::update(t);
            } else {
                set_child1(t, erase(child1(t), k - (lsiz + 1)));
                return node_type::update(t);
            }
        }
        static node_pointer pop_front(node_pointer t) {
            return erase(t, 0);
        }
        static node_pointer pop_back(node_pointer t) {
            return erase(t, safe_size(t) - 1);
        }

        static node_pointer rotate(node_pointer t, uint32_t k) {
            auto [tl, tr] = split(t, k);
            return merge(tr, tl);
        }

        static value_type& get(node_pointer t, uint32_t k) {
            while (true) {
                node_type::push(t);
                if (const uint32_t lsiz = safe_size(child0(t)); k == lsiz) {
                    return value(t);
                } else if (k < lsiz) {
                    t = child0(t);
                } else {
                    k -= lsiz + 1;
                    t = child1(t);
                }
            }
        }

        template <typename Func>
        static node_pointer set_update(node_pointer t, uint32_t k, const Func& f) {
            node_type::push(t);
            if (const uint32_t lsiz = safe_size(child0(t)); k == lsiz) {
                value_type& val = value(t);
                val = f(const_cast<const value_type&>(val));
            } else if (k < lsiz) {
                set_child0(t, set_update(child0(t), k, f));
            } else {
                set_child1(t, set_update(child1(t), k - (lsiz + 1), f));
            }
            return node_type::update(t);
        }

        static node_pointer reverse_all(node_pointer t) {
            if (t != null) {
                reversed(t) ^= true;
                std::swap(child0(t), child1(t));
            }
            return t;
        }
        static node_pointer reverse(node_pointer t, uint32_t l, uint32_t r) {
            auto [tl, tm, tr] = split(t, l, r);
            return merge(tl, Derived::reverse_all(tm), tr);
        }

        static std::vector<value_type> dump(node_pointer t) {
            std::vector<value_type> res;
            res.reserve(safe_size(t));
            auto rec = [&](auto rec, node_pointer t) -> void {
                if (t == null) return;
                node_type::push(t);
                rec(rec, child0(t));
                res.push_back(value(t));
                rec(rec, child1(t));
            };
            rec(rec, t);
            return res;
        }

        // Predicate : (value, index) -> { false, true }
        template <typename Predicate>
        static uint32_t binary_search(node_pointer t, const Predicate& f) {
            int ng = -1, ok = safe_size(t);
            while (ok - ng > 1) {
                node_type::push(t);
                const int lsiz = safe_size(child0(t));
                if (f(value(t), ng + lsiz + 1)) {
                    ok = ng + lsiz + 1;
                    t = child0(t);
                } else {
                    ng += lsiz + 1;
                    t = child1(t);
                }
            }
            return ok;
        }

        struct NodeIterator {
            std::vector<node_pointer> stk;

            value_type& operator*() const {
                return value(stk.back());
            }

            NodeIterator& operator++() {
                node_pointer t = stk.back();
                if (child1(t) == null) {
                    up</*suc = */true>();
                } else {
                    down</*suc = */true>(child1(t), 0);
                }
                return *this;
            }
            NodeIterator operator++(int) {
                NodeIterator res = *this;
                ++(*this);
                return res;
            }

            NodeIterator& operator--() {
                node_pointer t = stk.back();
                if (child0(t) == null) {
                    up</*suc = */false>();
                } else {
                    down</*suc = */false>(child0(t), 0);
                }
                return *this;
            }
            NodeIterator operator--(int) {
                NodeIterator res = *this;
                --(*this);
                return res;
            }
        
            NodeIterator& operator+=(int k) {
                if (k >= 0) suc(k);
                else pre(-k);
                return *this;
            }
            NodeIterator operator+(int k) {
                NodeIterator res = *this;
                res += k;
                return res;
            }

            NodeIterator& operator-=(int k) {
                return *this += -k;
            }
            NodeIterator operator-(int k) {
                return *this + (-k);
            }

            bool operator==(NodeIterator& other) const {
                return stk.empty() ? other.stk.empty() : other.stk.size() and stk.back() == other.stk.back();
            }
        private:
            template <bool suc>
            void up() {
                node_pointer t = stk.back();
                do {
                    stk.pop_back();
                    if (t == child(stk.back(), not suc)) {
                        break;
                    }
                    t = stk.back();
                } while (stk.size());
            }
            template <bool suc>
            void down(node_pointer t, size_t k) {
                while (true) {
                    node_type::push(t);
                    stk.push_back(t);
                    
                    node_pointer siz = safe_size(child(t, not suc));
                    if (k == siz) {
                        break;
                    } else if (k < siz) {
                        t = child(t, not suc);
                    } else {
                        k -= siz + 1;
                        t = child(t, suc);
                    }
                }
            }
            void suc(size_t k) {
                while (k) {
                    node_pointer t = stk.back();
                    node_pointer rsiz = safe_size(child1(t));
                    if (k > rsiz) {
                        up</*suc = */true>();
                        k -= rsiz + 1;
                    } else {
                        down</*suc = */true>(child1(t), k - 1);
                        break;
                    }
                }
            }
            void pre(size_t k) {
                while (k) {
                    node_pointer t = stk.back();
                    node_pointer lsiz = safe_size(child0(t));
                    if (k > lsiz) {
                        up</*suc = */false>();
                        k -= lsiz + 1;
                    } else {
                        down</*suc = */false>(child0(t), k - 1);
                        break;
                    }
                }
            }
        };

        static NodeIterator begin(node_pointer t) {
            std::vector<node_pointer> stk;
            while (t != null) {
                node_type::push(t);
                stk.push_back(t);
                t = child0(t);
            }
            return NodeIterator{ stk };
        }
        static NodeIterator end(node_pointer t) {
            return NodeIterator{};
        }
        static NodeIterator kth_iterator(node_pointer t, uint32_t k) {
            std::vector<node_pointer> stk;
            while (t != null) {
                node_type::push(t);
                stk.push_back(t);
                uint32_t siz = safe_size(child0(t));
                if (k == siz) {
                    break;
                } else if (k < siz) {
                    t = child0(t);
                } else {
                    k -= siz + 1;
                    t = child1(t);
                }
            }
            return NodeIterator{ stk };
        }
    };
} // namespace suisen::internal::implicit_treap

#endif // SUISEN_IMPLICIT_TREAP_BASE
