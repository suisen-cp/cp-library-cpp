#include <iostream>
#include <limits>
#include <vector>

namespace suisen {
class dynamic_bitset {
    public:
        explicit dynamic_bitset() {}
        explicit dynamic_bitset(const unsigned int n) {
            _bits.assign(outer_index(n) + 1, 0ULL);
        }
        inline int size() const {
            return _bits.size() * BLOCK_SIZE;
        }
        dynamic_bitset& operator|=(const dynamic_bitset& other) {
            ensure_size(other.size());
            int siz = other._bits.size();
            for (int i = 0; i < siz; ++i) {
                _bits[i] |= other._bits[i];
            }
            cut_leading_zeros();
            return *this;
        }
        dynamic_bitset& operator&=(const dynamic_bitset& other) {
            ensure_size(other.size());
            int siz = other._bits.size();
            for (int i = 0; i < siz; ++i) {
                _bits[i] &= other._bits[i];
            }
            _bits.erase(_bits.begin() + siz, _bits.end());
            cut_leading_zeros();
            return *this;
        }
        dynamic_bitset& operator^=(const dynamic_bitset& other) {
            ensure_size(other.size());
            int siz = other._bits.size();
            for (int i = 0; i < siz; ++i) {
                _bits[i] ^= other._bits[i];
            }
            cut_leading_zeros();
            return *this;
        }
        dynamic_bitset& operator<<=(const unsigned int shamt) {
            if (size() == 0) return *this;
            int ishamt = outer_index(shamt);
            int lshamt = inner_index(shamt);
            if (lshamt) {
                ensure_size(size() + shamt);
                int rshamt = BLOCK_SIZE - lshamt;
                int siz = _bits.size();
                for (int i = siz - 1; i > ishamt; --i) {
                    _bits[i] = (_bits[i - ishamt] << lshamt) | (_bits[i - ishamt - 1] >> rshamt);
                }
                _bits[ishamt] = _bits[0] << lshamt;
                std::fill(_bits.begin(), _bits.begin() + ishamt, 0ULL);
            } else {
                _bits.insert(_bits.begin(), ishamt, 0ULL);
            }
            cut_leading_zeros();
            return *this;
        }
        dynamic_bitset& operator>>=(const unsigned int shamt) {
            int ishamt = outer_index(shamt);
            if (ishamt >= _bits.size()) {
                _bits.clear();
                return *this;
            }
            int rshamt = inner_index(shamt);
            if (rshamt) {
                int lshamt = BLOCK_SIZE - rshamt;
                int sz = _bits.size();
                for (int i = 0; i + ishamt + 1 < sz; ++i) {
                    _bits[i] = (_bits[i + ishamt] >> rshamt) | (_bits[i + ishamt + 1] << lshamt);
                }
                _bits[sz - ishamt - 1] = _bits[sz - 1] >> rshamt;
                _bits.erase(_bits.end() - ishamt, _bits.end());
            } else {
                _bits.erase(_bits.begin(), _bits.begin() + ishamt);
            }
            cut_leading_zeros();
            return *this;
        }
        dynamic_bitset operator|(const dynamic_bitset& other) {
            return dynamic_bitset(_bits) |= other;
        }
        dynamic_bitset operator&(const dynamic_bitset& other) {
            return dynamic_bitset(_bits) &= other;
        }
        dynamic_bitset operator^(const dynamic_bitset& other) {
            return dynamic_bitset(_bits) ^= other;
        }
        dynamic_bitset operator<<(const unsigned int shamt) {
            return dynamic_bitset(_bits) <<= shamt;
        }
        dynamic_bitset operator>>(const unsigned int shamt) {
            return dynamic_bitset(_bits) >>= shamt;
        }
        bool operator[](const unsigned int n) const {
            if (n >= size()) return false;
            return (_bits[outer_index(n)] >> inner_index(n)) & 1;
        }
        void set(const unsigned int n, bool val = true) {
            if (not val and n >= size()) return;
            if (val) {
                ensure_size(n + 1);
                _bits[outer_index(n)] |= 1ULL << inner_index(n);
            } else {
                _bits[outer_index(n)] &= ~(1ULL << inner_index(n));
            }
        }
        void range_set(const unsigned int l, const unsigned int r, bool val = true) {
            if (not val and l >= size()) return;
            const int out_l = outer_index(l), out_r = outer_index(r - 1);
            const int in_l = inner_index(l), in_r = inner_index(r - 1);
            const unsigned long long mask_r = in_r == 63 ? ~0ULL : (1ULL << (in_r + 1)) - 1ULL;
            const unsigned long long mask_l = in_l == 0  ?  0ULL : (1ULL << in_l) - 1ULL;
            if (val) {
                ensure_size(r + 1);
                if (out_l < out_r) {
                    _bits[out_l] |= ~0ULL ^ mask_l;
                    for (int i = out_l + 1; i <= out_r - 1; ++i) {
                        _bits[i] = ~0ULL;
                    }
                    _bits[out_r] |= mask_r;
                } else {
                    _bits[out_l] |= mask_r ^ mask_l;
                }
            } else {
                if (out_l < out_r) {
                    _bits[out_l] &= mask_l;
                    for (int i = out_l + 1; i <= out_r - 1; ++i) {
                        _bits[i] = 0ULL;
                    }
                    _bits[out_r] &= ~mask_r;
                } else {
                    _bits[out_l] &= ~(mask_r ^ mask_l);
                }
                cut_leading_zeros();
            }
        }
        void clear() {
            _bits.clear();
        }
        void flip(const unsigned int n) {
            ensure_size(n + 1);
            _bits[outer_index(n)] ^= 1ULL << inner_index(n);
        }
        friend std::ostream& operator<<(std::ostream &out, const dynamic_bitset &bs) {
            std::string res;
            for (auto it = bs._bits.rbegin(); it != bs._bits.rend(); ++it) {
                unsigned long long bits = *it;
                for (int j = BLOCK_SIZE - 1; j >= 0; --j) {
                    res += char('0' + ((bits >> j) & 1));
                }
            }
            out << res;
            return out;
        }
        const std::vector<unsigned long long>& data() const {
            return _bits;
        }
    private:
        static constexpr unsigned int BLOCK_SIZE = std::numeric_limits<unsigned long long>::digits;
        static constexpr unsigned int LOG_BLOCK_SIZE = __builtin_ctz(BLOCK_SIZE);
    
        std::vector<unsigned long long> _bits;

        dynamic_bitset(const std::vector<unsigned long long> &bits) : _bits(bits) {}

        static constexpr unsigned int outer_index(unsigned int k) {
            return k >> LOG_BLOCK_SIZE;
        }
        static constexpr unsigned int inner_index(unsigned int k) {
            return k & (BLOCK_SIZE - 1);
        }
        void ensure_size(const unsigned int n) {
            int old_size = _bits.size();
            int new_size = outer_index(n == 0 ? n : n - 1) + 1;
            if (new_size > old_size) {
                _bits.resize(new_size, 0ULL);
            }
        }
        void cut_leading_zeros() {
            while (_bits.size() and _bits.back() == 0ULL) _bits.pop_back();
        }
};
} // namespace suisen