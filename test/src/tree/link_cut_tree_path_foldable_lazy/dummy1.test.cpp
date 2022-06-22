#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>

#include "library/tree/link_cut_tree_path_foldable_lazy.hpp"

int op(int x, int y) {
    return std::max(x, y);
}
int e() {
    return 0;
}
int mapping(int f, int x, int) {
    return f + x;
}
int composition(int f, int g) {
    return f + g;
}
int id() {
    return 0;
}
int toggle(int x) {
    return x;
}

using DynamicTree = suisen::LinkCutTreePathFoldableLazy<int, op, e, int, mapping, composition, id, toggle>;

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
    assert(sum_0 == 2);

    DynamicTree::link(nodes[1], nodes[4]);

    /**
     * [0(1)]---[1(2)]---[4(5)]   [2(3)]   [3(4)]
     */

    int sum_1 = DynamicTree::prod(nodes[0], nodes[4]);
    assert(sum_1 == 5);

    DynamicTree::apply(nodes[1], nodes[4], -6);

    /**
     * [0(1)]---[1(-4)]---[4(-1)]   [2(3)]   [3(4)]
     */

    int sum_2 = DynamicTree::prod(nodes[0], nodes[4]);
    assert(sum_2 == 1);

    DynamicTree::link(nodes[1], nodes[3]);

    /**
     * [0(1)]---[1(-4)]---[4(-1)]   [2(3)]
     *            |
     *          [3(4)]
     */

    auto path_0 = DynamicTree::path(nodes[3], nodes[4]);
    assert(*path_0 == (std::vector<DynamicTree::node_pointer_type>{ nodes[3], nodes[1], nodes[4] }));

    auto path_1 = DynamicTree::path(nodes[3], nodes[3]);
    assert(*path_1 == (std::vector<DynamicTree::node_pointer_type>{ nodes[3] }));

    auto path_2 = DynamicTree::path(nodes[0], nodes[2]);
    assert(path_2 == std::nullopt);

    int sum_3 = DynamicTree::prod(nodes[3], nodes[4]);
    assert(sum_3 == 4);

    DynamicTree::link(nodes[3], nodes[2]);

    /**
     * [0(1)]---[1(-4)]---[4(-1)]
     *            |
     *          [3(4)]---[2(3)]
     */

    int sum_4 = DynamicTree::prod(nodes[1], nodes[2]);
    assert(sum_4 == 4);

    DynamicTree::apply(nodes[0], nodes[3], 3);

    /**
     * [0(4)]---[1(-1)]---[4(-1)]
     *            |
     *          [3(7)]---[2(3)]
     */

    int val_0 = DynamicTree::get(nodes[3]);
    assert(val_0 == 7);

    int sum_5 = DynamicTree::prod(nodes[4], nodes[3]);
    assert(sum_5 == 7);

    DynamicTree::set(nodes[3], 0);

    /**
     * [0(4)]---[1(-1)]---[4(-1)]
     *            |
     *          [3(0)]---[2(3)]
     */

    int sum_6 = DynamicTree::prod(nodes[0], nodes[4]);
    assert(sum_6 == 4);

    DynamicTree::apply(nodes[0], nodes[0], -3);

    /**
     * [0(1)]---[1(-1)]---[4(-1)]
     *            |
     *          [3(0)]---[2(3)]
     */

    int val_1 = DynamicTree::get(nodes[2]);
    assert(val_1 == 3);

    auto path_3 = DynamicTree::path(nodes[0], nodes[3]);
    assert(*path_3 == (std::vector<DynamicTree::node_pointer_type>{ nodes[0], nodes[1], nodes[3] }));

    DynamicTree::cut(nodes[1], nodes[3]);

    /**
     * [0(1)]---[1(-1)]---[4(-1)]
     * 
     *          [3(0)]---[2(3)]
     */

    auto path_4 = DynamicTree::path(nodes[1], nodes[3]);
    assert(path_4 == std::nullopt);

    DynamicTree::apply(nodes[1], nodes[1], 3);

    /**
     * [0(1)]---[1(2)]---[4(-1)]
     * 
     *          [3(0)]---[2(3)]
     */

    int val_2 = DynamicTree::get(nodes[0]);
    assert(val_2 == 1);

    int sum_7 = DynamicTree::prod(nodes[0], nodes[4]);
    assert(sum_7 == 2);

    DynamicTree::link(nodes[0], nodes[2]);

    /**
     * [0(1)]---[1(2)]---[4(-1)]
     *   |
     * [2(3)]---[3(0)]
     */

    int sum_8 = DynamicTree::prod(nodes[1], nodes[3]);
    assert(sum_8 == 3);

    DynamicTree::cut(nodes[1], nodes[0]);

    /**
     * [0(1)]   [1(2)]---[4(-1)]
     *   |
     * [2(3)]---[3(0)]
     */

    auto path_5 = DynamicTree::path(nodes[0], nodes[4]);
    assert(path_5 == std::nullopt);

    DynamicTree::link(nodes[2], nodes[4]);

    /**
     * [0(1)]
     *   |
     * [2(3)]---[3(0)]
     *   |
     * [4(-1)]
     *   |
     * [1(2)]
     */

    int sum_9 = DynamicTree::prod(nodes[3], nodes[4]);
    assert(sum_9 == 3);

    auto path_6 = DynamicTree::path(nodes[0], nodes[1]);
    assert(*path_6 == (std::vector<DynamicTree::node_pointer_type>{ nodes[0], nodes[2], nodes[4], nodes[1] }));

    auto path_7 = DynamicTree::path(nodes[4], nodes[3]);
    assert(*path_7 == (std::vector<DynamicTree::node_pointer_type>{ nodes[4], nodes[2], nodes[3] }));

    int val_3 = DynamicTree::get(nodes[3]);
    assert(val_3 == 0);

    DynamicTree::apply(nodes[0], nodes[1], -5);

    /**
     * [0(-4)]
     *   |
     * [2(-2)]---[3(0)]
     *   |
     * [4(-6)]
     *   |
     * [1(-3)]
     */

    DynamicTree::apply(nodes[3], nodes[1], 2);

    /**
     * [0(-4)]
     *   |
     * [2(0)]---[3(2)]
     *   |
     * [4(-4)]
     *   |
     * [1(-1)]
     */

    int sum_10 = DynamicTree::prod(nodes[0], nodes[3]);
    assert(sum_10 == 2);

    int val_4 = DynamicTree::get(nodes[0]);
    assert(val_4 == -4);

    int val_5 = DynamicTree::get(nodes[1]);
    assert(val_5 == -1);

    int val_6 = DynamicTree::get(nodes[2]);
    assert(val_6 == 0);

    int val_7 = DynamicTree::get(nodes[3]);
    assert(val_7 == 2);

    int val_8 = DynamicTree::get(nodes[4]);
    assert(val_8 == -4);
}

int main() {
    test();
    std::cout << "Hello World" << std::endl;
    return 0;
}