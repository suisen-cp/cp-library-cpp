#ifndef SUISEN_COMPRESSED_SEGMENT_TREE
#define SUISEN_COMPRESSED_SEGMENT_TREE

#include <algorithm>
#include <array>
#include <vector>

namespace suisen {
    namespace internal::compressed_segment_tree {
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
    struct CompressedSegmentTree {
        using value_type = T;
        using index_type = Index;
        using point_type = std::array<index_type, K>;
        using cube_type = std::array<std::pair<index_type, index_type>, K>;
        using data_type = CompressedSegmentTree<value_type, op, e, inv, K - 1, index_type>;

        CompressedSegmentTree() = default;

        void add_point(const point_type& p) {
            comp.add(p[0]);
            points.push_back(p);
        }
        void build() {
            n = comp.build();
            data.assign(2 * n, data_type{});
            for (const auto& p : points) for (int k = n + comp(p[0]); k; k >>= 1) {
                data[k - 1].add_point(tail(p));
            }
            points.clear();
            points.shrink_to_fit();
            for (auto& t : data) t.build();
        }

        value_type query(const cube_type& p) const {
            auto tp = tail(p);
            value_type sml = e(), smr = e();
            int l = comp(p[0].first) + n, r = comp(p[0].second) + n;
            for (; l < r; l >>= 1, r >>= 1) {
                if (l & 1) sml = op(sml, data[l++].query(tp));
                if (r & 1) smr = op(data[--r].query(tp), smr);
            }
            return op(sml, smr);
        }
        void set(const point_type& p, const value_type& val) {
            int i = comp(p[0]) + n;
            while (i >>= 1) data[i].set(tail(p), val);
        }
    private:
        int n;
        internal::compressed_segment_tree::Compressor<index_type> comp;
        std::vector<point_type> points;
        std::vector<data_type> data;

        template <typename X>
        static constexpr auto tail(const X& p) {
            return tail_impl(p, std::make_index_sequence<K - 1>{});
        }
        template <typename X, std::size_t... Seq>
        static constexpr auto tail_impl(const X& p, std::index_sequence<Seq...>) {
            return std::conditional_t<std::is_same_v<X, point_type>, typename data_type::point_type, typename data_type::cube_type>{ p[1 + Seq]... };
        }
    };
    template <typename T, T(*op)(T, T), T(*e)(), typename Index>
    struct CompressedSegmentTree<T, op, e, std::size_t(1), Index> {
        using value_type = T;
        using index_type = Index;
        using point_type = index_type;
        using cube_type = std::pair<index_type, index_type>;
        using data_type = value_type;

        CompressedSegmentTree() = default;

        void add_point(const point_type& p) { comp.add(p); }
        void build() {
            n = comp.build();
            data.assign(2 * n, e());
        }

        value_type query(const index_type& l, const index_type& r) const {
            return query({ l, r });
        }
        value_type query(const cube_type& p) const {
            value_type sml = e(), smr = e();
            int l = comp(p.first) + n, r = comp(p.second) + n;
            for (; l < r; l >>= 1, r >>= 1) {
                if (l & 1) sml = op(sml, data[l++]);
                if (r & 1) smr = op(data[--r], smr);
            }
            return op(sml, smr);
        }

        void set(const point_type& p, const value_type& val) {
            int i = comp(p) + n;
            data[i] = val;
            while (i >>= 1) data[i] = op(data[2 * i + 0], data[2 * i + 1]);
        }
    private:
        int n;
        internal::compressed_segment_tree::Compressor<index_type> comp;
        std::vector<data_type> data;
    };
} // namespace suisen


#endif // SUISEN_COMPRESSED_SEGMENT_TREE