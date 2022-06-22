#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>

#include "library/tree/link_cut_tree_path_foldable.hpp"

int op(int x, int y) { return x + y; }
int e() { return 0; }
int toggle(int x) { return x; }

using DynamicTree = suisen::LinkCutTreePathFoldable<int, op, e, toggle>;

void test() {
    const int n = 5;

    DynamicTree::init_pool(n);

    std::vector<int> init_values { 1, 2, 3, 4, 5 };

    std::vector<DynamicTree::node_pointer_type> nodes = DynamicTree::make_nodes(init_values);

    /**
     * [0(1)]   [1(2)]   [2(3)]   [3(4)]   [4(5)]
     */

    DynamicTree::link(nodes[0], nodes[1]);

    /**
     * [0(1)]---[1(2)]   [2(3)]   [3(4)]   [4(5)]
     */

    int sum_0 = DynamicTree::prod(nodes[0], nodes[1]);
    assert(sum_0 == 1 + 2);


    DynamicTree::link(nodes[1], nodes[4]);

    /**
     * [0(1)]---[1(2)]---[4(5)]   [2(3)]   [3(4)]
     */

    int sum_1 = DynamicTree::prod(nodes[0], nodes[4]);
    assert(sum_1 == 1 + 2 + 5);

    DynamicTree::link(nodes[1], nodes[3]);

    /**
     * [0(1)]---[1(2)]---[4(5)]   [2(3)]
     *            |
     *          [3(4)]
     */

    auto path_0 = DynamicTree::path(nodes[3], nodes[4]);
    assert(*path_0 == (std::vector<DynamicTree::node_pointer_type>{ nodes[3], nodes[1], nodes[4] }));

    auto path_1 = DynamicTree::path(nodes[3], nodes[3]);
    assert(*path_1 == (std::vector<DynamicTree::node_pointer_type>{ nodes[3] }));

    auto path_2 = DynamicTree::path(nodes[0], nodes[2]);
    assert(path_2 == std::nullopt);

    int sum_2 = DynamicTree::prod(nodes[3], nodes[4]);
    assert(sum_2 == 4 + 2 + 5);

    DynamicTree::link(nodes[3], nodes[2]);

    /**
     * [0(1)]---[1(2)]---[4(5)]
     *            |
     *          [3(4)]---[2(3)]
     */

    int sum_3 = DynamicTree::prod(nodes[1], nodes[2]);
    assert(sum_3 == 2 + 4 + 3);

    DynamicTree::set(nodes[1], 7);

    /**
     * [0(1)]---[1(7)]---[4(5)]
     *            |
     *          [3(4)]---[2(3)]
     */

    int sum_4 = DynamicTree::prod(nodes[0], nodes[4]);
    assert(sum_4 == 1 + 7 + 5);

    auto path_3 = DynamicTree::path(nodes[0], nodes[3]);
    assert(*path_3 == (std::vector<DynamicTree::node_pointer_type>{ nodes[0], nodes[1], nodes[3] }));

    DynamicTree::cut(nodes[1], nodes[3]);

    /**
     * [0(1)]---[1(7)]---[4(5)]
     * 
     *          [3(4)]---[2(3)]
     */

    auto path_4 = DynamicTree::path(nodes[1], nodes[3]);
    assert(path_4 == std::nullopt);

    DynamicTree::set(nodes[4], 9);

    /**
     * [0(1)]---[1(7)]---[4(9)]
     * 
     *          [3(4)]---[2(3)]
     */

    int sum_5 = DynamicTree::prod(nodes[0], nodes[4]);
    assert(sum_5 == 1 + 7 + 9);

    DynamicTree::link(nodes[0], nodes[2]);

    /**
     * [0(1)]---[1(7)]---[4(9)]
     *   |
     * [2(3)]---[3(4)]
     */

    int sum_6 = DynamicTree::prod(nodes[1], nodes[3]);
    assert(sum_6 == 7 + 1 + 3 + 4);

    DynamicTree::cut(nodes[1], nodes[0]);

    /**
     * [0(1)]   [1(7)]---[4(9)]
     *   |
     * [2(3)]---[3(4)]
     */

    auto path_5 = DynamicTree::path(nodes[0], nodes[4]);
    assert(path_5 == std::nullopt);

    DynamicTree::link(nodes[2], nodes[4]);

    /**
     * [0(1)]
     *   |
     * [2(3)]---[3(4)]
     *   |
     * [4(9)]
     *   |
     * [1(7)]
     */

    int sum_7 = DynamicTree::prod(nodes[3], nodes[4]);
    assert(sum_7 == 4 + 3 + 9);

    auto path_6 = DynamicTree::path(nodes[0], nodes[1]);
    assert(*path_6 == (std::vector<DynamicTree::node_pointer_type>{ nodes[0], nodes[2], nodes[4], nodes[1] }));

    auto path_7 = DynamicTree::path(nodes[4], nodes[3]);
    assert(*path_7 == (std::vector<DynamicTree::node_pointer_type>{ nodes[4], nodes[2], nodes[3] }));
}

int main() {
    test();
    std::cout << "Hello World" << std::endl;
    return 0;
}