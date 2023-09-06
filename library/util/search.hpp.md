---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: ''
    links: []
  bundledCode: "#line 1 \"library/util/search.hpp\"\n#include <cassert>\n#include\
    \ <cstdint>\n#include <functional>\n#include <type_traits>\n\nnamespace suisen\
    \ {\n    enum class ternary_search_tag { Convex, Concave };\n\n    /**\n     *\
    \ @brief \n     * @tparam tag ternary_search_tag::Convex if f is convex, ternary_search_tag::Concave\
    \ if f is concave\n     * @param l min argument\n     * @param r max argument\n\
    \     * @param num number of loops determined by the required accuracy.\n    \
    \ * @param f convex/concave function\n     * @return argmin_{l<=x<=r} f(x) if\
    \ f is convex, argmax_{l<=x<=r} f(x) if f is concave\n     */\n    template <ternary_search_tag\
    \ tag, typename Arg, typename Fun,\n        std::enable_if_t<std::conjunction_v<std::is_invocable<Fun,\
    \ Arg>, std::is_floating_point<Arg>>, std::nullptr_t> = nullptr>\n    Arg ternary_search_key(Arg\
    \ l, Arg r, std::size_t num, const Fun &f) {\n        assert(l <= r);\n      \
    \  const auto compare = std::conditional_t<tag == ternary_search_tag::Convex,\
    \ std::greater<>, std::less<>>{};\n        while (num--) {\n            const\
    \ Arg ml = l + (r - l) / 3, mr = r - (r - l) / 3;\n            if (compare(f(ml),\
    \ f(mr))) l = ml;\n            else r = mr;\n        }\n        return l;\n  \
    \  }\n\n    /**\n     * @brief \n     * @tparam tag ternary_search_tag::Convex\
    \ if f is convex, ternary_search_tag::Concave if f is concave\n     * @param l\
    \ min argument\n     * @param r max argument\n     * @param f convex/concave function\n\
    \     * @return argmin_{l<=x<=r} f(x) if f is convex, argmax_{l<=x<=r} f(x) if\
    \ f is concave\n     */\n    template <ternary_search_tag tag, typename Arg, typename\
    \ Fun,\n        std::enable_if_t<std::conjunction_v<std::is_invocable<Fun, Arg>,\
    \ std::is_integral<Arg>>, std::nullptr_t> = nullptr>\n    Arg ternary_search_key(Arg\
    \ l, Arg r, const Fun &f) {\n        assert(l <= r);\n        const auto compare\
    \ = std::conditional_t<tag == ternary_search_tag::Convex, std::greater<>, std::less<>>{};\n\
    \        while (r - l >= 3) {\n            const Arg ml = l + (r - l) / 3, mr\
    \ = r - (r - l) / 3;\n            if (compare(f(ml), f(mr))) l = ml;\n       \
    \     else r = mr;\n        }\n        Arg x = l;\n        auto fx = f(x);\n \
    \       for (Arg y = l + 1; y <= r; ++y) {\n            if (auto fy = f(y); compare(fx,\
    \ fy)) x = y, fx = fy;\n        }\n        return x;\n    }\n\n    /**\n     *\
    \ @brief \n     * @tparam tag ternary_search_tag::Convex if f is convex, ternary_search_tag::Concave\
    \ if f is concave\n     * @param l min argument\n     * @param r max argument\n\
    \     * @param num number of loops determined by the required accuracy.\n    \
    \ * @param f convex/concave function\n     * @return min_{l<=x<=r} f(x) if f is\
    \ convex, max_{l<=x<=r} f(x) if f is concave\n     */\n    template <ternary_search_tag\
    \ tag, typename Arg, typename Fun,\n        std::enable_if_t<std::conjunction_v<std::is_invocable<Fun,\
    \ Arg>, std::is_floating_point<Arg>>, std::nullptr_t> = nullptr>\n    std::invoke_result_t<Fun,\
    \ Arg> ternary_search_value(const Arg &l, const Arg &r, const std::size_t &num,\
    \ const Fun &f) {\n        return f(ternary_search_key<tag>(l, r, num, f));\n\
    \    }\n\n    /**\n     * @brief \n     * @tparam tag ternary_search_tag::Convex\
    \ if f is convex, ternary_search_tag::Concave if f is concave\n     * @param l\
    \ min argument\n     * @param r max argument\n     * @param f convex/concave function\n\
    \     * @return min_{l<=x<=r} f(x) if f is convex, max_{l<=x<=r} f(x) if f is\
    \ concave\n     */\n    template <ternary_search_tag tag, typename Arg, typename\
    \ Fun,\n        std::enable_if_t<std::conjunction_v<std::is_invocable<Fun, Arg>,\
    \ std::is_integral<Arg>>, std::nullptr_t> = nullptr>\n    Arg ternary_search_value(Arg\
    \ l, Arg r, const Fun &f) {\n        return f(ternary_search_key<tag>(l, r, f));\n\
    \    }\n\n    /**\n     * @brief \n     * @param l_ng f(l_ng) must be false\n\
    \     * @param r_ok f(r_ok) must be true\n     * @param f non-decreasing predicate\
    \ function\n     * @return min x s.t. f(x) is true\n     */\n    template <typename\
    \ Arg, typename Fun,\n        std::enable_if_t<std::conjunction_v<std::is_invocable_r<bool,\
    \ Fun, Arg>, std::is_integral<Arg>>, std::nullptr_t> = nullptr>\n    Arg binary_search(Arg\
    \ l_ng, Arg r_ok, const Fun &f) {\n        assert(l_ng <= r_ok);\n        assert(not\
    \ f(l_ng));\n        assert(f(r_ok));\n        while ((r_ok - l_ng) > 1) {\n \
    \           Arg m = l_ng + ((r_ok - l_ng) >> 1);\n            (f(m) ? r_ok : l_ng)\
    \ = m;\n        }\n        return r_ok;\n    }\n\n    /**\n     * @brief \n  \
    \   * @param l_ng f(l_ng) must be false\n     * @param f non-decreasing predicate\
    \ function\n     * @return min x s.t. f(x) is true\n     */\n    template <typename\
    \ Arg, typename Fun,\n        std::enable_if_t<std::conjunction_v<std::is_invocable_r<bool,\
    \ Fun, Arg>, std::is_integral<Arg>>, std::nullptr_t> = nullptr>\n    Arg binary_search_exponential(Arg\
    \ l_ng, const Fun &f) {\n        assert(not f(l_ng));\n        Arg w = 1;\n  \
    \      while (not f(l_ng + w)) w <<= 1;\n        Arg r_ok = l_ng + w;\n      \
    \  while ((r_ok - l_ng) > 1) {\n            Arg m = l_ng + ((r_ok - l_ng) >> 1);\n\
    \            (f(m) ? r_ok : l_ng) = m;\n        }\n        return r_ok;\n    }\n\
    } // namespace suisen\n"
  code: "#include <cassert>\n#include <cstdint>\n#include <functional>\n#include <type_traits>\n\
    \nnamespace suisen {\n    enum class ternary_search_tag { Convex, Concave };\n\
    \n    /**\n     * @brief \n     * @tparam tag ternary_search_tag::Convex if f\
    \ is convex, ternary_search_tag::Concave if f is concave\n     * @param l min\
    \ argument\n     * @param r max argument\n     * @param num number of loops determined\
    \ by the required accuracy.\n     * @param f convex/concave function\n     * @return\
    \ argmin_{l<=x<=r} f(x) if f is convex, argmax_{l<=x<=r} f(x) if f is concave\n\
    \     */\n    template <ternary_search_tag tag, typename Arg, typename Fun,\n\
    \        std::enable_if_t<std::conjunction_v<std::is_invocable<Fun, Arg>, std::is_floating_point<Arg>>,\
    \ std::nullptr_t> = nullptr>\n    Arg ternary_search_key(Arg l, Arg r, std::size_t\
    \ num, const Fun &f) {\n        assert(l <= r);\n        const auto compare =\
    \ std::conditional_t<tag == ternary_search_tag::Convex, std::greater<>, std::less<>>{};\n\
    \        while (num--) {\n            const Arg ml = l + (r - l) / 3, mr = r -\
    \ (r - l) / 3;\n            if (compare(f(ml), f(mr))) l = ml;\n            else\
    \ r = mr;\n        }\n        return l;\n    }\n\n    /**\n     * @brief \n  \
    \   * @tparam tag ternary_search_tag::Convex if f is convex, ternary_search_tag::Concave\
    \ if f is concave\n     * @param l min argument\n     * @param r max argument\n\
    \     * @param f convex/concave function\n     * @return argmin_{l<=x<=r} f(x)\
    \ if f is convex, argmax_{l<=x<=r} f(x) if f is concave\n     */\n    template\
    \ <ternary_search_tag tag, typename Arg, typename Fun,\n        std::enable_if_t<std::conjunction_v<std::is_invocable<Fun,\
    \ Arg>, std::is_integral<Arg>>, std::nullptr_t> = nullptr>\n    Arg ternary_search_key(Arg\
    \ l, Arg r, const Fun &f) {\n        assert(l <= r);\n        const auto compare\
    \ = std::conditional_t<tag == ternary_search_tag::Convex, std::greater<>, std::less<>>{};\n\
    \        while (r - l >= 3) {\n            const Arg ml = l + (r - l) / 3, mr\
    \ = r - (r - l) / 3;\n            if (compare(f(ml), f(mr))) l = ml;\n       \
    \     else r = mr;\n        }\n        Arg x = l;\n        auto fx = f(x);\n \
    \       for (Arg y = l + 1; y <= r; ++y) {\n            if (auto fy = f(y); compare(fx,\
    \ fy)) x = y, fx = fy;\n        }\n        return x;\n    }\n\n    /**\n     *\
    \ @brief \n     * @tparam tag ternary_search_tag::Convex if f is convex, ternary_search_tag::Concave\
    \ if f is concave\n     * @param l min argument\n     * @param r max argument\n\
    \     * @param num number of loops determined by the required accuracy.\n    \
    \ * @param f convex/concave function\n     * @return min_{l<=x<=r} f(x) if f is\
    \ convex, max_{l<=x<=r} f(x) if f is concave\n     */\n    template <ternary_search_tag\
    \ tag, typename Arg, typename Fun,\n        std::enable_if_t<std::conjunction_v<std::is_invocable<Fun,\
    \ Arg>, std::is_floating_point<Arg>>, std::nullptr_t> = nullptr>\n    std::invoke_result_t<Fun,\
    \ Arg> ternary_search_value(const Arg &l, const Arg &r, const std::size_t &num,\
    \ const Fun &f) {\n        return f(ternary_search_key<tag>(l, r, num, f));\n\
    \    }\n\n    /**\n     * @brief \n     * @tparam tag ternary_search_tag::Convex\
    \ if f is convex, ternary_search_tag::Concave if f is concave\n     * @param l\
    \ min argument\n     * @param r max argument\n     * @param f convex/concave function\n\
    \     * @return min_{l<=x<=r} f(x) if f is convex, max_{l<=x<=r} f(x) if f is\
    \ concave\n     */\n    template <ternary_search_tag tag, typename Arg, typename\
    \ Fun,\n        std::enable_if_t<std::conjunction_v<std::is_invocable<Fun, Arg>,\
    \ std::is_integral<Arg>>, std::nullptr_t> = nullptr>\n    Arg ternary_search_value(Arg\
    \ l, Arg r, const Fun &f) {\n        return f(ternary_search_key<tag>(l, r, f));\n\
    \    }\n\n    /**\n     * @brief \n     * @param l_ng f(l_ng) must be false\n\
    \     * @param r_ok f(r_ok) must be true\n     * @param f non-decreasing predicate\
    \ function\n     * @return min x s.t. f(x) is true\n     */\n    template <typename\
    \ Arg, typename Fun,\n        std::enable_if_t<std::conjunction_v<std::is_invocable_r<bool,\
    \ Fun, Arg>, std::is_integral<Arg>>, std::nullptr_t> = nullptr>\n    Arg binary_search(Arg\
    \ l_ng, Arg r_ok, const Fun &f) {\n        assert(l_ng <= r_ok);\n        assert(not\
    \ f(l_ng));\n        assert(f(r_ok));\n        while ((r_ok - l_ng) > 1) {\n \
    \           Arg m = l_ng + ((r_ok - l_ng) >> 1);\n            (f(m) ? r_ok : l_ng)\
    \ = m;\n        }\n        return r_ok;\n    }\n\n    /**\n     * @brief \n  \
    \   * @param l_ng f(l_ng) must be false\n     * @param f non-decreasing predicate\
    \ function\n     * @return min x s.t. f(x) is true\n     */\n    template <typename\
    \ Arg, typename Fun,\n        std::enable_if_t<std::conjunction_v<std::is_invocable_r<bool,\
    \ Fun, Arg>, std::is_integral<Arg>>, std::nullptr_t> = nullptr>\n    Arg binary_search_exponential(Arg\
    \ l_ng, const Fun &f) {\n        assert(not f(l_ng));\n        Arg w = 1;\n  \
    \      while (not f(l_ng + w)) w <<= 1;\n        Arg r_ok = l_ng + w;\n      \
    \  while ((r_ok - l_ng) > 1) {\n            Arg m = l_ng + ((r_ok - l_ng) >> 1);\n\
    \            (f(m) ? r_ok : l_ng) = m;\n        }\n        return r_ok;\n    }\n\
    } // namespace suisen\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/search.hpp
  requiredBy: []
  timestamp: '2023-09-06 20:34:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/search.hpp
layout: document
redirect_from:
- /library/library/util/search.hpp
- /library/library/util/search.hpp.html
title: ''
---
