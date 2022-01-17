#ifndef SUISEN_SEGMENT_TREE_2D
#define SUISEN_SEGMENT_TREE_2D

#include <cassert>
#include <vector>

namespace suisen {
    template <typename T, T(*op)(T, T), T(*e)()>
    struct SegmentTree2D {
        SegmentTree2D() {}
        SegmentTree2D(int n, int m) : SegmentTree2D(std::vector(2 * n, std::vector(2 * m, e()))) {}
        SegmentTree2D(const std::vector<std::vector<T>> &a) : n(a.size()), m(n == 0 ? 0 : a[0].size()), dat(2 * n, std::vector<T>(2 * m, e())) {
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
                dat[n + i][m + j] = a[i][j];
            }
            for (int i = 1; i < 2 * n; ++i) for (int j = m - 1; j > 0; --j) {
                dat[i][j] = op(dat[i][2 * j + 0], dat[i][2 * j + 1]);
            }
            for (int i = n - 1; i > 0; --i) for (int j = 1; j < 2 * m; ++j) {
                dat[i][j] = op(dat[2 * i + 0][j], dat[2 * i + 1][j]);
            }
        }

        T operator()(int u, int d, int l, int r) const {
            assert(0 <= u and u <= d and d <= n and 0 <= l and l <= r and r <= m);
            auto inner_query = [&](const auto &seg) {
                T res_l = e(), res_r = e();
                for (int tl = l + m, tr = r + m; tl < tr; tl >>= 1, tr >>= 1) {
                    if (tl & 1) res_l = op(res_l, seg[tl++]);
                    if (tr & 1) res_r = op(seg[--tr], res_r);
                }
                return op(res_l, res_r);
            };
            T res_u = e(), res_d = e();
            for (int tu = u + n, td = d + n; tu < td; tu >>= 1, td >>= 1) {
                if (tu & 1) res_u = op(res_u, inner_query(dat[tu++]));
                if (td & 1) res_d = op(inner_query(dat[--td]), res_d);
            }
            return op(res_u, res_d);
        }

        T get(int i, int j) const {
            assert(0 <= i and i < n and 0 <= j and j < m);
            return dat[n + i][m + j];
        }

        void set(int i, int j, const T &val) {
            assert(0 <= i and i < n and 0 <= j and j < m);
            dat[n + i][m + j] = val;
            for (int tj = (m + j) >> 1; tj; tj >>= 1) {
                dat[n + i][tj] = op(dat[n + i][2 * tj + 0], dat[n + i][2 * tj + 1]);
            }
            for (int ti = (n + i) >> 1; ti; ti >>= 1) {
                for (int tj = m + j; tj; tj >>= 1) {
                    dat[ti][tj] = op(dat[2 * ti + 0][tj], dat[2 * ti + 1][tj]);
                }
            }
        }

    private:
        int n, m;
        std::vector<std::vector<T>> dat;
    };
}

#endif // SUISEN_SEGMENT_TREE_2D
