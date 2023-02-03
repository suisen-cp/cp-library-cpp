
#include <algorithm>
#include <iostream>

#include "library/datastructure/bbst/implicit_treap.hpp"

using Set = suisen::DynamicArray<long long>;
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
 
    int q;
    long long a, b;
    std::cin >> q >> a >> b;
 
    Set st = std::vector{ a - b, a + b };
 
    while (q --> 0) {
        int t;
        long long a2, b2;
        std::cin >> t >> a2 >> b2;
        if (t == 1) {
            st.insert(st.lower_bound(a2 - b2), a2 - b2);
            st.insert(st.lower_bound(a2 + b2), a2 + b2);
        } else {
            long long l = a2, r = b2;
            auto it = st.lower_bound(l);
            if (it != st.end() and *it <= r) {
                std::cout << 0 << '\n';
            } else {
                long long ans = std::numeric_limits<long long>::max();
                if (it != st.end()) {
                    ans = std::min(ans, std::abs(*it - r));
                }
                if (it != st.begin()) {
                    ans = std::min(ans, std::abs(*--it - l));
                }
                std::cout << ans << '\n';
            }
        }
    }
    return 0;
}