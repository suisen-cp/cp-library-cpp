#include <functional>
#include <string>

namespace suisen {
namespace debug {
    namespace internal {
        namespace tree {
            template <typename E>
            std::string edge_to_str(const E edge) {
                return "+-[" + std::to_string(edge) + "]- ";
            }
            template <>
            std::string edge_to_str<std::string>(const std::string edge) {
                return std::string("+-[") + edge + std::string("]- ");
            }
            template <>
            std::string edge_to_str<char>(const char edge) {
                return std::string("+-[") + edge + std::string("]- ");
            }
            template <>
            std::string edge_to_str<nullptr_t>(nullptr_t) {
                return "+-- ";
            }
            template <typename E>
            std::string leaf_to_str(const E edge) {
                return "(" + std::to_string(edge) + ")";
            }
            template <>
            std::string leaf_to_str<char>(const char edge) {
                return std::string("(") + edge + std::string(")");
            }
            template <>
            std::string leaf_to_str<std::string>(const std::string edge) {
                return std::string("(") + edge + std::string(")");
            }
            template <>
            std::string leaf_to_str<nullptr_t>(const nullptr_t) {
                return "";
            }

            template <typename node_t, typename node_info_t, typename edge_info_t, typename leaf_info_t>
            std::string tree_to_string(
                const node_t root,
                const leaf_info_t cum_info,
                const std::function<std::vector<std::pair<edge_info_t, node_t>>(node_t)> children_getter,
                const std::function<leaf_info_t(leaf_info_t, edge_info_t)> accumulator,
                const std::function<node_info_t(node_t)> node_info_getter,
                const std::string &prefix = ""
            ) {
                auto chs = children_getter(root);
                auto res = std::to_string(node_info_getter(root)) + ' ';
                if (chs.size() == 0) {
                    return res + tree::leaf_to_str(cum_info) + "\n";
                }
                auto rec = [&](const node_t next_root, const leaf_info_t next_cum_info, const std::string &next_prefix) {
                    return tree_to_string<node_t, node_info_t, edge_info_t, leaf_info_t>(
                        next_root, next_cum_info, children_getter, accumulator, node_info_getter, next_prefix
                    );
                };
                auto indent = prefix + std::string(res.size(), ' ');
                int sz = chs.size();
                for (int i = 0; i < sz; ++i) {
                    auto [edge_info, next_root] = chs[i];
                    auto edge_str = tree::edge_to_str(edge_info);
                    auto next_prefix = indent + std::string(edge_str.size(), ' ');
                    if (i + 1 < sz) next_prefix[indent.size()] = '|';
                    if (i == 0) {
                        res += edge_str + rec(next_root, accumulator(cum_info, edge_info), next_prefix);
                    } else {
                        res += indent + "|\n";
                        res += indent + edge_str + rec(next_root, accumulator(cum_info, edge_info), next_prefix);
                    }
                }
                return res;
            }

            template <typename node_t, typename node_info_t, typename edge_info_t>
            std::string tree_to_string(
                const node_t root,
                const std::function<std::vector<std::pair<edge_info_t, node_t>>(node_t)> children_getter,
                const std::function<node_info_t(node_t)> node_info_getter
            ) {
                auto accumulator = [](nullptr_t, edge_info_t) -> nullptr_t {
                    return nullptr;
                };
                return tree_to_string<node_t, node_info_t, edge_info_t, nullptr_t>(
                    root, nullptr, children_getter, accumulator, node_info_getter
                );
            }

            template <typename node_t, typename node_info_t>
            std::string tree_to_string(
                const node_t root,
                const std::function<std::vector<node_t>(node_t)> children_getter,
                const std::function<node_info_t(node_t)> node_info_getter
            ) {
                auto cg = [&](node_t node) -> std::vector<std::pair<nullptr_t, node_t>> {
                    auto chs = children_getter(node);
                    int sz = chs.size();
                    std::vector<std::pair<nullptr_t, node_t>> res(sz);
                    for (int i = 0; i < sz; ++i) res[i] = {nullptr, chs[i]};
                    return res;
                };
                return tree_to_string<node_t, node_info_t, nullptr_t>(root, cg, node_info_getter);
            }
        }
    }

