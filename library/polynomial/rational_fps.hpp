#ifndef SUISEN_RATIONAL_FPS
#define SUISEN_RATIONAL_FPS

#include <queue>

#include "library/polynomial/fps.hpp"

namespace suisen {
    template <typename mint>
    struct RationalFPS {
        FPS<mint> num, den;
        RationalFPS(const FPS<mint>& num = { 0 }, const FPS<mint>& den = { 1 }) : num(num), den(den) {}
        RationalFPS(const std::pair<FPS<mint>, FPS<mint>>& p) : num(p.first), den(p.second) {}

        FPS<mint> to_fps(int max_deg) const {
            return (num * den.inv(max_deg)).pre_inplace(max_deg);
        }

        RationalFPS<mint> operator+() const { return *this; }
        RationalFPS<mint> operator-() const { return { -num, den }; }

        friend RationalFPS<mint> operator+(const RationalFPS& lhs, const RationalFPS& rhs) {
            return { lhs.num * rhs.den + lhs.den * rhs.num, lhs.den * rhs.den };
        }
        friend RationalFPS<mint> operator-(const RationalFPS& lhs, const RationalFPS& rhs) {
            return { lhs.num * rhs.den - lhs.den * rhs.num, lhs.den * rhs.den };
        }
        friend RationalFPS<mint> operator*(const RationalFPS& lhs, const RationalFPS& rhs) {
            return { lhs.num * rhs.num, lhs.den * rhs.den };
        }
        friend RationalFPS<mint> operator*(const RationalFPS& lhs, const mint& val) {
            return { lhs.num * val, lhs.den };
        }
        friend RationalFPS<mint> operator/(const RationalFPS& lhs, const mint& val) {
            return { lhs.num, lhs.den * val };
        }
        friend RationalFPS<mint> operator*(const mint& val, const RationalFPS& lhs) {
            return { lhs.num * val, lhs.den };
        }
        friend RationalFPS<mint> operator/(const mint& val, const RationalFPS& lhs) {
            return { lhs.den * val, lhs.num };
        }

        RationalFPS<mint>& operator+=(const RationalFPS& rhs) { return *this = *this + rhs; }
        RationalFPS<mint>& operator-=(const RationalFPS& rhs) { return *this = *this - rhs; }
        RationalFPS<mint>& operator*=(const RationalFPS& rhs) { return *this = *this * rhs; }
        RationalFPS<mint>& operator*=(const mint& val) { return num *= val, *this; }
        RationalFPS<mint>& operator/=(const mint& val) { return den *= val, *this; }

        RationalFPS<mint> inv() const { return { den, num }; }
        RationalFPS<mint>& inv_inplace() { return std::swap(num, den), * this; }

        FPS<mint> normalize() {
            auto [q, r] = num.div_mod(den);
            num = std::move(r);
            return q;
        }

        static RationalFPS<mint> sum(const std::vector<RationalFPS<mint>>& fs) {
            auto comp = [](const RationalFPS<mint>& f, const RationalFPS<mint>& g) {
                return f.den.size() > g.den.size();
            };
            std::priority_queue<RationalFPS<mint>, std::vector<RationalFPS<mint>>, decltype(comp)> pq{ comp };
            for (const auto& f : fs) pq.push(f);

            while (pq.size() > 1) {
                auto f = pq.top();
                pq.pop();
                auto g = pq.top();
                pq.pop();
                pq.emplace(f + g);
            }
            return pq.top();
        }
        static RationalFPS<mint> prod(const std::vector<RationalFPS<mint>>& fs) {
            std::vector<FPS<mint>> nums, dens;
            for (const auto &f : fs) nums.push_back(f.num), dens.push_back(f.den);
            return { FPS<mint>::prod(nums), FPS<mint>::prod(dens) };
        }
    };
} // namespace suisen

#endif // SUISEN_RATIONAL_FPS
