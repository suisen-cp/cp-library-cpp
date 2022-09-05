#ifndef SUISEN_COMPRESSED_FENWICK_TREE_PREFIX
#define SUISEN_COMPRESSED_FENWICK_TREE_PREFIX

#include <algorithm>
#include <array>
#include <vector>

namespace suisen {
    namespace internal::compressed_fenwick_tree_prefix {
        template <typename T>
        struct Compressor {
            using value_type = T;
            Compressor() = default;
            void add(const value_type& x) { xs.push_back(x); }
            int build() {
                std::sort(xs.begin(), xs.end());
                xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
                return xs.size();
            }
            int operator()(const value_type& x) const { return std::lower_bound(xs.begin(), xs.end(), x) - xs.begin(); }
        private:
            std::vector<value_type> xs;
        };
    }

    template <typename T, T(*op)(T, T), T(*e)(), std::size_t K = 1, typename Index = int>
    struct CompressedFenwickTreePrefix {
        using value_type = T;
        using index_type = Index;
        using point_type = std::array<index_type, K>;
        using data_type = CompressedFenwickTreePrefix<value_type, op, e, K - 1, index_type>;

        CompressedFenwickTreePrefix() = default;

        void add_point(const point_type& p) {
            comp.add(p[0]);
            points.push_back(p);
        }
        void build() {
            data.assign(n = comp.build(), data_type{});
            for (const auto& p : points) for (int k = comp(p[0]) + 1; k; k -= k & -k) {
                data[k - 1].add_point(tail(p));
            }
            points.clear();
            points.shrink_to_fit();
            for (auto& t : data) t.build();
        }

        value_type prefix_query(const point_type& p) const {
            value_type res = e();
            for (int r = comp(p[0]); r; r -= r & -r) res = op(res, data[r - 1].prefix_query(tail(p)));
            return res;
        }
        void apply(const point_type& p, const value_type& val) {
            for (int r = comp(p[0]) + 1; r <= n; r += r & -r) data[r - 1].apply(tail(p), val);
        }
    private:
        int n;
        internal::compressed_fenwick_tree_prefix::Compressor<index_type> comp;
        std::vector<point_type> points;
        std::vector<data_type> data;

        static constexpr auto tail(const point_type& p) {
            return tail_impl(p, std::make_index_sequence<K - 1>{});
        }
        template <std::size_t... Seq>
        static constexpr auto tail_impl(const point_type& p, std::index_sequence<Seq...>) {
            return typename data_type::point_type{ p[1 + Seq]... };
        }
    };
    template <typename T, T(*op)(T, T), T(*e)(), typename Index>
    struct CompressedFenwickTreePrefix<T, op, e, std::size_t(1), Index> {
        using value_type = T;
        using index_type = Index;
        using point_type = index_type;
        using data_type = value_type;

        CompressedFenwickTreePrefix() = default;

        void add_point(const point_type& p) { comp.add(p); }
        void build() { data.assign(n = comp.build(), e()); }

        value_type prefix_query(const point_type& p) const {
            value_type res = e();
            for (int r = comp(p); r; r -= r & -r) res = op(res, data[r - 1]);
            return res;
        }
        void apply(const point_type& p, const value_type& val) {
            for (int r = comp(p) + 1; r <= n; r += r & -r) data[r - 1] = op(data[r - 1], val);
        }
    private:
        int n;
        internal::compressed_fenwick_tree_prefix::Compressor<index_type> comp;
        std::vector<data_type> data;
    };
} // namespace suisen


#endif // SUISEN_COMPRESSED_FENWICK_TREE_PREFIX
