---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/datastructure/range_foldable_map.hpp
    title: Range Foldable Map
  - icon: ':x:'
    path: library/datastructure/splay_tree_map.hpp
    title: Splay Tree Map
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':question:'
    path: library/util/update_proxy_object.hpp
    title: Update Proxy Object
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/datastructure/lazy_eval_map/leq_and_neq.test.cpp
    title: test/src/datastructure/lazy_eval_map/leq_and_neq.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/lazy_eval_map.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <tuple>\n\n#line 1 \"library/util/update_proxy_object.hpp\"\
    \n\n\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n\
    #include <type_traits>\n\nnamespace suisen {\n// ! utility\ntemplate <typename\
    \ ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\ntemplate <bool cond_v, typename Then, typename OrElse>\nconstexpr\
    \ decltype(auto) constexpr_if(Then&& then, OrElse&& or_else) {\n    if constexpr\
    \ (cond_v) {\n        return std::forward<Then>(then);\n    } else {\n       \
    \ return std::forward<OrElse>(or_else);\n    }\n}\n\n// ! function\ntemplate <typename\
    \ ReturnType, typename Callable, typename ...Args>\nusing is_same_as_invoke_result\
    \ = std::is_same<std::invoke_result_t<Callable, Args...>, ReturnType>;\ntemplate\
    \ <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T, F, T>;\n\
    template <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
    \ F, T, T>;\n\ntemplate <typename Comparator, typename T>\nusing is_comparator\
    \ = std::is_same<std::invoke_result_t<Comparator, T, T>, bool>;\n\n// ! integral\n\
    template <typename T, typename = constraints_t<std::is_integral<T>>>\nconstexpr\
    \ int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\ntemplate\
    \ <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool value =\
    \ bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T>\nstruct\
    \ safely_multipliable {};\ntemplate <>\nstruct safely_multipliable<int> { using\
    \ type = long long; };\ntemplate <>\nstruct safely_multipliable<long long> { using\
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned int>\
    \ { using type = unsigned long long; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long int> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long long> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<float>\
    \ { using type = float; };\ntemplate <>\nstruct safely_multipliable<double> {\
    \ using type = double; };\ntemplate <>\nstruct safely_multipliable<long double>\
    \ { using type = long double; };\ntemplate <typename T>\nusing safely_multipliable_t\
    \ = typename safely_multipliable<T>::type;\n\ntemplate <typename T, typename =\
    \ void>\nstruct rec_value_type {\n    using type = T;\n};\ntemplate <typename\
    \ T>\nstruct rec_value_type<T, std::void_t<typename T::value_type>> {\n    using\
    \ type = typename rec_value_type<typename T::value_type>::type;\n};\ntemplate\
    \ <typename T>\nusing rec_value_type_t = typename rec_value_type<T>::type;\n\n\
    } // namespace suisen\n\n\n#line 5 \"library/util/update_proxy_object.hpp\"\n\n\
    namespace suisen {\n\ntemplate <typename T, typename UpdateFunc, constraints_t<std::is_invocable<UpdateFunc>>\
    \ = nullptr>\nstruct UpdateProxyObject {\n    public:\n        UpdateProxyObject(T\
    \ &v, UpdateFunc update) : v(v), update(update) {}\n        operator T() const\
    \ { return v; }\n        auto& operator++() && { ++v, update(); return *this;\
    \ }\n        auto& operator--() && { --v, update(); return *this; }\n        auto&\
    \ operator+=(const T &val) && { v += val, update(); return *this; }\n        auto&\
    \ operator-=(const T &val) && { v -= val, update(); return *this; }\n        auto&\
    \ operator*=(const T &val) && { v *= val, update(); return *this; }\n        auto&\
    \ operator/=(const T &val) && { v /= val, update(); return *this; }\n        auto&\
    \ operator%=(const T &val) && { v %= val, update(); return *this; }\n        auto&\
    \ operator =(const T &val) && { v  = val, update(); return *this; }\n        auto&\
    \ operator<<=(const T &val) && { v <<= val, update(); return *this; }\n      \
    \  auto& operator>>=(const T &val) && { v >>= val, update(); return *this; }\n\
    \        template <typename F, constraints_t<is_uni_op<F, T>> = nullptr>\n   \
    \     auto& apply(F f) && { v = f(v), update(); return *this; }\n    private:\n\
    \        T &v;\n        UpdateFunc update;\n};\n\n} // namespace suisen\n\n\n\
    #line 1 \"library/datastructure/range_foldable_map.hpp\"\n\n\n\n#line 6 \"library/datastructure/range_foldable_map.hpp\"\
    \n\n#line 1 \"library/datastructure/splay_tree_map.hpp\"\n\n\n\n#line 5 \"library/datastructure/splay_tree_map.hpp\"\
    \n#include <cstddef>\n#include <vector>\n#include <utility>\n\nnamespace suisen\
    \ {\nnamespace internal::splay_tree_map {\n\ntemplate <typename Key, typename\
    \ Val, typename Derived>\nstruct MapNodeBase {\n    using node_ptr_t = Derived\
    \ *;\n\n    Key key;\n    Val val;\n    int siz;\n    node_ptr_t ch[2] {nullptr,\
    \ nullptr};\n\n    MapNodeBase() : key(), val(), siz(1) {}\n    MapNodeBase(const\
    \ Key &key, const Val &val) : key(key), val(val), siz(1) {}\n\n    ~MapNodeBase()\
    \ {\n        delete ch[0];\n        delete ch[1];\n    }\n\n    void update()\
    \ {\n        siz = 1 + size(ch[0]) + size(ch[1]);\n    }\n    void push() {}\n\
    \n    static int size(node_ptr_t node) {\n        return node == nullptr ? 0 :\
    \ node->siz;\n    }\n\n    static node_ptr_t rotate(node_ptr_t node, bool is_right)\
    \ {\n        node_ptr_t root = node->ch[is_right ^ true];\n        node->ch[is_right\
    \ ^ true] = root->ch[is_right];\n        root->ch[is_right] = node;\n        node->update(),\
    \ root->update();\n        return root;\n    }\n\n    static node_ptr_t splay_by_index(node_ptr_t\
    \ node, int index) {\n        std::vector<node_ptr_t> path;\n        node_ptr_t\
    \ work_root = new Derived();\n        node_ptr_t work_leaf[2] { work_root, work_root\
    \ };\n        while (true) {\n            node->push();\n            int size_l\
    \ = size(node->ch[0]);\n            bool is_right = index > size_l;\n        \
    \    node_ptr_t next_node = node->ch[is_right];\n            if (index == size_l\
    \ or next_node == nullptr) { // found the target node\n                break;\n\
    \            }\n            if (is_right) {\n                index -= size_l +\
    \ 1;\n            }\n            int size_l_ch = size(next_node->ch[0]);\n   \
    \         if (index != size_l_ch) {\n                bool is_right_ch = index\
    \ > size_l_ch;\n                if (is_right_ch == is_right) { // zig-zig\n  \
    \                  if (is_right_ch) {\n                        index -= size_l_ch\
    \ + 1;\n                    }\n                    next_node->push();\n      \
    \              node = rotate(node, is_right ^ true);\n                    next_node\
    \ = node->ch[is_right];\n                    if (next_node == nullptr) { // found\
    \ the target node\n                        break;\n                    }\n   \
    \             }\n            }\n            path.push_back(node);\n          \
    \  work_leaf[is_right]->ch[is_right] = node;\n            work_leaf[is_right]\
    \ = node;\n            node = next_node;\n        }\n        work_leaf[0]->ch[0]\
    \ = node->ch[1];\n        work_leaf[1]->ch[1] = node->ch[0];\n        node->ch[0]\
    \ = work_root->ch[1];\n        node->ch[1] = work_root->ch[0];\n    \n       \
    \ work_root->ch[0] = work_root->ch[1] = nullptr;\n        delete work_root;\n\n\
    \        while (path.size()) {\n            path.back()->update(), path.pop_back();\n\
    \        }\n        node->update();\n\n        return node;\n    }\n\n    static\
    \ node_ptr_t splay_by_key(node_ptr_t node, const Key &x) {\n        if (node ==\
    \ nullptr) return node;\n        std::vector<node_ptr_t> path;\n        node_ptr_t\
    \ work_root = new Derived();\n        node_ptr_t work_leaf[2] { work_root, work_root\
    \ };\n        while (true) {\n            node->push();\n            if (x ==\
    \ node->key) {\n                break;\n            }\n            bool is_right\
    \ = x > node->key;\n            node_ptr_t next_node = node->ch[is_right];\n \
    \           if (next_node == nullptr) {\n                break;\n            }\n\
    \            if (x != next_node->key) {\n                bool is_right_ch = x\
    \ > next_node->key;\n                if (is_right_ch == is_right) { // zig-zig\n\
    \                    next_node->push();\n                    node = rotate(node,\
    \ is_right ^ true);\n                    next_node = node->ch[is_right];\n   \
    \                 if (next_node == nullptr) { // found the target node\n     \
    \                   break;\n                    }\n                }\n       \
    \     }\n            path.push_back(node);\n            work_leaf[is_right]->ch[is_right]\
    \ = node;\n            work_leaf[is_right] = node;\n            node = next_node;\n\
    \        }\n        work_leaf[0]->ch[0] = node->ch[1];\n        work_leaf[1]->ch[1]\
    \ = node->ch[0];\n        node->ch[0] = work_root->ch[1];\n        node->ch[1]\
    \ = work_root->ch[0];\n\n        work_root->ch[0] = work_root->ch[1] = nullptr;\n\
    \        delete work_root;\n\n        while (path.size()) {\n            path.back()->update(),\
    \ path.pop_back();\n        }\n        node->update();\n\n        return node;\n\
    \    }\n    static std::pair<node_ptr_t, bool> find_key(node_ptr_t node, const\
    \ Key &key) {\n        if (node == nullptr) return { node, false };\n        node\
    \ = splay_by_key(node, key);\n        return { node, node->key == key };\n   \
    \ }\n    static std::pair<node_ptr_t, node_ptr_t> split_by_index(node_ptr_t node,\
    \ int k) {\n        if (k == 0) return { nullptr, node };\n        if (k == size(node))\
    \ return { node, nullptr };\n        node_ptr_t r = splay_by_index(node, k);\n\
    \        node_ptr_t l = r->ch[0];\n        r->ch[0] = nullptr;\n        r->update();\n\
    \        return { l, r };\n    }\n    static std::tuple<node_ptr_t, node_ptr_t,\
    \ node_ptr_t> split_by_index(node_ptr_t node, int l, int r) {\n        auto [tl,\
    \ tmr] = split_by_index(node, l);\n        auto [tm, tr] = split_by_index(tmr,\
    \ r - l);\n        return { tl, tm, tr };\n    }\n    static std::pair<node_ptr_t,\
    \ node_ptr_t> split_by_key(node_ptr_t node, const Key &key) {\n        if (node\
    \ == nullptr) return { nullptr, nullptr };\n        node_ptr_t r = splay_by_key(node,\
    \ key);\n        if (r->key >= key) {\n            node_ptr_t l = r->ch[0];\n\
    \            r->ch[0] = nullptr;\n            r->update();\n            return\
    \ { l, r };\n        } else {\n            node_ptr_t l = r->ch[1];\n        \
    \    r->ch[1] = nullptr;\n            r->update();\n            return { r, l\
    \ };\n        }\n    }\n    static std::tuple<node_ptr_t, node_ptr_t, node_ptr_t>\
    \ split_by_key(node_ptr_t node, const Key &l, const Key &r) {\n        auto [tl,\
    \ tmr] = split_by_key(node, l);\n        auto [tm, tr] = split_by_key(tmr, r);\n\
    \        return { tl, tm, tr };\n    }\n    static node_ptr_t merge(node_ptr_t\
    \ l, node_ptr_t r) {\n        if (l == nullptr) return r;\n        if (r == nullptr)\
    \ return l;\n        node_ptr_t new_root = splay_by_index(r, 0);\n        new_root->ch[0]\
    \ = l;\n        new_root->update();\n        return new_root;\n    }\n    static\
    \ node_ptr_t merge(node_ptr_t tl, node_ptr_t tm, node_ptr_t tr) {\n        return\
    \ merge(merge(tl, tm), tr);\n    }\n    static node_ptr_t insert(node_ptr_t node,\
    \ const Key &key, const Val &val, bool overwrite = true) {\n        auto [l, r]\
    \ = split_by_key(node, key);\n        if (r != nullptr and r->key == key) {\n\
    \            if (overwrite) {\n                r->val = val;\n               \
    \ r->update();\n            }\n            return merge(l, r);\n        }\n  \
    \      node_ptr_t new_node = new Derived(key, val);\n        new_node->ch[0] =\
    \ l;\n        new_node->ch[1] = r;\n        new_node->update();\n        return\
    \ new_node;\n    }\n    static node_ptr_t erase_index(node_ptr_t node, int index)\
    \ {\n        auto [l, r] = split(index ? node : splay(node, 0), index);\n    \
    \    assert(r->ch[0] == nullptr);\n        node_ptr_t res = merge(l, r->ch[1]);\n\
    \        r->ch[1] = nullptr;\n        delete r;\n        return res;\n    }\n\
    \    static std::pair<node_ptr_t, bool> erase_key(node_ptr_t node, const Key &key)\
    \ {\n        auto [l, r] = split_by_key(node, key);\n        if (r == nullptr\
    \ or r->key != key) return { merge(l, r), false };\n        assert(r->ch[0] ==\
    \ nullptr);\n        node_ptr_t res = merge(l, r->ch[1]);\n        r->ch[1] =\
    \ nullptr;\n        delete r;\n        return { res, true };\n    }\n    static\
    \ Val get_or_default(node_ptr_t node, const Key &key, const Val &default_value)\
    \ {\n        auto [new_root, found] = find_key(node, key);\n        node = new_root;\n\
    \        return found ? new_root->val : default_value;\n    }\n};\n\ntemplate\
    \ <typename Key, typename Val>\nstruct SplayTreeMapNode : public MapNodeBase<Key,\
    \ Val, SplayTreeMapNode<Key, Val>> {\n    using Base = MapNodeBase<Key, Val, SplayTreeMapNode<Key,\
    \ Val>>;\n    using Base::MapNodeBase;\n    using node_ptr_t = typename Base::node_ptr_t;\n\
    };\n}\n\ntemplate <typename Key, typename Val>\nclass SplayTreeMap {\n    protected:\n\
    \        using Node = internal::splay_tree_map::SplayTreeMapNode<Key, Val>;\n\
    \        using node_ptr_t = typename Node::node_ptr_t;\n    public:\n        SplayTreeMap()\
    \ : root(nullptr) {}\n        ~SplayTreeMap() {\n            delete root;\n  \
    \      }\n\n        SplayTreeMap& operator=(const SplayTreeMap&) = delete;\n \
    \       SplayTreeMap& operator=(SplayTreeMap&& other) {\n            if (other.root\
    \ == root) return *this;\n            delete root;\n            root = other.root;\n\
    \            other.root = nullptr;\n            return *this;\n        }\n\n \
    \       int size() {\n            return Node::size(root);\n        }\n      \
    \  bool contains(const Key &key) {\n            auto [new_root, found] = Node::find_key(root,\
    \ key);\n            root = new_root;\n            return found;\n        }\n\
    \        void insert(const Key &key, const Val &val) {\n            root = Node::insert(root,\
    \ key, val, true);\n        }\n        void insert_if_absent(const Key &key, const\
    \ Val &val) {\n            root = Node::insert(root, key, val, false);\n     \
    \   }\n        bool erase_key(const Key &key) {\n            auto [new_root, is_erased]\
    \ = Node::erase_key(root, key);\n            root = new_root;\n            return\
    \ is_erased;\n        }\n        void erase_index(int k) {\n            index_bounds_check(k,\
    \ size() + 1);\n            root = Node::erase_index(root, k);\n        }\n  \
    \      Val& get_or_create(const Key &key, const Val &val) {\n            root\
    \ = Node::insert(root, key, val, false);\n            return root->val;\n    \
    \    }\n        Val& operator[](const Key &key) {\n            return get_or_create(key,\
    \ Val{});\n        }\n        Val get_or_default(const Key &key, const Val &default_value)\
    \ {\n            auto [new_root, res] = Node::get_or_default(root, key, default_value);\n\
    \            root = new_root;\n            return res;\n        }\n        std::pair<Key,\
    \ Val> kth_entry(int k) {\n            index_bounds_check(k, size());\n      \
    \      root = Node::splay_by_index(root, k);\n            return { root->key,\
    \ root->val };\n        }\n        SplayTreeMap split_by_index(int k) {\n    \
    \        index_bounds_check(k, size() + 1);\n            auto [l, r] = Node::split_by_index(root,\
    \ k);\n            root = l;\n            return SplayTreeMap<Key, Val>(r);\n\
    \        }\n        SplayTreeMap split_by_key(const Key &key) {\n            auto\
    \ [l, r] = Node::split_by_key(root, key);\n            root = l;\n           \
    \ return SplayTreeMap<Key, Val>(r);\n        }\n        void merge(SplayTreeMap\
    \ &&r) {\n            assert(root != r.root);\n            root = Node::merge(root,\
    \ r.root);\n            r.root = nullptr;\n        }\n        void swap(SplayTreeMap\
    \ &r) {\n            std::swap(root, r.root);\n        }\n\n    protected:\n \
    \       Node *root;\n\n        SplayTreeMap(node_ptr_t root) : root(root) {}\n\
    \    \n        static void index_bounds_check(unsigned int k, unsigned int n)\
    \ {\n            assert(k < n);\n        }\n        static void range_bounds_check(unsigned\
    \ int l, unsigned int r, unsigned int n) {\n            assert(l <= r and r <=\
    \ n);\n        }\n};\n\n}\n\n\n#line 9 \"library/datastructure/range_foldable_map.hpp\"\
    \n\nnamespace suisen {\nnamespace internal::range_foldable_map {\n\ntemplate <typename\
    \ Key, typename Val, Val(*op)(Val, Val), Val (*e)(), typename Derived>\nstruct\
    \ RangeFoldableMapNodeBase : public internal::splay_tree_map::MapNodeBase<Key,\
    \ Val, Derived> {\n    using Base = internal::splay_tree_map::MapNodeBase<Key,\
    \ Val, Derived>;\n    using node_ptr_t = typename Base::node_ptr_t;\n    Val dat;\n\
    \    RangeFoldableMapNodeBase() : RangeFoldableMapNodeBase(Key{}, e()) {}\n  \
    \  RangeFoldableMapNodeBase(const Key &key, const Val &val) : Base::MapNodeBase(key,\
    \ val), dat(val) {}\n    void update() {\n        Base::update();\n        dat\
    \ = op(op(prod_all(this->ch[0]), this->val), prod_all(this->ch[1]));\n    }\n\
    \    static Val prod_all(node_ptr_t node) {\n        return node == nullptr ?\
    \ e() : node->dat;\n    }\n    static std::pair<node_ptr_t, Val> prod_by_index(node_ptr_t\
    \ node, int l, int r) {\n        auto [tl, tm, tr] = Base::split_by_index(node,\
    \ l, r);\n        Val res = prod_all(tm);\n        return { Base::merge(tl, tm,\
    \ tr), res };\n    }\n    static std::pair<node_ptr_t, Val> prod_by_key(node_ptr_t\
    \ node, const Key &l, const Key &r) {\n        auto [tl, tm, tr] = Base::split_by_key(node,\
    \ l, r);\n        Val res = prod_all(tm);\n        return { Base::merge(tl, tm,\
    \ tr), res };\n    }\n};\n\ntemplate <typename Key, typename Val, Val(*op)(Val,\
    \ Val), Val (*e)()>\nstruct RangeFoldableMapNode : public RangeFoldableMapNodeBase<Key,\
    \ Val, op, e, RangeFoldableMapNode<Key, Val, op, e>> {\n    using Base = RangeFoldableMapNodeBase<Key,\
    \ Val, op, e, RangeFoldableMapNode<Key, Val, op, e>>;\n    using Base::RangeFoldableMapNodeBase;\n\
    \    using node_ptr_t = typename Base::node_ptr_t;\n};\n}\n\ntemplate <typename\
    \ Key, typename Val, Val(*op)(Val, Val), Val (*e)()>\nclass RangeFoldableMap {\n\
    \    using Node = internal::range_foldable_map::RangeFoldableMapNode<Key, Val,\
    \ op, e>;\n    using node_ptr_t = typename Node::node_ptr_t;\n    public:\n  \
    \      RangeFoldableMap() : root(nullptr) {}\n        ~RangeFoldableMap() {\n\
    \            delete root;\n        }\n\n        RangeFoldableMap& operator=(const\
    \ RangeFoldableMap&) = delete;\n        RangeFoldableMap& operator=(RangeFoldableMap&&\
    \ other) {\n            if (other.root == root) return *this;\n            delete\
    \ root;\n            root = other.root;\n            other.root = nullptr;\n \
    \           return *this;\n        }\n\n        int size() {\n            return\
    \ Node::size(root);\n        }\n        bool contains(const Key &key) {\n    \
    \        auto [new_root, found] = Node::find_key(root, key);\n            root\
    \ = new_root;\n            return found;\n        }\n        void insert(const\
    \ Key &key, const Val &val) {\n            root = Node::insert(root, key, val,\
    \ true);\n        }\n        void insert_if_absent(const Key &key, const Val &val)\
    \ {\n            root = Node::insert(root, key, val, false);\n        }\n    \
    \    bool erase_key(const Key &key) {\n            auto [new_root, is_erased]\
    \ = Node::erase_key(root, key);\n            root = new_root;\n            return\
    \ is_erased;\n        }\n        void erase_index(int k) {\n            index_bounds_check(k,\
    \ size() + 1);\n            root = Node::erase_index(root, k);\n        }\n  \
    \      Val& get_or_create(const Key &key, const Val &val) {\n            root\
    \ = Node::insert(root, key, val, false);\n            return root->val;\n    \
    \    }\n\n        auto operator[](const Key &key) {\n            get_or_create(key,\
    \ e());\n            return UpdateProxyObject { root->val, [this]{ root->update();\
    \ } };\n        }\n        Val operator()(const Key &l, const Key &r) {\n    \
    \        return prod(l, r);\n        }\n        Val prod_by_key(const Key &l,\
    \ const Key &r) {\n            auto [new_root, res] = Node::prod_by_key(root,\
    \ l, r);\n            root = new_root;\n            return res;\n        }\n \
    \       Val prod_by_index(int l, int r) {\n            auto [new_root, res] =\
    \ Node::prod_by_index(root, l, r);\n            root = new_root;\n           \
    \ return res;\n        }\n        Val prod_all() {\n            return Node::prod_all(root);\n\
    \        }\n\n        Val get_or_default(const Key &key, const Val &default_value)\
    \ {\n            auto [new_root, res] = Node::get_or_default(root, key, default_value);\n\
    \            root = new_root;\n            return res;\n        }\n        std::pair<Key,\
    \ Val> kth_entry(int k) {\n            index_bounds_check(k, size());\n      \
    \      root = Node::splay_by_index(root, k);\n            return { root->key,\
    \ root->val };\n        }\n        RangeFoldableMap split_by_index(int k) {\n\
    \            index_bounds_check(k, size() + 1);\n            auto [l, r] = Node::split_by_index(root,\
    \ k);\n            root = l;\n            return RangeFoldableMap(r);\n      \
    \  }\n        RangeFoldableMap split_by_key(const Key &key) {\n            auto\
    \ [l, r] = Node::split_by_key(root, key);\n            root = l;\n           \
    \ return RangeFoldableMap(r);\n        }\n        void merge(RangeFoldableMap\
    \ &&r) {\n            assert(root == nullptr or root != r.root);\n           \
    \ root = Node::merge(root, r.root);\n            r.root = nullptr;\n        }\n\
    \        void swap(RangeFoldableMap &r) {\n            std::swap(root, r.root);\n\
    \        }\n\n    protected:\n        Node *root;\n\n        RangeFoldableMap(node_ptr_t\
    \ root) : root(root) {}\n    \n        static void index_bounds_check(unsigned\
    \ int k, unsigned int n) {\n            assert(k < n);\n        }\n        static\
    \ void range_bounds_check(unsigned int l, unsigned int r, unsigned int n) {\n\
    \            assert(l <= r and r <= n);\n        }\n};\n\n}\n\n\n#line 9 \"library/datastructure/lazy_eval_map.hpp\"\
    \n\nnamespace suisen {\nnamespace internal::lazy_eval_map {\n\ntemplate <typename\
    \ Key, typename Val, Val(*op)(Val, Val), Val (*e)(), typename F, Val(*mapping)(F,\
    \ Val), F(*composition)(F, F), F(*id)(), typename Derived>\nstruct LazyEvalMapNodeBase\
    \ : public internal::range_foldable_map::RangeFoldableMapNodeBase<Key, Val, op,\
    \ e, Derived> {\n    using Base = internal::range_foldable_map::RangeFoldableMapNodeBase<Key,\
    \ Val, op, e, Derived>;\n    using node_ptr_t = typename Base::node_ptr_t;\n \
    \   F laz;\n\n    LazyEvalMapNodeBase() : LazyEvalMapNodeBase(Key{}, e()) {}\n\
    \    LazyEvalMapNodeBase(const Key &key, const Val &val) : Base::RangeFoldableMapNodeBase(key,\
    \ val), laz(id()) {}\n\n    void push() {\n        Base::push();\n        apply_all(this->ch[0],\
    \ laz), apply_all(this->ch[1], laz);\n        laz = id();\n    }\n    static void\
    \ apply_all(node_ptr_t node, const F &f) {\n        if (node == nullptr) return;\n\
    \        node->val = mapping(f, node->val);\n        node->dat = mapping(f, node->dat);\n\
    \        node->laz = composition(f, node->laz);\n    }\n    static node_ptr_t\
    \ apply_by_key(node_ptr_t node, const Key &l, const Key &r, const F &f) {\n  \
    \      auto [tl, tm, tr] = Base::split_by_key(node, l, r);\n        apply_all(tm,\
    \ f);\n        return Base::merge(tl, tm, tr);\n    }\n    static node_ptr_t apply_by_index(node_ptr_t\
    \ node, int l, int r, const F &f) {\n        auto [tl, tm, tr] = Base::split_by_index(node,\
    \ l, r);\n        apply_all(tm, f);\n        return Base::merge(tl, tm, tr);\n\
    \    }\n};\n\ntemplate <typename Key, typename Val, Val(*op)(Val, Val), Val (*e)(),\
    \ typename F, Val(*mapping)(F, Val), F(*composition)(F, F), F(*id)()>\nstruct\
    \ LazyEvalMapNode : public LazyEvalMapNodeBase<Key, Val, op, e, F, mapping, composition,\
    \ id, LazyEvalMapNode<Key, Val, op, e, F, mapping, composition, id>> {\n    using\
    \ Base = LazyEvalMapNodeBase<Key, Val, op, e, F, mapping, composition, id, LazyEvalMapNode<Key,\
    \ Val, op, e, F, mapping, composition, id>>;\n    using Base::LazyEvalMapNodeBase;\n\
    \    using node_ptr_t = typename Base::node_ptr_t;\n};\n}\n\ntemplate <typename\
    \ Key, typename Val, Val(*op)(Val, Val), Val (*e)(), typename F, Val(*mapping)(F,\
    \ Val), F(*composition)(F, F), F(*id)()>\nclass LazyEvalMap {\n    using Node\
    \ = internal::lazy_eval_map::LazyEvalMapNode<Key, Val, op, e, F, mapping, composition,\
    \ id>;\n    using node_ptr_t = typename Node::node_ptr_t;\n    public:\n     \
    \   LazyEvalMap() : root(nullptr) {}\n        ~LazyEvalMap() {\n            delete\
    \ root;\n        }\n\n        LazyEvalMap& operator=(const LazyEvalMap&) = delete;\n\
    \        LazyEvalMap& operator=(LazyEvalMap&& other) {\n            if (other.root\
    \ == root) return *this;\n            delete root;\n            root = other.root;\n\
    \            other.root = nullptr;\n            return *this;\n        }\n\n \
    \       int size() {\n            return Node::size(root);\n        }\n      \
    \  bool contains(const Key &key) {\n            auto [new_root, found] = Node::find_key(root,\
    \ key);\n            root = new_root;\n            return found;\n        }\n\
    \        void insert(const Key &key, const Val &val) {\n            root = Node::insert(root,\
    \ key, val, true);\n        }\n        void insert_if_absent(const Key &key, const\
    \ Val &val) {\n            root = Node::insert(root, key, val, false);\n     \
    \   }\n        bool erase_key(const Key &key) {\n            auto [new_root, is_erased]\
    \ = Node::erase_key(root, key);\n            root = new_root;\n            return\
    \ is_erased;\n        }\n        void erase_index(int k) {\n            index_bounds_check(k,\
    \ size() + 1);\n            root = Node::erase_index(root, k);\n        }\n  \
    \      Val& get_or_create(const Key &key, const Val &val) {\n            root\
    \ = Node::insert(root, key, val, false);\n            return root->val;\n    \
    \    }\n\n        auto operator[](const Key &key) {\n            get_or_create(key,\
    \ e());\n            return UpdateProxyObject { root->val, [this]{ root->update();\
    \ } };\n        }\n        Val operator()(const Key &l, const Key &r) {\n    \
    \        return prod(l, r);\n        }\n        Val prod_by_key(const Key &l,\
    \ const Key &r) {\n            auto [new_root, res] = Node::prod_by_key(root,\
    \ l, r);\n            root = new_root;\n            return res;\n        }\n \
    \       Val prod_by_index(int l, int r) {\n            auto [new_root, res] =\
    \ Node::prod_by_index(root, l, r);\n            root = new_root;\n           \
    \ return res;\n        }\n        Val prod_all() {\n            return Node::prod_all(root);\n\
    \        }\n        void apply_by_key(const Key &l, const Key &r, const F &f)\
    \ {\n            root = Node::apply_by_key(root, l, r, f);\n        }\n      \
    \  void apply_by_index(int l, int r, const F &f) {\n            root = Node::apply_by_index(root,\
    \ l, r, f);\n        }\n        void apply_all(const F &f) {\n            Node::apply_all(root,\
    \ f);\n        }\n\n        Val get_or_default(const Key &key, const Val &default_value)\
    \ {\n            auto [new_root, res] = Node::get_or_default(root, key, default_value);\n\
    \            root = new_root;\n            return res;\n        }\n        std::pair<Key,\
    \ Val> kth_entry(int k) {\n            index_bounds_check(k, size());\n      \
    \      root = Node::splay_by_index(root, k);\n            return { root->key,\
    \ root->val };\n        }\n        LazyEvalMap split_by_index(int k) {\n     \
    \       index_bounds_check(k, size() + 1);\n            auto [l, r] = Node::split_by_index(root,\
    \ k);\n            root = l;\n            return LazyEvalMap(r);\n        }\n\
    \        LazyEvalMap split_by_key(const Key &key) {\n            auto [l, r] =\
    \ Node::split_by_key(root, key);\n            root = l;\n            return LazyEvalMap(r);\n\
    \        }\n        void merge(LazyEvalMap &&r) {\n            assert(root !=\
    \ r.root);\n            root = Node::merge(root, r.root);\n            r.root\
    \ = nullptr;\n        }\n        void swap(LazyEvalMap &r) {\n            std::swap(root,\
    \ r.root);\n        }\n\n    protected:\n        Node *root;\n\n        LazyEvalMap(node_ptr_t\
    \ root) : root(root) {}\n    \n        static void index_bounds_check(unsigned\
    \ int k, unsigned int n) {\n            assert(k < n);\n        }\n        static\
    \ void range_bounds_check(unsigned int l, unsigned int r, unsigned int n) {\n\
    \            assert(l <= r and r <= n);\n        }\n};\n\n}\n\n\n\n"
  code: "#ifndef SUISEN_LAZY_EVAL_MAP\n#define SUISEN_LAZY_EVAL_MAP\n\n#include <cassert>\n\
    #include <tuple>\n\n#include \"library/util/update_proxy_object.hpp\"\n#include\
    \ \"library/datastructure/range_foldable_map.hpp\"\n\nnamespace suisen {\nnamespace\
    \ internal::lazy_eval_map {\n\ntemplate <typename Key, typename Val, Val(*op)(Val,\
    \ Val), Val (*e)(), typename F, Val(*mapping)(F, Val), F(*composition)(F, F),\
    \ F(*id)(), typename Derived>\nstruct LazyEvalMapNodeBase : public internal::range_foldable_map::RangeFoldableMapNodeBase<Key,\
    \ Val, op, e, Derived> {\n    using Base = internal::range_foldable_map::RangeFoldableMapNodeBase<Key,\
    \ Val, op, e, Derived>;\n    using node_ptr_t = typename Base::node_ptr_t;\n \
    \   F laz;\n\n    LazyEvalMapNodeBase() : LazyEvalMapNodeBase(Key{}, e()) {}\n\
    \    LazyEvalMapNodeBase(const Key &key, const Val &val) : Base::RangeFoldableMapNodeBase(key,\
    \ val), laz(id()) {}\n\n    void push() {\n        Base::push();\n        apply_all(this->ch[0],\
    \ laz), apply_all(this->ch[1], laz);\n        laz = id();\n    }\n    static void\
    \ apply_all(node_ptr_t node, const F &f) {\n        if (node == nullptr) return;\n\
    \        node->val = mapping(f, node->val);\n        node->dat = mapping(f, node->dat);\n\
    \        node->laz = composition(f, node->laz);\n    }\n    static node_ptr_t\
    \ apply_by_key(node_ptr_t node, const Key &l, const Key &r, const F &f) {\n  \
    \      auto [tl, tm, tr] = Base::split_by_key(node, l, r);\n        apply_all(tm,\
    \ f);\n        return Base::merge(tl, tm, tr);\n    }\n    static node_ptr_t apply_by_index(node_ptr_t\
    \ node, int l, int r, const F &f) {\n        auto [tl, tm, tr] = Base::split_by_index(node,\
    \ l, r);\n        apply_all(tm, f);\n        return Base::merge(tl, tm, tr);\n\
    \    }\n};\n\ntemplate <typename Key, typename Val, Val(*op)(Val, Val), Val (*e)(),\
    \ typename F, Val(*mapping)(F, Val), F(*composition)(F, F), F(*id)()>\nstruct\
    \ LazyEvalMapNode : public LazyEvalMapNodeBase<Key, Val, op, e, F, mapping, composition,\
    \ id, LazyEvalMapNode<Key, Val, op, e, F, mapping, composition, id>> {\n    using\
    \ Base = LazyEvalMapNodeBase<Key, Val, op, e, F, mapping, composition, id, LazyEvalMapNode<Key,\
    \ Val, op, e, F, mapping, composition, id>>;\n    using Base::LazyEvalMapNodeBase;\n\
    \    using node_ptr_t = typename Base::node_ptr_t;\n};\n}\n\ntemplate <typename\
    \ Key, typename Val, Val(*op)(Val, Val), Val (*e)(), typename F, Val(*mapping)(F,\
    \ Val), F(*composition)(F, F), F(*id)()>\nclass LazyEvalMap {\n    using Node\
    \ = internal::lazy_eval_map::LazyEvalMapNode<Key, Val, op, e, F, mapping, composition,\
    \ id>;\n    using node_ptr_t = typename Node::node_ptr_t;\n    public:\n     \
    \   LazyEvalMap() : root(nullptr) {}\n        ~LazyEvalMap() {\n            delete\
    \ root;\n        }\n\n        LazyEvalMap& operator=(const LazyEvalMap&) = delete;\n\
    \        LazyEvalMap& operator=(LazyEvalMap&& other) {\n            if (other.root\
    \ == root) return *this;\n            delete root;\n            root = other.root;\n\
    \            other.root = nullptr;\n            return *this;\n        }\n\n \
    \       int size() {\n            return Node::size(root);\n        }\n      \
    \  bool contains(const Key &key) {\n            auto [new_root, found] = Node::find_key(root,\
    \ key);\n            root = new_root;\n            return found;\n        }\n\
    \        void insert(const Key &key, const Val &val) {\n            root = Node::insert(root,\
    \ key, val, true);\n        }\n        void insert_if_absent(const Key &key, const\
    \ Val &val) {\n            root = Node::insert(root, key, val, false);\n     \
    \   }\n        bool erase_key(const Key &key) {\n            auto [new_root, is_erased]\
    \ = Node::erase_key(root, key);\n            root = new_root;\n            return\
    \ is_erased;\n        }\n        void erase_index(int k) {\n            index_bounds_check(k,\
    \ size() + 1);\n            root = Node::erase_index(root, k);\n        }\n  \
    \      Val& get_or_create(const Key &key, const Val &val) {\n            root\
    \ = Node::insert(root, key, val, false);\n            return root->val;\n    \
    \    }\n\n        auto operator[](const Key &key) {\n            get_or_create(key,\
    \ e());\n            return UpdateProxyObject { root->val, [this]{ root->update();\
    \ } };\n        }\n        Val operator()(const Key &l, const Key &r) {\n    \
    \        return prod(l, r);\n        }\n        Val prod_by_key(const Key &l,\
    \ const Key &r) {\n            auto [new_root, res] = Node::prod_by_key(root,\
    \ l, r);\n            root = new_root;\n            return res;\n        }\n \
    \       Val prod_by_index(int l, int r) {\n            auto [new_root, res] =\
    \ Node::prod_by_index(root, l, r);\n            root = new_root;\n           \
    \ return res;\n        }\n        Val prod_all() {\n            return Node::prod_all(root);\n\
    \        }\n        void apply_by_key(const Key &l, const Key &r, const F &f)\
    \ {\n            root = Node::apply_by_key(root, l, r, f);\n        }\n      \
    \  void apply_by_index(int l, int r, const F &f) {\n            root = Node::apply_by_index(root,\
    \ l, r, f);\n        }\n        void apply_all(const F &f) {\n            Node::apply_all(root,\
    \ f);\n        }\n\n        Val get_or_default(const Key &key, const Val &default_value)\
    \ {\n            auto [new_root, res] = Node::get_or_default(root, key, default_value);\n\
    \            root = new_root;\n            return res;\n        }\n        std::pair<Key,\
    \ Val> kth_entry(int k) {\n            index_bounds_check(k, size());\n      \
    \      root = Node::splay_by_index(root, k);\n            return { root->key,\
    \ root->val };\n        }\n        LazyEvalMap split_by_index(int k) {\n     \
    \       index_bounds_check(k, size() + 1);\n            auto [l, r] = Node::split_by_index(root,\
    \ k);\n            root = l;\n            return LazyEvalMap(r);\n        }\n\
    \        LazyEvalMap split_by_key(const Key &key) {\n            auto [l, r] =\
    \ Node::split_by_key(root, key);\n            root = l;\n            return LazyEvalMap(r);\n\
    \        }\n        void merge(LazyEvalMap &&r) {\n            assert(root !=\
    \ r.root);\n            root = Node::merge(root, r.root);\n            r.root\
    \ = nullptr;\n        }\n        void swap(LazyEvalMap &r) {\n            std::swap(root,\
    \ r.root);\n        }\n\n    protected:\n        Node *root;\n\n        LazyEvalMap(node_ptr_t\
    \ root) : root(root) {}\n    \n        static void index_bounds_check(unsigned\
    \ int k, unsigned int n) {\n            assert(k < n);\n        }\n        static\
    \ void range_bounds_check(unsigned int l, unsigned int r, unsigned int n) {\n\
    \            assert(l <= r and r <= n);\n        }\n};\n\n}\n\n\n#endif // SUISEN_LAZY_EVAL_MAP\n"
  dependsOn:
  - library/util/update_proxy_object.hpp
  - library/type_traits/type_traits.hpp
  - library/datastructure/range_foldable_map.hpp
  - library/datastructure/splay_tree_map.hpp
  isVerificationFile: false
  path: library/datastructure/lazy_eval_map.hpp
  requiredBy: []
  timestamp: '2022-05-31 16:25:25+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/datastructure/lazy_eval_map/leq_and_neq.test.cpp
documentation_of: library/datastructure/lazy_eval_map.hpp
layout: document
title: Lazy Eval Map
---
## Lazy Eval Map