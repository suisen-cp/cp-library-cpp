#ifndef SUISEN_GAUSSIAN_ELIMINATION_F2
#define SUISEN_GAUSSIAN_ELIMINATION_F2

#include "library/linear_algebra/matrix_f2.hpp"

namespace suisen {
    struct SolutionSpace {
        SolutionSpace() : _solution(std::nullopt), _basis{} {}
        SolutionSpace(const std::optional<DynamicBitSet> &solution, const std::vector<DynamicBitSet> &basis = {}) : _solution(solution), _basis(basis) {}
        int dim() const { return _basis.size(); }
        int rank() const { return _solution->size() - _basis.size(); }
        bool has_solution() const { return bool(_solution); }
        const DynamicBitSet& solution() const { return *_solution; }
        const std::vector<DynamicBitSet>& basis() const { return _basis; }

        SolutionSpace normalized() {
            SolutionSpace res{ _solution };
            res += *this;
            res._normalized = true;
            return res;
        }
        void normalize() {
            *this = normalized();
        }
        bool add_base(DynamicBitSet v) {
            assert(_normalized);
            for (const auto& e : _basis) if (DynamicBitSet w = e ^ v; w < v) v = std::move(w);
            return v ? (_basis.push_back(v), true) : false;
        }
        friend SolutionSpace& operator+=(SolutionSpace& s, const SolutionSpace& t) {
            for (const DynamicBitSet& base : t._basis) s.add_base(base);
            return s;
        }
        friend SolutionSpace operator+(SolutionSpace s, const SolutionSpace& t) {
            s += t;
            return s;
        }
        friend SolutionSpace& operator&=(SolutionSpace& s, const SolutionSpace& t) {
            return s = s & t;
        }
        friend SolutionSpace operator&(const SolutionSpace& s, const SolutionSpace& t) {
            if (not s._normalized and t._normalized) return t & s;
            assert(s._normalized);
            std::vector<std::pair<DynamicBitSet, DynamicBitSet>> basis;
            for (const DynamicBitSet& e : s._basis) basis.emplace_back(e, e);
            SolutionSpace res;
            for (DynamicBitSet e : t._basis) {
                DynamicBitSet s(e.size());
                for (const auto& [v, t] : basis) if (DynamicBitSet w = e ^ v; w < e) e = std::move(w), s ^= t;
                if (e) basis.emplace_back(e, s);
                else res.add_base(s);
            }
            return res;
        }
    private:
        bool _normalized = false;
        std::optional<DynamicBitSet> _solution;
        std::vector<DynamicBitSet> _basis;
    };

    SolutionSpace gaussian_elimination_f2(MatrixF2 A, const DynamicBitSet &b) {
        assert(A.row_size() == b.size());
        const std::size_t n = A.row_size(), m = A.col_size();
        for (std::size_t i = 0; i < n; ++i) A[i].push_back(b[i]);

        std::vector<std::size_t> ones, zeros;
        std::size_t rank = 0;
        for (std::size_t j = 0; rank < n and j < m; ++j) {
            for (std::size_t i = rank + 1; i < n; ++i) if (A[i][j]) {
                std::swap(A[rank], A[i]);
                if (A[i][j]) A[i] ^= A[rank];
            }
            if (A[rank][j]) {
                for (std::size_t i = 0; i < rank; ++i) if (A[i][j]) A[i] ^= A[rank];
                ++rank;
                ones.push_back(j);
            } else {
                zeros.push_back(j);
            }
        }
        for (std::size_t i = rank; i < n; ++i) {
            if (A[i][m]) return SolutionSpace{};
        }
        DynamicBitSet solution(m);
        for (std::size_t i = 0; i < rank; ++i) {
            solution[ones[i]] = A[i][m];
        }
        std::vector<DynamicBitSet> basis;
        for (std::size_t j : zeros) {
            DynamicBitSet base(m);
            for (std::size_t i = 0; i < rank; ++i) base[ones[i]] = A[i][j];
            base[j] = 1;
            basis.push_back(std::move(base));
        }
        return SolutionSpace{ solution, basis };
    }
} // namespace suisen


#endif // SUISEN_GAUSSIAN_ELIMINATION_F2
