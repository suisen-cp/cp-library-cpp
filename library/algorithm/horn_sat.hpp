#ifndef SUISEN_HORN_SAT
#define SUISEN_HORN_SAT

#include <cassert>
#include <queue>
#include <vector>

namespace suisen {

class HornSAT {
    public:
        HornSAT() : HornSAT(0) {}
        HornSAT(const int n) : n(n), ans(n, false), ls(n) {}

        void add_clause(const std::vector<int> &lhs, int rhs, bool val) {
            const int sz = cnt.size();
            cnt.push_back(lhs.size());
            for (int i : lhs) ls[i].push_back(sz);
            r.emplace_back(rhs, val);
            has_answer = false;
        }

        void add_clause(int rhs, bool val) {
            add_clause({}, rhs, val);
        }

        bool satisfiable() {
            const int m = r.size();
            std::deque<std::pair<int, bool>> dq;
            std::vector<int> c = cnt;
            for (int j = 0; j < m; ++j) {
                if (c[j] == 0) dq.push_back(r[j]);
            }
            std::vector<bool> seen(n, false);
            while (dq.size()) {
                const auto [i, val] = dq.front();
                dq.pop_front();
                assert(i < n);
                if (i < 0) return has_answer = false;
                if (not seen[i]) {
                    ans[i] = val;
                    seen[i] = true;
                    for (const int j : ls[i]) {
                        if (--c[j] == 0) dq.push_back(r[j]);
                    }
                } else if (val != ans[i]) return has_answer = false;
            }
            for (int i = 0; i < n; ++i) {
                if (not seen[i]) ans[i] = false;
            }
            return has_answer = true;
        }

        // Call after `satisfiable()`.
        const std::vector<bool>& answer() {
            assert(has_answer);
            return ans;
        }

    private:
        const int n;
        std::vector<bool> ans;
        std::vector<int> cnt;
        std::vector<std::vector<int>> ls;
        std::vector<std::pair<int, bool>> r;
        bool has_answer = true;
};

} // namespace suisen


#endif // SUISEN_HORN_SAT
