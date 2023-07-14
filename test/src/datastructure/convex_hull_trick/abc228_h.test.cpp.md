---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/datastructure/convex_hull_trick.hpp
    title: "Convex Hull Trick (\u50BE\u304D\u304C\u5358\u8ABF\u3068\u306F\u9650\u3089\
      \u306A\u3044\u5834\u5408)"
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc228/tasks/abc228_h
    links:
    - https://atcoder.jp/contests/abc228/tasks/abc228_h
  bundledCode: "#line 1 \"test/src/datastructure/convex_hull_trick/abc228_h.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc228/tasks/abc228_h\"\n\n#include\
    \ <algorithm>\n#include <iostream>\n#include <vector>\n\n#line 1 \"library/datastructure/convex_hull_trick.hpp\"\
    \n\n\n\n#include <cassert>\n#include <limits>\n#include <set>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#line 5 \"library/type_traits/type_traits.hpp\"\n#include <type_traits>\n\
    \nnamespace suisen {\ntemplate <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\ntemplate <bool cond_v, typename Then, typename OrElse>\nconstexpr\
    \ decltype(auto) constexpr_if(Then&& then, OrElse&& or_else) {\n    if constexpr\
    \ (cond_v) return std::forward<Then>(then);\n    else return std::forward<OrElse>(or_else);\n\
    }\n\n// ! function\ntemplate <typename ReturnType, typename Callable, typename\
    \ ...Args>\nusing is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable,\
    \ Args...>, ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op =\
    \ is_same_as_invoke_result<T, F, T>;\ntemplate <typename F, typename T>\nusing\
    \ is_bin_op = is_same_as_invoke_result<T, F, T, T>;\n\ntemplate <typename Comparator,\
    \ typename T>\nusing is_comparator = std::is_same<std::invoke_result_t<Comparator,\
    \ T, T>, bool>;\n\n// ! integral\ntemplate <typename T, typename = constraints_t<std::is_integral<T>>>\n\
    constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\n\
    template <typename T, size_t n> struct is_nbit { static constexpr bool value =\
    \ bit_num<T> == n; };\ntemplate <typename T, size_t n> static constexpr bool is_nbit_v\
    \ = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T> struct safely_multipliable\
    \ {};\ntemplate <> struct safely_multipliable<int> { using type = long long; };\n\
    template <> struct safely_multipliable<long long> { using type = __int128_t; };\n\
    template <> struct safely_multipliable<unsigned int> { using type = unsigned long\
    \ long; };\ntemplate <> struct safely_multipliable<unsigned long int> { using\
    \ type = __uint128_t; };\ntemplate <> struct safely_multipliable<unsigned long\
    \ long> { using type = __uint128_t; };\ntemplate <> struct safely_multipliable<float>\
    \ { using type = float; };\ntemplate <> struct safely_multipliable<double> { using\
    \ type = double; };\ntemplate <> struct safely_multipliable<long double> { using\
    \ type = long double; };\ntemplate <typename T> using safely_multipliable_t =\
    \ typename safely_multipliable<T>::type;\n\ntemplate <typename T, typename = void>\
    \ struct rec_value_type { using type = T; };\ntemplate <typename T> struct rec_value_type<T,\
    \ std::void_t<typename T::value_type>> {\n    using type = typename rec_value_type<typename\
    \ T::value_type>::type;\n};\ntemplate <typename T> using rec_value_type_t = typename\
    \ rec_value_type<T>::type;\n\ntemplate <typename T> class is_iterable {\n    template\
    \ <typename T_>\n    static auto test(T_ e) -> decltype(e.begin(), e.end(), std::true_type{});\n\
    \    static std::false_type test(...);\npublic:\n    static constexpr bool value\
    \ = decltype(test(std::declval<T>()))::value;\n};\ntemplate <typename T> static\
    \ constexpr bool is_iterable_v = is_iterable<T>::value;\n\ntemplate <typename\
    \ T> class is_writable {\n    template <typename T_>\n    static auto test(T_\
    \ e) -> decltype(std::declval<std::ostream&>() << e, std::true_type{});\n    static\
    \ std::false_type test(...);\npublic:\n    static constexpr bool value = decltype(test(std::declval<T>()))::value;\n\
    };\ntemplate <typename T> static constexpr bool is_writable_v = is_writable<T>::value;\n\
    \ntemplate <typename T> class is_readable {\n    template <typename T_>\n    static\
    \ auto test(T_ e) -> decltype(std::declval<std::istream&>() >> e, std::true_type{});\n\
    \    static std::false_type test(...);\npublic:\n    static constexpr bool value\
    \ = decltype(test(std::declval<T>()))::value;\n};\ntemplate <typename T> static\
    \ constexpr bool is_readable_v = is_readable<T>::value;\n} // namespace suisen\n\
    \n\n#line 9 \"library/datastructure/convex_hull_trick.hpp\"\n\nnamespace suisen\
    \ {\n    namespace internal::convex_hull_trick {\n        template <typename T>\n\
    \        struct Line {\n            // f(x)=ax+b,m=max{x|f=argmin_{f' in S}{f'(x)}}\n\
    \            mutable T a, b, m;\n            Line(const T& a, const T& b, const\
    \ T& m) : a(a), b(b), m(m) {}\n            bool operator<(const Line<T>& rhs)\
    \ const { return a < rhs.a; }\n            bool operator<(const T& x) const {\
    \ return not (m < x); }\n        };\n\n        template <typename T, std::enable_if_t<std::is_integral<T>::value,\
    \ std::nullptr_t> = nullptr>\n        inline T div(const T& num, const T& den)\
    \ {\n            return num / den - ((num ^ den) < 0 and num % den);\n       \
    \ }\n        template <typename T, std::enable_if_t<std::negation<std::is_integral<T>>::value,\
    \ std::nullptr_t> = nullptr>\n        inline T div(const T& num, const T& den)\
    \ {\n            return num / den;\n        }\n    }\n\n    template <typename\
    \ T, bool is_min_query = true>\n    class ConvexHullTrick : std::multiset<internal::convex_hull_trick::Line<T>,\
    \ std::less<>> {\n        using iterator = typename std::multiset<internal::convex_hull_trick::Line<T>>::iterator;\n\
    \        using MultT = safely_multipliable_t<T>;\n        using Line = internal::convex_hull_trick::Line<T>;\n\
    \n        static constexpr T inf = std::numeric_limits<T>::max();\n    public:\n\
    \        bool has_line() const {\n            return not this->empty();\n    \
    \    }\n\n        void add_line(T slope, T intercept) {\n            if constexpr\
    \ (not is_min_query) slope = -slope, intercept = -intercept;\n            auto\
    \ it = this->emplace(slope, intercept, inf);\n            auto itl = it;\n   \
    \         for (; itl != this->begin();) {\n                if (update_intersec_right(--itl,\
    \ it)) {\n                    ++itl;\n                    break;\n           \
    \     }\n            }\n            auto itm = this->erase(itl, it), itr = std::next(itm);\n\
    \            if (not update_intersec_right(itm, itr)) {\n                update_intersec_right(--itm,\
    \ itr);\n            }\n            for (it = itm; itr != this->end();) {\n  \
    \              itm = itr++;\n                if (itr != this->end() and itm->m\
    \ <= itr->m) {\n                    update_intersec_right(it, itr);\n        \
    \        } else {\n                    break;\n                }\n           \
    \ }\n            if (it != itm) this->erase(std::next(it), itm);\n        }\n\n\
    \        MultT query(T x) {\n            assert(not this->empty());\n        \
    \    const iterator l = --(this-> template lower_bound<T>(x));\n            auto\
    \ res = (MultT) l->a * x + l->b;\n            if constexpr (is_min_query) {\n\
    \                return res;\n            } else {\n                return -res;\n\
    \            }\n        }\n    private:\n        // updates r->m and returns whether\
    \ l is necessary or not.\n        bool update_intersec_right(iterator l, iterator\
    \ r) {\n            if (r == this->end()) return true;\n            if (l->a ==\
    \ r->a) {\n                r->m = r->b <= l->b ? inf : -inf;\n            } else\
    \ {\n                r->m = internal::convex_hull_trick::div(r->b - l->b, l->a\
    \ - r->a);\n            }\n            return l->m > r->m;\n        }\n    };\n\
    \    template <typename T>\n    using MinCHT = ConvexHullTrick<T, /* is_min_query\
    \ = */ true>;\n    template <typename T>\n    using MaxCHT = ConvexHullTrick<T,\
    \ /* is_min_query = */ false>;\n} // namespace suisen\n\n\n#line 8 \"test/src/datastructure/convex_hull_trick/abc228_h.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, x;\n    std::cin >> n >> x;\n\n    std::vector<std::pair<long long,\
    \ long long>> ps(n);\n    for (auto &[a, c] : ps) std::cin >> a >> c;\n    std::sort(ps.begin(),\
    \ ps.end());\n\n    suisen::ConvexHullTrick<long long> cht;\n    \n    long long\
    \ ans = 0;\n    long long s = 0, t = 0;\n    cht.add_line(-s, t);\n    for (const\
    \ auto &[a, c] : ps) {\n        s += c, t += a * c;\n        ans = cht.query(a)\
    \ + x + a * s - t;\n        cht.add_line(-s, ans + t);\n    }\n\n    std::cout\
    \ << ans << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc228/tasks/abc228_h\"\n\n\
    #include <algorithm>\n#include <iostream>\n#include <vector>\n\n#include \"library/datastructure/convex_hull_trick.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, x;\n    std::cin >> n >> x;\n\n    std::vector<std::pair<long long,\
    \ long long>> ps(n);\n    for (auto &[a, c] : ps) std::cin >> a >> c;\n    std::sort(ps.begin(),\
    \ ps.end());\n\n    suisen::ConvexHullTrick<long long> cht;\n    \n    long long\
    \ ans = 0;\n    long long s = 0, t = 0;\n    cht.add_line(-s, t);\n    for (const\
    \ auto &[a, c] : ps) {\n        s += c, t += a * c;\n        ans = cht.query(a)\
    \ + x + a * s - t;\n        cht.add_line(-s, ans + t);\n    }\n\n    std::cout\
    \ << ans << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/datastructure/convex_hull_trick.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/datastructure/convex_hull_trick/abc228_h.test.cpp
  requiredBy: []
  timestamp: '2023-07-13 15:42:30+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/datastructure/convex_hull_trick/abc228_h.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/convex_hull_trick/abc228_h.test.cpp
- /verify/test/src/datastructure/convex_hull_trick/abc228_h.test.cpp.html
title: test/src/datastructure/convex_hull_trick/abc228_h.test.cpp
---
