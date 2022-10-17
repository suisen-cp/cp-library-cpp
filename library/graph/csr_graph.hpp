#ifndef SUISEN_CSR
#define SUISEN_CSR

#include <algorithm>
#include <cassert>
#include <limits>
#include <type_traits>
#include <tuple>
#include <vector>

namespace suisen {
    namespace internal::csr_graph { struct graph_base_tag {}; }
    struct directed_graph_tag : internal::csr_graph::graph_base_tag {};
    struct undirected_graph_tag : internal::csr_graph::graph_base_tag {};
    template <typename T>
    struct is_graph_tag { static constexpr bool value = std::is_base_of_v<internal::csr_graph::graph_base_tag, T>; };
    template <typename T>
    constexpr bool is_graph_tag_v = is_graph_tag<T>::value;

    template <typename WeightType = void>
    struct Graph {
        template <typename GraphTag, typename, std::enable_if_t<is_graph_tag_v<GraphTag>, std::nullptr_t>>
        friend struct GraphBuilder;

        using weight_type = WeightType;
        static constexpr bool weighted = std::negation_v<std::is_same<weight_type, void>>;

        using input_edge_type = std::conditional_t<weighted, std::tuple<int, int, weight_type>, std::pair<int, int>>;
    private:
        using internal_edge_type = std::conditional_t<weighted, std::pair<int, weight_type>, int>;
        struct Edge : public internal_edge_type {
            using internal_edge_type::internal_edge_type;
            operator int() const { return std::get<0>(*this); }
        };
    public:
        using edge_type = std::conditional_t<weighted, Edge, int>;
    private:
        struct AdjacentList {
            friend struct Graph;

            using value_type = edge_type;
            using iterator = typename std::vector<value_type>::iterator;
            using const_iterator = typename std::vector<value_type>::const_iterator;
            using reverse_iterator = typename std::vector<value_type>::reverse_iterator;
            using const_reverse_iterator = typename std::vector<value_type>::const_reverse_iterator;

            AdjacentList() = default;

            int size() const { return _siz; }
            bool empty() const { return _siz == 0; }
            int capacity() const { return _cap; }

            value_type& operator[](int i) { return *(begin() + i); }
            const value_type& operator[](int i) const { return *(cbegin() + i); }
            value_type& at(uint32_t i) { assert(i < _siz); return *(begin() + i); }
            const value_type& at(uint32_t i) const { assert(i < _siz); return *(cbegin() + i); }

            value_type* data() { return _g->_edges.data() + _offset; }
            const value_type* data() const { return _g->_edges.data() + _offset; }

            iterator begin() const { return _g->_edges.begin() + _offset; }
            iterator end() const { return begin() + _siz; }
            const_iterator cbegin() const { return _g->_edges.cbegin() + _offset; }
            const_iterator cend() const { return cbegin() + _siz; }
            reverse_iterator rbegin() const { return _g->_edges.rbegin() + (_g->_edges.size() - (_offset + _siz)); }
            reverse_iterator rend() const { return rbegin() + _siz; }
            const_reverse_iterator crbegin() const { return _g->_edges.crbegin() + (_g->_edges.size() - (_offset + _siz)); }
            const_reverse_iterator crend() const { return crbegin() + _siz; }

            void erase(const_iterator pos) {
                erase(pos, std::next(pos));
            }
            void erase(const_iterator first, const_iterator last) {
                const int num = last - first, k = first - cbegin();
                assert(num >= 0);
                if (num == 0) return;
                assert(0 <= k and k <= _siz - num);
                std::move(begin() + k + num, end(), begin() + k);
                _siz -= num;
            }
            void pop_back() {
                assert(_siz);
                --_siz;
            }
            void clear() { _siz = 0; }

            const value_type& back() const { return *--cend(); }
            value_type& back() { return *--end(); }
            const value_type& front() const { return *cbegin(); }
            value_type& front() { return *begin(); }

            void push_back(const value_type& x) {
                ++_siz;
                assert(_siz <= _cap);
                back() = x;
            }
            template <typename ...Args>
            void emplace_back(Args &&...args) {
                ++_siz;
                assert(_siz <= _cap);
                back() = value_type(std::forward<Args>(args)...);
            }

