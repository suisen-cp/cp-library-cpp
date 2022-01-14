#ifndef SUISEN_ZDD
#define SUISEN_ZDD

#include <array>
#include <cstdint>
#include <limits>
#include <optional>
#include <queue>
#include <set>
#include <vector>
#include <unordered_map>

#include "library/util/tuple_hash.hpp"

namespace suisen {

    namespace internal::zdd {
        using zdd_lev_t = uint32_t;
        using zdd_t = uint32_t;

        constexpr zdd_t ZERO = 0;
        constexpr zdd_t ONE = 1;

        zdd_t next_id = 2;

        std::unordered_map<std::tuple<zdd_t, zdd_t, zdd_lev_t>, zdd_t> zdd_cache;
        std::vector<std::array<zdd_t, 2>> child(next_id);
        std::vector<zdd_lev_t> level(next_id);

        zdd_lev_t next_lev = 1;

        template <typename Cache, typename ...Args>
        auto check_cache(const Cache& cache, Args &&...args) {
            return cache.find(std::make_tuple(std::forward<Args>(args)...));
        }

        template <typename Cache, typename Result, typename ...Args>
        auto register_result(Cache& cache, Result f, Args &&...args) {
            return cache[std::make_tuple(std::forward<Args>(args)...)] = f;
        }
    } // namespace zdd
    
    struct ZDD {

        ZDD(internal::zdd::zdd_t id = internal::zdd::ZERO) : id(id) {}

        static ZDD terminal0() {
            return ZDD(internal::zdd::ZERO);
        }
        static ZDD terminal1() {
            return ZDD(internal::zdd::ONE);
        }

        static internal::zdd::zdd_lev_t new_level() {
            return internal::zdd::next_lev++;
        }

        static internal::zdd::zdd_t create_zdd(ZDD l, ZDD r, internal::zdd::zdd_lev_t lev) {
            using namespace internal::zdd;
            if (r.id == ZERO) return l.id;
            if (auto it = check_cache(zdd_cache, l.id, r.id, lev); it != zdd_cache.end()) return it->second;
            child.push_back(std::array<zdd_t, 2>{ l.id, r.id });
            level.push_back(lev);
            return register_result(zdd_cache, next_id++, l.id, r.id, lev);
        }

        bool is_terminal0() const {
            return id == internal::zdd::ZERO;
        }
        bool is_terminal1() const {
            return id == internal::zdd::ONE;
        }

        ZDD operator[](int edge_id) const {
            return internal::zdd::child[id][edge_id];
        }
        internal::zdd::zdd_lev_t top() const {
            return internal::zdd::level[id];
        }

        static ZDD change(ZDD f, internal::zdd::zdd_lev_t lev) {
            using namespace internal::zdd;
            static std::unordered_map<std::tuple<zdd_t, zdd_lev_t>, ZDD> cache;
            if (lev == f.top()) {
                return create_zdd(f[1], f[0], lev);
            } else if (lev < f.top()) {
                if (auto it = check_cache(cache, f.id, lev); it != cache.end()) return it->second;
                return register_result(cache, create_zdd(change(f[0], lev), change(f[1], lev), f.top()), f.id, lev);
            } else {
                return create_zdd(terminal0(), f, lev);
            }
        }

        static ZDD onset0(ZDD f, internal::zdd::zdd_lev_t lev) {
            using namespace internal::zdd;
            if (lev == f.top()) {
                return create_zdd(f[1], terminal0(), lev);
            } else if (lev < f.top()) {
                static std::unordered_map<std::tuple<zdd_t, zdd_lev_t>, ZDD> cache;
                if (auto it = check_cache(cache, f.id, lev); it != cache.end()) return it->second;
                return register_result(cache, create_zdd(onset0(f[0], lev), onset0(f[1], lev), f.top()), f.id, lev);
            } else {
                return terminal0();
            }
        }

