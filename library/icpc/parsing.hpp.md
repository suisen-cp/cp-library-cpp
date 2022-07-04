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
  bundledCode: "#line 1 \"library/icpc/parsing.hpp\"\n#include <iostream>\n#include\
    \ <optional>\n#include <string>\n\nnamespace suisen::parsing {\n    using State\
    \ = std::string::const_iterator;\n\n    struct ParseError {\n        ParseError(const\
    \ std::string& message = \"\") {\n            std::cerr << message << std::endl;\n\
    \        }\n    };\n\n    namespace internal {\n        void print_rest_of_string(State\
    \ it) {\n            cerr << \"Rest string is '\";\n            while (*it) cerr\
    \ << *it++;\n            cerr << \"'\" << endl;\n        }\n    }\n\n    void\
    \ consume(State& it, char expected) {\n        if (*it == expected) {\n      \
    \      *it++;\n        } else {\n            cerr << \"Expected '\" << expected\
    \ << \"' but got '\" << *it << \"'\" << endl;\n            internal::print_rest_of_string(it);\n\
    \            throw ParseError{};\n        }\n    }\n\n    bool in(const State&\
    \ it, char l, char r) {\n        return l <= *it and *it <= r;\n    }\n    bool\
    \ is(const State& it, char c) {\n        return *it == c;\n    }\n\n    void assert_range(const\
    \ State& it, char lo, char hi) {\n        if (in(it, lo, hi)) {\n            cerr\
    \ << \"Expected [\" << lo << \"-\" << hi << \"] but got '\" << *it << \"'\" <<\
    \ endl;\n            internal::print_rest_of_string(it);\n            throw ParseError{};\n\
    \        }\n    }\n    void assert_exact(const State& it, char c) {\n        if\
    \ (not is(it, c)) {\n            cerr << \"Expected '\" << c << \"' but got '\"\
    \ << *it << \"'\" << endl;\n            internal::print_rest_of_string(it);\n\
    \            throw ParseError{};\n        }\n    }\n\n    long long nonnegative_number(State&\
    \ it) {\n        long long res = 0;\n        assert_range(it, '0', '9');\n   \
    \     while (in(it, '0', '9')) res = res * 10 + (*it++ - '0');\n        return\
    \ res;\n    }\n    long long number(State& it) {\n        long long res = 0;\n\
    \        bool neg = false;\n        while (is(it, '-')) neg = not neg, consume(it,\
    \ '-');\n        while (in(it, '0', '9')) res = res * 10 + (*it++ - '0');\n  \
    \      if (neg) res = -res;\n        return res;\n    }\n\n    namespace normal_expression\
    \ {\n        namespace internal {\n            long long expr(State& it);\n  \
    \          long long term(State& it);\n            long long factor(State& it);\n\
    \n            long long expr(State& it) {\n                long long res = term(it);\n\
    \                while (true) {\n                    if (*it == '+') {\n     \
    \                   consume(it, '+');\n                        res = res + term(it);\n\
    \                    } else if (*it == '-') {\n                        consume(it,\
    \ '-');\n                        res = res - term(it);\n                    }\
    \ else break;\n                }\n                return res;\n            }\n\
    \            long long term(State& it) {\n                long long res = factor(it);\n\
    \                while (true) {\n                    if (*it == '*') {\n     \
    \                   consume(it, '*');\n                        res = res * factor(it);\n\
    \                    } else if (*it == '/') {\n                        consume(it,\
    \ '/');\n                        res = res / factor(it);\n                   \
    \ } else break;\n                }\n                return res;\n            }\n\
    \            long long factor(State& it) {\n                bool neg = false;\n\
    \                while (is(it, '-')) neg = not neg, consume(it, '-');\n      \
    \          long long res;\n                if (is(it, '(')) {\n              \
    \      consume(it, '(');\n                    res = expr(it);\n              \
    \      consume(it, ')');\n                } else {\n                    res =\
    \ nonnegative_number(it);\n                }\n                if (neg) res = -res;\n\
    \                return res;\n            }\n        }\n\n        long long parse(State&\
    \ it) {\n            return internal::expr(it);\n        }\n    }\n}\n"
  code: "#include <iostream>\n#include <optional>\n#include <string>\n\nnamespace\
    \ suisen::parsing {\n    using State = std::string::const_iterator;\n\n    struct\
    \ ParseError {\n        ParseError(const std::string& message = \"\") {\n    \
    \        std::cerr << message << std::endl;\n        }\n    };\n\n    namespace\
    \ internal {\n        void print_rest_of_string(State it) {\n            cerr\
    \ << \"Rest string is '\";\n            while (*it) cerr << *it++;\n         \
    \   cerr << \"'\" << endl;\n        }\n    }\n\n    void consume(State& it, char\
    \ expected) {\n        if (*it == expected) {\n            *it++;\n        } else\
    \ {\n            cerr << \"Expected '\" << expected << \"' but got '\" << *it\
    \ << \"'\" << endl;\n            internal::print_rest_of_string(it);\n       \
    \     throw ParseError{};\n        }\n    }\n\n    bool in(const State& it, char\
    \ l, char r) {\n        return l <= *it and *it <= r;\n    }\n    bool is(const\
    \ State& it, char c) {\n        return *it == c;\n    }\n\n    void assert_range(const\
    \ State& it, char lo, char hi) {\n        if (in(it, lo, hi)) {\n            cerr\
    \ << \"Expected [\" << lo << \"-\" << hi << \"] but got '\" << *it << \"'\" <<\
    \ endl;\n            internal::print_rest_of_string(it);\n            throw ParseError{};\n\
    \        }\n    }\n    void assert_exact(const State& it, char c) {\n        if\
    \ (not is(it, c)) {\n            cerr << \"Expected '\" << c << \"' but got '\"\
    \ << *it << \"'\" << endl;\n            internal::print_rest_of_string(it);\n\
    \            throw ParseError{};\n        }\n    }\n\n    long long nonnegative_number(State&\
    \ it) {\n        long long res = 0;\n        assert_range(it, '0', '9');\n   \
    \     while (in(it, '0', '9')) res = res * 10 + (*it++ - '0');\n        return\
    \ res;\n    }\n    long long number(State& it) {\n        long long res = 0;\n\
    \        bool neg = false;\n        while (is(it, '-')) neg = not neg, consume(it,\
    \ '-');\n        while (in(it, '0', '9')) res = res * 10 + (*it++ - '0');\n  \
    \      if (neg) res = -res;\n        return res;\n    }\n\n    namespace normal_expression\
    \ {\n        namespace internal {\n            long long expr(State& it);\n  \
    \          long long term(State& it);\n            long long factor(State& it);\n\
    \n            long long expr(State& it) {\n                long long res = term(it);\n\
    \                while (true) {\n                    if (*it == '+') {\n     \
    \                   consume(it, '+');\n                        res = res + term(it);\n\
    \                    } else if (*it == '-') {\n                        consume(it,\
    \ '-');\n                        res = res - term(it);\n                    }\
    \ else break;\n                }\n                return res;\n            }\n\
    \            long long term(State& it) {\n                long long res = factor(it);\n\
    \                while (true) {\n                    if (*it == '*') {\n     \
    \                   consume(it, '*');\n                        res = res * factor(it);\n\
    \                    } else if (*it == '/') {\n                        consume(it,\
    \ '/');\n                        res = res / factor(it);\n                   \
    \ } else break;\n                }\n                return res;\n            }\n\
    \            long long factor(State& it) {\n                bool neg = false;\n\
    \                while (is(it, '-')) neg = not neg, consume(it, '-');\n      \
    \          long long res;\n                if (is(it, '(')) {\n              \
    \      consume(it, '(');\n                    res = expr(it);\n              \
    \      consume(it, ')');\n                } else {\n                    res =\
    \ nonnegative_number(it);\n                }\n                if (neg) res = -res;\n\
    \                return res;\n            }\n        }\n\n        long long parse(State&\
    \ it) {\n            return internal::expr(it);\n        }\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: library/icpc/parsing.hpp
  requiredBy: []
  timestamp: '2022-07-05 04:32:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/icpc/parsing.hpp
layout: document
redirect_from:
- /library/library/icpc/parsing.hpp
- /library/library/icpc/parsing.hpp.html
title: library/icpc/parsing.hpp
---