            void insert(const_iterator pos, const value_type& x) {
                emplace(pos, x);
            }
            void insert(const_iterator pos, int num, const value_type& x) {
                const int k = pos - cbegin();
                assert(0 <= k and k <= _siz);
                std::fill(begin() + k, shift_back(begin() + k, num), x);
            }
            template <class RandomAccessIterator>
            auto insert(const_iterator pos, RandomAccessIterator first, RandomAccessIterator last) -> decltype(*first++, last - first, void()) {
                const int num = last - first, k = pos - cbegin();
                assert(0 <= k and k <= _siz);
                shift_back(begin() + k, num);
                std::copy(first, last, begin() + k);
            }
            void insert(const_iterator pos, std::initializer_list<value_type> il) { insert(pos, il.begin(), il.end()); }
            template <typename ...Args>
            void emplace(const_iterator pos, Args &&...args) {
                const int k = pos - cbegin();
                assert(0 <= k and k <= _siz);
                *--shift_back(begin() + k) = value_type(std::forward<Args>(args)...);
            }
        private:
            mutable Graph* _g;
            int _cap;
            int _offset;
            int _siz;

            iterator shift_back(iterator pos, int num = 1) {
                _siz += num;
                assert(_siz <= _cap);
                return std::move_backward(pos, end() - num, end());
            }
        };
    public:
        using adjacent_list = AdjacentList;

        Graph() = default;

        template <typename GraphTag, std::enable_if_t<is_graph_tag_v<GraphTag>, std::nullptr_t> = nullptr>
        Graph(const int n, const std::vector<input_edge_type>& edges, GraphTag, std::vector<int> cap = {}) : _n(n), _adj(_n) {
            static constexpr bool undirected = std::is_same_v<undirected_graph_tag, GraphTag>;

            for (const auto& e : edges) {
                const int u = std::get<0>(e);
                const int v = std::get<1>(e);
                ++_adj[u]._siz;
                if constexpr (undirected) ++_adj[v]._siz;
            }
            if (cap.empty()) cap.resize(_n, std::numeric_limits<int>::max());
            int edge_num = 0;
            for (int i = 0; i < _n; ++i) {
                _adj[i]._g = this;
                _adj[i]._cap = std::min(_adj[i]._siz, cap[i]);
                _adj[i]._offset = edge_num;
                edge_num += _adj[i]._siz;
            }
            _edges.resize(edge_num);
            std::vector<typename std::vector<edge_type>::iterator> ptr(_n);
            for (int i = 0; i < _n; ++i) ptr[i] = _adj[i].begin();
            for (const auto& e : edges) {
                const int u = std::get<0>(e);
                const int v = std::get<1>(e);
                if constexpr (weighted) {
                    const weight_type& w = std::get<2>(e);
                    *ptr[u]++ = { v, w };
                    if constexpr (undirected) *ptr[v]++ = { u, w };
                } else {
                    *ptr[u]++ = v;
                    if constexpr (undirected) *ptr[v]++ = u;
                }
            }
        }
        Graph(const std::vector<std::vector<edge_type>> &g) : Graph(g.size(), make_edges(g), directed_graph_tag{}) {}

        static Graph create_directed_graph(const int n, const std::vector<input_edge_type>& edges, const std::vector<int> &cap = {}) {
            return Graph(n, edges, directed_graph_tag{}, cap);
        }
        static Graph create_undirected_graph(const int n, const std::vector<input_edge_type>& edges, const std::vector<int> &cap = {}) {
            return Graph(n, edges, undirected_graph_tag{}, cap);
        }

        adjacent_list& operator[](int i) {
            _adj[i]._g = this;
            return _adj[i];
        }
        const adjacent_list& operator[](int i) const {
            _adj[i]._g = const_cast<Graph*>(this);
            return _adj[i];
        }

        int size() const {
            return _n;
        }

        void shrink_to_fit() {
            int edge_num = 0;
            for (const auto& l : _adj) edge_num += l.size();

            std::vector<edge_type> new_edges(edge_num);
            auto it = new_edges.begin();
            for (int i = 0; i < _n; ++i) {
                int nl = it - new_edges.begin();
                it = std::move(_adj[i].begin(), _adj[i].end(), it);
                _adj[i]._offset = nl;
                _adj[i]._cap = _adj[i]._siz;
            }
            _edges.swap(new_edges);
        }

        static std::conditional_t<weighted, weight_type, int> get_weight(const edge_type& edge) {
            if constexpr (weighted) return std::get<1>(edge);
            else return 1;
        }

