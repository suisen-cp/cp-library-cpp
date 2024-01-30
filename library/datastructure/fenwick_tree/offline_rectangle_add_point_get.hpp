#ifndef SUISEN_OFFLINE_RECT_ADD_POINT_GET
#define SUISEN_OFFLINE_RECT_ADD_POINT_GET

#include <algorithm>
#include <array>
#include <numeric>
#include <vector>

#include <atcoder/fenwicktree>

namespace suisen {
    template <typename T, typename Index = int>
    struct OfflineRectangleAddPointGet {
    private:
        using Rectangle = std::array<Index, 4>;
        using Point = std::array<Index, 2>;
    public:
        void add(Index l, Index r, Index d, Index u, T w) {
            assert(l <= r and d <= u);
            if (l == r or d == u) return;
            _rects.push_back({ l, r, d, u });
            _weights.push_back(w);
        }
        void get(Index x, Index y) {
            _points.push_back({ x, y });
            _times.push_back(_rects.size());
        }

        std::vector<T> solve() const {
            std::vector<T> ans(_points.size());

            const int rect_num = _rects.size();

            using Key = std::pair<Index, int>;
            constexpr auto comp_key = [](const Key &k1, const Key& k2) { return k1.first < k2.first; };

            /**
             * [---------------------8]
             * [---------4]............[----------12]
             * [---2]......[---6]......[--10]........[----14]
             * [1]...[3]...[5]...[7]...[9]...[11]....[13]....
             * 
             * ---------------- rectangles ----------------->
             */

            // Event      (l,d,+w), (l,u,-w), (r,d,-w), (r,u,+w)
            // Index(x)      2i        2i       2i+1      2i+1
            // Index(y)      2i       2i+1       2i       2i+1
            std::vector<Key> es_asc_x(2 * rect_num), es_asc_y(2 * rect_num);
            for (int i = 0; i < rect_num; ++i) {
                es_asc_x[2 * i + 0] = Key{ _rects[i][0], 2 * i + 0 }; // l
                es_asc_x[2 * i + 1] = Key{ _rects[i][1], 2 * i + 1 }; // r
                es_asc_y[2 * i + 0] = Key{ _rects[i][2], 2 * i + 0 }; // d
                es_asc_y[2 * i + 1] = Key{ _rects[i][3], 2 * i + 1 }; // u
            }
            std::vector<std::vector<Key>> ps_asc_x(rect_num), ps_asc_y(rect_num);
            for (int pid = 0; pid < int(_points.size()); ++pid) if (_times[pid]) {
                const int r = floor_pow2(_times[pid]);
                ps_asc_x[r - 1].emplace_back(_points[pid][0], pid); // x
                ps_asc_y[r - 1].emplace_back(_points[pid][1], pid); // y
            }

            std::vector<int> ps_comp_y(_points.size()), es_comp_y(2 * rect_num);

            for (int r = 1; r <= rect_num; ++r) {
                const int w = -r & r, l = r - w;
                for (int t = 1; t < w; t <<= 1) {
                    // Merge Sort
                    // r=8 : {8}  -> {7,8}   -> {5,6,7,8}    -> {1,2,3,4,5,6,7,8}
                    // r=12: {12} -> {11,12} -> {9,10,11,12}
                    auto it_r_x = es_asc_x.begin() + 2 * r, it_m_x = it_r_x - 2 * t, it_l_x = it_m_x - 2 * t;
                    std::inplace_merge(it_l_x, it_m_x, it_r_x, comp_key);
                    auto it_r_y = es_asc_y.begin() + 2 * r, it_m_y = it_r_y - 2 * t, it_l_y = it_m_y - 2 * t;
                    std::inplace_merge(it_l_y, it_m_y, it_r_y, comp_key);
                }

                const int point_num = ps_asc_x[r - 1].size();
                if (point_num == 0) continue;
                if (r == (-r & r)) {
                    std::sort(ps_asc_x[r - 1].begin(), ps_asc_x[r - 1].end(), comp_key);
                    std::sort(ps_asc_y[r - 1].begin(), ps_asc_y[r - 1].end(), comp_key);
                }
                int num_y = 0;
                {
                    std::vector<Key> mixed_asc_y(es_asc_y.begin() + 2 * l, es_asc_y.begin() + 2 * r);
                    const int mid_siz = mixed_asc_y.size(), siz = mid_siz + point_num;
                    mixed_asc_y.reserve(siz);
                    for (const auto& [y, pid] : ps_asc_y[r - 1]) mixed_asc_y.emplace_back(y, ~pid);
                    std::inplace_merge(mixed_asc_y.begin(), mixed_asc_y.begin() + mid_siz, mixed_asc_y.end(), comp_key);
                    for (int t = 0; t < siz; ++t) {
                        const Key pkey = t ? mixed_asc_y[t - 1] : Key{ 0, 0 }, key = mixed_asc_y[t];
                        num_y += t and comp_key(pkey, key) and (pkey.second < 0) and (key.second >= 0);
                        const int i = key.second;
                        (i >= 0 ? es_comp_y[i] : ps_comp_y[~i]) = num_y;
                    }
                    ++num_y;
                }
                atcoder::fenwick_tree<T> ft(num_y);
                for (int j = 0, i = 2 * l; j < point_num; ++j) {
                    const auto &[px, pid] = ps_asc_x[r - 1][j];
                    for (; i < 2 * r; ++i) {
                        const auto &[ex, eid] = es_asc_x[i];
                        if (px < ex) break;
                        const T& w = _weights[eid >> 1];
                        ft.add(es_comp_y[eid & ~1], (eid & 1) ? -w : +w);
                        ft.add(es_comp_y[eid | 1], (eid & 1) ? +w : -w);
                    }
                    ans[pid] += ft.sum(0, ps_comp_y[pid] + 1);
                }
                for (Key &key : ps_asc_x[r - 1]) if (int d = _times[key.second] - r) {
                    ps_asc_x[r + floor_pow2(d) - 1].push_back(std::move(key));
                }
                ps_asc_x[r - 1].clear(), ps_asc_x[r - 1].shrink_to_fit();
                for (Key &key : ps_asc_y[r - 1]) if (int d = _times[key.second] - r) {
                    ps_asc_y[r + floor_pow2(d) - 1].push_back(std::move(key));
                }
                ps_asc_y[r - 1].clear(), ps_asc_y[r - 1].shrink_to_fit();
            }
            return ans;
        }
    private:
        std::vector<Rectangle> _rects{};
        std::vector<T> _weights{};
        std::vector<Point> _points{};
        std::vector<int> _times{};

        static int floor_pow2(int x) { return 1 << (31 - __builtin_clz(x)); }
    };
} // namespace suisen

#endif // SUISEN_OFFLINE_RECT_ADD_POINT_GET