        static ZDD onset1(ZDD f, internal::zdd::zdd_lev_t lev) {
            using namespace internal::zdd;
            if (lev == f.top()) {
                return create_zdd(terminal0(), f[1], lev);
            } else if (lev < f.top()) {
                static std::unordered_map<std::tuple<zdd_t, zdd_lev_t>, ZDD> cache;
                if (auto it = check_cache(cache, f.id, lev); it != cache.end()) return it->second;
                return register_result(cache, create_zdd(onset1(f[0], lev), onset1(f[1], lev), f.top()), f.id, lev);
            } else {
                return terminal0();
            }
        }

        static ZDD offset(ZDD f, internal::zdd::zdd_lev_t lev) {
            using namespace internal::zdd;
            if (lev == f.top()) {
                return create_zdd(f[0], terminal0(), lev);
            } else if (lev < f.top()) {
                static std::unordered_map<std::tuple<zdd_t, zdd_lev_t>, ZDD> cache;
                if (auto it = check_cache(cache, f.id, lev); it != cache.end()) return it->second;
                return register_result(cache, create_zdd(offset(f[0], lev), offset(f[1], lev), f.top()), f.id, lev);
            } else {
                return f;
            }
        }

        friend ZDD operator&(ZDD f, ZDD g) {
            if (f.is_terminal0() or g.is_terminal0()) return terminal0();
            if (f.is_terminal1() and g.is_terminal1()) return terminal1();

            if (f.top() < g.top()) std::swap(f, g);

            using namespace internal::zdd;
            static std::unordered_map<std::tuple<zdd_t, zdd_t>, ZDD> cache;
            if (auto it = check_cache(cache, f.id, g.id); it != cache.end()) return it->second;
            
            ZDD res = f.top() > g.top() ? f[0] & g : create_zdd(f[0] & g[0], f[1] & g[1], f.top());
            return register_result(cache, res, f.id, g.id);
        }

        friend ZDD operator+(ZDD f, ZDD g) {
            if (f.is_terminal0() or g.is_terminal0()) return f.id ^ g.id;
            if (f.is_terminal1() and g.is_terminal1()) return terminal1();

            if (f.top() < g.top()) std::swap(f, g);

            using namespace internal::zdd;
            static std::unordered_map<std::tuple<zdd_t, zdd_t>, ZDD> cache;
            if (auto it = check_cache(cache, f.id, g.id); it != cache.end()) return it->second;

            ZDD res = f.top() > g.top() ? create_zdd(f[0] + g, f[1], f.top()) : create_zdd(f[0] + g[0], f[1] + g[1], f.top());
            return register_result(cache, res, f.id, g.id);
        }

        friend ZDD operator-(ZDD f, ZDD g) {
            if (g.is_terminal0()) return f;
            if (f.is_terminal0() or (f.is_terminal1() and g.is_terminal1())) return terminal0();

            using namespace internal::zdd;
            static std::unordered_map<std::tuple<zdd_t, zdd_t>, ZDD> cache;
            if (auto it = check_cache(cache, f.id, g.id); it != cache.end()) return it->second;

            ZDD res;
            if (f.top() > g.top()) {
                res = create_zdd(f[0] - g, f[1], f.top());
            } else if (f.top() == g.top()) {
                res = create_zdd(f[0] - g[0], f[1] - g[1], f.top());
            } else {
                res = f - g[0];
            }
            return register_result(cache, res, f.id, g.id);
        }

        friend ZDD operator^(ZDD f, ZDD g) {
            if (f.is_terminal0() or g.is_terminal0()) return f.id ^ g.id;
            if (f.id == g.id) return terminal0();

            if (f.top() < g.top()) std::swap(f, g);

            using namespace internal::zdd;
            static std::unordered_map<std::tuple<zdd_t, zdd_t>, ZDD> cache;
            if (auto it = check_cache(cache, f.id, g.id); it != cache.end()) return it->second;
            
            ZDD res = f.top() > g.top() ? create_zdd(f[0] ^ g, f[1], f.top()) : create_zdd(f[0] ^ g[0], f[1] ^ g[1], f.top());
            return register_result(cache, res, f.id, g.id);
        }

