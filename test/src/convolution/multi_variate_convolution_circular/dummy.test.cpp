#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>

#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/convolution/multi_variate_convolution_circular.hpp"

void test1() {
    using namespace suisen;

    std::vector<int> n { 2, 45, 73 };
    const int l = std::reduce(n.begin(), n.end(), 1, std::multiplies<int>()); // 6570

    suisen::multi_variate_convolution_circular<mint> conv(n);

    std::vector<mint> f(l), g(l);
    std::iota(f.begin(), f.end(), 123109233);
    std::iota(g.begin(), g.end(), 213082409);

    std::vector<mint> h_expected = conv.convolution_naive(f, g);
    std::vector<mint> h_actual = conv.convolution(f, g);

    assert(h_expected == h_actual);
}

void test2() {
    using namespace suisen;

    std::vector<int> n { 2, 3, 2, 4, 3, 5 };
    const int l = std::reduce(n.begin(), n.end(), 1, std::multiplies<int>()); // 720

    suisen::multi_variate_convolution_circular<mint> conv(n);

    std::vector<mint> f(l), g(l);
    std::iota(f.begin(), f.end(), 12038);
    std::iota(g.begin(), g.end(), 4392);

    std::vector<mint> h_expected = conv.convolution_naive(f, g);
    std::vector<mint> h_actual = conv.convolution(f, g);

    assert(h_expected == h_actual);
}

void test3() {
    using namespace suisen;

    std::vector<int> n {};
    const int l = std::reduce(n.begin(), n.end(), 1, std::multiplies<int>()); // 1

    suisen::multi_variate_convolution_circular<mint> conv(n);

    std::vector<mint> f(l), g(l);
    std::iota(f.begin(), f.end(), 4);
    std::iota(g.begin(), g.end(), 3);

    std::vector<mint> h_expected = conv.convolution_naive(f, g);
    std::vector<mint> h_actual = conv.convolution(f, g);

    assert(h_expected == h_actual);
}

#include "library/util/timer.hpp"

void perf_test1() {
    using namespace suisen;

    std::vector<int> n(18, 2);
    const int l = std::reduce(n.begin(), n.end(), 1, std::multiplies<int>()); // 262144

    suisen::multi_variate_convolution_circular<mint> conv(n);

    std::vector<mint> f(l), g(l);
    std::iota(f.begin(), f.end(), 2348042);
    std::iota(g.begin(), g.end(), 5439850);

    Timer t;
    std::vector<mint> h_actual = conv.convolution(f, g);
    double elapsed = t.elapsed();
    
    std::cerr << "Solved in " << elapsed << " ms." << std::endl;

    if (elapsed > 2000) {
        std::cerr << "TLE" << std::endl;
        // assert(false);
    }
}

void perf_test2() {
    using namespace suisen;

    std::vector<int> n(11, 3);
    const int l = std::reduce(n.begin(), n.end(), 1, std::multiplies<int>()); // 177147

    suisen::multi_variate_convolution_circular<mint> conv(n);

    std::vector<mint> f(l), g(l);
    std::iota(f.begin(), f.end(), 2348042);
    std::iota(g.begin(), g.end(), 5439850);

    Timer t;
    std::vector<mint> h_actual = conv.convolution(f, g);
    double elapsed = t.elapsed();
    
    std::cerr << "Solved in " << elapsed << " ms." << std::endl;

    if (elapsed > 2000) {
        std::cerr << "TLE" << std::endl;
        // assert(false);
    }
}

