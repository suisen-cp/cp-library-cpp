#ifndef SUISEN_NIMBER
#define SUISEN_NIMBER

#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>

#ifdef _MSC_VER
#  include <intrin.h>
#else
#  include <x86intrin.h>
#endif

namespace suisen {
    namespace internal::nimber {
        constexpr size_t L = 8;
        constexpr size_t B = 1 << L;

        constexpr uint8_t get_kth_block(uint64_t x, uint8_t k) {
            using namespace internal::nimber;
            return (x >> (L * k)) & 0xffu;
        }

        // x * y
        struct table_x_mul_y_constexpr {
            std::array<std::array<uint64_t, B>, B> tab;
            constexpr table_x_mul_y_constexpr() : tab() {
                for (uint32_t x = 0; x < B; ++x) for (uint32_t y = 0; y < B; ++y) {
                    tab[x][y] = mul_rec(x, y);
                }
            }
            constexpr uint64_t operator()(uint32_t x, uint32_t y) const {
                return tab[x][y];
            }
            constexpr uint64_t mul_rec(uint64_t x, uint64_t y) const {
                if (x > y) return mul_rec(y, x);
                if (x == 0) return 0;
                if (x == 1) return y;
                if (x < B and y < B and tab[x][y]) return tab[x][y];
                for (uint8_t shamt = 32;; shamt >>= 1) {
                    uint64_t mask = (uint64_t(1) << shamt) - 1;
                    uint64_t xu = x >> shamt, xl = x & mask;
                    uint64_t yu = y >> shamt, yl = y & mask;
                    if (xu) {
                        uint64_t zll = mul_rec(xl, yl);
                        uint64_t zul = mul_rec(xu, yl);
                        uint64_t zlu = mul_rec(xl, yu);
                        uint64_t zuu = mul_rec(xu, yu);
                        return zll ^ ((zlu ^ zul ^ zuu) << shamt) ^ mul_rec(zuu, uint64_t(1) << (shamt - 1));
                    } else if (yu) {
                        return (mul_rec(xl, yu) << shamt) ^ mul_rec(xl, yl);
                    }
                }
            }
        } table_x_mul_y{};

        // 2^8i * 2^8j * x
        struct table_2_8i_mul_2_8j_mul_x_constexpr {
            std::array<std::array<std::array<uint64_t, B>, L>, L> tab;
            constexpr table_2_8i_mul_2_8j_mul_x_constexpr() : tab() {
                for (uint32_t i = 0; i < L; ++i) for (uint32_t j = 0; j < L; ++j) {
                    uint64_t mul_2_8i_2_8j = table_x_mul_y.mul_rec(uint64_t(1) << (8 * i), uint64_t(1) << (8 * j));
                    for (uint32_t x = 0; x < B; ++x) {
                        tab[i][j][x] = table_x_mul_y.mul_rec(mul_2_8i_2_8j, x);
                    }
                }
            }
            constexpr uint64_t operator()(uint32_t i, uint32_t j, uint32_t x) const {
                return tab[i][j][x];
            }
        } table_2_8i_mul_2_8j_mul_x{};

        template <typename std::size_t SIZE = 64>
        struct nimber {
            static_assert(SIZE > 0 and (SIZE & -SIZE) == SIZE); // SIZE must be power of 2.

            constexpr nimber(uint64_t x = 0) : _val(x) {}

            constexpr uint64_t val() const { return _val; }

            static constexpr nimber zero() { return 0; }
            static constexpr nimber one()  { return 1; }

            friend constexpr bool operator==(const nimber& x, const nimber& y) { return x._val == y._val; }
            friend constexpr bool operator!=(const nimber& x, const nimber& y) { return x._val != y._val; }
            friend constexpr bool operator< (const nimber& x, const nimber& y) { return x._val <  y._val; }
            friend constexpr bool operator<=(const nimber& x, const nimber& y) { return x._val <= y._val; }
            friend constexpr bool operator> (const nimber& x, const nimber& y) { return x._val >  y._val; }
            friend constexpr bool operator>=(const nimber& x, const nimber& y) { return x._val >= y._val; }

            friend constexpr nimber operator+(const nimber& x) { return x; }
            friend constexpr nimber operator-(const nimber& x) { return x; }

            friend constexpr nimber operator+(const nimber& x, const nimber& y) { return x._val ^ y._val; }
            friend constexpr nimber operator-(const nimber& x, const nimber& y) { return x._val ^ y._val; }
            friend constexpr nimber operator*(const nimber& x, const nimber& y) {
                uint64_t res = 0;
                for (uint8_t i = 0; i < block_num; ++i) {
                    uint64_t xi = get_kth_block(x._val, i);
                    for (uint8_t j = 0; j < block_num; ++j) {
                        uint64_t yj = get_kth_block(y._val, j);
                        res ^= table_2_8i_mul_2_8j_mul_x(i, j, table_x_mul_y(xi, yj));
                    }
                }
                return res;
            }
            friend constexpr nimber operator/(const nimber& x, const nimber& y) { return x * y.inv(); }
            
            friend constexpr nimber& operator+=(nimber& x, const nimber& y) { return x = x + y; }
            friend constexpr nimber& operator-=(nimber& x, const nimber& y) { return x = x - y; }
            friend constexpr nimber& operator*=(nimber& x, const nimber& y) { return x = x * y; }
            friend constexpr nimber& operator/=(nimber& x, const nimber& y) { return x = x / y; }

            nimber inv() const {
                uint32_t q = 0;
                while (__uint128_t(1) << (1 << q) <= _val) ++q;
                return pow((__uint128_t(1) << (1 << q)) - 2);
            }
            nimber pow(uint64_t b) const {
                nimber res = 1, pow_a = *this;
                for (; b; b >>= 1) {
                    if (b & 1) res *= pow_a;
                    pow_a *= pow_a;
                }
                return res;
            }

            constexpr operator bool() { return _val != 0; }
            constexpr operator uint64_t() { return _val; }

            friend std::ostream& operator<<(std::ostream& ous, const nimber& x) { return ous << x._val; }
            friend std::istream& operator>>(std::istream& ins, nimber& x) { return ins >> x._val; }
        private:
            uint64_t _val;

            static constexpr std::size_t block_num = (SIZE + L - 1) / L;
        };
    }
    using nimber64_t = internal::nimber::nimber<64>;
    using nimber32_t = internal::nimber::nimber<32>;
    using nimber16_t = internal::nimber::nimber<16>;
    using nimber8_t = internal::nimber::nimber<8>;
    using nimber4_t = internal::nimber::nimber<4>;
    using nimber2_t = internal::nimber::nimber<2>;
    using nimber1_t = internal::nimber::nimber<1>;
    using nimber = nimber64_t;
} // namespace suisen

namespace std {
    template <size_t SIZE>
    struct hash<suisen::internal::nimber::nimber<SIZE>> {
        size_t operator()(const suisen::internal::nimber::nimber<SIZE>& x) const { return hash<uint64_t>()(x.val()); }
    };
} // namespace std

#endif // SUISEN_NIMBER
