#ifndef SUISEN_STATIC_RANGE_INVERSION_NUMBER_QUERY
#define SUISEN_STATIC_RANGE_INVERSION_NUMBER_QUERY

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

/**
 * @brief Static Range Inversion Number Query
 */

namespace suisen {
    template <typename T>
    struct StaticRangeInversionNumberQuery {
        StaticRangeInversionNumberQuery(std::vector<T> a) : _block_siz(std::max(1, int(::sqrt(a.size())))), _block_num(ceil_div(a.size(),_block_siz)) {
            a.resize(_block_siz * _block_num, std::numeric_limits<T>::max());

            _sorted.resize(_block_num);
            for (int block_id = 0; block_id < _block_num; ++block_id) {
                const int offset = block_id * _block_siz;
                _sorted[block_id].resize(_block_siz);
                for (int i = 0; i < _block_siz; ++i) _sorted[block_id][i] = { a[offset + i], offset + i };
                std::sort(_sorted[block_id].begin(), _sorted[block_id].end());
            }

            _pinv = build_pinv<std::less<T>>(a);
            std::reverse(a.begin(), a.end());
            _sinv = build_pinv<std::greater<T>>(a);
            std::reverse(_sinv.begin(), _sinv.end());
        }

        /**
         * @brief Calcuates the inversion number of the subarray (a_l, ..., a_{r-1}).
         * @param l left (closed)
         * @param r right (open)
         * @return Inversion number of (a_l, ..., a_{r-1})
         */
        long long operator()(int l, int r) const {
            const int bl = l / _block_siz, br = ceil_div(r, _block_siz);
            // [bl][bl+1,...,br-2][br-1]
            if (br - bl == 1) {
                /**
                 *             l   r
                 *         | A | B | C |
                 * Blocks: |           |
                 *
                 * Inv(B)=Inv(AB)+Inv(BC)-Inv(ABC)+Inv(A,C)
                 */
                long long res = _pinv[bl][r - bl * _block_siz] + _sinv[bl + 1][(bl + 1) * _block_siz - l] - _pinv[bl][_block_siz];
                for (int k = _block_siz - 1, cnt = 0; k >= 0; --k) {
                    cnt += _sorted[bl][k].second < l;
                    if (_sorted[bl][k].second >= r) {
                        res += cnt;
                    }
                }
                return res;
            } else {
                /**
                 *           l                         r
                 *           | A |        B        | C |
                 * Blocks: |     |     |     |     |     |
                 *
                 * Inv(ABC)=Inv(AB)+Inv(BC)-Inv(B)+Inv(A,C)
                 */
                const int ml = (bl + 1) * _block_siz, mr = (br - 1) * _block_siz;
                long long res = _pinv[bl + 1][r - ml] + _sinv[br - 1][mr - l] - _pinv[bl + 1][mr - ml];
                for (int k = _block_siz - 1, j = _block_siz, cnt = 0; k >= 0; --k) {
                    if (_sorted[br - 1][k].second >= r) continue;
                    while (j > 0 and _sorted[bl][j - 1].first > _sorted[br - 1][k].first) {
                        cnt += _sorted[bl][--j].second >= l;
                    }
                    res += cnt;
                }
                return res;
            }
        }

    private:
        int _block_siz, _block_num;

        // _pinv[i][j] := inversion number of the subarray (a_{i * _block_siz}, ..., a_{i * _block_siz + j - 1})
        // _sinv[i][j] := inversion number of the subarray (a_{i * _block_siz - j}, ..., a_{i * _block_siz - 1})
        std::vector<std::vector<long long>> _pinv, _sinv;

        // _sorted[i] := sorted array of { (a_{i * _block_siz + j}, i * _block_siz + j) | 0 <= j < _block_siz }
        std::vector<std::vector<std::pair<T, int>>> _sorted;

        template <typename Compare>
        std::vector<std::vector<long long>> build_pinv(const std::vector<T>& a) const {
            Compare cmp{};
            auto cmp_pair = [&](auto& p, auto& q) { return cmp(p.first, q.first); };

            std::vector<std::vector<long long>> pinv(_block_num + 1);

            // invariant: suf is the sorted array of { (a_i, i) | i is in the k-th block s.t. k > block_id }
            std::vector<std::pair<T, int>> suf;
            for (int block_id = _block_num - 1; block_id >= 0; --block_id) {
                const int offset = block_id * _block_siz;
                pinv[block_id].resize(_block_siz * (_block_num - block_id) + 1);
                std::vector<std::pair<T, int>> pre(_block_siz);
                for (int i = 0; i < _block_siz; ++i) {
                    pre[i] = { a[offset + i], offset + i };
                    pinv[block_id][i + 1] = pinv[block_id][i];
                    for (int j = 0; j < i; ++j) pinv[block_id][i + 1] += cmp(a[offset + i], a[offset + j]);
                }
                std::sort(pre.begin(), pre.end(), cmp_pair);

                /**
                 * | A |  B  |x|
                 * Inv(ABx)=Inv(AB)+Inv(Bx)-Inv(B)+Inv(A,x)
                 */

                 // calculates Inv(A,a_i) for all i >= _block_siz * block_id
                for (int i = _block_siz * (_block_num - 1 - block_id) - 1, j = _block_siz; i >= 0; --i) {
                    while (j > 0 and cmp(suf[i].first, pre[j - 1].first)) --j;
                    pinv[block_id][suf[i].second - offset + 1] += _block_siz - j;
                }

                for (int i = _block_siz; i < _block_siz * (_block_num - block_id); ++i) {
                    pinv[block_id][i + 1] += pinv[block_id][i] + pinv[block_id + 1][i + 1 - _block_siz] - pinv[block_id + 1][i - _block_siz];
                }

                std::copy(pre.begin(), pre.end(), std::back_inserter(suf));
                std::inplace_merge(suf.begin(), suf.end() - _block_siz, suf.end(), cmp_pair);
            }
            return pinv;
        }

        static constexpr int ceil_div(int num, int den) { return (num + den - 1) / den; }
    };
} // namespace suisen


#endif // SUISEN_STATIC_RANGE_INVERSION_NUMBER_QUERY
