#define PROBLEM "https://judge.yosupo.jp/problem/stern_brocot_tree"

#include "library/number/stern_brocot_tree.hpp"

#include <iostream>

using sbt_node = suisen::sbt_node<int>;

void query_encode_path() {
    int a, b;
    std::cin >> a >> b;
    sbt_node node(a, b);
    const auto p = node.path();
    std::cout << p.size();
    for (const auto& [dir, num] : p) {
        std::cout << ' ' << (dir == sbt_node::Left ? 'L' : 'R') << ' '<< num;
    }
    std::cout << '\n';
}
void query_decode_path() {
    int k;
    std::cin >> k;
    sbt_node node;
    for (int i = 0; i < k; ++i) {
        char c;
        int n;
        std::cin >> c >> n;
        sbt_node::sbt_arc dir = c == 'L' ? sbt_node::Left : sbt_node::Right;
        node.move_down(dir, n);
    }
    const auto [num, den] = node.get();
    std::cout << num << ' ' << den << '\n';
}
void query_lca() {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    auto [num, den] = sbt_node::lca({ a, b }, { c, d }).get();
    std::cout << num << ' ' << den << '\n';
}
void query_ancestor() {
    int k, a, b;
    std::cin >> k >> a >> b;
    sbt_node node(a, b);
    if (node.move_up(node.depth() - k)) {
        const auto [num, den] = node.get();
        std::cout << num << ' ' << den << '\n';
    } else {
        std::cout << -1 << '\n';
    }
}
void query_range() {
    int a, b;
    std::cin >> a >> b;
    auto [l, r] = sbt_node(a, b).range();
    auto [num_l, den_l] = l;
    auto [num_r, den_r] = r;
    std::cout << num_l << ' ' << den_l << ' ' << num_r << ' ' << den_r << '\n';
}

int main() {
    using namespace std::string_literals;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        std::string op;
        std::cin >> op;
        if (op == "ENCODE_PATH"s) query_encode_path();
        if (op == "DECODE_PATH"s) query_decode_path();
        if (op == "LCA"s) query_lca();
        if (op == "ANCESTOR"s) query_ancestor();
        if (op == "RANGE"s) query_range();
    }
}