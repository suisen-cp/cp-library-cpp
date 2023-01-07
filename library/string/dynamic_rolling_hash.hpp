#ifndef SUISEN_DYNAMIC_ROLLING_HASH
#define SUISEN_DYNAMIC_ROLLING_HASH

#include <random>

#include "library/number/sieve_of_eratosthenes.hpp"
#include "library/number/modint_2^61m1.hpp"
#include "library/datastructure/bbst/red_black_segment_tree.hpp"

namespace suisen {
    namespace internal::dynamic_rolling_hash {
        struct BaseGen {
            static inline std::mt19937_64 rng{ std::random_device{}() };
            static inline std::uniform_int_distribution<uint64_t> dist{ 0, modint2p61m1::mod() - 1 };
            
            static uint32_t generate() {
                return dist(rng);
            }
        };

        template <size_t id>
        uint32_t base() {
            static uint32_t _base = 0;
            return _base ? _base : (_base = BaseGen::generate());
        }

        template <size_t base_num_>
        struct Hash {
            static constexpr size_t base_num = base_num_;

            using child_type = Hash<base_num - 1>;
            using hash_type = std::array<uint64_t, base_num>;

            modint2p61m1 hash;
            modint2p61m1 offset;

            child_type hash_lo;

            Hash() : Hash(0) {}
            template <typename T>
            Hash(const T& val): hash(val), offset(base<base_num>()), hash_lo(val) {}

            operator hash_type() const {
                hash_type res;
                store_hash(res);
                return res;
            }

            template <typename Container>
            void store_hash(Container& h) const {
                h[base_num - 1] = hash.val();
                hash_lo.store_hash(h);
            }

            static Hash identity() {
                return { 0, 1, child_type::identity() };
            }
            static Hash merge(const Hash &l, const Hash &r) {
                return { l.hash * r.offset + r.hash, l.offset * r.offset, child_type::merge(l.hash_lo, r.hash_lo) };
            }
            static Hash merge_noref(Hash l, Hash r) {
                return merge(l, r);
            }
        private:
            Hash(const modint2p61m1& hash, const modint2p61m1& offset, const child_type& hash_lo): hash(hash), offset(offset), hash_lo(hash_lo) {}
        };

        template <>
        struct Hash<1> {
            static constexpr size_t base_num = 1;

            modint2p61m1 hash;
            modint2p61m1 offset;

            using hash_type = uint64_t;

            Hash() : Hash(0) {}
            template <typename T>
            Hash(const T& val): hash(val), offset(base<base_num>()) {}

            operator hash_type() const {
                return hash.val();
            }

            template <typename Container>
            void store_hash(Container& h) const {
                h[0] = hash.val();
            }

            static Hash identity() {
                return { 0, 1 };
            }
            static Hash merge(const Hash &l, const Hash &r) {
                return { l.hash * r.offset + r.hash, l.offset * r.offset };
            }
            static Hash merge_noref(Hash l, Hash r) {
                return merge(l, r);
            }
        private:
            Hash(const modint2p61m1& hash, const modint2p61m1& offset): hash(hash), offset(offset) {}
        };
    }

    template <std::size_t base_num>
    using Hash = internal::dynamic_rolling_hash::Hash<base_num>;

    template <size_t base_num_ = 1>
    struct DynamicRollingHash {
        static constexpr size_t base_num = base_num_;
    private:
        using hash_ = Hash<base_num>;

        using node = bbst::segtree::RedBlackTreeNode<hash_, hash_::merge_noref, hash_::identity>;

        node* _seq;
    public:
        using hash = typename hash_::hash_type;

        DynamicRollingHash(): _seq(nullptr) {}
        template <typename Seq>
        DynamicRollingHash(const Seq& a): _seq(node::build(a)) {}

        static void init_pool(size_t reserving_node_num) {
            node::init_pool(reserving_node_num);
        }

        template <typename T>
        void set(size_t k, const T& val) {
            _seq = node::update_value(_seq, k, val);
        }
        template <typename T>
        void insert(size_t k, const T& val) {
            _seq = node::insert(_seq, k, val);
        }
        template <typename T>
        void push_back(const T& val) {
            insert(node::size(_seq), val);
        }
        template <typename T>
        void push_front(const T& val) {
            insert(0, val);
        }
        void erase(size_t k) {
            _seq = node::erase(_seq, k).first;
        }
        void pop_back() {
            erase(node::size(_seq) - 1);
        }
        void pop_front() {
            erase(0);
        }

        hash operator()(int l, int r) {
            hash_ res;
            std::tie(_seq, res) = node::prod(_seq, l, r);
            return res;
        }
    };
}

#endif // SUISEN_DYNAMIC_ROLLING_HASH
