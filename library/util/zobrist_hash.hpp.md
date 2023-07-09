---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/zobrist_hash.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <array>\n#include <map>\n#include <vector>\n#include <random>\n\nnamespace\
    \ suisen {\n\n    template <typename ContainerType, typename ValueType, typename\
    \ HashType, typename Derived>\n    struct ZobristHashBase {\n        using container_type\
    \ = ContainerType;\n        using value_type = ValueType;\n        using hash_type\
    \ = std::make_unsigned_t<HashType>;\n        using rng_type = std::mt19937_64;\n\
    \        using self_type = Derived;\n\n        template <typename ...Args>\n \
    \       ZobristHashBase(Args &&...args) : rng(std::random_device{}()), h(std::forward<Args>(args)...)\
    \ {}\n\n        hash_type operator()(const value_type &val) {\n            Self::ensure_key_existence(h,\
    \ val, rng);\n            return h[val];\n        }\n        hash_type empty_set()\
    \ const {\n            return 0;\n        }\n        hash_type sigleton_set(const\
    \ value_type& val) {\n            return (*this)(val);\n        }\n        hash_type\
    \ flip(hash_type old_hash, const value_type& val) {\n            return old_hash\
    \ ^ (*this)(val);\n        }\n        hash_type xor_set(hash_type set1, hash_type\
    \ set2) const {\n            return set1 ^ set2;\n        }\n\n    protected:\n\
    \        rng_type rng;\n        container_type h;\n\n    private:\n        struct\
    \ Self : public self_type {\n            using self_type::ensure_key_existence;\n\
    \        };\n    };\n\n    template <typename HashType = std::uint64_t, std::enable_if_t<std::is_integral_v<HashType>,\
    \ std::nullptr_t> = nullptr>\n    struct VecZobristHash : public ZobristHashBase<std::vector<std::make_unsigned_t<HashType>>,\
    \ std::size_t, HashType, VecZobristHash<HashType>> {\n        using Base = ZobristHashBase<std::vector<std::make_unsigned_t<HashType>>,\
    \ std::size_t, HashType, VecZobristHash<HashType>>;\n\n        VecZobristHash()\
    \ = default;\n        VecZobristHash(typename Base::value_type max_val) : Base(max_val\
    \ + 1) {\n            std::generate(this->h.begin(), this->h.end(), this->rng);\n\
    \        }\n\n    protected:\n        static void ensure_key_existence(typename\
    \ Base::container_type& h, typename Base::value_type v, typename Base::rng_type&\
    \ rng) {\n            if (std::size_t old_size = h.size(); old_size <= v) {\n\
    \                h.resize(v + 1);\n                for (std::size_t i = old_size;\
    \ i <= v; ++i) h[i] = rng();\n            }\n        }\n    };\n\n    template\
    \ <std::size_t N, typename HashType = std::uint64_t, std::enable_if_t<std::is_integral_v<HashType>,\
    \ std::nullptr_t> = nullptr>\n    struct ArrZobristHash : public ZobristHashBase<std::array<std::make_unsigned_t<HashType>,\
    \ N + 1>, std::size_t, HashType, ArrZobristHash<N, HashType>> {\n        using\
    \ Base = ZobristHashBase<std::array<std::make_unsigned_t<HashType>, N + 1>, std::size_t,\
    \ HashType, ArrZobristHash<N, HashType>>;\n\n        ArrZobristHash() {\n    \
    \        std::generate(this->h.begin(), this->h.end(), this->rng);\n        }\n\
    \    protected:\n        static void ensure_key_existence(typename Base::container_type&,\
    \ typename Base::value_type, typename Base::rng_type&) {}\n    };\n\n    template\
    \ <typename ValueType, typename HashType = std::uint64_t, std::enable_if_t<std::is_integral_v<HashType>,\
    \ std::nullptr_t> = nullptr>\n    struct MapZobristHash : public ZobristHashBase<std::map<ValueType,\
    \ std::make_unsigned_t<HashType>>, ValueType, HashType, MapZobristHash<ValueType,\
    \ HashType>> {\n        using Base = ZobristHashBase<std::map<ValueType, std::make_unsigned_t<HashType>>,\
    \ ValueType, HashType, MapZobristHash<ValueType, HashType>>;\n\n        MapZobristHash()\
    \ = default;\n        template <typename Container>\n        MapZobristHash(const\
    \ Container& universal_set) {\n            for (auto& val : universal_set) this->h[val]\
    \ = (this->rng)();\n        }\n\n    protected:\n        static void ensure_key_existence(typename\
    \ Base::container_type& h, const typename Base::value_type &v, typename Base::rng_type&\
    \ rng) {\n            if (auto it = h.find(v); it == h.end()) h[v] = rng();\n\
    \        }\n    };\n\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_ZOBRIST_HASH\n#define SUISEN_ZOBRIST_HASH\n\n#include <algorithm>\n\
    #include <array>\n#include <map>\n#include <vector>\n#include <random>\n\nnamespace\
    \ suisen {\n\n    template <typename ContainerType, typename ValueType, typename\
    \ HashType, typename Derived>\n    struct ZobristHashBase {\n        using container_type\
    \ = ContainerType;\n        using value_type = ValueType;\n        using hash_type\
    \ = std::make_unsigned_t<HashType>;\n        using rng_type = std::mt19937_64;\n\
    \        using self_type = Derived;\n\n        template <typename ...Args>\n \
    \       ZobristHashBase(Args &&...args) : rng(std::random_device{}()), h(std::forward<Args>(args)...)\
    \ {}\n\n        hash_type operator()(const value_type &val) {\n            Self::ensure_key_existence(h,\
    \ val, rng);\n            return h[val];\n        }\n        hash_type empty_set()\
    \ const {\n            return 0;\n        }\n        hash_type sigleton_set(const\
    \ value_type& val) {\n            return (*this)(val);\n        }\n        hash_type\
    \ flip(hash_type old_hash, const value_type& val) {\n            return old_hash\
    \ ^ (*this)(val);\n        }\n        hash_type xor_set(hash_type set1, hash_type\
    \ set2) const {\n            return set1 ^ set2;\n        }\n\n    protected:\n\
    \        rng_type rng;\n        container_type h;\n\n    private:\n        struct\
    \ Self : public self_type {\n            using self_type::ensure_key_existence;\n\
    \        };\n    };\n\n    template <typename HashType = std::uint64_t, std::enable_if_t<std::is_integral_v<HashType>,\
    \ std::nullptr_t> = nullptr>\n    struct VecZobristHash : public ZobristHashBase<std::vector<std::make_unsigned_t<HashType>>,\
    \ std::size_t, HashType, VecZobristHash<HashType>> {\n        using Base = ZobristHashBase<std::vector<std::make_unsigned_t<HashType>>,\
    \ std::size_t, HashType, VecZobristHash<HashType>>;\n\n        VecZobristHash()\
    \ = default;\n        VecZobristHash(typename Base::value_type max_val) : Base(max_val\
    \ + 1) {\n            std::generate(this->h.begin(), this->h.end(), this->rng);\n\
    \        }\n\n    protected:\n        static void ensure_key_existence(typename\
    \ Base::container_type& h, typename Base::value_type v, typename Base::rng_type&\
    \ rng) {\n            if (std::size_t old_size = h.size(); old_size <= v) {\n\
    \                h.resize(v + 1);\n                for (std::size_t i = old_size;\
    \ i <= v; ++i) h[i] = rng();\n            }\n        }\n    };\n\n    template\
    \ <std::size_t N, typename HashType = std::uint64_t, std::enable_if_t<std::is_integral_v<HashType>,\
    \ std::nullptr_t> = nullptr>\n    struct ArrZobristHash : public ZobristHashBase<std::array<std::make_unsigned_t<HashType>,\
    \ N + 1>, std::size_t, HashType, ArrZobristHash<N, HashType>> {\n        using\
    \ Base = ZobristHashBase<std::array<std::make_unsigned_t<HashType>, N + 1>, std::size_t,\
    \ HashType, ArrZobristHash<N, HashType>>;\n\n        ArrZobristHash() {\n    \
    \        std::generate(this->h.begin(), this->h.end(), this->rng);\n        }\n\
    \    protected:\n        static void ensure_key_existence(typename Base::container_type&,\
    \ typename Base::value_type, typename Base::rng_type&) {}\n    };\n\n    template\
    \ <typename ValueType, typename HashType = std::uint64_t, std::enable_if_t<std::is_integral_v<HashType>,\
    \ std::nullptr_t> = nullptr>\n    struct MapZobristHash : public ZobristHashBase<std::map<ValueType,\
    \ std::make_unsigned_t<HashType>>, ValueType, HashType, MapZobristHash<ValueType,\
    \ HashType>> {\n        using Base = ZobristHashBase<std::map<ValueType, std::make_unsigned_t<HashType>>,\
    \ ValueType, HashType, MapZobristHash<ValueType, HashType>>;\n\n        MapZobristHash()\
    \ = default;\n        template <typename Container>\n        MapZobristHash(const\
    \ Container& universal_set) {\n            for (auto& val : universal_set) this->h[val]\
    \ = (this->rng)();\n        }\n\n    protected:\n        static void ensure_key_existence(typename\
    \ Base::container_type& h, const typename Base::value_type &v, typename Base::rng_type&\
    \ rng) {\n            if (auto it = h.find(v); it == h.end()) h[v] = rng();\n\
    \        }\n    };\n\n} // namespace suisen\n\n\n#endif // SUISEN_ZOBRIST_HASH\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/zobrist_hash.hpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/zobrist_hash.hpp
layout: document
title: Zobrist Hash
---
## Zobrist Hash