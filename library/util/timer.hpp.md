---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/tree/frequency_table_of_tree_distance.hpp
    title: Frequency Table Of Tree Distance
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/graph/csr_graph/dummy.test.cpp
    title: test/src/graph/csr_graph/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/frequency_table_of_tree_distance/frequency_table_of_tree_distance.test.cpp
    title: test/src/tree/frequency_table_of_tree_distance/frequency_table_of_tree_distance.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/timer.hpp\"\n\n\n\n#include <chrono>\n\nnamespace\
    \ suisen {\n    struct Timer {\n        using minutes_t = std::chrono::minutes;\n\
    \        using seconds_t = std::chrono::seconds;\n        using milliseconds_t\
    \ = std::chrono::milliseconds;\n        using microseconds_t = std::chrono::microseconds;\n\
    \        using nanoseconds_t = std::chrono::nanoseconds;\n\n        Timer() {\
    \ start(); }\n\n        void start() {\n            _start = std::chrono::system_clock::now();\n\
    \        }\n        template <typename TimeUnit = std::chrono::milliseconds>\n\
    \        double elapsed() const {\n            return std::chrono::duration_cast<TimeUnit>(std::chrono::system_clock::now()\
    \ - _start).count();\n        }\n\n        template <typename TimeUnit = std::chrono::milliseconds,\
    \ typename Proc>\n        static double measure(Proc &&proc) {\n            Timer\
    \ timer;\n            proc();\n            return timer.elapsed<TimeUnit>();\n\
    \        }\n    private:\n        decltype(std::chrono::system_clock::now()) _start;\n\
    \    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_TIMER\n#define SUISEN_TIMER\n\n#include <chrono>\n\nnamespace\
    \ suisen {\n    struct Timer {\n        using minutes_t = std::chrono::minutes;\n\
    \        using seconds_t = std::chrono::seconds;\n        using milliseconds_t\
    \ = std::chrono::milliseconds;\n        using microseconds_t = std::chrono::microseconds;\n\
    \        using nanoseconds_t = std::chrono::nanoseconds;\n\n        Timer() {\
    \ start(); }\n\n        void start() {\n            _start = std::chrono::system_clock::now();\n\
    \        }\n        template <typename TimeUnit = std::chrono::milliseconds>\n\
    \        double elapsed() const {\n            return std::chrono::duration_cast<TimeUnit>(std::chrono::system_clock::now()\
    \ - _start).count();\n        }\n\n        template <typename TimeUnit = std::chrono::milliseconds,\
    \ typename Proc>\n        static double measure(Proc &&proc) {\n            Timer\
    \ timer;\n            proc();\n            return timer.elapsed<TimeUnit>();\n\
    \        }\n    private:\n        decltype(std::chrono::system_clock::now()) _start;\n\
    \    };\n} // namespace suisen\n\n\n#endif // SUISEN_TIMER\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/timer.hpp
  requiredBy:
  - library/tree/frequency_table_of_tree_distance.hpp
  timestamp: '2022-08-21 18:25:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/graph/csr_graph/dummy.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
  - test/src/tree/frequency_table_of_tree_distance/frequency_table_of_tree_distance.test.cpp
documentation_of: library/util/timer.hpp
layout: document
title: Timer
---
## Timer