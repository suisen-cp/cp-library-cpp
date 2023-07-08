#ifndef SUISEN_ZOBRIST_HASH
#define SUISEN_ZOBRIST_HASH

#include <algorithm>
#include <array>
#include <map>
#include <vector>
#include <random>

namespace suisen {

    template <typename ContainerType, typename ValueType, typename HashType, typename Derived>
    struct ZobristHashBase {
        using container_type = ContainerType;
        using value_type = ValueType;
        using hash_type = std::make_unsigned_t<HashType>;
        using rng_type = std::mt19937_64;
        using self_type = Derived;

        template <typename ...Args>
        ZobristHashBase(Args &&...args) : rng(std::random_device{}()), h(std::forward<Args>(args)...) {}

        hash_type operator()(const value_type &val) {
            Self::ensure_key_existence(h, val, rng);
            return h[val];
        }
        hash_type empty_set() const {
            return 0;
        }
        hash_type sigleton_set(const value_type& val) {
            return (*this)(val);
        }
        hash_type flip(hash_type old_hash, const value_type& val) {
            return old_hash ^ (*this)(val);
        }
        hash_type xor_set(hash_type set1, hash_type set2) const {
            return set1 ^ set2;
        }

    protected:
        rng_type rng;
        container_type h;

    private:
        struct Self : public self_type {
            using self_type::ensure_key_existence;
        };
    };

    template <typename HashType = std::uint64_t, std::enable_if_t<std::is_integral_v<HashType>, std::nullptr_t> = nullptr>
    struct VecZobristHash : public ZobristHashBase<std::vector<std::make_unsigned_t<HashType>>, std::size_t, HashType, VecZobristHash<HashType>> {
        using Base = ZobristHashBase<std::vector<std::make_unsigned_t<HashType>>, std::size_t, HashType, VecZobristHash<HashType>>;

        VecZobristHash() = default;
        VecZobristHash(typename Base::value_type max_val) : Base(max_val + 1) {
            std::generate(this->h.begin(), this->h.end(), this->rng);
        }

    protected:
        static void ensure_key_existence(typename Base::container_type& h, typename Base::value_type v, typename Base::rng_type& rng) {
            if (std::size_t old_size = h.size(); old_size <= v) {
                h.resize(v + 1);
                for (std::size_t i = old_size; i <= v; ++i) h[i] = rng();
            }
        }
    };

    template <std::size_t N, typename HashType = std::uint64_t, std::enable_if_t<std::is_integral_v<HashType>, std::nullptr_t> = nullptr>
    struct ArrZobristHash : public ZobristHashBase<std::array<std::make_unsigned_t<HashType>, N + 1>, std::size_t, HashType, ArrZobristHash<N, HashType>> {
        using Base = ZobristHashBase<std::array<std::make_unsigned_t<HashType>, N + 1>, std::size_t, HashType, ArrZobristHash<N, HashType>>;

        ArrZobristHash() {
            std::generate(this->h.begin(), this->h.end(), this->rng);
        }
    protected:
        static void ensure_key_existence(typename Base::container_type&, typename Base::value_type, typename Base::rng_type&) {}
    };

    template <typename ValueType, typename HashType = std::uint64_t, std::enable_if_t<std::is_integral_v<HashType>, std::nullptr_t> = nullptr>
    struct MapZobristHash : public ZobristHashBase<std::map<ValueType, std::make_unsigned_t<HashType>>, ValueType, HashType, MapZobristHash<ValueType, HashType>> {
        using Base = ZobristHashBase<std::map<ValueType, std::make_unsigned_t<HashType>>, ValueType, HashType, MapZobristHash<ValueType, HashType>>;

        MapZobristHash() = default;
        template <typename Container>
        MapZobristHash(const Container& universal_set) {
            for (auto& val : universal_set) this->h[val] = (this->rng)();
        }

    protected:
        static void ensure_key_existence(typename Base::container_type& h, const typename Base::value_type &v, typename Base::rng_type& rng) {
            if (auto it = h.find(v); it == h.end()) h[v] = rng();
        }
    };

} // namespace suisen


#endif // SUISEN_ZOBRIST_HASH
