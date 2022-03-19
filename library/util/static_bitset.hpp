#ifndef SUISEN_STATIC_BITSET
#define SUISEN_STATIC_BITSET

#include <array>
#include <cstdint>
#include <iostream>

namespace suisen {
    template <std::size_t N>
    struct static_bitset {
    private:
        static constexpr std::size_t L = (N + 63) >> 6;
    public:
        static_bitset() {}
        static_bitset(std::array<uint64_t, L> data) : _data(data) {}

        static_bitset<N>& operator&=(const static_bitset<N>& rhs) {
            for (std::size_t i = 0; i < L; ++i) _data[i] &= rhs._data[i];
            return *this;
        }
        static_bitset<N>& operator|=(const static_bitset<N>& rhs) {
            for (std::size_t i = 0; i < L; ++i) _data[i] |= rhs._data[i];
            return *this;
        }
        static_bitset<N>& operator^=(const static_bitset<N>& rhs) {
            for (std::size_t i = 0; i < L; ++i) _data[i] ^= rhs._data[i];
            return *this;
        }
        static_bitset<N> operator&(const static_bitset<N>& rhs) const {
            return static_bitset<N>(_data) &= rhs;
        }
        static_bitset<N> operator|(const static_bitset<N>& rhs) const {
            return static_bitset<N>(_data) |= rhs;
        }
        static_bitset<N> operator^(const static_bitset<N>& rhs) const {
            return static_bitset<N>(_data) ^= rhs;
        }
        static_bitset<N> operator~() const {
            static_bitset<N> res;
            for (std::size_t i = 0; i < L; ++i) res._data[i] = ~_data[i];
            return res;
        }
        static_bitset<N>& operator<<=(const std::size_t shamt) {
            if (shamt >= N) {
                _data.fill(0);
                return *this;
            }
            std::size_t large_shamt = outer_index(shamt);
            std::size_t small_shamt = inner_index(shamt);
            if (small_shamt) {
                std::size_t rshamt = 64 - small_shamt;
                for (std::size_t i = L - 1; i > large_shamt; --i) {
                    _data[i] = (_data[i - large_shamt] << small_shamt) | (_data[i - large_shamt - 1] >> rshamt);
                }
                _data[large_shamt] = _data[0] << small_shamt;
            } else {
                for (std::size_t i = L; i-- > large_shamt;) {
                    _data[i] = _data[i - large_shamt];
                }
            }
            for (std::size_t i = large_shamt; i-- > 0;) _data[i] = 0;
            return *this;
        }
        static_bitset<N>& operator>>=(const std::size_t shamt) {
            if (shamt >= N) {
                _data.fill(0);
                return *this;
            }
            if (shamt == 0) {
                return *this;
            }
            std::size_t large_shamt = outer_index(shamt);
            std::size_t small_shamt = inner_index(shamt);
            if (small_shamt) {
                std::size_t lshamt = 64 - small_shamt;
                for (std::size_t i = 0; i + large_shamt + 1 < L; ++i) {
                    _data[i] = (_data[i + large_shamt] >> small_shamt) | (_data[i + large_shamt + 1] << lshamt);
                }
                _data[L - large_shamt - 1] = _data[L - 1] >> small_shamt;
            } else {
                for (std::size_t i = 0; i + large_shamt < L; ++i) {
                    _data[i] = _data[i + large_shamt];
                }
            }
            for (std::size_t i = L - large_shamt; i < L; ++i) _data[i] = 0;
            return *this;
        }
        static_bitset<N> operator<<(const std::size_t shamt) const {
            return static_bitset<N>(_data) <<= shamt;
        }
        static_bitset<N> operator>>(const std::size_t shamt) const {
            return static_bitset<N>(_data) >>= shamt;
        }
        bool operator!=(const static_bitset<N>& rhs) const {
            for (std::size_t i = L; i-- > 0;) if (_data[i] != rhs._data[i]) return true;
            return false;
        }
        bool operator==(const static_bitset<N>& rhs) const {
            return not (*this != rhs);
        }
        bool operator<(const static_bitset<N>& rhs) const {
            for (std::size_t i = L; i-- > 0;) if (_data[i] != rhs._data[i]) return _data[i] < rhs._data[i];
            return false;
        }
        bool operator<=(const static_bitset<N>& rhs) const {
            return not (*this > rhs);
        }
        bool operator>(const static_bitset<N>& rhs) const {
            return rhs < *this;
        }
        bool operator>=(const static_bitset<N>& rhs) const {
            return not (*this < rhs);
        }
        bool operator[](std::size_t i) {
            return (_data[outer_index(i)] >> inner_index(i)) & 1;
        }
        operator bool() const {
            for (const auto& e : _data) if (e) return true;
            return false;
        }
        void range_set(const std::size_t l, const std::size_t r, bool val = true) {
            if (l >= r) return;
            const std::size_t out_l = outer_index(l), out_r = outer_index(r - 1);
            const std::size_t in_l = inner_index(l), in_r = inner_index(r - 1);
            const uint64_t mask_r = in_r == 63 ? ~0ULL : (1ULL << (in_r + 1)) - 1ULL;
            const uint64_t mask_l = in_l == 0 ? 0ULL : (1ULL << in_l) - 1ULL;
            if (val) {
                if (out_l < out_r) {
                    _data[out_l] |= ~0ULL ^ mask_l;
                    for (std::size_t i = out_l + 1; i < out_r; ++i) _data[i] = ~0ULL;
                    _data[out_r] |= mask_r;
                } else {
                    _data[out_l] |= mask_r ^ mask_l;
                }
            } else {
                if (out_l < out_r) {
                    _data[out_l] &= mask_l;
                    for (std::size_t i = out_l + 1; i < out_r; ++i) _data[i] = 0ULL;
                    _data[out_r] &= ~mask_r;
                } else {
                    _data[out_l] &= ~(mask_r ^ mask_l);
                }
            }
        }
        void set(const std::size_t n, bool val = true) {
            if (val) {
                _data[outer_index(n)] |= uint64_t(1) << inner_index(n);
            } else {
                _data[outer_index(n)] &= ~(uint64_t(1) << inner_index(n));
            }
        }
        void flip(const std::size_t n) {
            _data[outer_index(n)] ^= 1ULL << inner_index(n);
        }
        void clear() {
            _data.fill(0);
        }
        const std::array<uint64_t, L>& data() const {
            return _data;
        }
        friend std::ostream& operator<<(std::ostream& out, const static_bitset<N>& bs) {
            for (std::size_t i = N; i-- > 0;) out << char('0' + bs[i]);
            return out;
        }
    private:
        std::array<uint64_t, L> _data{};

        static constexpr std::size_t outer_index(std::size_t k) {
            return k >> 6;
        }
        static constexpr std::size_t inner_index(std::size_t k) {
            return k & 63;
        }
    };
} // namespace suisen


#endif // SUISEN_STATIC_BITSET