void perf_test3() {
    using namespace suisen;

    std::vector<int> n { 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
    const int l = std::reduce(n.begin(), n.end(), 1, std::multiplies<int>()); // 236196

    suisen::multi_variate_convolution_circular<mint> conv(n);

    std::vector<mint> f(l), g(l);
    std::iota(f.begin(), f.end(), 2348042);
    std::iota(g.begin(), g.end(), 5439850);

    Timer t;
    std::vector<mint> h_actual = conv.convolution(f, g);
    double elapsed = t.elapsed();
    
    std::cerr << "Solved in " << elapsed << " ms." << std::endl;

    if (elapsed > 2000) {
        std::cerr << "TLE" << std::endl;
        // assert(false);
    }
}

void perf_test4() {
    using namespace suisen;

    std::vector<int> n(9, 4);
    const int l = std::reduce(n.begin(), n.end(), 1, std::multiplies<int>()); // 262144

    suisen::multi_variate_convolution_circular<mint> conv(n);

    std::vector<mint> f(l), g(l);
    std::iota(f.begin(), f.end(), 2348042);
    std::iota(g.begin(), g.end(), 5439850);

    Timer t;
    std::vector<mint> h_actual = conv.convolution(f, g);
    double elapsed = t.elapsed();
    
    std::cerr << "Solved in " << elapsed << " ms." << std::endl;

    if (elapsed > 2000) {
        std::cerr << "TLE" << std::endl;
        // assert(false);
    }
}

void perf_test5() {
    using namespace suisen;

    std::vector<int> n(7, 6);
    const int l = std::reduce(n.begin(), n.end(), 1, std::multiplies<int>()); // 279936

    suisen::multi_variate_convolution_circular<mint> conv(n);

    std::vector<mint> f(l), g(l);
    std::iota(f.begin(), f.end(), 2348042);
    std::iota(g.begin(), g.end(), 5439850);

    Timer t;
    std::vector<mint> h_actual = conv.convolution(f, g);
    double elapsed = t.elapsed();
    
    std::cerr << "Solved in " << elapsed << " ms." << std::endl;

    if (elapsed > 2000) {
        std::cerr << "TLE" << std::endl;
        // assert(false);
    }
}

void perf_test6() {
    using namespace suisen;

    std::vector<int> n(6, 8);
    const int l = std::reduce(n.begin(), n.end(), 1, std::multiplies<int>()); // 262144

    suisen::multi_variate_convolution_circular<mint> conv(n);

    std::vector<mint> f(l), g(l);
    std::iota(f.begin(), f.end(), 2348042);
    std::iota(g.begin(), g.end(), 5439850);

    Timer t;
    std::vector<mint> h_actual = conv.convolution(f, g);
    double elapsed = t.elapsed();
    
    std::cerr << "Solved in " << elapsed << " ms." << std::endl;

    if (elapsed > 2000) {
        std::cerr << "TLE" << std::endl;
        // assert(false);
    }
}

void perf_test7() {
    using namespace suisen;

    std::vector<int> n(5, 12);
    const int l = std::reduce(n.begin(), n.end(), 1, std::multiplies<int>()); // 248832

    suisen::multi_variate_convolution_circular<mint> conv(n);

    std::vector<mint> f(l), g(l);
    std::iota(f.begin(), f.end(), 2348042);
    std::iota(g.begin(), g.end(), 5439850);

    Timer t;
    std::vector<mint> h_actual = conv.convolution(f, g);
    double elapsed = t.elapsed();
    
    std::cerr << "Solved in " << elapsed << " ms." << std::endl;

    if (elapsed > 2000) {
        std::cerr << "TLE" << std::endl;
        // assert(false);
    }
}

void perf_test8() {
    using namespace suisen;

    std::vector<int> n(4, 22);
    const int l = std::reduce(n.begin(), n.end(), 1, std::multiplies<int>()); // 234256

    suisen::multi_variate_convolution_circular<mint> conv(n);

    std::vector<mint> f(l), g(l);
    std::iota(f.begin(), f.end(), 2348042);
    std::iota(g.begin(), g.end(), 5439850);

    Timer t;
    std::vector<mint> h_actual = conv.convolution(f, g);
    double elapsed = t.elapsed();
    
    std::cerr << "Solved in " << elapsed << " ms." << std::endl;

    if (elapsed > 2000) {
        std::cerr << "TLE" << std::endl;
        // assert(false);
    }
}

void perf_test9() {
    using namespace suisen;

    std::vector<int> n(3, 64);
    const int l = std::reduce(n.begin(), n.end(), 1, std::multiplies<int>()); // 262144

    suisen::multi_variate_convolution_circular<mint> conv(n);

    std::vector<mint> f(l), g(l);
    std::iota(f.begin(), f.end(), 2348042);
    std::iota(g.begin(), g.end(), 5439850);

    Timer t;
    std::vector<mint> h_actual = conv.convolution(f, g);
    double elapsed = t.elapsed();
    
    std::cerr << "Solved in " << elapsed << " ms." << std::endl;

    if (elapsed > 2000) {
        std::cerr << "TLE" << std::endl;
        // assert(false);
    }
}

void perf_test10() {
    using namespace suisen;

    std::vector<int> n(2, 512);
    const int l = std::reduce(n.begin(), n.end(), 1, std::multiplies<int>()); // 262144

    suisen::multi_variate_convolution_circular<mint> conv(n);

    std::vector<mint> f(l), g(l);
    std::iota(f.begin(), f.end(), 2348042);
    std::iota(g.begin(), g.end(), 5439850);

    Timer t;
    std::vector<mint> h_actual = conv.convolution(f, g);
    double elapsed = t.elapsed();
    
    std::cerr << "Solved in " << elapsed << " ms." << std::endl;

    if (elapsed > 2000) {
        std::cerr << "TLE" << std::endl;
        // assert(false);
    }
}

void test() {
    test1();
    test2();
    test3();
    perf_test1();
    perf_test2();
    perf_test3();
    perf_test4();
    perf_test5();
    perf_test6();
    perf_test7();
    perf_test8();
    perf_test9();
    perf_test10();
}

int main() {
    test();
    std::cout << "Hello World" << std::endl;
    return 0;
}
