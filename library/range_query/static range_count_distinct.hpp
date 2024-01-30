#ifndef SUISEN_STATIC_RANGE_COUNT_DISTINCT
#define SUISEN_STATIC_RANGE_COUNT_DISTINCT

#include <cassert>
#include <cstdint>
#include <cstddef>
#include <unordered_map>
#include <utility>
#include <vector>

#include <atcoder/fenwicktree>

namespace suisen {
    struct StaticRangeCountDistinctOffline {
        StaticRangeCountDistinctOffline() : StaticRangeCountDistinctOffline(std::vector<int>{}) {}
        explicit StaticRangeCountDistinctOffline(const std::vector<int>& a) : _n(a.size()), _q(0), _a(a) {}

        void reserve(int q) { _qs.reserve(q); }

        // Return the ID of the given query (NOT the answer)
        int add_query(int l, int r) {
            assert(0 <= l and l <= r and r <= _n);
            _qs.emplace_back(l, r);
            return _q++;
        }

        std::vector<int> solve() const {
            // last[v] = 1 + max{ i | a[i]=v or i=-1 }
            std::unordered_map<int, int> last;
            // prv[i] = 1 + max{ j | a[i]=a[j] or j=-1 }
            std::vector<int> prv(_n);
            for (int i = 0; i < _n; ++i) {
                prv[i] = std::exchange(last[_a[i]], i + 1);
            }
            // sort ranges by bucket sort
            std::vector<int> index(_n + 2);
            for (auto& [l, r] : _qs) {
                ++index[r];
            }
            for (int i = 1; i <= _n; ++i) {
                index[i] += index[i - 1];
            }
            index[_n + 1] = _q;
            std::vector<int> qs_ord(_q);
            for (int qid = 0; qid < _q; ++qid) {
                qs_ord[--index[_qs[qid].second]] = qid;
            }

            atcoder::fenwick_tree<int> ft(_n + 1);
            std::vector<int> ans(_q);
            for (int r = 0; r <= _n; ++r) {
                for (int i = index[r]; i < index[r + 1]; ++i) {
                    const int qid = qs_ord[i], l = _qs[qid].first;
                    assert(_qs[qid].second == r);
                    ans[qid] = ft.sum(0, l + 1) - l;
                }
                if (r < _n) ft.add(prv[r], 1);
            }
            return ans;
        }

    private:
        int _n, _q;
        std::vector<int> _a;
        std::vector<std::pair<int, int>> _qs;
    };
} // namespace suisen

#endif // SUISEN_STATIC_RANGE_COUNT_DISTINCT
