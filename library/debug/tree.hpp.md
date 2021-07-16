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
  bundledCode: "#line 1 \"library/debug/tree.hpp\"\n#include <functional>\n#include\
    \ <string>\n\nnamespace suisen {\nnamespace debug {\n    namespace internal {\n\
    \        namespace tree {\n            template <typename E>\n            std::string\
    \ edge_to_str(const E edge) {\n                return \"+-[\" + std::to_string(edge)\
    \ + \"]- \";\n            }\n            template <>\n            std::string\
    \ edge_to_str<std::string>(const std::string edge) {\n                return std::string(\"\
    +-[\") + edge + std::string(\"]- \");\n            }\n            template <>\n\
    \            std::string edge_to_str<char>(const char edge) {\n              \
    \  return std::string(\"+-[\") + edge + std::string(\"]- \");\n            }\n\
    \            template <>\n            std::string edge_to_str<nullptr_t>(nullptr_t)\
    \ {\n                return \"+-- \";\n            }\n            template <typename\
    \ E>\n            std::string leaf_to_str(const E edge) {\n                return\
    \ \"(\" + std::to_string(edge) + \")\";\n            }\n            template <>\n\
    \            std::string leaf_to_str<char>(const char edge) {\n              \
    \  return std::string(\"(\") + edge + std::string(\")\");\n            }\n   \
    \         template <>\n            std::string leaf_to_str<std::string>(const\
    \ std::string edge) {\n                return std::string(\"(\") + edge + std::string(\"\
    )\");\n            }\n            template <>\n            std::string leaf_to_str<nullptr_t>(const\
    \ nullptr_t) {\n                return \"\";\n            }\n\n            template\
    \ <typename node_t, typename node_info_t, typename edge_info_t, typename leaf_info_t>\n\
    \            std::string tree_to_string(\n                const node_t root,\n\
    \                const leaf_info_t cum_info,\n                const std::function<std::vector<std::pair<edge_info_t,\
    \ node_t>>(node_t)> children_getter,\n                const std::function<leaf_info_t(leaf_info_t,\
    \ edge_info_t)> accumulator,\n                const std::function<node_info_t(node_t)>\
    \ node_info_getter,\n                const std::string &prefix = \"\"\n      \
    \      ) {\n                auto chs = children_getter(root);\n              \
    \  auto res = std::to_string(node_info_getter(root)) + ' ';\n                if\
    \ (chs.size() == 0) {\n                    return res + tree::leaf_to_str(cum_info)\
    \ + \"\\n\";\n                }\n                auto rec = [&](const node_t next_root,\
    \ const leaf_info_t next_cum_info, const std::string &next_prefix) {\n       \
    \             return tree_to_string<node_t, node_info_t, edge_info_t, leaf_info_t>(\n\
    \                        next_root, next_cum_info, children_getter, accumulator,\
    \ node_info_getter, next_prefix\n                    );\n                };\n\
    \                auto indent = prefix + std::string(res.size(), ' ');\n      \
    \          int sz = chs.size();\n                for (int i = 0; i < sz; ++i)\
    \ {\n                    auto [edge_info, next_root] = chs[i];\n             \
    \       auto edge_str = tree::edge_to_str(edge_info);\n                    auto\
    \ next_prefix = indent + std::string(edge_str.size(), ' ');\n                \
    \    if (i + 1 < sz) next_prefix[indent.size()] = '|';\n                    if\
    \ (i == 0) {\n                        res += edge_str + rec(next_root, accumulator(cum_info,\
    \ edge_info), next_prefix);\n                    } else {\n                  \
    \      res += indent + \"|\\n\";\n                        res += indent + edge_str\
    \ + rec(next_root, accumulator(cum_info, edge_info), next_prefix);\n         \
    \           }\n                }\n                return res;\n            }\n\
    \n            template <typename node_t, typename node_info_t, typename edge_info_t>\n\
    \            std::string tree_to_string(\n                const node_t root,\n\
    \                const std::function<std::vector<std::pair<edge_info_t, node_t>>(node_t)>\
    \ children_getter,\n                const std::function<node_info_t(node_t)> node_info_getter\n\
    \            ) {\n                auto accumulator = [](nullptr_t, edge_info_t)\
    \ -> nullptr_t {\n                    return nullptr;\n                };\n  \
    \              return tree_to_string<node_t, node_info_t, edge_info_t, nullptr_t>(\n\
    \                    root, nullptr, children_getter, accumulator, node_info_getter\n\
    \                );\n            }\n\n            template <typename node_t, typename\
    \ node_info_t>\n            std::string tree_to_string(\n                const\
    \ node_t root,\n                const std::function<std::vector<node_t>(node_t)>\
    \ children_getter,\n                const std::function<node_info_t(node_t)> node_info_getter\n\
    \            ) {\n                auto cg = [&](node_t node) -> std::vector<std::pair<nullptr_t,\
    \ node_t>> {\n                    auto chs = children_getter(node);\n        \
    \            int sz = chs.size();\n                    std::vector<std::pair<nullptr_t,\
    \ node_t>> res(sz);\n                    for (int i = 0; i < sz; ++i) res[i] =\
    \ {nullptr, chs[i]};\n                    return res;\n                };\n  \
    \              return tree_to_string<node_t, node_info_t, nullptr_t>(root, cg,\
    \ node_info_getter);\n            }\n        }\n    }\n\n    /**\n     * template\
    \ args:\n     * - node_t: \u9802\u70B9\u306E\u578B\n     * - node_info_t: \u9802\
    \u70B9\u60C5\u5831\u306E\u578B\n     * - edge_info_t: \u8FBA\u60C5\u5831\u306E\
    \u578B\n     * - leaf_info_t: \u6839\u304B\u3089\u8FBA\u60C5\u5831\u3092\u7D2F\
    \u7A4D\u3057\u3066\u3067\u304D\u308B\u8449\u306E\u5024\u306E\u578B (\u4F8B\u3048\
    \u3070 Trie \u6728\u3067\u306F\uFF0C\u6839\u304B\u3089\u8449\u3078\u306E\u30D1\
    \u30B9\u4E0A\u306B\u3042\u308B\u8FBA\u306E\u6587\u5B57\u3092\u7D2F\u7A4D\u3057\
    \u3066\u6587\u5B57\u5217\u3092\u4F5C\u308B)\n     * \n     * args:\n     * - node_t\
    \ root: \u6839\n     * - init: \u7D2F\u7A4D\u3059\u308B\u8FBA\u60C5\u5831\u306E\
    \u521D\u671F\u5024\n     * - std::function<std::vector<std::pair<edge_info_t,\
    \ node_t>>(node_t)> children_getter: \u9802\u70B9\u3092\u5F15\u6570\u306B\u3068\
    \u3063\u3066(\u8FBA\u60C5\u5831, \u5B50\u9802\u70B9)\u306E\u30EA\u30B9\u30C8\u3092\
    \u8FD4\u3059\u95A2\u6570\n     * - std::function<leaf_info_t(leaf_info_t, edge_info_t)>\
    \ accumulator: \u8FBA\u60C5\u5831\u3092\u7D2F\u7A4D\u3059\u308B\u95A2\u6570\uFF0E\
    (\u73FE\u5728\u306E\u7D2F\u7A4D\u5024, \u8FBA\u60C5\u5831) -> \u5B50\u306E\u7D2F\
    \u7A4D\u5024\n     * - std::function<node_info_t(node_t)> node_info_getter: \u9802\
    \u70B9\u3092\u5F15\u6570\u306B\u3068\u3063\u3066\u9802\u70B9\u60C5\u5831\u3092\
    \u8FD4\u3059\u95A2\u6570\n     */\n    template <typename node_t, typename node_info_t,\
    \ typename edge_info_t, typename leaf_info_t = edge_info_t>\n    std::string tree_to_string(\n\
    \        const node_t root,\n        const leaf_info_t init,\n        const std::function<std::vector<std::pair<edge_info_t,\
    \ node_t>>(node_t)> children_getter,\n        const std::function<leaf_info_t(leaf_info_t,\
    \ edge_info_t)> accumulator,\n        const std::function<node_info_t(node_t)>\
    \ node_info_getter\n    ) { return internal::tree::tree_to_string<>(root, init,\
    \ children_getter, accumulator, node_info_getter); }\n\n    /**\n     * template\
    \ args:\n     * - node_t: \u9802\u70B9\u306E\u578B\n     * - node_info_t: \u9802\
    \u70B9\u60C5\u5831\u306E\u578B\n     * - edge_info_t: \u8FBA\u60C5\u5831\u306E\
    \u578B\n     * \n     * args:\n     * - node_t root: \u6839\n     * - std::function<std::vector<std::pair<edge_info_t,\
    \ node_t>>(node_t)> children_getter: \u9802\u70B9\u3092\u5F15\u6570\u306B\u3068\
    \u3063\u3066(\u8FBA\u60C5\u5831, \u5B50\u9802\u70B9)\u306E\u30EA\u30B9\u30C8\u3092\
    \u8FD4\u3059\u95A2\u6570\n     * - std::function<node_info_t(node_t)> node_info_getter:\
    \ \u9802\u70B9\u3092\u5F15\u6570\u306B\u3068\u3063\u3066\u9802\u70B9\u60C5\u5831\
    \u3092\u8FD4\u3059\u95A2\u6570\n     */\n    template <typename node_t, typename\
    \ node_info_t, typename edge_info_t>\n    std::string tree_to_string(\n      \
    \  const node_t root,\n        const std::function<std::vector<std::pair<edge_info_t,\
    \ node_t>>(node_t)> children_getter,\n        const std::function<node_info_t(node_t)>\
    \ node_info_getter\n    ) { return internal::tree::tree_to_string<>(root, children_getter,\
    \ node_info_getter); }\n\n    /**\n     * template args:\n     * - node_t: \u9802\
    \u70B9\u306E\u578B\n     * - node_info_t: \u9802\u70B9\u60C5\u5831\u306E\u578B\
    \n     * \n     * args:\n     * - node_t root: \u6839\n     * - std::function<std::vector<node_t>(node_t)>\
    \ children_getter: \u9802\u70B9\u3092\u5F15\u6570\u306B\u3068\u3063\u3066\u5B50\
    \u9802\u70B9\u306E\u30EA\u30B9\u30C8\u3092\u8FD4\u3059\u95A2\u6570\n     * - std::function<node_info_t(node_t)>\
    \ node_info_getter: \u9802\u70B9\u3092\u5F15\u6570\u306B\u3068\u3063\u3066\u9802\
    \u70B9\u60C5\u5831\u3092\u8FD4\u3059\u95A2\u6570\n     */\n    template <typename\
    \ node_t, typename node_info_t = node_t>\n    std::string tree_to_string(\n  \
    \      const node_t root,\n        const std::function<std::vector<node_t>(node_t)>\
    \ children_getter,\n        const std::function<node_info_t(node_t)> node_info_getter\n\
    \    ) { return internal::tree::tree_to_string<>(root, children_getter, node_info_getter);\
    \ }\n\n    /**\n     * \u6728\u304C vector<vector<pair<\u8FBA\u60C5\u5831\u306E\
    \u578B, \u9802\u70B9\u306E\u578B>>> \u3067\u8868\u73FE\u3055\u308C\u3066\u3044\
    \u308B\u5834\u5408\u306B\u7279\u6B8A\u5316\u3057\u305F\u3084\u3064\u3067\uFF0C\
    \n     * \u306A\u304A\u304B\u3064\u8449\u304C\u6839\u304B\u3089\u306E\u30D1\u30B9\
    \u4E0A\u306E\u8FBA\u60C5\u5831\u3092\u7D2F\u7A4D\u3057\u305F\u5024\u3092\u6301\
    \u3064\u5834\u5408\n     */\n    template <typename node_t, typename edge_info_t,\
    \ typename leaf_info_t = edge_info_t>\n    std::string tree_to_string(\n     \
    \   const node_t root,\n        const leaf_info_t init,\n        const std::function<leaf_info_t(leaf_info_t,\
    \ edge_info_t)> accumulator,\n        const std::vector<std::vector<std::pair<edge_info_t,\
    \ node_t>>> &g\n    ) {\n        auto children_getter = [&](node_t node) { return\
    \ g[node]; };\n        auto node_info_getter = [&](node_t node) { return node;\
    \ };\n        return tree_to_string<node_t, node_t, edge_info_t, leaf_info_t>(root,\
    \ init, children_getter, accumulator, node_info_getter);\n    }\n\n    /**\n \
    \    * \u6728\u304C vector<vector<pair<\u8FBA\u60C5\u5831\u306E\u578B, \u9802\u70B9\
    \u306E\u578B>>> \u3067\u8868\u73FE\u3055\u308C\u3066\u3044\u308B\u5834\u5408\u306B\
    \u7279\u6B8A\u5316\u3057\u305F\u3084\u3064\n     */\n    template <typename node_t,\
    \ typename edge_info_t>\n    std::string tree_to_string(const node_t root, const\
    \ std::vector<std::vector<std::pair<edge_info_t, node_t>>> &g) {\n        auto\
    \ children_getter = [&](node_t node) { return g[node]; };\n        auto node_info_getter\
    \ = [&](node_t node) { return node; };\n        return tree_to_string<node_t,\
    \ node_t, edge_info_t>(root, children_getter, node_info_getter);\n    }\n\n  \
    \  /**\n     * \u6728\u304C vector<vector<\u9802\u70B9\u306E\u578B>> \u3067\u8868\
    \u73FE\u3055\u308C\u3066\u3044\u308B\u5834\u5408\u306B\u7279\u6B8A\u5316\u3057\
    \u305F\u3084\u3064\n     */\n    template <typename node_t>\n    std::string tree_to_string(const\
    \ node_t root, const std::vector<std::vector<node_t>> &g) {\n        auto children_getter\
    \ = [&](node_t node) { return g[node]; };\n        auto node_info_getter = [&](node_t\
    \ node) { return node; };\n        return tree_to_string<node_t, node_t>(root,\
    \ children_getter, node_info_getter);\n    }\n}\n} // namespace suisen\n\n"
  code: "#include <functional>\n#include <string>\n\nnamespace suisen {\nnamespace\
    \ debug {\n    namespace internal {\n        namespace tree {\n            template\
    \ <typename E>\n            std::string edge_to_str(const E edge) {\n        \
    \        return \"+-[\" + std::to_string(edge) + \"]- \";\n            }\n   \
    \         template <>\n            std::string edge_to_str<std::string>(const\
    \ std::string edge) {\n                return std::string(\"+-[\") + edge + std::string(\"\
    ]- \");\n            }\n            template <>\n            std::string edge_to_str<char>(const\
    \ char edge) {\n                return std::string(\"+-[\") + edge + std::string(\"\
    ]- \");\n            }\n            template <>\n            std::string edge_to_str<nullptr_t>(nullptr_t)\
    \ {\n                return \"+-- \";\n            }\n            template <typename\
    \ E>\n            std::string leaf_to_str(const E edge) {\n                return\
    \ \"(\" + std::to_string(edge) + \")\";\n            }\n            template <>\n\
    \            std::string leaf_to_str<char>(const char edge) {\n              \
    \  return std::string(\"(\") + edge + std::string(\")\");\n            }\n   \
    \         template <>\n            std::string leaf_to_str<std::string>(const\
    \ std::string edge) {\n                return std::string(\"(\") + edge + std::string(\"\
    )\");\n            }\n            template <>\n            std::string leaf_to_str<nullptr_t>(const\
    \ nullptr_t) {\n                return \"\";\n            }\n\n            template\
    \ <typename node_t, typename node_info_t, typename edge_info_t, typename leaf_info_t>\n\
    \            std::string tree_to_string(\n                const node_t root,\n\
    \                const leaf_info_t cum_info,\n                const std::function<std::vector<std::pair<edge_info_t,\
    \ node_t>>(node_t)> children_getter,\n                const std::function<leaf_info_t(leaf_info_t,\
    \ edge_info_t)> accumulator,\n                const std::function<node_info_t(node_t)>\
    \ node_info_getter,\n                const std::string &prefix = \"\"\n      \
    \      ) {\n                auto chs = children_getter(root);\n              \
    \  auto res = std::to_string(node_info_getter(root)) + ' ';\n                if\
    \ (chs.size() == 0) {\n                    return res + tree::leaf_to_str(cum_info)\
    \ + \"\\n\";\n                }\n                auto rec = [&](const node_t next_root,\
    \ const leaf_info_t next_cum_info, const std::string &next_prefix) {\n       \
    \             return tree_to_string<node_t, node_info_t, edge_info_t, leaf_info_t>(\n\
    \                        next_root, next_cum_info, children_getter, accumulator,\
    \ node_info_getter, next_prefix\n                    );\n                };\n\
    \                auto indent = prefix + std::string(res.size(), ' ');\n      \
    \          int sz = chs.size();\n                for (int i = 0; i < sz; ++i)\
    \ {\n                    auto [edge_info, next_root] = chs[i];\n             \
    \       auto edge_str = tree::edge_to_str(edge_info);\n                    auto\
    \ next_prefix = indent + std::string(edge_str.size(), ' ');\n                \
    \    if (i + 1 < sz) next_prefix[indent.size()] = '|';\n                    if\
    \ (i == 0) {\n                        res += edge_str + rec(next_root, accumulator(cum_info,\
    \ edge_info), next_prefix);\n                    } else {\n                  \
    \      res += indent + \"|\\n\";\n                        res += indent + edge_str\
    \ + rec(next_root, accumulator(cum_info, edge_info), next_prefix);\n         \
    \           }\n                }\n                return res;\n            }\n\
    \n            template <typename node_t, typename node_info_t, typename edge_info_t>\n\
    \            std::string tree_to_string(\n                const node_t root,\n\
    \                const std::function<std::vector<std::pair<edge_info_t, node_t>>(node_t)>\
    \ children_getter,\n                const std::function<node_info_t(node_t)> node_info_getter\n\
    \            ) {\n                auto accumulator = [](nullptr_t, edge_info_t)\
    \ -> nullptr_t {\n                    return nullptr;\n                };\n  \
    \              return tree_to_string<node_t, node_info_t, edge_info_t, nullptr_t>(\n\
    \                    root, nullptr, children_getter, accumulator, node_info_getter\n\
    \                );\n            }\n\n            template <typename node_t, typename\
    \ node_info_t>\n            std::string tree_to_string(\n                const\
    \ node_t root,\n                const std::function<std::vector<node_t>(node_t)>\
    \ children_getter,\n                const std::function<node_info_t(node_t)> node_info_getter\n\
    \            ) {\n                auto cg = [&](node_t node) -> std::vector<std::pair<nullptr_t,\
    \ node_t>> {\n                    auto chs = children_getter(node);\n        \
    \            int sz = chs.size();\n                    std::vector<std::pair<nullptr_t,\
    \ node_t>> res(sz);\n                    for (int i = 0; i < sz; ++i) res[i] =\
    \ {nullptr, chs[i]};\n                    return res;\n                };\n  \
    \              return tree_to_string<node_t, node_info_t, nullptr_t>(root, cg,\
    \ node_info_getter);\n            }\n        }\n    }\n\n    /**\n     * template\
    \ args:\n     * - node_t: \u9802\u70B9\u306E\u578B\n     * - node_info_t: \u9802\
    \u70B9\u60C5\u5831\u306E\u578B\n     * - edge_info_t: \u8FBA\u60C5\u5831\u306E\
    \u578B\n     * - leaf_info_t: \u6839\u304B\u3089\u8FBA\u60C5\u5831\u3092\u7D2F\
    \u7A4D\u3057\u3066\u3067\u304D\u308B\u8449\u306E\u5024\u306E\u578B (\u4F8B\u3048\
    \u3070 Trie \u6728\u3067\u306F\uFF0C\u6839\u304B\u3089\u8449\u3078\u306E\u30D1\
    \u30B9\u4E0A\u306B\u3042\u308B\u8FBA\u306E\u6587\u5B57\u3092\u7D2F\u7A4D\u3057\
    \u3066\u6587\u5B57\u5217\u3092\u4F5C\u308B)\n     * \n     * args:\n     * - node_t\
    \ root: \u6839\n     * - init: \u7D2F\u7A4D\u3059\u308B\u8FBA\u60C5\u5831\u306E\
    \u521D\u671F\u5024\n     * - std::function<std::vector<std::pair<edge_info_t,\
    \ node_t>>(node_t)> children_getter: \u9802\u70B9\u3092\u5F15\u6570\u306B\u3068\
    \u3063\u3066(\u8FBA\u60C5\u5831, \u5B50\u9802\u70B9)\u306E\u30EA\u30B9\u30C8\u3092\
    \u8FD4\u3059\u95A2\u6570\n     * - std::function<leaf_info_t(leaf_info_t, edge_info_t)>\
    \ accumulator: \u8FBA\u60C5\u5831\u3092\u7D2F\u7A4D\u3059\u308B\u95A2\u6570\uFF0E\
    (\u73FE\u5728\u306E\u7D2F\u7A4D\u5024, \u8FBA\u60C5\u5831) -> \u5B50\u306E\u7D2F\
    \u7A4D\u5024\n     * - std::function<node_info_t(node_t)> node_info_getter: \u9802\
    \u70B9\u3092\u5F15\u6570\u306B\u3068\u3063\u3066\u9802\u70B9\u60C5\u5831\u3092\
    \u8FD4\u3059\u95A2\u6570\n     */\n    template <typename node_t, typename node_info_t,\
    \ typename edge_info_t, typename leaf_info_t = edge_info_t>\n    std::string tree_to_string(\n\
    \        const node_t root,\n        const leaf_info_t init,\n        const std::function<std::vector<std::pair<edge_info_t,\
    \ node_t>>(node_t)> children_getter,\n        const std::function<leaf_info_t(leaf_info_t,\
    \ edge_info_t)> accumulator,\n        const std::function<node_info_t(node_t)>\
    \ node_info_getter\n    ) { return internal::tree::tree_to_string<>(root, init,\
    \ children_getter, accumulator, node_info_getter); }\n\n    /**\n     * template\
    \ args:\n     * - node_t: \u9802\u70B9\u306E\u578B\n     * - node_info_t: \u9802\
    \u70B9\u60C5\u5831\u306E\u578B\n     * - edge_info_t: \u8FBA\u60C5\u5831\u306E\
    \u578B\n     * \n     * args:\n     * - node_t root: \u6839\n     * - std::function<std::vector<std::pair<edge_info_t,\
    \ node_t>>(node_t)> children_getter: \u9802\u70B9\u3092\u5F15\u6570\u306B\u3068\
    \u3063\u3066(\u8FBA\u60C5\u5831, \u5B50\u9802\u70B9)\u306E\u30EA\u30B9\u30C8\u3092\
    \u8FD4\u3059\u95A2\u6570\n     * - std::function<node_info_t(node_t)> node_info_getter:\
    \ \u9802\u70B9\u3092\u5F15\u6570\u306B\u3068\u3063\u3066\u9802\u70B9\u60C5\u5831\
    \u3092\u8FD4\u3059\u95A2\u6570\n     */\n    template <typename node_t, typename\
    \ node_info_t, typename edge_info_t>\n    std::string tree_to_string(\n      \
    \  const node_t root,\n        const std::function<std::vector<std::pair<edge_info_t,\
    \ node_t>>(node_t)> children_getter,\n        const std::function<node_info_t(node_t)>\
    \ node_info_getter\n    ) { return internal::tree::tree_to_string<>(root, children_getter,\
    \ node_info_getter); }\n\n    /**\n     * template args:\n     * - node_t: \u9802\
    \u70B9\u306E\u578B\n     * - node_info_t: \u9802\u70B9\u60C5\u5831\u306E\u578B\
    \n     * \n     * args:\n     * - node_t root: \u6839\n     * - std::function<std::vector<node_t>(node_t)>\
    \ children_getter: \u9802\u70B9\u3092\u5F15\u6570\u306B\u3068\u3063\u3066\u5B50\
    \u9802\u70B9\u306E\u30EA\u30B9\u30C8\u3092\u8FD4\u3059\u95A2\u6570\n     * - std::function<node_info_t(node_t)>\
    \ node_info_getter: \u9802\u70B9\u3092\u5F15\u6570\u306B\u3068\u3063\u3066\u9802\
    \u70B9\u60C5\u5831\u3092\u8FD4\u3059\u95A2\u6570\n     */\n    template <typename\
    \ node_t, typename node_info_t = node_t>\n    std::string tree_to_string(\n  \
    \      const node_t root,\n        const std::function<std::vector<node_t>(node_t)>\
    \ children_getter,\n        const std::function<node_info_t(node_t)> node_info_getter\n\
    \    ) { return internal::tree::tree_to_string<>(root, children_getter, node_info_getter);\
    \ }\n\n    /**\n     * \u6728\u304C vector<vector<pair<\u8FBA\u60C5\u5831\u306E\
    \u578B, \u9802\u70B9\u306E\u578B>>> \u3067\u8868\u73FE\u3055\u308C\u3066\u3044\
    \u308B\u5834\u5408\u306B\u7279\u6B8A\u5316\u3057\u305F\u3084\u3064\u3067\uFF0C\
    \n     * \u306A\u304A\u304B\u3064\u8449\u304C\u6839\u304B\u3089\u306E\u30D1\u30B9\
    \u4E0A\u306E\u8FBA\u60C5\u5831\u3092\u7D2F\u7A4D\u3057\u305F\u5024\u3092\u6301\
    \u3064\u5834\u5408\n     */\n    template <typename node_t, typename edge_info_t,\
    \ typename leaf_info_t = edge_info_t>\n    std::string tree_to_string(\n     \
    \   const node_t root,\n        const leaf_info_t init,\n        const std::function<leaf_info_t(leaf_info_t,\
    \ edge_info_t)> accumulator,\n        const std::vector<std::vector<std::pair<edge_info_t,\
    \ node_t>>> &g\n    ) {\n        auto children_getter = [&](node_t node) { return\
    \ g[node]; };\n        auto node_info_getter = [&](node_t node) { return node;\
    \ };\n        return tree_to_string<node_t, node_t, edge_info_t, leaf_info_t>(root,\
    \ init, children_getter, accumulator, node_info_getter);\n    }\n\n    /**\n \
    \    * \u6728\u304C vector<vector<pair<\u8FBA\u60C5\u5831\u306E\u578B, \u9802\u70B9\
    \u306E\u578B>>> \u3067\u8868\u73FE\u3055\u308C\u3066\u3044\u308B\u5834\u5408\u306B\
    \u7279\u6B8A\u5316\u3057\u305F\u3084\u3064\n     */\n    template <typename node_t,\
    \ typename edge_info_t>\n    std::string tree_to_string(const node_t root, const\
    \ std::vector<std::vector<std::pair<edge_info_t, node_t>>> &g) {\n        auto\
    \ children_getter = [&](node_t node) { return g[node]; };\n        auto node_info_getter\
    \ = [&](node_t node) { return node; };\n        return tree_to_string<node_t,\
    \ node_t, edge_info_t>(root, children_getter, node_info_getter);\n    }\n\n  \
    \  /**\n     * \u6728\u304C vector<vector<\u9802\u70B9\u306E\u578B>> \u3067\u8868\
    \u73FE\u3055\u308C\u3066\u3044\u308B\u5834\u5408\u306B\u7279\u6B8A\u5316\u3057\
    \u305F\u3084\u3064\n     */\n    template <typename node_t>\n    std::string tree_to_string(const\
    \ node_t root, const std::vector<std::vector<node_t>> &g) {\n        auto children_getter\
    \ = [&](node_t node) { return g[node]; };\n        auto node_info_getter = [&](node_t\
    \ node) { return node; };\n        return tree_to_string<node_t, node_t>(root,\
    \ children_getter, node_info_getter);\n    }\n}\n} // namespace suisen\n\n"
  dependsOn: []
  isVerificationFile: false
  path: library/debug/tree.hpp
  requiredBy: []
  timestamp: '2021-07-16 04:04:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/debug/tree.hpp
layout: document
redirect_from:
- /library/library/debug/tree.hpp
- /library/library/debug/tree.hpp.html
title: library/debug/tree.hpp
---
