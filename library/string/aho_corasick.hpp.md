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
  bundledCode: "#line 1 \"library/string/aho_corasick.hpp\"\n\n\n\n#include <cassert>\n\
    #include <deque>\n#include <map>\n#include <vector>\n\nnamespace suisen {\n  \
    \  template <typename T = char>\n    struct AhoCorasick {\n        using value_type\
    \ = T;\n\n        AhoCorasick() : _next(1) {}\n\n        template <typename Container,\
    \ std::enable_if_t<std::is_constructible_v<value_type, typename Container::value_type>,\
    \ std::nullptr_t> = nullptr>\n        void add(const Container& s) {\n       \
    \     int cur = init_state();\n            for (value_type c : s) {\n        \
    \        auto [it, inserted] = _next[cur].try_emplace(c, _next.size());\n    \
    \            if (inserted) _next.emplace_back();\n                cur = it->second;\n\
    \            }\n            _marks.push_back(cur);\n            _built = false;\n\
    \        }\n\n        void build() {\n            _built = true;\n           \
    \ const int n = _next.size();\n            _failure.resize(n, 0);\n          \
    \  _count.resize(n, 0);\n            for (int mark : _marks) ++_count[mark];\n\
    \            std::deque<int> dq{ 0 };\n            while (dq.size()) {\n     \
    \           const int cur = dq.front();\n                dq.pop_front();\n   \
    \             for (const auto& [c, nxt] : _next[cur]) {\n                    if\
    \ (cur) {\n                        _failure[nxt] = next_state(_failure[cur], c);\n\
    \                        _count[nxt] += _count[_failure[nxt]];\n             \
    \       }\n                    dq.push_back(nxt);\n                }\n       \
    \     }\n        }\n\n        int init_state() const {\n            return 0;\n\
    \        }\n        int next_state(int state, value_type c) const {\n        \
    \    assert(_built);\n            while (true) {\n                if (auto it\
    \ = _next[state].find(c); it == _next[state].end()) {\n                    if\
    \ (state == 0) return 0;\n                    state = _failure[state];\n     \
    \           } else {\n                    return it->second;\n               \
    \ }\n            }\n        }\n        int count_suffix_matching(int state) const\
    \ {\n            assert(_built);\n            return _count[state];\n        }\n\
    \    private:\n        std::vector<int> _failure;\n        std::vector<std::map<value_type,\
    \ int>> _next;\n        std::vector<int> _marks;\n        std::vector<int> _count;\n\
    \        bool _built = true;\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_AHO_CORASICK\n#define SUISEN_AHO_CORASICK\n\n#include <cassert>\n\
    #include <deque>\n#include <map>\n#include <vector>\n\nnamespace suisen {\n  \
    \  template <typename T = char>\n    struct AhoCorasick {\n        using value_type\
    \ = T;\n\n        AhoCorasick() : _next(1) {}\n\n        template <typename Container,\
    \ std::enable_if_t<std::is_constructible_v<value_type, typename Container::value_type>,\
    \ std::nullptr_t> = nullptr>\n        void add(const Container& s) {\n       \
    \     int cur = init_state();\n            for (value_type c : s) {\n        \
    \        auto [it, inserted] = _next[cur].try_emplace(c, _next.size());\n    \
    \            if (inserted) _next.emplace_back();\n                cur = it->second;\n\
    \            }\n            _marks.push_back(cur);\n            _built = false;\n\
    \        }\n\n        void build() {\n            _built = true;\n           \
    \ const int n = _next.size();\n            _failure.resize(n, 0);\n          \
    \  _count.resize(n, 0);\n            for (int mark : _marks) ++_count[mark];\n\
    \            std::deque<int> dq{ 0 };\n            while (dq.size()) {\n     \
    \           const int cur = dq.front();\n                dq.pop_front();\n   \
    \             for (const auto& [c, nxt] : _next[cur]) {\n                    if\
    \ (cur) {\n                        _failure[nxt] = next_state(_failure[cur], c);\n\
    \                        _count[nxt] += _count[_failure[nxt]];\n             \
    \       }\n                    dq.push_back(nxt);\n                }\n       \
    \     }\n        }\n\n        int init_state() const {\n            return 0;\n\
    \        }\n        int next_state(int state, value_type c) const {\n        \
    \    assert(_built);\n            while (true) {\n                if (auto it\
    \ = _next[state].find(c); it == _next[state].end()) {\n                    if\
    \ (state == 0) return 0;\n                    state = _failure[state];\n     \
    \           } else {\n                    return it->second;\n               \
    \ }\n            }\n        }\n        int count_suffix_matching(int state) const\
    \ {\n            assert(_built);\n            return _count[state];\n        }\n\
    \    private:\n        std::vector<int> _failure;\n        std::vector<std::map<value_type,\
    \ int>> _next;\n        std::vector<int> _marks;\n        std::vector<int> _count;\n\
    \        bool _built = true;\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_AHO_CORASICK\n"
  dependsOn: []
  isVerificationFile: false
  path: library/string/aho_corasick.hpp
  requiredBy: []
  timestamp: '2022-09-11 20:50:26+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/string/aho_corasick.hpp
layout: document
title: Aho Corasick
---
## Aho Corasick