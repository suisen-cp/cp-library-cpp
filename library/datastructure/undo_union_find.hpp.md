---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/undo_union_find.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ suisen {\n    struct UndoUnionFind {\n        UndoUnionFind() : UndoUnionFind(0)\
    \ {}\n        explicit UndoUnionFind(std::size_t n) : _n(n), _dat(n, -1) {}\n\n\
    \        int root(std::size_t x) {\n            assert(x < _n);\n            return\
    \ _dat[x] < 0 ? x : root(_dat[x]);\n        }\n        int operator[](std::size_t\
    \ x) {\n            return root(x);\n        }\n        bool merge(std::size_t\
    \ x, std::size_t y) {\n            x = root(x), y = root(y);\n            if (x\
    \ == y) return false;\n            if (_dat[x] > _dat[y]) std::swap(x, y);\n \
    \           _history.emplace_back(x, std::exchange(_dat[x], _dat[x] + _dat[y]));\n\
    \            _history.emplace_back(y, std::exchange(_dat[y], x));\n          \
    \  return true;\n        }\n        bool same(std::size_t x, std::size_t y) {\n\
    \            return root(x) == root(y);\n        }\n        int size(std::size_t\
    \ x) {\n            return -_dat[root(x)];\n        }\n        auto groups() {\n\
    \            std::vector<std::vector<int>> res(_n);\n            for (int i =\
    \ 0; i < _n; ++i) res[root(i)].push_back(i);\n            res.erase(std::remove_if(res.begin(),\
    \ res.end(), [](const auto &g) { return g.empty(); }), res.end());\n         \
    \   return res;\n        }\n        void snapshot() {\n            _history.clear();\n\
    \        }\n        void undo() {\n            assert(_history.size());\n    \
    \        _dat[_history.back().first] = _history.back().second, _history.pop_back();\n\
    \            _dat[_history.back().first] = _history.back().second, _history.pop_back();\n\
    \        }\n        void rollback() {\n            while (_history.size()) undo();\n\
    \        }\n    private:\n        std::size_t _n;\n        std::vector<int> _dat;\n\
    \        std::vector<std::pair<int, int>> _history;\n    };\n} // namespace suisen\n\
    \n\n\n"
  code: "#ifndef SUISEN_UNDO_UNION_FIND\n#define SUISEN_UNDO_UNION_FIND\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ suisen {\n    struct UndoUnionFind {\n        UndoUnionFind() : UndoUnionFind(0)\
    \ {}\n        explicit UndoUnionFind(std::size_t n) : _n(n), _dat(n, -1) {}\n\n\
    \        int root(std::size_t x) {\n            assert(x < _n);\n            return\
    \ _dat[x] < 0 ? x : root(_dat[x]);\n        }\n        int operator[](std::size_t\
    \ x) {\n            return root(x);\n        }\n        bool merge(std::size_t\
    \ x, std::size_t y) {\n            x = root(x), y = root(y);\n            if (x\
    \ == y) return false;\n            if (_dat[x] > _dat[y]) std::swap(x, y);\n \
    \           _history.emplace_back(x, std::exchange(_dat[x], _dat[x] + _dat[y]));\n\
    \            _history.emplace_back(y, std::exchange(_dat[y], x));\n          \
    \  return true;\n        }\n        bool same(std::size_t x, std::size_t y) {\n\
    \            return root(x) == root(y);\n        }\n        int size(std::size_t\
    \ x) {\n            return -_dat[root(x)];\n        }\n        auto groups() {\n\
    \            std::vector<std::vector<int>> res(_n);\n            for (int i =\
    \ 0; i < _n; ++i) res[root(i)].push_back(i);\n            res.erase(std::remove_if(res.begin(),\
    \ res.end(), [](const auto &g) { return g.empty(); }), res.end());\n         \
    \   return res;\n        }\n        void snapshot() {\n            _history.clear();\n\
    \        }\n        void undo() {\n            assert(_history.size());\n    \
    \        _dat[_history.back().first] = _history.back().second, _history.pop_back();\n\
    \            _dat[_history.back().first] = _history.back().second, _history.pop_back();\n\
    \        }\n        void rollback() {\n            while (_history.size()) undo();\n\
    \        }\n    private:\n        std::size_t _n;\n        std::vector<int> _dat;\n\
    \        std::vector<std::pair<int, int>> _history;\n    };\n} // namespace suisen\n\
    \n\n#endif // SUISEN_UNDO_UNION_FIND\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/undo_union_find.hpp
  requiredBy: []
  timestamp: '2022-01-15 00:27:49+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/undo_union_find.hpp
layout: document
redirect_from:
- /library/library/datastructure/undo_union_find.hpp
- /library/library/datastructure/undo_union_find.hpp.html
title: library/datastructure/undo_union_find.hpp
---
