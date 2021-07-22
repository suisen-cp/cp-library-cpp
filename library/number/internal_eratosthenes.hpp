#ifndef SUISEN_INTERNAL_ERATOSTHENES
#define SUISEN_INTERNAL_ERATOSTHENES

#include <cstdint>
#include <cassert>

namespace suisen::internal::sieve {

constexpr std::uint8_t K = 8;
constexpr std::uint8_t PROD = 2 * 3 * 5;
constexpr std::uint8_t RM[K] = { 1,  7, 11, 13, 17, 19, 23, 29 };
constexpr std::uint8_t DR[K] = { 6,  4,  2,  4,  2,  4,  6,  2 };
constexpr std::uint8_t DF[K][K] = {
    { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 1, 1, 0, 1, 1, 1, 1 },
    { 2, 2, 0, 2, 0, 2, 2, 1 }, { 3, 1, 1, 2, 1, 1, 3, 1 },
    { 3, 3, 1, 2, 1, 3, 3, 1 }, { 4, 2, 2, 2, 2, 2, 4, 1 },
    { 5, 3, 1, 4, 1, 3, 5, 1 }, { 6, 4, 2, 4, 2, 4, 6, 1 },
};
constexpr std::uint8_t DRP[K] = { 180, 120,  60, 120,  60, 120, 180,  60 };
constexpr std::uint8_t DFP[K][K] = {
    {   0,   0,   0,   0,   0,   0,   0,  30 }, {  30,  30,  30,   0,  30,  30,  30,  30 },
    {  60,  60,   0,  60,   0,  60,  60,  30 }, {  90,  30,  30,  60,  30,  30,  90,  30 },
    {  90,  90,  30,  60,  30,  90,  90,  30 }, { 120,  60,  60,  60,  60,  60, 120,  30 },
    { 150,  90,  30, 120,  30,  90, 150,  30 }, { 180, 120,  60, 120,  60, 120, 180,  30 },
};

constexpr std::uint8_t MASK[K][K] = {
    { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 }, { 0x02, 0x20, 0x10, 0x01, 0x80, 0x08, 0x04, 0x40 },
    { 0x04, 0x10, 0x01, 0x40, 0x02, 0x80, 0x08, 0x20 }, { 0x08, 0x01, 0x40, 0x20, 0x04, 0x02, 0x80, 0x10 },
    { 0x10, 0x80, 0x02, 0x04, 0x20, 0x40, 0x01, 0x08 }, { 0x20, 0x08, 0x80, 0x02, 0x40, 0x01, 0x10, 0x04 },
    { 0x40, 0x04, 0x08, 0x80, 0x01, 0x10, 0x20, 0x02 }, { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 },
};
constexpr std::uint8_t OFFSET[K][K] = {
    {  1,  7, 11, 13, 17, 19, 23, 29 }, {  7, 19, 17,  1, 29, 13, 11, 23 },
    { 11, 17,  1, 23,  7, 29, 13, 19 }, { 13,  1, 23, 19, 11,  7, 29, 17 },
    { 17, 29,  7, 11, 19, 23,  1, 13 }, { 19, 13, 29,  7, 23,  1, 17, 11 },
    { 23, 11, 13, 29,  1, 17, 19,  7 }, { 29, 23, 19, 17, 13, 11,  7,  1 },
};

constexpr std::uint8_t mask_to_index(const std::uint8_t bits) {
    switch (bits) {
        case 1 << 0: return 0;
        case 1 << 1: return 1;
        case 1 << 2: return 2;
        case 1 << 3: return 3;
        case 1 << 4: return 4;
        case 1 << 5: return 5;
        case 1 << 6: return 6;
        case 1 << 7: return 7;
        default: assert(false);
    }
}
} // namespace suisen::internal::sieve

#endif // SUISEN_INTERNAL_ERATOSTHENES
