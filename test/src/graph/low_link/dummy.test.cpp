#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>

#include "library/graph/low_link.hpp"

void test_compnum_1() {
    suisen::LowLink ll(1);
    ll.build();
    assert(ll.connected_component_num_if_removed(0) == 0);
}
void test_compnum_2() {
    suisen::LowLink ll(1);
    ll.add_edge(0, 0);
    ll.build();
    assert(ll.connected_component_num_if_removed(0) == 0);
    assert(ll.connected_component_num_if_removed(0, 0) == 1);
}
void test_compnum_3() {
    suisen::LowLink ll(2);
    ll.add_edge(0, 1);
    ll.build();
    assert(ll.connected_component_num_if_removed(0) == 1);
    assert(ll.connected_component_num_if_removed(1) == 1);
    assert(ll.connected_component_num_if_removed(0, 1) == 2);
}
void test_compnum_4() {
    suisen::LowLink ll(2);
    ll.add_edge(0, 1);
    ll.add_edge(0, 1);
    ll.build();
    assert(ll.connected_component_num_if_removed(0) == 1);
    assert(ll.connected_component_num_if_removed(1) == 1);
    assert(ll.connected_component_num_if_removed(0, 1) == 1);
}
void test_compnum_5() {
    suisen::LowLink ll(3);
    ll.add_edge(0, 1);
    ll.add_edge(1, 2);
    ll.add_edge(2, 0);
    ll.build();
    assert(ll.connected_component_num_if_removed(0) == 1);
    assert(ll.connected_component_num_if_removed(1) == 1);
    assert(ll.connected_component_num_if_removed(2) == 1);
}
void test_compnum_6() {
    suisen::LowLink ll(3);
    ll.add_edge(1, 2);
    ll.add_edge(1, 2);
    ll.build();
    assert(ll.connected_component_num_if_removed(0) == 1);
    assert(ll.connected_component_num_if_removed(1) == 2);
    assert(ll.connected_component_num_if_removed(2) == 2);
}
void test_compnum_7() {
    suisen::LowLink ll(3);
    ll.add_edge(0, 1);
    ll.add_edge(1, 2);
    ll.build();
    assert(ll.connected_component_num_if_removed(0) == 1);
    assert(ll.connected_component_num_if_removed(1) == 2);
    assert(ll.connected_component_num_if_removed(2) == 1);
}

void test() {
    {
        test_compnum_1();
        test_compnum_2();
        test_compnum_3();
        test_compnum_4();
        test_compnum_5();
        test_compnum_6();
        test_compnum_7();
    }
}

int main() {
    test();
    std::cout << "Hello World" << std::endl;
    return 0;
}
