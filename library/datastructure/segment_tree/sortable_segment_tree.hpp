#ifndef SUISEN_SORTABLE_SEGTREE
#define SUISEN_SORTABLE_SEGTREE

#include "library/util/pointer_32bit.hpp"

#include <algorithm>
#include <cassert>
#include <random>
#include <tuple>
#include <utility>
#include <vector>

namespace suisen {
    template <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T), typename Key = int>
    struct SortableSegmentTree {
    private:
        static constexpr bool use_32bit_pointer = true;

        struct InnerNode;
        struct OuterNode;
        using inner_node = InnerNode;
        using outer_node = OuterNode;
        using inner_node_pointer = std::conditional_t<use_32bit_pointer, ptr32<inner_node>, inner_node*>;
        using outer_node_pointer = std::conditional_t<use_32bit_pointer, ptr32<outer_node>, outer_node*>;
    public:
        using size_type = int;
        using key_type = Key;
        using value_type = T;
    private:
        using random_engine = std::mt19937;

        using priority_type = std::invoke_result_t<random_engine>;

        static priority_type random_priority() {
            static random_engine engine{ std::random_device{}() };
            return engine();
        }

        struct InnerNode {
            priority_type _priority;

            size_type _siz;
            key_type _key;
            key_type _kmin, _kmax;

            value_type _val;
            value_type _sum;

            inner_node_pointer _ch[2]{ nullptr, nullptr };

            InnerNode(const key_type& key, const value_type& val) : _priority(random_priority()), _siz(1), _key(key), _kmin(key), _kmax(key), _val(val), _sum(val) {}

            static size_type& size(inner_node_pointer t) { return t->_siz; }
            static size_type safe_size(inner_node_pointer t) { return t ? size(t) : 0; }

            static const key_type& const_key(inner_node_pointer t) { return t->_key; }
            static key_type& key(inner_node_pointer t) { return t->_key; }
            static key_type& min_key(inner_node_pointer t) { return t->_kmin; }
            static key_type& max_key(inner_node_pointer t) { return t->_kmax; }

            static const value_type& const_value(inner_node_pointer t) { return t->_val; }
            static value_type& value(inner_node_pointer t) { return t->_val; }
            static std::pair<key_type, value_type> set(inner_node_pointer t, const key_type& new_key, const value_type& new_val) {
                return { std::exchange(key(t), new_key), std::exchange(value(t), new_val) };
            }

            static value_type& sum(inner_node_pointer t) { return t->_sum; }
            static value_type safe_sum(inner_node_pointer t) { return t ? sum(t) : e(); }

            static priority_type& priority(inner_node_pointer t) { return t->_priority; }

            static inner_node_pointer& child0(inner_node_pointer t) { return t->_ch[0]; }
            static inner_node_pointer& child1(inner_node_pointer t) { return t->_ch[1]; }
            static inner_node_pointer set_child0(inner_node_pointer t, inner_node_pointer ct) { return std::exchange(child0(t), ct); }
            static inner_node_pointer set_child1(inner_node_pointer t, inner_node_pointer ct) { return std::exchange(child1(t), ct); }

            static inner_node_pointer update(inner_node_pointer t) {
                size(t) = safe_size(child0(t)) + safe_size(child1(t)) + 1;
                sum(t) = op(op(safe_sum(child0(t)), value(t)), safe_sum(child1(t)));
                min_key(t) = child0(t) ? min_key(child0(t)) : key(t);
                max_key(t) = child1(t) ? max_key(child1(t)) : key(t);
                return t;
            }

            static inner_node_pointer alloc_node(const key_type& key, const value_type& val) {
                if constexpr (use_32bit_pointer) {
                    return inner_node_pointer::alloc(key, val);
                } else {
                    return new inner_node(key, val);
                }
            }
            static void dealloc_node(inner_node_pointer t) {
                if constexpr (use_32bit_pointer) {
                    inner_node_pointer::dealloc(t);
                } else {
                    delete t;
                }
            }
            static void dealloc_all(inner_node_pointer t) {
                if (not t) return;
                dealloc_all(child0(t));
                dealloc_all(child1(t));
                dealloc_node(t);
            }

            static value_type get_at(inner_node_pointer t, size_type k) {
                assert(0 <= k and k < safe_size(t));
                while (true) {
                    if (const size_type lsiz = safe_size(child0(t)); k <= lsiz) {
                        if (k == lsiz) return value(t);
                        t = child0(t);
                    } else {
                        t = child1(t);
                        k -= lsiz + 1;
                    }
                }
            }
            static value_type set_at(inner_node_pointer t, size_type k, const value_type& val) {
                assert(0 <= k and k < safe_size(t));
                static std::vector<inner_node_pointer> stack{};
                while (true) {
                    stack.push_back(t);
                    if (const size_type lsiz = safe_size(child0(t)); k <= lsiz) {
                        if (k == lsiz) {
                            value_type old_val = value(t);
                            value(t) = val;
                            while (stack.size()) update(stack.back()), stack.pop_back();
                            return old_val;
                        }
                        t = child0(t);
                    } else {
                        t = child1(t);
                        k -= lsiz + 1;
                    }
                }
            }
            static value_type prod_at_range(inner_node_pointer t, size_type l, size_type r) {
                if (not t) return e();
                if (l <= 0 and r >= size(t)) return sum(t);
                size_type lsiz = safe_size(child0(t));
                if (r <= lsiz) return prod_at_range(child0(t), l, r);
                if (l > lsiz) return prod_at_range(child1(t), l - (lsiz + 1), r - (lsiz + 1));
                value_type sum_l = prod_at_range(child0(t), l, r);
                value_type sum_r = prod_at_range(child1(t), l - (lsiz + 1), r - (lsiz + 1));
                return op(op(sum_l, value(t)), sum_r);
            }

            static std::pair<inner_node_pointer, inner_node_pointer> split_at(inner_node_pointer t, size_type k) {
                if (k == 0) return { nullptr, t };
                if (k == safe_size(t)) return { t, nullptr };

                static std::vector<inner_node_pointer> lp{}, rp{};

                while (true) {
                    if (const size_type lsiz = safe_size(child0(t)); k <= lsiz) {
                        if (rp.size()) set_child0(rp.back(), t);
                        rp.push_back(t);
                        if (k == lsiz) {
                            if (lp.size()) set_child1(lp.back(), child0(t));

                            inner_node_pointer lt = set_child0(t, nullptr), rt = nullptr;

                            while (lp.size()) update(lt = lp.back()), lp.pop_back();
                            while (rp.size()) update(rt = rp.back()), rp.pop_back();

                            return { lt, rt };
                        }
                        t = child0(t);
                    } else {
                        if (lp.size()) set_child1(lp.back(), t);
                        lp.push_back(t);
                        t = child1(t);
                        k -= lsiz + 1;
                    }
                }
            }
            static std::pair<inner_node_pointer, inner_node_pointer> split_key(inner_node_pointer t, key_type k) {
                if (not t) return { nullptr, nullptr };
                if (k <= min_key(t)) return { nullptr, t };
                if (k > max_key(t)) return { t, nullptr };

                static std::vector<inner_node_pointer> lp{}, rp{};

                while (t) {
                    if (k <= key(t)) {
                        if (rp.size()) set_child0(rp.back(), t);
                        rp.push_back(t);
                        inner_node_pointer nt = child0(t);
                        if (not nt or max_key(nt) < k) break;
                        t = nt;
                    } else {
                        if (lp.size()) set_child1(lp.back(), t);
                        lp.push_back(t);
                        t = child1(t);
                    }
                }

                inner_node_pointer lt = nullptr, rt = nullptr;
                if (t) {
                    if (lp.size()) set_child1(lp.back(), child0(t));
                    lt = set_child0(t, nullptr);
                } else {
                    if (lp.size()) set_child1(lp.back(), nullptr);
                }

                while (lp.size()) update(lt = lp.back()), lp.pop_back();
                while (rp.size()) update(rt = rp.back()), rp.pop_back();

                return { lt, rt };
            }

            static inner_node_pointer concat_nonnull(inner_node_pointer tl, inner_node_pointer tr) {
                assert(max_key(tl) < min_key(tr));
                if (priority(tl) < priority(tr)) {
                    if (inner_node_pointer tm = child0(tr); not tm) {
                        set_child0(tr, tl);
                    } else {
                        set_child0(tr, concat_nonnull(tl, tm));
                    }
                    return update(tr);
                } else {
                    if (inner_node_pointer tm = child1(tl); not tm) {
                        set_child1(tl, tr);
                    } else {
                        set_child1(tl, concat_nonnull(tm, tr));
                    }
                    return update(tl);
                }
            }
            static inner_node_pointer concat(inner_node_pointer tl, inner_node_pointer tr) {
                if (not tl) return tr;
                if (not tr) return tl;
                return concat_nonnull(tl, tr);
            }
            static inner_node_pointer merge(inner_node_pointer t1, inner_node_pointer t2) {
                if (not t1) return t2;
                if (not t2) return t1;
                if (key(t1) > key(t2)) std::swap(t1, t2);
                if (max_key(t1) <= min_key(t2)) return concat_nonnull(t1, t2);
                if (key(t1) <= min_key(t2)) {
                    inner_node_pointer tr = set_child1(t1, nullptr);
                    return concat_nonnull(update(t1), merge(t2, tr));
                } else if (max_key(t1) <= key(t2)) {
                    inner_node_pointer tl = set_child0(t2, nullptr);
                    return concat_nonnull(merge(t1, tl), update(t2));
                } else {
                    auto [t2_l, t2_r] = split_key(t2, key(t1));
                    assert(t2_l and t2_r);
                    inner_node_pointer tr = set_child1(t1, nullptr);
                    inner_node_pointer tl = update(t1);
                    return concat_nonnull(merge(tl, t2_l), merge(tr, t2_r));
                }
            }

            template <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool, Predicate, value_type>, std::nullptr_t> = nullptr>
            static std::pair<size_type, value_type> max_right(inner_node_pointer t, const Predicate& f, const value_type& init_sum = e()) {
                size_type r = 0;
                value_type s = init_sum;
                while (t) {
                    if (value_type nxt_s = op(s, safe_sum(child0(t))); f(nxt_s)) {
                        s = std::move(nxt_s);
                        r += safe_size(child0(t));
                        if (nxt_s = op(s, value(t)); f(nxt_s)) {
                            s = std::move(nxt_s);
                            r += 1;
                            t = child1(t);
                        } else break;
                    } else {
                        t = child0(t);
                    }
                }
                return { r, s };
            }
            template <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool, Predicate, value_type>, std::nullptr_t> = nullptr>
            static std::pair<size_type, value_type> min_left(inner_node_pointer t, const Predicate& f, const value_type& init_sum = e()) {
                size_type l = safe_size(t);
                value_type s = init_sum;
                while (t) {
                    if (value_type nxt_s = op(safe_sum(child1(t)), s); f(nxt_s)) {
                        s = std::move(nxt_s);
                        l -= safe_size(child1(t));
                        if (nxt_s = op(value(t), s); f(nxt_s)) {
                            s = std::move(nxt_s);
                            l -= 1;
                            t = child0(t);
                        } else break;
                    } else {
                        t = child1(t);
                    }
                }
                return { l, s };
            }

            template <typename Func, std::enable_if_t<std::is_invocable_r_v<void, Func, key_type, value_type>, std::nullptr_t> = nullptr>
            static void foreach(inner_node_pointer t, bool rev, const Func& f) {
                if (not t) return;
                if (rev) {
                    foreach(child1(t), rev, f), f(const_key(t), const_value(t)), foreach(child0(t), rev, f);
                } else {
                    foreach(child0(t), rev, f), f(const_key(t), const_value(t)), foreach(child1(t), rev, f);
                }
            }
        };

        struct OuterNode {
            priority_type _priority;

            size_type _siz;
            value_type _sum;

            bool _rev;
            inner_node_pointer _inner_node;

            outer_node_pointer _ch[2]{ nullptr, nullptr };

            OuterNode(inner_node_pointer inner_node, bool rev = false) : _priority(random_priority()), _siz(inner_node::size(inner_node)), _sum(inner_node::sum(inner_node)), _rev(rev), _inner_node(inner_node) {
                if (rev) _sum = toggle(std::move(_sum));
            }

            static size_type& size(outer_node_pointer t) { return t->_siz; }
            static size_type safe_size(outer_node_pointer t) { return t ? size(t) : 0; }
            static size_type inner_size(outer_node_pointer t) { return inner_node::size(inner(t)); }

            static value_type& sum(outer_node_pointer t) { return t->_sum; }
            static value_type safe_sum(outer_node_pointer t) { return t ? sum(t) : e(); };
            static value_type inner_sum(outer_node_pointer t) {
                value_type res = inner_node::sum(inner(t));
                return reversed(t) ? toggle(std::move(res)) : res;
            }

            static bool& reversed(outer_node_pointer t) { return t->_rev; }

            static priority_type& priority(outer_node_pointer t) { return t->_priority; }

            static outer_node_pointer& child0(outer_node_pointer t) { return t->_ch[0]; }
            static outer_node_pointer& child1(outer_node_pointer t) { return t->_ch[1]; }
            static outer_node_pointer set_child0(outer_node_pointer t, outer_node_pointer ct) { return std::exchange(child0(t), ct); }
            static outer_node_pointer set_child1(outer_node_pointer t, outer_node_pointer ct) { return std::exchange(child1(t), ct); }

            static inner_node_pointer& inner(outer_node_pointer t) { return t->_inner_node; }

            static outer_node_pointer update(outer_node_pointer t) { // t : not nullptr
                size(t) = safe_size(child0(t)) + safe_size(child1(t)) + inner_size(t);
                sum(t) = op(op(safe_sum(child0(t)), inner_sum(t)), safe_sum(child1(t)));
                return t;
            }

            static outer_node_pointer alloc_node(inner_node_pointer inner_node, bool rev = false) {
                if (not inner_node) return nullptr;
                if constexpr (use_32bit_pointer) {
                    return outer_node_pointer::alloc(inner_node, rev);
                } else {
                    return new outer_node(inner_node, rev);
                }
            }
            static void dealloc_node(outer_node_pointer t) {
                if (not t) return;
                inner_node::dealloc_all(inner(t));
                if constexpr (use_32bit_pointer) {
                    outer_node_pointer::dealloc(t);
                } else {
                    delete t;
                }
            }
            static void dealloc_all(outer_node_pointer t) {
                if (not t) return;
                dealloc_all(child0(t));
                dealloc_all(child1(t));
                dealloc_node(t);
            }

            static outer_node_pointer build(const std::vector<std::pair<key_type, value_type>>& dat) {
                const size_t n = dat.size();

                if (n == 0) return nullptr;

                std::vector<priority_type> priorities(n);
                std::generate(priorities.begin(), priorities.end(), random_priority);
                std::make_heap(priorities.begin(), priorities.end());

                std::vector<outer_node_pointer> nodes(n);

                size_t fpow2 = 1;
                while ((fpow2 << 1) <= n) fpow2 <<= 1; // 2^floor(log_2(n))

                if constexpr (use_32bit_pointer) {
                    inner_node_pointer::reserve(n);
                    outer_node_pointer::reserve(n);
                }

                for (size_t bbst_index = 1, skipped = 0; bbst_index < 2 * fpow2; ++bbst_index) {
                    size_t heap_index = (fpow2 | ((bbst_index - 1) >> 1)) >> __builtin_ctz(bbst_index);
                    if (heap_index <= n) {
                        size_t index = bbst_index - skipped;
                        inner_node_pointer inner = inner_node::alloc_node(dat[index - 1].first, dat[index - 1].second);
                        nodes[heap_index - 1] = outer_node::alloc_node(inner);
                        inner_node::priority(inner) = priorities[heap_index - 1];
                    } else {
                        ++skipped;
                    }
                }
                for (size_t i = fpow2 - 1; i >= 1; --i) {
                    size_t li = 2 * i, ri = 2 * i + 1;
                    if (li <= n) set_child0(nodes[i - 1], nodes[li - 1]);
                    if (ri <= n) set_child1(nodes[i - 1], nodes[ri - 1]);
                    update(nodes[i - 1]);
                }
                return nodes[0];
            }

            static value_type get_at(outer_node_pointer t, size_type k) {
                assert(0 <= k and k < safe_size(t));
                while (true) {
                    if (const size_type lsiz = safe_size(child0(t)), msiz = inner_node::safe_size(inner(t)); k < lsiz + msiz) {
                        if (k >= lsiz) {
                            size_type k_inner = k - lsiz;
                            return inner_node::get_at(inner(t), reversed(t) ? inner_node::safe_size(inner(t)) - k_inner - 1 : k_inner);
                        }
                        t = child0(t);
                    } else {
                        t = child1(t);
                        k -= lsiz + msiz;
                    }
                }
            }
            static value_type set_at(outer_node_pointer t, size_type k, const value_type& val) {
                assert(0 <= k and k < safe_size(t));
                static std::vector<outer_node_pointer> stack{};
                while (true) {
                    stack.push_back(t);
                    if (const size_type lsiz = safe_size(child0(t)), msiz = inner_node::safe_size(inner(t)); k < lsiz + msiz) {
                        if (k >= lsiz) {
                            size_type k_inner = k - lsiz;
                            value_type old_val = inner_node::set_at(inner(t), reversed(t) ? inner_node::safe_size(inner(t)) - k_inner - 1 : k_inner, val);
                            while (stack.size()) update(stack.back()), stack.pop_back();
                            return old_val;
                        }
                        t = child0(t);
                    } else {
                        t = child1(t);
                        k -= lsiz + msiz;
                    }
                }
            }
            static value_type prod(outer_node_pointer t, size_type l, size_type r) {
                if (not t) return e();
                if (l <= 0 and r >= size(t)) return sum(t);
                size_type lsiz = safe_size(child0(t));
                if (r <= lsiz) return prod(child0(t), l, r);
                size_type msiz = inner_size(t);
                if (l >= lsiz + msiz) return prod(child1(t), l - (lsiz + msiz), r - (lsiz + msiz));
                value_type sum_l = prod(child0(t), l, r);
                value_type sum_r = prod(child1(t), l - (lsiz + msiz), r - (lsiz + msiz));
                if (reversed(t)) {
                    value_type sum_m = inner_node::prod_at_range(inner(t), msiz - (r - lsiz), msiz - (l - lsiz));
                    return op(op(sum_l, toggle(sum_m)), sum_r);
                } else {
                    value_type sum_m = inner_node::prod_at_range(inner(t), l - lsiz, r - lsiz);
                    return op(op(sum_l, sum_m), sum_r);
                }
            }

            static std::pair<outer_node_pointer, outer_node_pointer> split_at(outer_node_pointer t, size_type k) {
                if (k == 0) return { nullptr, t };
                if (k == safe_size(t)) return { t, nullptr };

                static std::vector<outer_node_pointer> lp{}, rp{};

                while (true) {
                    if (const size_type lsiz = safe_size(child0(t)), msiz = inner_node::safe_size(inner(t)); k < lsiz + msiz) {
                        if (k >= lsiz) {
                            outer_node_pointer tl, tr;
                            if (reversed(t)) {
                                size_type k_inner = inner_node::safe_size(inner(t)) - (k - lsiz);
                                auto [inner_tr, inner_tl] = inner_node::split_at(inner(t), k_inner);
                                tl = outer_node::alloc_node(inner_tl, true);
                                tr = outer_node::alloc_node(inner_tr, true);
                            } else {
                                size_type k_inner = k - lsiz;
                                auto [inner_tl, inner_tr] = inner_node::split_at(inner(t), k_inner);
                                tl = outer_node::alloc_node(inner_tl, false);
                                tr = outer_node::alloc_node(inner_tr, false);
                            }

                            tl = concat(std::exchange(child0(t), nullptr), tl);
                            tr = concat(tr, std::exchange(child1(t), nullptr));

                            inner(t) = nullptr;
                            dealloc_node(t);

                            if (rp.size()) set_child0(rp.back(), tr);
                            if (lp.size()) set_child1(lp.back(), tl);

                            outer_node_pointer lt = tl, rt = tr;

                            while (lp.size()) update(lt = lp.back()), lp.pop_back();
                            while (rp.size()) update(rt = rp.back()), rp.pop_back();

                            return { lt, rt };
                        }
                        if (rp.size()) set_child0(rp.back(), t);
                        rp.push_back(t);
                        t = child0(t);
                    } else {
                        if (lp.size()) set_child1(lp.back(), t);
                        lp.push_back(t);
                        t = child1(t);
                        k -= lsiz + msiz;
                    }
                }
            }
            static std::tuple<outer_node_pointer, outer_node_pointer, outer_node_pointer> split_at_range(outer_node_pointer t, size_type l, size_type r) {
                auto [tlm, tr] = split_at(t, r);
                auto [tl, tm] = split_at(tlm, l);
                return { tl, tm, tr };
            }

            static outer_node_pointer concat_nonnull(outer_node_pointer tl, outer_node_pointer tr) {
                if (priority(tl) < priority(tr)) {
                    if (outer_node_pointer tm = child0(tr); not tm) {
                        set_child0(tr, tl);
                    } else {
                        set_child0(tr, concat_nonnull(tl, tm));
                    }
                    return update(tr);
                } else {
                    if (outer_node_pointer tm = child1(tl); not tm) {
                        set_child1(tl, tr);
                    } else {
                        set_child1(tl, concat_nonnull(tm, tr));
                    }
                    return update(tl);
                }
            }
            static outer_node_pointer concat(outer_node_pointer tl, outer_node_pointer tr) {
                if (not tl) return tr;
                if (not tr) return tl;
                return concat_nonnull(tl, tr);
            }
            static outer_node_pointer concat(outer_node_pointer tl, outer_node_pointer tm, outer_node_pointer tr) {
                return concat(concat(tl, tm), tr);
            }

            static inner_node_pointer merge_all(outer_node_pointer t) {
                if (not t) return nullptr;
                inner_node_pointer res = inner_node::merge(inner_node::merge(merge_all(child0(t)), inner(t)), merge_all(child1(t)));
                inner(t) = nullptr;
                dealloc_node(t);
                return res;
            }

            template <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool, Predicate, value_type>, std::nullptr_t> = nullptr>
            static std::pair<size_type, value_type> max_right_prefix(outer_node_pointer t, const Predicate& f) {
                size_type r = 0;
                value_type s = e();
                while (t) {
                    if (value_type nxt_s = op(s, safe_sum(child0(t))); f(nxt_s)) {
                        s = std::move(nxt_s);
                        r += safe_size(child0(t));
                        if (nxt_s = op(s, inner_sum(t)); f(nxt_s)) {
                            s = std::move(nxt_s);
                            r += inner_size(t);
                            t = child1(t);
                        } else {
                            size_type r_inner;
                            std::tie(r_inner, s) = inner_node::max_right(inner(t), f, s);
                            r += r_inner;
                            break;
                        }
                    } else {
                        t = child0(t);
                    }
                }
                return { r, s };
            }
            template <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool, Predicate, value_type>, std::nullptr_t> = nullptr>
            static std::tuple<outer_node_pointer, size_type, value_type> max_right(outer_node_pointer t, size_type l, const Predicate& f) {
                auto [tl, tr] = split_at(t, l);
                auto [r, s] = max_right_prefix(tr, f);
                return { concat(tl, tr), l + r, s };
            }
            
            template <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool, Predicate, value_type>, std::nullptr_t> = nullptr>
            static std::pair<size_type, value_type> min_left_suffix(outer_node_pointer t, const Predicate& f) {
                size_type l = safe_size(t);
                value_type s = e();
                while (t) {
                    if (value_type nxt_s = op(safe_sum(child1(t)), s); f(nxt_s)) {
                        s = std::move(nxt_s);
                        l -= safe_size(child1(t));
                        if (nxt_s = op(inner_sum(t), s); f(nxt_s)) {
                            s = std::move(nxt_s);
                            l -= inner_size(t);
                            t = child0(t);
                        } else {
                            size_type l_inner;
                            std::tie(l_inner, s) = inner_node::min_left(inner(t), f, s);
                            l -= inner_size(t) - l_inner;
                            break;
                        }
                    } else {
                        t = child1(t);
                    }
                }
                return { l, s };
            }
            template <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool, Predicate, value_type>, std::nullptr_t> = nullptr>
            static std::tuple<outer_node_pointer, size_type, value_type> min_left(outer_node_pointer t, size_type r, const Predicate& f) {
                auto [tl, tr] = split_at(t, r);
                auto [l, s] = min_left_suffix(tl, f);
                return { concat(tl, tr), l, s };
            }

            template <typename Func, std::enable_if_t<std::is_invocable_r_v<void, Func, key_type, value_type>, std::nullptr_t> = nullptr>
            static void foreach(outer_node_pointer t, bool rev, const Func& f) {
                if (not t) return;
                if (rev) {
                    foreach(child1(t), rev, f);
                    inner_node::foreach(inner(t), not reversed(t), f);
                    foreach(child0(t), rev, f);
                } else {
                    foreach(child0(t), rev, f);
                    inner_node::foreach(inner(t), reversed(t), f);
                    foreach(child1(t), rev, f);
                }
            }
        };

        outer_node_pointer _root;
    public:
        SortableSegmentTree() : _root(nullptr) {}
        SortableSegmentTree(const std::vector<std::pair<key_type, value_type>>& dat) : _root(outer_node::build(dat)) {}
        ~SortableSegmentTree() {
            outer_node::dealloc_all(_root);
        }

        size_type size() {
            return outer_node::safe_size(_root);
        }

        auto operator[](size_type k) {
            struct proxy {
                outer_node_pointer root;
                size_type k;
                operator value_type()&& { return outer_node::get_at(root, k); }
                value_type operator=(const value_type& val)&& { return outer_node::set_at(root, k, val), val; }
            };
            return proxy{ _root, k };
        }
        value_type get(size_type k) {
            assert(0 <= k and k < size());
            return outer_node::get_at(_root, k);
        }
        // returns old value
        value_type set_value(size_type k, const value_type& val) {
            assert(0 <= k and k < size());
            return outer_node::set_at(_root, k, val);
        }
        // returns old {key, value}
        std::pair<key_type, value_type> set_key_value(size_type i, const key_type& key, const value_type& val) {
            assert(0 <= i and i < size());
            auto [tl, tm, tr] = outer_node::split_at_range(_root, i, i + 1);
            inner_node_pointer tm_inner = outer_node::inner(tm);
            std::pair<key_type, value_type> res = inner_node::set(tm_inner, key, val);
            inner_node::update(tm_inner);
            _root = outer_node::concat(tl, outer_node::update(tm), tr);
            return res;
        }

        void insert(size_type i, const key_type& key, const value_type& val) {
            assert(0 <= i and i <= size());
            auto [tl, tr] = outer_node::split_at(_root, i);
            auto tm = outer_node::alloc_node(inner_node::alloc_node(key, val));
            _root = outer_node::concat(tl, tm, tr);
        }
        void push_front(const key_type& key, const value_type& val) { insert(0, key, val); }
        void push_back(const key_type& key, const value_type& val) { insert(size(), key, val); }

        std::pair<key_type, value_type> erase(size_type i) {
            assert(0 <= i and i < size());
            auto [tl, tm, tr] = outer_node::split_at_range(_root, i, i + 1);
            _root = outer_node::concat(tl, tr);
            inner_node_pointer tm_inner = outer_node::inner(tm);
            std::pair<key_type, value_type> res { std::move(inner_node::key(tm_inner)), std::move(inner_node::value(tm_inner)) };
            outer_node::dealloc_node(tm);
            return res;
        }
        std::pair<key_type, value_type> pop_front() { erase(0); }
        std::pair<key_type, value_type> pop_back() { erase(size() - 1); }

        value_type prod(size_type l, size_type r) {
            assert(0 <= l and l <= r and r <= size());
            if (l == r) return e();
            if (r - l == 1) return (*this)[l];
            return outer_node::prod(_root, l, r);
        }

        enum struct SortingPolicy { ascending, descending };
        void sort(size_type l, size_type r, SortingPolicy policy = SortingPolicy::ascending) {
            assert(0 <= l and l <= r and r <= size());
            if (l == r) return;
            auto [tl, tm, tr] = outer_node::split_at_range(_root, l, r);
            _root = outer_node::concat(tl, outer_node::alloc_node(outer_node::merge_all(tm), policy == SortingPolicy::descending), tr);
        }
        void sort_asc(size_type l, size_type r) { sort(l, r, SortingPolicy::ascending); }
        void sort_dsc(size_type l, size_type r) { sort(l, r, SortingPolicy::descending); }

        // returns { r := max{ r' | f(prod(l, r')) = true }, prod(l, r) }
        template <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool, Predicate, value_type>, std::nullptr_t> = nullptr>
        std::pair<size_type, value_type> max_right(size_type l, const Predicate& f) {
            assert(0 <= l and l <= size());
            assert(f(e()));
            auto [new_root, r, s] = outer_node::max_right(_root, l, f);
            _root = new_root;
            return { r, s };
        }
        // returns { l := min{ l' | f(prod(l', r)) = true }, prod(l, r) }
        template <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool, Predicate, value_type>, std::nullptr_t> = nullptr>
        std::pair<size_type, value_type> min_left(size_type r, const Predicate& f) {
            assert(0 <= r and r <= size());
            assert(f(e()));
            auto [new_root, l, s] = outer_node::min_left(_root, r, f);
            _root = new_root;
            return { l, s };
        }

        template <typename Func, std::enable_if_t<std::is_invocable_r_v<void, Func, key_type, value_type>, std::nullptr_t> = nullptr>
        void foreach(const Func& f, bool reversed = false) {
            outer_node::foreach(_root, reversed, f);
        }
        std::vector<key_type> dump_keys() {
            std::vector<key_type> res(size());
            auto it = res.begin();
            foreach([&it](const key_type& key, const value_type&) { *it++ = key; });
            return res;
        }
        std::vector<value_type> dump_values() {
            std::vector<value_type> res(size());
            auto it = res.begin();
            foreach([&it](const key_type&, const value_type& val) { *it++ = val; });
            return res;
        }
        std::vector<std::pair<key_type, value_type>> dump_entries() {
            std::vector<std::pair<key_type, value_type>> res(size());
            auto it = res.begin();
            foreach([&it](const key_type& key, const value_type& val) { *it++ = std::pair{ key, val }; });
            return res;
        }
    };
} // namespace suisen

#endif // SUISEN_SORTABLE_SEGTREE
