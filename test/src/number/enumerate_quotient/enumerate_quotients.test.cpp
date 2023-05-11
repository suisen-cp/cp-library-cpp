#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_quotients"

#include <cstring>
#include <iomanip>
#include <iostream>
#include "library/number/enumerate_quotient.hpp"

namespace maspy {
    struct Printer {
        Printer(FILE* _fp): fp(_fp) {}
        ~Printer() { flush(); }

        static constexpr size_t SIZE = 1 << 15;
        FILE* fp;
        char line[SIZE], small[50];
        size_t pos = 0;
        void flush() {
            fwrite(line, 1, pos, fp);
            pos = 0;
        }
        void write(const char val) {
            if (pos == SIZE) flush();
            line[pos++] = val;
        }
        template <class T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
        void write(T val) {
            if (pos > (1 << 15) - 50) flush();
            if (val == 0) {
                write('0');
                return;
            }
            if (val < 0) {
                write('-');
                val = -val; // todo min
            }
            size_t len = 0;
            while (val) {
                small[len++] = char(0x30 | (val % 10));
                val /= 10;
            }
            for (size_t i = 0; i < len; i++) { line[pos + i] = small[len - 1 - i]; }
            pos += len;
        }
        template <class T>
        void write(const std::vector<T> val) {
            auto n = val.size();
            for (size_t i = 0; i < n; i++) {
                if (i) write(' ');
                write(val[i]);
            }
        }
    };
}

maspy::Printer printer{ stdout };

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n;
    std::cin >> n;

    printer.write(suisen::quotient_num(n));
    printer.write('\n');
    suisen::foreach_quotients(n, [](long long d) { printer.write(d), printer.write(' '); });
    printer.write('\n');
}