        Graph reversed(const std::vector<int> &cap = {}) const {
            std::vector<input_edge_type> edges;
            for (int i = 0; i < _n; ++i) {
                for (const auto &edge : (*this)[i]) {
                    if constexpr (weighted) edges.emplace_back(std::get<0>(edge), i, std::get<1>(edge));
                    else edges.emplace_back(edge, i);
                }
            }
            return Graph(_n, std::move(edges), directed_graph_tag{}, cap);
        }
    private:
        int _n;
        std::vector<adjacent_list> _adj;
        std::vector<edge_type> _edges;

        static std::vector<input_edge_type> make_edges(const std::vector<std::vector<edge_type>> &g) {
            const int n = g.size();
            std::vector<input_edge_type> edges;
            for (int i = 0; i < n; ++i) for (const auto &e : g[i]) {
                if constexpr (weighted) edges.emplace_back(i, std::get<0>(e), std::get<1>(e));
                else edges.emplace_back(i, e);
            }
            return edges;
        }
    };

    template <typename GraphTag>
    Graph(int, std::vector<std::pair<int, int>>, GraphTag, std::vector<int> = {}) -> Graph<void>;
    template <typename WeightType, typename GraphTag>
    Graph(int, std::vector<std::tuple<int, int, WeightType>>, GraphTag, std::vector<int> = {}) -> Graph<WeightType>;

    Graph(std::vector<std::vector<int>>) -> Graph<void>;
    template <typename WeightType>
    Graph(std::vector<std::vector<std::pair<int, WeightType>>>) -> Graph<WeightType>;

    template <typename GraphTag, typename WeightType = void,
        std::enable_if_t<is_graph_tag_v<GraphTag>, std::nullptr_t> = nullptr>
    struct GraphBuilder {
        using graph_tag = GraphTag;
        using weight_type = WeightType;
        using edge_type = typename Graph<weight_type>::input_edge_type;

        GraphBuilder(int n = 0) : _n(n) {}

        void add_edge(const edge_type& edge) {
            check_not_moved();
            _edges.push_back(edge);
        }
        template <typename ...Args>
        void emplace_edge(Args &&...args) {
            check_not_moved();
            _edges.emplace_back(std::forward<Args>(args)...);
        }
        template <typename EdgeContainer, std::enable_if_t<std::is_constructible_v<edge_type, typename EdgeContainer::value_type>, std::nullptr_t> = nullptr>
        void add_edges(const EdgeContainer &edges) {
            for (const auto &edge : edges) add_edge(edge);
        }

        template <bool move_edges = true>
        Graph<weight_type> build() {
            if constexpr (move_edges) {
                _moved = true;
                return Graph<weight_type>(_n, std::move(_edges), graph_tag{});
            } else {
                return Graph<weight_type>(_n, _edges, graph_tag{});
            }
        }
        Graph<weight_type> build_without_move() {
            return build<false>();
        }

        static Graph<weight_type> build(const int n, const std::vector<edge_type> &edges) {
            GraphBuilder builder(n);
            builder.add_edges(edges);
            return builder.build();
        }
    private:
        int _n;
        std::vector<edge_type> _edges;
        bool _moved = false;

        void check_not_moved() {
            if (not _moved) return;
            std::cerr << "[\033[31mERROR\033[m] Edges are already moved. If you want to add edges after calling build() and build another graph, you should use build_without_move() instead." << std::endl;
            assert(false);
        }
    };
    template <typename WeightType = void>
    using DirectedGraphBuilder = GraphBuilder<directed_graph_tag, WeightType>;
    template <typename WeightType = void>
    using UndirectedGraphBuilder = GraphBuilder<undirected_graph_tag, WeightType>;

    template <typename Weight, std::enable_if_t<std::negation_v<std::is_same<Weight, void>>, std::nullptr_t> = nullptr>
    using WeightedGraph = Graph<Weight>;
    using UnweightedGraph = Graph<void>;

    template <typename T>
    struct is_weighted_graph { static constexpr bool value = false; };
    template <typename WeightType>
    struct is_weighted_graph<Graph<WeightType>> { static constexpr bool value = Graph<WeightType>::weighted; };
    template <typename T>
    constexpr bool is_weighted_graph_v = is_weighted_graph<T>::value;

    template <typename T>
    struct is_unweighted_graph { static constexpr bool value = false; };
    template <typename WeightType>
    struct is_unweighted_graph<Graph<WeightType>> { static constexpr bool value = not Graph<WeightType>::weighted; };
    template <typename T>
    constexpr bool is_unweighted_graph_v = is_unweighted_graph<T>::value;
} // namespace suisen

#endif // SUISEN_CSR
