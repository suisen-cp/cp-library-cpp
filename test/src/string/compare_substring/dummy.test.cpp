#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>
#include <random>

#include "library/string/compare_substring.hpp"

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    const std::size_t n = v.size();
    for (std::size_t i = 0; i < n; ++i) {
        out << v[i];
        if (i + 1 != n) out << ' ';
    }
    return out;
}

template <typename Container>
auto subsegment(const Container& container, int l, int r) {
    Container res;
    std::copy(std::next(std::begin(container), l), std::next(std::begin(container), r), std::back_inserter(res));
    return res;
}

template <typename Container>
void test(const Container& s) {
    std::cerr << "  [\033[32mINFO\033[m] Test \"" << s << "\" ... ";

    auto naive_compare = [&s](int l1, int r1, int l2, int r2) {
        auto s1 = subsegment(s, l1, r1);
        auto s2 = subsegment(s, l2, r2);
        return s1 < s2 ? -1 : s1 > s2 ? 1 : 0;
    };
    suisen::CompareSubstring<suisen::compare_substring_rmq::SparseTableRmQ> fast_compare(s);

    const int n = std::size(s);
    for (int l1 = 0; l1 <= n; ++l1) for (int r1 = l1; r1 <= n; ++r1) {
        for (int l2 = 0; l2 <= n; ++l2) for (int r2 = l2; r2 <= n; ++r2) {
            int res1 = naive_compare(l1, r1, l2, r2);
            int res2 = fast_compare(l1, r1, l2, r2);

            if (res1 != res2) {
                auto to_symbol = [](int res) { return res == 0 ? '=' : res > 0 ? '>' : '<'; };

                std::cerr << "\033[31mFailed.\033[m" << std::endl;
                std::cerr << "  compare s[" << l1 << "," << r1 << ") s[" << l2 << "," << r2 << "):" << std::endl;
                std::cerr << "    s[" << l1 << "," << r1 << ") = \"" << subsegment(s, l1, r1) << "\"" << std::endl;
                std::cerr << "    s[" << l2 << "," << r2 << ") = \"" << subsegment(s, l2, r2) << "\"" << std::endl;
                std::cerr << "    expected : " << to_symbol(res1) << std::endl;
                std::cerr << "    actual   : " << to_symbol(res2) << std::endl;

                std::cerr << "[\033[31mERROR\033[m] Test Failed." << std::endl;

                assert(false);
            }
        }
    }
    std::cerr << "\033[32mOK.\033[m" << std::endl;
}

std::string random_lowercase_alphabet(int len, int alphabet_size, uint32_t seed = 0) {
    std::mt19937 rng{ seed ? seed : std::random_device{}() };
    std::uniform_int_distribution<int> dist(0, alphabet_size - 1);
    std::string res(len, '?');
    std::generate(std::begin(res), std::end(res), [&] { return 'a' + dist(rng); });
    return res;
}

std::vector<uint32_t> random_vector_of_uint32_t(int len, uint32_t max_value = std::numeric_limits<uint32_t>::max(), uint32_t seed = 0) {
    std::mt19937 rng{ seed ? seed : std::random_device{}() };
    std::uniform_int_distribution<uint32_t> dist(0, max_value);
    std::vector<uint32_t> res(len);
    std::generate(std::begin(res), std::end(res), [&] { return dist(rng); });
    return res;
}

void run_tests() {
    std::cerr << "[\033[32mINFO\033[m] Handmade string..." << std::endl;
    test(std::string("abracadabra"));
    std::cerr << "[\033[32mINFO\033[m] OK." << std::endl;

    std::cerr << "[\033[32mINFO\033[m] Random string of lowercase alphabets..." << std::endl;
    test(random_lowercase_alphabet(10, 1));
    test(random_lowercase_alphabet(30, 2));
    test(random_lowercase_alphabet(30, 26));
    std::cerr << "[\033[32mINFO\033[m] OK." << std::endl;

    std::cerr << "[\033[32mINFO\033[m] Random vector of integers..." << std::endl;
    test(random_vector_of_uint32_t(10, 0));
    test(random_vector_of_uint32_t(30, 1));
    test(random_vector_of_uint32_t(30, 25));
    test(random_vector_of_uint32_t(30));
    std::cerr << "[\033[32mINFO\033[m] OK." << std::endl;
}

int main() {
    run_tests();

    std::cout << "Hello World" << std::endl;
    return 0;
}