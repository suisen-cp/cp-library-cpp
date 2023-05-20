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
  bundledCode: "#line 1 \"library/math/factorial_embeded.hpp\"\n\n\n\n#include <iostream>\n\
    #include <limits>\n\nnamespace suisen {\n    // write (iB)! for i=0,1,...,(MOD-1)/B\n\
    \    template <int MOD, int B>\n    void write_embeded_factorial(std::ostream&\
    \ out) {\n        constexpr int D = (MOD - 1) / B + 1;\n\n        out << \"namespace\
    \ suisen::internal::factorial_embeded {\" << '\\n';\n        out << \"    static\
    \ constexpr int MOD = \" << MOD << \";\" << '\\n';\n        out << \"    static\
    \ constexpr int B = \" << B << \";\" << '\\n';\n        out << \"    static constexpr\
    \ int D = \" << D << \";\" << '\\n';\n        out << \"    static constexpr int\
    \ F[D]{\" << '\\n';\n        out << \"        \";\n        long long f = 1;\n\
    \        for (int i = 0; i < D; ++i) {\n            out << f << \",\";\n     \
    \       if (i == D - 1) break;\n            const int l = i * B + 1, r = (i +\
    \ 1) * B;\n            for (int j = l; j <= r; ++j) f = f * j % MOD;\n       \
    \ }\n        out << '\\n';\n        out << \"    };\" << '\\n';\n        out <<\
    \ \"    constexpr int factorial_embeded(long long n) {\" << '\\n';\n        out\
    \ << \"        if (n >= MOD) return 0;\" << '\\n';\n        out << \"        int\
    \ q = n / B;\" << '\\n';\n        out << \"        long long ans = F[q];\" <<\
    \ '\\n';\n        out << \"        for (long long i = q * B + 1; i <= n; ++i)\
    \ {\" << '\\n';\n        out << \"            ans = ans * i % MOD;\" << '\\n';\n\
    \        out << \"        }\" << '\\n';\n        out << \"        return ans;\"\
    \ << '\\n';\n        out << \"    }\" << '\\n';\n        out << \"}\" << '\\n';\n\
    \        out << \"using suisen::internal::factorial_embeded::factorial_embeded;\"\
    \ << '\\n';\n        out.flush();\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_FACTORIAL_EMBEDED\n#define SUISEN_FACTORIAL_EMBEDED\n\n#include\
    \ <iostream>\n#include <limits>\n\nnamespace suisen {\n    // write (iB)! for\
    \ i=0,1,...,(MOD-1)/B\n    template <int MOD, int B>\n    void write_embeded_factorial(std::ostream&\
    \ out) {\n        constexpr int D = (MOD - 1) / B + 1;\n\n        out << \"namespace\
    \ suisen::internal::factorial_embeded {\" << '\\n';\n        out << \"    static\
    \ constexpr int MOD = \" << MOD << \";\" << '\\n';\n        out << \"    static\
    \ constexpr int B = \" << B << \";\" << '\\n';\n        out << \"    static constexpr\
    \ int D = \" << D << \";\" << '\\n';\n        out << \"    static constexpr int\
    \ F[D]{\" << '\\n';\n        out << \"        \";\n        long long f = 1;\n\
    \        for (int i = 0; i < D; ++i) {\n            out << f << \",\";\n     \
    \       if (i == D - 1) break;\n            const int l = i * B + 1, r = (i +\
    \ 1) * B;\n            for (int j = l; j <= r; ++j) f = f * j % MOD;\n       \
    \ }\n        out << '\\n';\n        out << \"    };\" << '\\n';\n        out <<\
    \ \"    constexpr int factorial_embeded(long long n) {\" << '\\n';\n        out\
    \ << \"        if (n >= MOD) return 0;\" << '\\n';\n        out << \"        int\
    \ q = n / B;\" << '\\n';\n        out << \"        long long ans = F[q];\" <<\
    \ '\\n';\n        out << \"        for (long long i = q * B + 1; i <= n; ++i)\
    \ {\" << '\\n';\n        out << \"            ans = ans * i % MOD;\" << '\\n';\n\
    \        out << \"        }\" << '\\n';\n        out << \"        return ans;\"\
    \ << '\\n';\n        out << \"    }\" << '\\n';\n        out << \"}\" << '\\n';\n\
    \        out << \"using suisen::internal::factorial_embeded::factorial_embeded;\"\
    \ << '\\n';\n        out.flush();\n    }\n} // namespace suisen\n\n\n#endif //\
    \ SUISEN_FACTORIAL_EMBEDED\n"
  dependsOn: []
  isVerificationFile: false
  path: library/math/factorial_embeded.hpp
  requiredBy: []
  timestamp: '2023-05-11 13:32:58+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/math/factorial_embeded.hpp
layout: document
title: Factorial Embeded
---
## Factorial Embeded
