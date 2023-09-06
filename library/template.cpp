#include "library/template.hpp"

using namespace suisen;
using namespace std;
struct io_setup {
    io_setup(int precision = 20) {
        std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
        std::cout << std::fixed << std::setprecision(precision);
    }
} io_setup_ {};

constexpr int iinf = std::numeric_limits<int>::max() / 2;
constexpr long long linf = std::numeric_limits<long long>::max() / 2;

void solve() {

}

int main() {
    int test_case_num = 1;
    // read(test_case_num);
    LOOP(test_case_num) solve();
    return 0;
}