#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_large"

#include <iostream>
#include <cstring>

#include "library/convolution/convolution_large.hpp"

using mint = atcoder::modint998244353;

std::istream& operator>>(std::istream& in, mint& a) {
    long long e; in >> e; a = e;
    return in;
}

// from https://judge.yosupo.jp/submission/21623
namespace nyaan {
    namespace fastio {
        static constexpr uint32_t SZ = 1 << 17;
        char ibuf[SZ];
        char obuf[SZ];
        uint32_t pil = 0, pir = 0, por = 0;

        struct Pre {
            char num[40000];
            constexpr Pre() : num() {
                for (int i = 0; i < 10000; i++) {
                    int n = i;
                    for (int j = 3; j >= 0; j--) {
                        num[i * 4 + j] = n % 10 + '0';
                        n /= 10;
                    }
                }
            }
        } constexpr pre;

        __attribute__((target("avx2"), optimize("O3"))) inline void load() {
            memcpy(ibuf, ibuf + pil, pir - pil);
            pir = pir - pil + fread(ibuf + pir - pil, 1, SZ - pir + pil, stdin);
            pil = 0;
        }

        __attribute__((target("avx2"), optimize("O3"))) inline void flush() {
            fwrite(obuf, 1, por, stdout);
            por = 0;
        }

        inline void rd(char& c) { c = ibuf[pil++]; }

        template <typename T>
        __attribute__((target("avx2"), optimize("O3"))) inline void rd(T& x) {
            if (pil + 32 > pir) load();
            char c;
            do
                rd(c);
            while (c < '-');
            bool minus = 0;
            if constexpr (std::is_signed<T>::value) {
                if (c == '-') {
                    minus = 1;
                    rd(c);
                }
            }
            x = 0;
            while (c >= '0') {
                x = x * 10 + (c & 15);
                rd(c);
            }
            if constexpr (std::is_signed<T>::value) {
                if (minus) x = -x;
            }
        }

        inline void wt(char c) { obuf[por++] = c; }
        template <typename T>
        __attribute__((target("avx2"), optimize("O3"))) inline void wt(T x) {
            if (por + 32 > SZ) flush();
            if (!x) {
                wt('0');
                return;
            }
            if constexpr (std::is_signed<T>::value) {
                if (x < 0) {
                    wt('-');
                    x = -x;
                }
            }
            if (x >= 10000000000000000) {
                uint32_t r1 = x % 100000000;
                uint64_t q1 = x / 100000000;
                uint32_t r2 = q1 % 100000000;
                uint32_t q2 = q1 / 100000000;
                uint32_t n1 = r1 % 10000;
                uint32_t n2 = r1 / 10000;
                uint32_t n3 = r2 % 10000;
                uint32_t n4 = r2 / 10000;
                if (x >= 1000000000000000000) {
                    memcpy(obuf + por, pre.num + (q2 << 2) + 1, 3);
                    memcpy(obuf + por + 3, pre.num + (n4 << 2), 4);
                    memcpy(obuf + por + 7, pre.num + (n3 << 2), 4);
                    memcpy(obuf + por + 11, pre.num + (n2 << 2), 4);
                    memcpy(obuf + por + 15, pre.num + (n1 << 2), 4);
                    por += 19;
                } else if (x >= 100000000000000000) {
                    uint32_t q3 = (q2 * 205) >> 11;
                    uint32_t r3 = q2 - q3 * 10;
                    obuf[por + 0] = '0' + q3;
                    obuf[por + 1] = '0' + r3;
                    memcpy(obuf + por + 2, pre.num + (n4 << 2), 4);
                    memcpy(obuf + por + 6, pre.num + (n3 << 2), 4);
                    memcpy(obuf + por + 10, pre.num + (n2 << 2), 4);
                    memcpy(obuf + por + 14, pre.num + (n1 << 2), 4);
                    por += 18;
                } else {
                    obuf[por + 0] = '0' + q2;
                    memcpy(obuf + por + 1, pre.num + (n4 << 2), 4);
                    memcpy(obuf + por + 5, pre.num + (n3 << 2), 4);
                    memcpy(obuf + por + 9, pre.num + (n2 << 2), 4);
                    memcpy(obuf + por + 13, pre.num + (n1 << 2), 4);
                    por += 17;
                }
            } else {
                int i = 8;
                char buf[12];
                while (x >= 10000) {
                    memcpy(buf + i, pre.num + (x % 10000) * 4, 4);
                    x /= 10000;
                    i -= 4;
                }
                if (x < 100) {
                    if (x < 10) {
                        wt(char('0' + x));
                    } else {
                        obuf[por + 0] = '0' + x / 10;
                        obuf[por + 1] = '0' + x % 10;
                        por += 2;
                    }
                } else {
                    if (x < 1000) {
                        memcpy(obuf + por, pre.num + (x << 2) + 1, 3);
                        por += 3;
                    } else {
                        memcpy(obuf + por, pre.num + (x << 2), 4);
                        por += 4;
                    }
                }
                memcpy(obuf + por, buf + i + 4, 8 - i);
                por += 8 - i;
            }
        }

        struct Dummy {
            Dummy() { atexit(flush); }
        } dummy;
    }  // namespace fastio
}

int main() {
    std::size_t n, m;
    nyaan::fastio::rd(n);
    nyaan::fastio::rd(m);

    std::vector<mint> a(n), b(m);
    for (auto& e : a) {
        int v;
        nyaan::fastio::rd(v);
        e = v;
    }
    for (auto& e : b) {
        int v;
        nyaan::fastio::rd(v);
        e = v;
    }

    std::vector<mint> c = suisen::convolution_large(a, b);
    for (std::size_t i = 0; i < n + m - 1; ++i) {
        nyaan::fastio::wt(c[i].val());
        nyaan::fastio::wt('\n');
    }
    return 0;
}