#ifndef SUISEN_DEBUG_SUFFIX_AUTOMATON
#define SUISEN_DEBUG_SUFFIX_AUTOMATON

#include <sstream>

#include "library/string/suffix_automaton.hpp"

namespace suisen::debug {

template <typename T, typename SequenceType>
std::string to_dot(const SuffixAutomatonBase<T, SequenceType> &dfa, bool display_suffix_link = true, bool use_chart_api = false) {
    const std::string graph_rank_dir = "LR";
    const std::string node_shape = "circle";
    const std::string suffix_link_style = "dashed";
    const std::string suffix_link_color = "blue";

    const auto id = [&](int i) {
        return std::to_string(i);
    };
    const auto label = [&](int i) {
        std::string s = std::to_string(i);
        if (dfa.nodes[i].cloned) s += "C";
        return s;
    };
    const auto edge = [&](int i, int j) {
        return id(i) + "->" + id(j);
    };

    std::ostringstream oss;
    if (use_chart_api) oss << "http://chart.apis.google.com/chart?cht=gv&chl=";
    oss << "digraph{";
    oss << "graph[rankdir=" << graph_rank_dir << ",ordering=out];";
    oss << "node[shape=" << node_shape << ",width=0.5];";
    const int n = dfa.nodes.size();
    for (int i = 0; i < n; ++i) {
        oss << id(i) << "[label=\"" << label(i) << "\",fixedsize=true];";
    }
    for (int i = 0; i < n; ++i) {
        const auto &node = dfa.nodes[i];
        if (display_suffix_link and node.link >= 0) {
            oss << edge(i, node.link) << "[constraint=false,color=" << suffix_link_color << ",style=" << suffix_link_style << "];";
        }
        for (const auto &[k, v] : node.nxt) {
            oss << edge(i, v) << "[label=\"" << k << "\",fontsize=20];";
        }
    }
    oss << "}";
    return oss.str();
}

} // namespace suisen::debug


#endif // SUISEN_DEBUG_SUFFIX_AUTOMATON
