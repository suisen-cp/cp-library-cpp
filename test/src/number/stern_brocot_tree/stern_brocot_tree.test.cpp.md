---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/number/stern_brocot_tree.hpp
    title: Stern Brocot Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/stern_brocot_tree
    links:
    - https://judge.yosupo.jp/problem/stern_brocot_tree
  bundledCode: "#line 1 \"test/src/number/stern_brocot_tree/stern_brocot_tree.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/stern_brocot_tree\"\n\n#line\
    \ 1 \"library/number/stern_brocot_tree.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstdint>\n#include <limits>\n#include <type_traits>\n#include\
    \ <utility>\n#include <vector>\n\nnamespace suisen {\n    template <typename Int,\
    \ std::enable_if_t<std::is_integral_v<Int>, std::nullptr_t> = nullptr>\n    struct\
    \ sbt_node {\n        // { a, b } <==> a/b\n        using rational = std::pair<Int,\
    \ Int>;\n        using sbt_arc = bool;\n        static constexpr sbt_arc Left\
    \ = false, Right = true;\n        using sbt_path = std::vector<std::pair<sbt_arc,\
    \ Int>>;\n\n        // 1/1\n        sbt_node() = default;\n        // a/b (a and\
    \ b must be positive integer)\n        sbt_node(Int a, Int b) : sbt_node() {\n\
    \            assert(a > 0 and b > 0);\n            // implicitly computes the\
    \ continued fraction\n            sbt_arc dir = a < b ? Left : Right;\n      \
    \      if (dir == Left) std::swap(a, b);\n            for (; b; dir = not dir)\
    \ {\n                const Int q = a / b, r = a % b;\n                // If r\
    \ != 0: [...,1] ----(q   step)----> [...,q+1] = [...,q,1]\n                //\
    \ If r == 0: [...,1] ----(q-1 step)----> [...,q] (end)\n                move_down(dir,\
    \ q - (r == 0));\n                a = b, b = r;\n            }\n        }\n  \
    \      // { a, b } <==> a/b\n        sbt_node(const rational& x) : sbt_node(x.first,\
    \ x.second) {}\n        sbt_node(const sbt_path& path) : sbt_node() {\n      \
    \      for (const auto& [dir, first] : path) move_down(dir, first);\n        }\n\
    \n        operator rational() const { return { _l.first + _r.first, _l.second\
    \ + _r.second }; }\n        // get the rational number\n        rational get()\
    \ const { return *this; }\n        // { inf, sup } of the subtree\n        std::pair<rational,\
    \ rational> range() const { return { _l, _r }; }\n        // path from the root\
    \ node 1/1\n        const sbt_path& path() const { return _path; }\n        //\
    \ distance from the root node 1/1\n        Int depth() const { return _dep; }\n\
    \n        // lowest common ancestor\n        static sbt_node lca(const sbt_node&\
    \ a, const sbt_node& b) {\n            const sbt_path& pa = a.path(), & pb = b.path();\n\
    \            const int k = std::min(pa.size(), pb.size());\n            sbt_node\
    \ c;\n            for (int i = 0; i < k; ++i) {\n                if (pa[i] ==\
    \ pb[i]) {\n                    c.move_down(pa[i].first, pa[i].second);\n    \
    \            } else {\n                    if (pa[i].first == pb[i].first) {\n\
    \                        // same direction but different lengths\n           \
    \             c.move_down(pa[i].first, std::min(pa[i].second, pb[i].second));\n\
    \                    }\n                    break;\n                }\n      \
    \      }\n            return c;\n        }\n        // lowest common ancestor\n\
    \        sbt_node lca(const sbt_node& other) { return lca(*this, other); }\n\n\
    \        // distance from a to b\n        static Int dist(const sbt_node& a, const\
    \ sbt_node& b) {\n            const sbt_node c = lca(a, b);\n            return\
    \ (a.depth() - c.depth()) + (b.depth() - c.depth());\n        }\n        // distance\
    \ to another node\n        Int dist(const sbt_node& other) { return dist(*this,\
    \ other); }\n\n        // Check if this is an ancestor of the given node\n   \
    \     bool is_ancestor_of(const sbt_node& a) const { return less(_l, a) and less(a,\
    \ _r); }\n        // Check if this is a descendant of the given node\n       \
    \ bool is_descendant_of(const sbt_node& a) const { return a.is_ancestor_of(*this);\
    \ }\n\n        // move k steps to the root node. returns true if 0<=k<=depth,\
    \ false otherwise (and makes no change).\n        bool move_up(Int k) {\n    \
    \        if (k < 0 or k > depth()) return false;\n            while (k) {\n  \
    \              auto& [dir, first] = _path.back();\n                const Int u\
    \ = std::min(k, first);\n                k -= u;\n                _dep -= u;\n\
    \                if (dir == Left) {\n                    _r.first -= _l.first\
    \ * u, _r.second -= _l.second * u;\n                } else {\n               \
    \     _l.first -= _r.first * u, _l.second -= _r.second * u;\n                }\n\
    \                first -= u;\n                if (first == 0) _path.pop_back();\n\
    \            }\n            return true;\n        }\n\n        // move down k\
    \ steps to the left\n        void move_down_left(Int k) { move(Left, k); }\n \
    \       // move down k steps to the right\n        void move_down_right(Int k)\
    \ { move(Right, k); }\n        // move down k steps in the direction `dir`\n \
    \       void move_down(sbt_arc dir, Int k) {\n            assert(k >= 0);\n  \
    \          if (k == 0) return;\n            if (_path.size() and _path.back().first\
    \ == dir) {\n                _path.back().second += k;\n            } else {\n\
    \                _path.emplace_back(dir, k);\n            }\n            _dep\
    \ += k;\n            if (dir == Left) {\n                _r.first += _l.first\
    \ * k, _r.second += _l.second * k;\n            } else {\n                _l.first\
    \ += _r.first * k, _l.second += _r.second * k;\n            }\n        }\n\n \
    \       // move k steps to the destination node. returns true if dist(this, dst)<=k,\
    \ false otherwise (and makes no change).\n        bool move_to(const sbt_node&\
    \ dst, Int k) {\n            const sbt_node a = lca(dst);\n            const Int\
    \ d1 = depth() - a.depth(), d2 = dst.depth() - a.depth();\n            if (k <=\
    \ d1) return move_up(k);\n            if (k - d1 > d2) return false;\n       \
    \     *this = dst;\n            return move_up(d2 - (k - d1));\n        }\n\n\
    \        friend bool operator==(const sbt_node& a, const sbt_node& b) { return\
    \ a._l == b._l and a._r == b._r; }\n        friend bool operator!=(const sbt_node&\
    \ a, const sbt_node& b) { return not (a == b); }\n        friend bool operator<(const\
    \ sbt_node& a, const sbt_node& b) { return less(rational(a), rational(b)); }\n\
    \        friend bool operator>(const sbt_node& a, const sbt_node& b) { return\
    \ (b < a); }\n        friend bool operator<=(const sbt_node& a, const sbt_node&\
    \ b) { return not (b < a); }\n        friend bool operator>=(const sbt_node& a,\
    \ const sbt_node& b) { return not (a < b); }\n\n        static int compare_in_order(const\
    \ sbt_node& a, const sbt_node& b) {\n            if (a == b) return 0;\n     \
    \       return a < b ? -1 : +1;\n        }\n        static int compare_pre_order(const\
    \ sbt_node& a, const sbt_node& b) {\n            if (a == b) return 0;\n     \
    \       if (a.is_ancestor_of(b)) return -1;\n            if (b.is_ancestor_of(a))\
    \ return +1;\n            return a < b ? -1 : +1;\n        }\n        static int\
    \ compare_post_order(const sbt_node& a, const sbt_node& b) {\n            if (a\
    \ == b) return 0;\n            if (a.is_ancestor_of(b)) return +1;\n         \
    \   if (b.is_ancestor_of(a)) return -1;\n            return a < b ? -1 : +1;\n\
    \        }\n\n        // undirected\n        static auto auxiliary_tree(std::vector<sbt_node>\
    \ xs) {\n            std::sort(xs.begin(), xs.end(), [](const sbt_node& a, const\
    \ sbt_node& b) { return compare_pre_order(a, b) < 0; });\n            xs.erase(std::unique(xs.begin(),\
    \ xs.end()), xs.end());\n\n            const int k = xs.size();\n\n          \
    \  std::vector<std::vector<int>> g(k);\n\n            std::vector<int> st{ 0 };\n\
    \            for (int i = 0; i < k - 1; ++i) {\n                const sbt_node\
    \ w = lca(xs[i], xs[i + 1]);\n\n                if (w != xs[i]) {\n          \
    \          int id_last = st.back();\n                    st.pop_back();\n    \
    \                while (st.size() and w.depth() < xs[st.back()].depth()) {\n \
    \                       int id_u = st.back();\n                        g[id_u].push_back(id_last);\n\
    \                        g[id_last].push_back(id_u);\n                       \
    \ id_last = id_u;\n                        st.pop_back();\n                  \
    \  }\n                    int id_w = xs.size();\n                    if (st.empty()\
    \ or xs[st.back()] != w) {\n                        st.push_back(id_w);\n    \
    \                    xs.push_back(w);\n                        g.emplace_back();\n\
    \                    } else {\n                        id_w = st.back();\n   \
    \                 }\n                    g[id_w].push_back(id_last);\n       \
    \             g[id_last].push_back(id_w);\n                }\n               \
    \ st.push_back(i + 1);\n            }\n            if (k) assert(st.size());\n\
    \            const int root = st.empty() ? 0 : st.front();\n            const\
    \ int siz = st.size();\n            for (int i = 0; i < siz - 1; ++i) {\n    \
    \            g[st[i]].push_back(st[i + 1]);\n                g[st[i + 1]].push_back(st[i]);\n\
    \            }\n            struct AuxiliaryTree {\n                AuxiliaryTree(int\
    \ root, const std::vector<sbt_node> &nodes, const std::vector<std::vector<int>>\
    \ &g) : _root(root), _nodes(nodes), _g(g) {}\n                \n             \
    \   int size() const { return _nodes.size(); }\n\n                int root() const\
    \ { return _root; }\n                \n                std::vector<int>& operator[](int\
    \ i) { return _g[i]; }\n                const std::vector<int>& operator[](int\
    \ i) const { return _g[i]; }\n\n                const sbt_node& node(int i) const\
    \ { return _nodes[i]; }\n                const std::vector<sbt_node>& nodes()\
    \ const { return _nodes; }\n            private:\n                int _root;\n\
    \                std::vector<sbt_node> _nodes;\n                std::vector<std::vector<int>>\
    \ _g;\n            };\n            return AuxiliaryTree{ root, std::move(xs),\
    \ std::move(g) };\n        }\n    private:\n        rational _l = rational{ 0,\
    \ 1 }, _r = rational{ 1, 0 };\n        Int _dep = 0;\n        sbt_path _path{};\n\
    \n        static bool less(const rational& a, const rational& b) {\n         \
    \   using LInt = std::conditional_t<(std::numeric_limits<Int>::digits <= 32),\
    \ uint64_t, __uint128_t>;\n            return LInt(a.first) * b.second < LInt(b.first)\
    \ * a.second;\n        }\n    };\n}\n\n\n\n#line 4 \"test/src/number/stern_brocot_tree/stern_brocot_tree.test.cpp\"\
    \n\n#include <iostream>\n\nusing sbt_node = suisen::sbt_node<int>;\n\nvoid query_encode_path()\
    \ {\n    int a, b;\n    std::cin >> a >> b;\n    sbt_node node(a, b);\n    const\
    \ auto p = node.path();\n    std::cout << p.size();\n    for (const auto& [dir,\
    \ num] : p) {\n        std::cout << ' ' << (dir == sbt_node::Left ? 'L' : 'R')\
    \ << ' '<< num;\n    }\n    std::cout << '\\n';\n}\nvoid query_decode_path() {\n\
    \    int k;\n    std::cin >> k;\n    sbt_node node;\n    for (int i = 0; i < k;\
    \ ++i) {\n        char c;\n        int n;\n        std::cin >> c >> n;\n     \
    \   sbt_node::sbt_arc dir = c == 'L' ? sbt_node::Left : sbt_node::Right;\n   \
    \     node.move_down(dir, n);\n    }\n    const auto [num, den] = node.get();\n\
    \    std::cout << num << ' ' << den << '\\n';\n}\nvoid query_lca() {\n    int\
    \ a, b, c, d;\n    std::cin >> a >> b >> c >> d;\n    auto [num, den] = sbt_node::lca({\
    \ a, b }, { c, d }).get();\n    std::cout << num << ' ' << den << '\\n';\n}\n\
    void query_ancestor() {\n    int k, a, b;\n    std::cin >> k >> a >> b;\n    sbt_node\
    \ node(a, b);\n    if (node.move_up(node.depth() - k)) {\n        const auto [num,\
    \ den] = node.get();\n        std::cout << num << ' ' << den << '\\n';\n    }\
    \ else {\n        std::cout << -1 << '\\n';\n    }\n}\nvoid query_range() {\n\
    \    int a, b;\n    std::cin >> a >> b;\n    auto [l, r] = sbt_node(a, b).range();\n\
    \    auto [num_l, den_l] = l;\n    auto [num_r, den_r] = r;\n    std::cout <<\
    \ num_l << ' ' << den_l << ' ' << num_r << ' ' << den_r << '\\n';\n}\n\nint main()\
    \ {\n    using namespace std::string_literals;\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int t;\n    std::cin >> t;\n    while (t--)\
    \ {\n        std::string op;\n        std::cin >> op;\n        if (op == \"ENCODE_PATH\"\
    s) query_encode_path();\n        if (op == \"DECODE_PATH\"s) query_decode_path();\n\
    \        if (op == \"LCA\"s) query_lca();\n        if (op == \"ANCESTOR\"s) query_ancestor();\n\
    \        if (op == \"RANGE\"s) query_range();\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/stern_brocot_tree\"\n\n\
    #include \"library/number/stern_brocot_tree.hpp\"\n\n#include <iostream>\n\nusing\
    \ sbt_node = suisen::sbt_node<int>;\n\nvoid query_encode_path() {\n    int a,\
    \ b;\n    std::cin >> a >> b;\n    sbt_node node(a, b);\n    const auto p = node.path();\n\
    \    std::cout << p.size();\n    for (const auto& [dir, num] : p) {\n        std::cout\
    \ << ' ' << (dir == sbt_node::Left ? 'L' : 'R') << ' '<< num;\n    }\n    std::cout\
    \ << '\\n';\n}\nvoid query_decode_path() {\n    int k;\n    std::cin >> k;\n \
    \   sbt_node node;\n    for (int i = 0; i < k; ++i) {\n        char c;\n     \
    \   int n;\n        std::cin >> c >> n;\n        sbt_node::sbt_arc dir = c ==\
    \ 'L' ? sbt_node::Left : sbt_node::Right;\n        node.move_down(dir, n);\n \
    \   }\n    const auto [num, den] = node.get();\n    std::cout << num << ' ' <<\
    \ den << '\\n';\n}\nvoid query_lca() {\n    int a, b, c, d;\n    std::cin >> a\
    \ >> b >> c >> d;\n    auto [num, den] = sbt_node::lca({ a, b }, { c, d }).get();\n\
    \    std::cout << num << ' ' << den << '\\n';\n}\nvoid query_ancestor() {\n  \
    \  int k, a, b;\n    std::cin >> k >> a >> b;\n    sbt_node node(a, b);\n    if\
    \ (node.move_up(node.depth() - k)) {\n        const auto [num, den] = node.get();\n\
    \        std::cout << num << ' ' << den << '\\n';\n    } else {\n        std::cout\
    \ << -1 << '\\n';\n    }\n}\nvoid query_range() {\n    int a, b;\n    std::cin\
    \ >> a >> b;\n    auto [l, r] = sbt_node(a, b).range();\n    auto [num_l, den_l]\
    \ = l;\n    auto [num_r, den_r] = r;\n    std::cout << num_l << ' ' << den_l <<\
    \ ' ' << num_r << ' ' << den_r << '\\n';\n}\n\nint main() {\n    using namespace\
    \ std::string_literals;\n\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int t;\n    std::cin >> t;\n    while (t--) {\n        std::string op;\n\
    \        std::cin >> op;\n        if (op == \"ENCODE_PATH\"s) query_encode_path();\n\
    \        if (op == \"DECODE_PATH\"s) query_decode_path();\n        if (op == \"\
    LCA\"s) query_lca();\n        if (op == \"ANCESTOR\"s) query_ancestor();\n   \
    \     if (op == \"RANGE\"s) query_range();\n    }\n}"
  dependsOn:
  - library/number/stern_brocot_tree.hpp
  isVerificationFile: true
  path: test/src/number/stern_brocot_tree/stern_brocot_tree.test.cpp
  requiredBy: []
  timestamp: '2024-01-30 21:22:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/number/stern_brocot_tree/stern_brocot_tree.test.cpp
layout: document
redirect_from:
- /verify/test/src/number/stern_brocot_tree/stern_brocot_tree.test.cpp
- /verify/test/src/number/stern_brocot_tree/stern_brocot_tree.test.cpp.html
title: test/src/number/stern_brocot_tree/stern_brocot_tree.test.cpp
---