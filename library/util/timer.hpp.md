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
  bundledCode: "#line 1 \"library/util/timer.hpp\"\n\n\n\n#include <chrono>\n\nnamespace\
    \ suisen {\n    struct Timer {\n        using minutes_t = std::chrono::minutes;\n\
    \        using seconds_t = std::chrono::seconds;\n        using milliseconds_t\
    \ = std::chrono::milliseconds;\n        using microseconds_t = std::chrono::microseconds;\n\
    \        using nanoseconds_t = std::chrono::nanoseconds;\n\n        Timer() {\
    \ start(); }\n\n        void start() {\n            _start = std::chrono::system_clock::now();\n\
    \        }\n        template <typename TimeUnit>\n        double elapsed() const\
    \ {\n            return std::chrono::duration_cast<TimeUnit>(std::chrono::system_clock::now()\
    \ - _start).count();\n        }\n\n        template <typename TimeUnit, typename\
    \ Proc>\n        static double measure(Proc &&proc) {\n            Timer timer;\n\
    \            proc();\n            return timer.elapsed<TimeUnit>();\n        }\n\
    \    private:\n        decltype(std::chrono::system_clock::now()) _start;\n  \
    \  };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_TIMER\n#define SUISEN_TIMER\n\n#include <chrono>\n\nnamespace\
    \ suisen {\n    struct Timer {\n        using minutes_t = std::chrono::minutes;\n\
    \        using seconds_t = std::chrono::seconds;\n        using milliseconds_t\
    \ = std::chrono::milliseconds;\n        using microseconds_t = std::chrono::microseconds;\n\
    \        using nanoseconds_t = std::chrono::nanoseconds;\n\n        Timer() {\
    \ start(); }\n\n        void start() {\n            _start = std::chrono::system_clock::now();\n\
    \        }\n        template <typename TimeUnit>\n        double elapsed() const\
    \ {\n            return std::chrono::duration_cast<TimeUnit>(std::chrono::system_clock::now()\
    \ - _start).count();\n        }\n\n        template <typename TimeUnit, typename\
    \ Proc>\n        static double measure(Proc &&proc) {\n            Timer timer;\n\
    \            proc();\n            return timer.elapsed<TimeUnit>();\n        }\n\
    \    private:\n        decltype(std::chrono::system_clock::now()) _start;\n  \
    \  };\n} // namespace suisen\n\n\n#endif // SUISEN_TIMER\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/timer.hpp
  requiredBy: []
  timestamp: '2022-05-28 20:11:45+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/timer.hpp
layout: document
title: Timer
---
## Timer