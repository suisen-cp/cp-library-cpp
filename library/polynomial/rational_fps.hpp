#ifndef SUISEN_RATIONAL_FPS
#define SUISEN_RATIONAL_FPS

#include <queue>
#include <utility>

namespace suisen {
    template <typename FPSType>
    struct RationalFPS {
        using mint = typename FPSType::value_type;
        
        FPSType num, den;
        RationalFPS(const mint &v) : RationalFPS(FPSType{ v }) {}
        RationalFPS(const FPSType& num = { 0 }, const FPSType& den = { 1 }) : num(num), den(den) {}
        RationalFPS(const std::pair<FPSType, FPSType>& p) : num(p.first), den(p.second) {}

        FPSType to_fps(int n) const {
            int dlz = 0;
            while (dlz < den.size() and den[dlz] == 0) ++dlz;
            int nlz = 0;
            while (nlz < num.size() and num[nlz] == 0) ++nlz;
            assert(dlz != den.size());
            if (nlz == num.size()) {
                return FPSType(n, mint(0));
            }
            assert(dlz <= nlz);
            return ((num >> dlz) * (den >> dlz).inv(n)).cut(n);
        }

        RationalFPS<FPSType> operator+() const { return *this; }
        RationalFPS<FPSType> operator-() const { return { -num, den }; }

        friend RationalFPS<FPSType> operator+(const RationalFPS& lhs, const RationalFPS& rhs) {
            return { lhs.num * rhs.den + lhs.den * rhs.num, lhs.den * rhs.den };
        }
        friend RationalFPS<FPSType> operator-(const RationalFPS& lhs, const RationalFPS& rhs) {
            return { lhs.num * rhs.den - lhs.den * rhs.num, lhs.den * rhs.den };
        }
        friend RationalFPS<FPSType> operator*(const RationalFPS& lhs, const RationalFPS& rhs) {
            return { lhs.num * rhs.num, lhs.den * rhs.den };
        }
        friend RationalFPS<FPSType> operator*(const RationalFPS& lhs, const mint& val) {
            return { lhs.num * val, lhs.den };
        }
        friend RationalFPS<FPSType> operator/(const RationalFPS& lhs, const mint& val) {
            return { lhs.num, lhs.den * val };
        }
        friend RationalFPS<FPSType> operator*(const mint& val, const RationalFPS& lhs) {
            return { lhs.num * val, lhs.den };
        }
        friend RationalFPS<FPSType> operator/(const mint& val, const RationalFPS& lhs) {
            return { lhs.den * val, lhs.num };
        }

        RationalFPS<FPSType>& operator+=(const RationalFPS& rhs) { return *this = *this + rhs; }
        RationalFPS<FPSType>& operator-=(const RationalFPS& rhs) { return *this = *this - rhs; }
        RationalFPS<FPSType>& operator*=(const RationalFPS& rhs) { return *this = *this * rhs; }
        RationalFPS<FPSType>& operator*=(const mint& val) { return num *= val, *this; }
        RationalFPS<FPSType>& operator/=(const mint& val) { return den *= val, *this; }

        RationalFPS<FPSType> inv() const { return { den, num }; }
        RationalFPS<FPSType>& inv_inplace() { return std::swap(num, den), * this; }

        void cut(int n) {
            if (int(num.size()) > n) num.resize(n);
            if (int(den.size()) > n) den.resize(n);
        }

        FPSType normalize() {
            auto [q, r] = num.div_mod(den);
            num = std::move(r);
            return q;
        }

        static RationalFPS<FPSType> sum(const std::vector<RationalFPS<FPSType>>& fs) {
            auto comp = [](const RationalFPS<FPSType>& f, const RationalFPS<FPSType>& g) {
                return f.den.size() > g.den.size();
            };
            std::priority_queue<RationalFPS<FPSType>, std::vector<RationalFPS<FPSType>>, decltype(comp)> pq{ comp };
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
        static RationalFPS<FPSType> prod(const std::vector<RationalFPS<FPSType>>& fs) {
            std::vector<FPSType> nums, dens;
            for (const auto &f : fs) nums.push_back(f.num), dens.push_back(f.den);
            return { FPSType::prod(nums), FPSType::prod(dens) };
        }
    };
} // namespace suisen

#endif // SUISEN_RATIONAL_FPS
