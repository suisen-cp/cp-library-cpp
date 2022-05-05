#ifndef SUISEN_AUXILIARY_TREE
#define SUISEN_AUXILIARY_TREE

#include <algorithm>
#include "library/tree/heavy_light_decomposition.hpp"

namespace suisen {
    struct AuxiliaryTree {
        AuxiliaryTree() = default;
        AuxiliaryTree(const HeavyLightDecomposition& hld) : _n(hld.size()), _aux(_n), _hld(hld) {}

        const std::vector<int>& operator[](int u) const {
            return _aux[u];
        }

        void build(std::vector<int> vs) {
            const int k = vs.size();
            for (int v : _upd) _aux[v].clear();
            _upd.clear();

            std::sort(vs.begin(), vs.end(), [this](int i, int j) { return _hld.get_visit_time(i) < _hld.get_visit_time(j); });

            std::copy(vs.begin(), vs.end(), std::back_inserter(_upd));

            std::vector<int> st{ vs[0] };
            for (int i = 0; i < k - 1; ++i) {
                const int w = _hld.lca(vs[i], vs[i + 1]);

                if (w != vs[i]) {
                    _upd.push_back(w);
                    int last = st.back();
                    st.pop_back();
                    while (st.size() and _hld.get_depth(w) < _hld.get_depth(st.back())) {
                        int u = st.back();
                        _aux[u].push_back(last);
                        _aux[last].push_back(u);
                        last = st.back();
                        st.pop_back();
                    }

                    if (st.empty() or st.back() != w) {
                        st.push_back(w);
                        vs.push_back(w);
                        _aux[w].push_back(last);
                        _aux[last].push_back(w);
                    } else {
                        _aux[w].push_back(last);
                        _aux[last].push_back(w);
                    }
                }

                st.push_back(vs[i + 1]);
            }
            const int siz = st.size();
            for (int i = 0; i < siz - 1; ++i) {
                _aux[st[i]].push_back(st[i + 1]);
                _aux[st[i + 1]].push_back(st[i]);
            }
        }

        const HeavyLightDecomposition& get_hld() const {
            return _hld;
        }
    private:
        int _n;
        std::vector<std::vector<int>> _aux;
        HeavyLightDecomposition _hld;
        std::vector<int> _upd;
    };
} // namespace suisen

#endif // SUISEN_AUXILIARY_TREE
