#ifndef SUISEN_PALINDROMIC_TREE
#define SUISEN_PALINDROMIC_TREE

#include <array>
#include <cassert>
#include <vector>
#include <map>

namespace suisen {
    namespace internal::palindromic_tree {
        template <typename T>
        constexpr bool false_v = false;

        template <typename T, typename Sequence, typename ChildrenContainerType>
        struct PalindromicTreeBase {
            using container_type = Sequence;
            using value_type = T;

            using children_container_type = ChildrenContainerType;

            struct PalindromicTreeNode {
                friend struct PalindromicTreeBase;
                PalindromicTreeNode() = default;
            private:
                children_container_type _children;
                int _suffix_link;
                int _length;
                int _multiplicity;
                int _first_occurence;
            };

            using node_type = PalindromicTreeNode;
            using node_pointer_type = node_type*;

            static constexpr int NODE_NULL = -1;
            static constexpr int NODE_M1 = 0;
            static constexpr int NODE_0 = 1;

            PalindromicTreeBase() {
                _nodes.reserve(2);

                node_pointer_type node_m1 = _new_node();
                node_m1->_suffix_link = NODE_M1;
                node_m1->_length = -1;
                node_m1->_first_occurence = 1;

                node_pointer_type node_0 = _new_node();
                node_0->_suffix_link = NODE_M1;
                node_0->_length = 0;
                node_m1->_first_occurence = 0;

                _active_index = 0;
            }
            template <typename Iterable>
            PalindromicTreeBase(const Iterable& seq) : PalindromicTreeBase() {
                for (const auto& val : seq) add(val);
            }

            void add(const value_type& val) {
                _seq.push_back(val);
                _nodes.reserve(_nodes.size() + 1);

                node_pointer_type par_node = _find_next_longest_suffix_palindrome(_get_node(_active_index));
                auto& ch = par_node->_children;

                bool inserted;

                if constexpr (is_map) {
                    const auto [it, inserted_tmp] = ch.emplace(val, _nodes.size());
                    inserted = inserted_tmp;
                    _active_index = it->second;
                } else if constexpr (is_vector) {
                    if (value_type(ch.size()) <= val) ch.resize(val + 1, NODE_NULL);
                    if (ch[val] == NODE_NULL) {
                        inserted = true;
                        ch[val] = _nodes.size();
                        _active_index = _nodes.size();
                    } else {
                        _active_index = ch[val];
                    }
                } else if constexpr (is_array) {
                    if (ch[val] == NODE_NULL) {
                        inserted = true;
                        ch[val] = _nodes.size();
                        _active_index = _nodes.size();
                    } else {
                        _active_index = ch[val];
                    }
                } else {
                    static_assert(false_v<void>);
                }
                if (not inserted) {
                    ++_get_node(_active_index)->_multiplicity;
                    return;
                }

                node_pointer_type new_node = _new_node();

                new_node->_multiplicity = 1;
                new_node->_length = par_node->_length + 2;
                new_node->_first_occurence = _seq.size() - new_node->_length;
                if (new_node->_length == 1) {
                    new_node->_suffix_link = NODE_0;
                } else {
                    new_node->_suffix_link = _find_next_longest_suffix_palindrome(_get_node(par_node->_suffix_link))->_children[val];
                }
            }

            int node_num() const {
                return _nodes.size();
            }

            const node_type& get_node(int index) const {
                return _nodes[index];
            }

            int first_occurence(int index) const {
                return get_node(index)._first_occurence;
            }
            int length(int index) const {
                return get_node(index)._length;
            }
            int suffix_link(int index) const {
                return get_node(index)._suffix_link;
            }
            int node_multiplicity(int index) const {
                return get_node(index)._multiplicity;
            }
            const children_container_type& children(int index) const {
                return get_node(index)._children;
            }
            std::vector<int> parents() const {
                int sz = node_num();
                std::vector<int> res(sz, -1);
                for (int i = 0; i < sz; ++i) {
                    for (const auto& p : children(i)) {
                        if constexpr (is_map) {
                            res[p.second] = i;
                        } else if (p != NODE_NULL) {
                            res[p] = i;
                        }
                    }
                }
                return res;
            }

            const container_type get_palindrome(int index) {
                if (index == NODE_M1) return container_type{};
                int l = first_occurence(index), r = l + length(index);
                return container_type{ _seq.begin() + l, _seq.begin() + r };
            }

            std::vector<int> frequency_table() const {
                int sz = node_num();
                std::vector<int> res(sz);
                for (int i = sz; i-- > 1;) {
                    res[i] += node_multiplicity(i);
                    res[suffix_link(i)] += res[i];
                }
                return res;
            }

        private:
            static constexpr bool is_map = std::is_same_v<std::map<value_type, int>, children_container_type>;
            static constexpr bool is_vector = std::is_same_v<std::vector<value_type>, children_container_type>;
            static constexpr bool is_array = std::is_same_v<std::array<value_type, std::tuple_size_v<children_container_type>>, children_container_type>;

            int _active_index;
            container_type _seq;
            std::vector<node_type> _nodes;

            node_pointer_type _new_node() {
                node_pointer_type new_node = &_nodes.emplace_back();
                if constexpr (not (is_map or is_vector)) {
                    std::fill(new_node->_children.begin(), new_node->_children.end(), NODE_NULL);
                }
                return new_node;
            }

            node_pointer_type _find_next_longest_suffix_palindrome(node_pointer_type node) {
                const int sz = _seq.size();
                for (;; node = _get_node(node->_suffix_link)) {
                    int opposite_index = sz - node->_length - 2;
                    if (opposite_index >= 0 and _seq[opposite_index] == _seq.back()) return node;
                }
            }

            node_pointer_type _get_node(int index) {
                return &_nodes[index];
            }
        };
    } // namespace internal::palindromic_tree

    template <typename T, typename Sequence = std::vector<T>>
    struct PalindromicTree : public internal::palindromic_tree::PalindromicTreeBase<T, Sequence, std::map<T, int>> {
        using base_type = internal::palindromic_tree::PalindromicTreeBase<T, Sequence, std::map<T, int>>;
        using base_type::base_type;
    };

    template <typename T, typename Sequence = std::vector<T>>
    struct PalindromicTreeVec : public internal::palindromic_tree::PalindromicTreeBase<T, Sequence, std::vector<T>> {
        using base_type = internal::palindromic_tree::PalindromicTreeBase<T, Sequence, std::vector<T>>;
        using base_type::base_type;
    };

    template <typename T, std::size_t N, typename Sequence = std::vector<T>>
    struct PalindromicTreeArr : public internal::palindromic_tree::PalindromicTreeBase<T, Sequence, std::array<T, N>> {
        using base_type = internal::palindromic_tree::PalindromicTreeBase<T, Sequence, std::array<T, N>>;
        using base_type::base_type;
    };
} // namespace suisen


#endif // SUISEN_PALINDROMIC_TREE