    /**
     * template args:
     * - node_t: 頂点の型
     * - node_info_t: 頂点情報の型
     * - edge_info_t: 辺情報の型
     * - leaf_info_t: 根から辺情報を累積してできる葉の値の型 (例えば Trie 木では，根から葉へのパス上にある辺の文字を累積して文字列を作る)
     * 
     * args:
     * - node_t root: 根
     * - init: 累積する辺情報の初期値
     * - std::function<std::vector<std::pair<edge_info_t, node_t>>(node_t)> children_getter: 頂点を引数にとって(辺情報, 子頂点)のリストを返す関数
     * - std::function<leaf_info_t(leaf_info_t, edge_info_t)> accumulator: 辺情報を累積する関数．(現在の累積値, 辺情報) -> 子の累積値
     * - std::function<node_info_t(node_t)> node_info_getter: 頂点を引数にとって頂点情報を返す関数
     */
    template <typename node_t, typename node_info_t, typename edge_info_t, typename leaf_info_t = edge_info_t>
    std::string tree_to_string(
        const node_t root,
        const leaf_info_t init,
        const std::function<std::vector<std::pair<edge_info_t, node_t>>(node_t)> children_getter,
        const std::function<leaf_info_t(leaf_info_t, edge_info_t)> accumulator,
        const std::function<node_info_t(node_t)> node_info_getter
    ) { return internal::tree::tree_to_string<>(root, init, children_getter, accumulator, node_info_getter); }

    /**
     * template args:
     * - node_t: 頂点の型
     * - node_info_t: 頂点情報の型
     * - edge_info_t: 辺情報の型
     * 
     * args:
     * - node_t root: 根
     * - std::function<std::vector<std::pair<edge_info_t, node_t>>(node_t)> children_getter: 頂点を引数にとって(辺情報, 子頂点)のリストを返す関数
     * - std::function<node_info_t(node_t)> node_info_getter: 頂点を引数にとって頂点情報を返す関数
     */
    template <typename node_t, typename node_info_t, typename edge_info_t>
    std::string tree_to_string(
        const node_t root,
        const std::function<std::vector<std::pair<edge_info_t, node_t>>(node_t)> children_getter,
        const std::function<node_info_t(node_t)> node_info_getter
    ) { return internal::tree::tree_to_string<>(root, children_getter, node_info_getter); }

    /**
     * template args:
     * - node_t: 頂点の型
     * - node_info_t: 頂点情報の型
     * 
     * args:
     * - node_t root: 根
     * - std::function<std::vector<node_t>(node_t)> children_getter: 頂点を引数にとって子頂点のリストを返す関数
     * - std::function<node_info_t(node_t)> node_info_getter: 頂点を引数にとって頂点情報を返す関数
     */
    template <typename node_t, typename node_info_t = node_t>
    std::string tree_to_string(
        const node_t root,
        const std::function<std::vector<node_t>(node_t)> children_getter,
        const std::function<node_info_t(node_t)> node_info_getter
    ) { return internal::tree::tree_to_string<>(root, children_getter, node_info_getter); }

    /**
     * 木が vector<vector<pair<辺情報の型, 頂点の型>>> で表現されている場合に特殊化したやつで，
     * なおかつ葉が根からのパス上の辺情報を累積した値を持つ場合
     */
    template <typename node_t, typename edge_info_t, typename leaf_info_t = edge_info_t>
    std::string tree_to_string(
        const node_t root,
        const leaf_info_t init,
        const std::function<leaf_info_t(leaf_info_t, edge_info_t)> accumulator,
        const std::vector<std::vector<std::pair<edge_info_t, node_t>>> &g
    ) {
        auto children_getter = [&](node_t node) { return g[node]; };
        auto node_info_getter = [&](node_t node) { return node; };
        return tree_to_string<node_t, node_t, edge_info_t, leaf_info_t>(root, init, children_getter, accumulator, node_info_getter);
    }

    /**
     * 木が vector<vector<pair<辺情報の型, 頂点の型>>> で表現されている場合に特殊化したやつ
     */
    template <typename node_t, typename edge_info_t>
    std::string tree_to_string(const node_t root, const std::vector<std::vector<std::pair<edge_info_t, node_t>>> &g) {
        auto children_getter = [&](node_t node) { return g[node]; };
        auto node_info_getter = [&](node_t node) { return node; };
        return tree_to_string<node_t, node_t, edge_info_t>(root, children_getter, node_info_getter);
    }

    /**
     * 木が vector<vector<頂点の型>> で表現されている場合に特殊化したやつ
     */
    template <typename node_t>
    std::string tree_to_string(const node_t root, const std::vector<std::vector<node_t>> &g) {
        auto children_getter = [&](node_t node) { return g[node]; };
        auto node_info_getter = [&](node_t node) { return node; };
        return tree_to_string<node_t, node_t>(root, children_getter, node_info_getter);
    }
}
} // namespace suisen