        static ZDD restrict(ZDD f, ZDD g) {
            if (f.is_terminal0() or g.is_terminal0()) return terminal0();
            if (g.is_terminal1()) return f;

            using namespace internal::zdd;
            static std::unordered_map<std::tuple<zdd_t, zdd_t>, ZDD> cache;
            if (auto it = check_cache(cache, f.id, g.id); it != cache.end()) return it->second;

            ZDD res;
            if (f.top() > g.top()) {
                res = create_zdd(restrict(f[0], g), restrict(f[1], g), f.top());
            } else if (f.top() == g.top()) {
                res = create_zdd(restrict(f[0], g[0]), restrict(f[1], g[0]) + restrict(f[1], g[1]), f.top());
            } else {
                res = restrict(f, g[0]);
            }
            return register_result(cache, res, f.id, g.id);
        }

        static ZDD permit(ZDD f, ZDD g) {
            if (f.is_terminal0() or g.is_terminal0()) return terminal0();
            if (f.is_terminal1()) return f;

            using namespace internal::zdd;
            static std::unordered_map<std::tuple<zdd_t, zdd_t>, ZDD> cache;
            if (auto it = check_cache(cache, f.id, g.id); it != cache.end()) return it->second;

            ZDD res;
            if (f.top() > g.top()) {
                res = create_zdd(permit(f[0], g), terminal0(), f.top());
            } else if (f.top() == g.top()) {
                res = create_zdd(permit(f[0], g[0]) + permit(f[0], g[1]), permit(f[1], g[1]), f.top());
            } else {
                res = permit(f, g[0]) + permit(f, g[1]);
            }
            return register_result(cache, res, f.id, g.id);
        }

        template <typename T>
        static T card(ZDD f) {
            if (f.is_terminal0()) return 0;
            if (f.is_terminal1()) return 1;

            using namespace internal::zdd;
            static std::unordered_map<std::tuple<zdd_t>, T> cache;
            if (auto it = check_cache(cache, f.id); it != cache.end()) return it->second;

            return register_result(cache, card<T>(f[0]) + card<T>(f[1]), f.id);
        }

        static int32_t len(ZDD f) {
            if (f.is_terminal0()) return std::numeric_limits<int32_t>::min();
            if (f.is_terminal1()) return 0;

            using namespace internal::zdd;
            static std::unordered_map<std::tuple<zdd_t>, int> cache;
            if (auto it = check_cache(cache, f.id); it != cache.end()) return it->second;

            return register_result(cache, std::max(len(f[0]), 1 + len(f[1])), f.id);
        }

        static std::optional<std::vector<int32_t>> max_len_item(ZDD f) {
            if (f.is_terminal0()) return std::nullopt;
            if (f.is_terminal1()) return std::vector<int32_t>{};

            using namespace internal::zdd;
            static std::unordered_map<std::tuple<zdd_t>, std::optional<std::vector<int32_t>>> cache;
            if (auto it = check_cache(cache, f.id); it != cache.end()) return it->second;

            auto res0 = max_len_item(f[0]);
            auto res1 = max_len_item(f[1]);
            if (res0.has_value() and res1.has_value()) {
                res1->push_back(f.top());
                return register_result(cache, res0->size() > res1->size() ? res0 : res1, f.id);
            } else if (res0.has_value()) {
                return register_result(cache, res0, f.id);
            } else if (res1.has_value()) {
                return register_result(cache, res1, f.id);
            } else {
                return register_result(cache, std::nullopt, f.id);
            }
        }

        static int32_t size(ZDD f) {
            if (f.is_terminal0() or f.is_terminal1()) return 0;
            auto comp = [](ZDD f, ZDD g) { return f.top() < g.top(); };
            std::priority_queue<ZDD, std::vector<ZDD>, decltype(comp)> pq { comp };
            std::set vis { f.id };
            pq.push(f);
            while (pq.size()) {
                ZDD g = pq.top();
                pq.pop();
                for (int i : { 0, 1 }) {
                    if (g[i].is_terminal0() or g[i].is_terminal1()) continue;
                    if (vis.count(g[i].id)) continue;
                    vis.insert(g[i].id);
                    pq.push(g[i]);
                }
            }
            return vis.size();
        }

    private:
        internal::zdd::zdd_t id;
    };
} // namespace suisen


#endif // SUISEN_ZDD
