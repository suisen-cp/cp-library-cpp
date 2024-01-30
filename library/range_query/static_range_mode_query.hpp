#ifndef SUISEN_STATIC_RANGE_MODE_QUERY
#define SUISEN_STATIC_RANGE_MODE_QUERY

#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

namespace suisen {
    template <typename T>
    struct StaticRangeModeQuery {
        StaticRangeModeQuery() = default;
        explicit StaticRangeModeQuery(const std::vector<T> &a): _len(a.size()), _block_size(::sqrt(_len)), _block_num(_cld(_len, _block_size)) {
            // Computing the mapping from compressed values to original values
            _sorted = a;
            std::sort(_sorted.begin(), _sorted.end());
            _sorted.erase(std::unique(_sorted.begin(), _sorted.end()), _sorted.end());
            const int k = _sorted.size();

            // Bucket sort
            _a.resize(_len);
            _start.assign(k + 1, 0);
            for (int i = 0; i < _len; ++i) {
                // Compress
                _a[i] = std::lower_bound(_sorted.begin(), _sorted.end(), a[i]) - _sorted.begin();
                ++_start[_a[i]];
            }
            for (int i = 0; i < k; ++i) _start[i + 1] += _start[i];
            _pos.resize(_len);
            _pos_inv.resize(_len);
            for (int i = _len - 1; i >= 0; --i) {
                const int pos_index = --_start[_a[i]];
                _pos[pos_index] = i;
                _pos_inv[i] = pos_index;
            }

            // Precomputing
            _mode_blocks.assign((_block_num + 1) * (_block_num + 1), { 0, 0 });
            std::vector<int> freq(k);
            for (int l_block = 0; l_block <= _block_num; ++l_block) {
                freq.assign(k, 0);
                std::pair<int, int> mode{ 0, 0 }; // (max freq, mode)
                for (int r_block = l_block + 1; r_block <= _block_num; ++r_block) {
                    const int l_index = (r_block - 1) * _block_size;
                    const int r_index = std::min(_len, r_block * _block_size);
                    for (int i = l_index; i < r_index; ++i) {
                        mode = std::max(mode, { ++freq[_a[i]], _a[i] });
                    }
                    _query_blocks(l_block, r_block) = mode;
                }
            }
        }

        std::pair<T, int> query(const int l, const int r) const {
            assert(0 <= l and l < r and r <= _len);
            const int l_block = _cld(l, _block_size);
            const int r_block = _fld(r, _block_size);
            auto [freq, mode] = _query_blocks(l_block, r_block);
            for (int i = l; i < std::min(r, l_block * _block_size); ++i) {
                const int v = _a[i], pos_index = _pos_inv[i];
                if (not _check_right_bound(v, pos_index + freq, r)) continue;
                do ++freq; while (_check_right_bound(v, pos_index + freq, r));
                mode = v;
            }
            for (int i = r - 1; i >= std::max(l, r_block * _block_size); --i) {
                const int v = _a[i], pos_index = _pos_inv[i];
                if (not _check_left_bound(v, pos_index - freq, l)) continue;
                do ++freq; while (_check_left_bound(v, pos_index - freq, l));
                mode = v;
            }
            return { _sorted[mode], freq };
        }
        std::pair<T, int> operator()(int l, int r) const { return query(l, r); }
    private:
        int _len, _block_size, _block_num;
        // Mapping from compressed values to original values
        std::vector<T> _sorted;
        // Array of compressed values
        std::vector<int> _a;
        // Permutation sorted by (_a[i], i)
        std::vector<int> _pos;
        // Inverse permutation of _pos
        std::vector<int> _pos_inv;
        // _start[v] = min{ i | _a[_pos[i]]=v }
        std::vector<int> _start;
        // Flatten array of _mode_blocks[l][r] := (max freq, mode) of _a[l*_block_size,r*_block_size)
        std::vector<std::pair<int, int>> _mode_blocks;

        const auto& _query_blocks(int l_block, int r_block) const { return _mode_blocks[l_block * (_block_num + 1) + r_block]; }
        auto& _query_blocks(int l_block, int r_block) { return _mode_blocks[l_block * (_block_num + 1) + r_block]; }

        int _check_left_bound(int v, int pos_index, int l) const { return _start[v] <= pos_index and l <= _pos[pos_index]; }
        int _check_right_bound(int v, int pos_index, int r) const { return pos_index < _start[v + 1] and _pos[pos_index] < r; }

        static int _cld(int num, int den) { return (num + den - 1) / den; }
        static int _fld(int num, int den) { return num / den; }
    };
} // namespace suisen

#endif // SUISEN_STATIC_RANGE_MODE_QUERY
