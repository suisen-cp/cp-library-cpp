#ifndef SUISEN_BINARY_TRIE_PATRICIA
#define SUISEN_BINARY_TRIE_PATRICIA

#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <limits>
#include <optional>
#include <type_traits>
#include <utility>

#ifdef _MSC_VER
#  include <intrin.h>
#else
#  include <x86intrin.h>
#endif

namespace suisen {
    template <typename T, uint32_t bit_num, typename SizeType = int32_t, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    struct BinaryTriePatricia {
        using size_type = SizeType;
        using internal_size_type = std::make_unsigned_t<size_type>;

        using value_type = T;
        using unsigned_value_type = std::make_unsigned_t<value_type>;

        static constexpr uint32_t ary = 4;
        static constexpr uint32_t log_ary = 2;

        static_assert(bit_num <= std::numeric_limits<unsigned_value_type>::digits);
        static_assert(bit_num <= 64);

        struct Node;
        using node_type = Node;
        using node_pointer_type = node_type*;

        struct Node {
            unsigned_value_type val;
            uint32_t len;
            internal_size_type siz;
            node_pointer_type ch[ary]{};

            Node(const unsigned_value_type& val, uint32_t len, internal_size_type siz) : val(val), len(len), siz(siz) {}
            ~Node() {
                for (uint32_t i = 0; i < ary; ++i) delete ch[i];
            }

            static node_pointer_type new_node(const unsigned_value_type& val, uint32_t len, internal_size_type siz) {
                return new node_type(val, len, siz);
            }
        };

        BinaryTriePatricia() = default;
        ~BinaryTriePatricia() {
            delete _root;
        }

        // number of elements in the set
        int size() const {
            return _root->siz;
        }
        // true iff size() == 0
        bool empty() const {
            return _root->siz == 0;
        }

        // returns true iff insertion is succeeded.
        bool insert_if_absent(unsigned_value_type val) {
            bit_reverse(val);
            return _insert_if_absent(_root, 0, val);
        }
        void insert(unsigned_value_type val, internal_size_type num = 1) {
            bit_reverse(val);
            _insert(_root, 0, val, num);
        }
        // returns the number of erased elements
        size_type erase(unsigned_value_type val, internal_size_type num = 1) {
            if (num == 0) return 0;
            bit_reverse(val);
            _erase(_root, num, 0, val);
            return num;
        }
        
        size_type count(unsigned_value_type val) const {
            bit_reverse(val);
            node_pointer_type cur = _root;
            for (uint32_t l = 0; l < bit_num;) {
                const uint32_t ch_idx = val & (ary - 1);
                node_pointer_type nxt = cur->ch[ch_idx];
                if (not nxt or cut_lower(val ^ nxt->val, nxt->len)) return 0;
                val >>= nxt->len;
                l += nxt->len;
                cur = nxt;
            }
            return cur->siz;
        }
        bool contains(unsigned_value_type val) const { return count(val) != 0; }

        // min{ x ^ v | v in S }
        value_type xor_min(unsigned_value_type x) const {
            return xor_kth_min(x, 0);
        }
        // max{ x ^ v | v in S }
        value_type xor_max(const unsigned_value_type& x) const {
            return xor_min(~x);
        }

        // k-th smallest of { x ^ v | v in S } (0-indexed)
        value_type xor_kth_min(unsigned_value_type x, internal_size_type k) const {
            unsigned_value_type x_ = x;
            bit_reverse(x);
            unsigned_value_type res = 0;
            node_pointer_type cur = _root;
            for (uint32_t l = 0; l < bit_num;) {
                const uint32_t ch_idx = x & (ary - 1);
                node_pointer_type nxt = nullptr;
                for (int x : { 0, 2, 1, 3 }) {
                    if (nxt = cur->ch[ch_idx ^ x]; nxt) {
                        if (nxt->siz > k) break;
                        k -= nxt->siz;
                    }
                }
                res |= nxt->val << l;
                x >>= nxt->len;
                l += nxt->len;
                cur = nxt;
            }
            bit_reverse(res);
            return x_ ^ res;
        }
        // k-th largest of { x ^ v | v in S } (0-indexed)
        value_type xor_kth_max(unsigned_value_type x, internal_size_type k) const {
            return xor_kth_min(x, _root->siz - k - 1);
        }

        // #{ v in S | x ^ v < upper }
        size_type xor_count_lt (unsigned_value_type x, unsigned_value_type upper) const {
            if (upper >> bit_num) return _root->siz;
            bit_reverse(x);
            bit_reverse(upper);
            internal_size_type res = 0;
            node_pointer_type cur = _root;
            for (uint32_t l = 0; l < bit_num;) {
                const uint32_t ch_idx = x & (ary - 1);
                const uint32_t ch_idx_r = upper & (ary - 1);
                node_pointer_type nxt = nullptr;
                for (int x : { 0, 2, 1, 3 }) {
                    nxt = cur->ch[ch_idx ^ x];
                    if ((ch_idx ^ x) == ch_idx_r) break;
                    if (nxt) res += nxt->siz;
                }
                if (not nxt) break;
                x >>= nxt->len;
                upper >>= nxt->len;
                l += nxt->len;
                cur = nxt;
            }
            return res;
        }
        // #{ v in S | x ^ v <= upper }
        size_type xor_count_leq(unsigned_value_type x, unsigned_value_type upper) const {
            if (upper == std::numeric_limits<unsigned_value_type>::max()) return _root->siz;
            return xor_count_lt(x, upper + 1);
        }
        // #{ v in S | x ^ v >= lower }
        size_type xor_count_geq(unsigned_value_type x, unsigned_value_type lower) const {
            return _root->siz - xor_count_lt(x, lower);
        }
        // #{ v in S | x ^ v > lower }
        size_type xor_count_gt (unsigned_value_type x, unsigned_value_type lower) const {
            return _root->siz - xor_count_leq(x, lower);
        }

        // max{ x ^ v | x ^ v < upper } or std::nullopt
        std::optional<value_type> safe_xor_max_lt (unsigned_value_type x, unsigned_value_type upper) const {
            internal_size_type clt = xor_count_lt(x, upper);
            if (clt == 0) return std::nullopt;
            return xor_kth_min(clt - 1);
        }
        // max{ x ^ v | x ^ v <= upper } or std::nullopt
        std::optional<value_type> safe_xor_max_leq(unsigned_value_type x, unsigned_value_type upper) const {
            internal_size_type clt = xor_count_leq(x, upper);
            if (clt == 0) return std::nullopt;
            return xor_kth_min(clt - 1);
        }
        // min{ x ^ v | x ^ v >= lower } or std::nullopt
        std::optional<value_type> safe_xor_min_geq(unsigned_value_type x, unsigned_value_type lower) const {
            internal_size_type clt = xor_count_lt(x, lower);
            if (clt == _root->siz) return std::nullopt;
            return xor_kth_min(clt);
        }
        // min{ x ^ v | x ^ v > lower } or std::nullopt
        std::optional<value_type> safe_xor_min_gt (unsigned_value_type x, unsigned_value_type lower) const {
            internal_size_type clt = xor_count_leq(x, lower);
            if (clt == _root->siz) return std::nullopt;
            return xor_kth_min(clt);
        }

        // max{ x ^ v | x ^ v < upper } or Runtime Error
        value_type xor_max_lt (unsigned_value_type x, unsigned_value_type upper) const { return *safe_xor_max_lt (x, upper); }
        // max{ x ^ v | x ^ v <= upper } or Runtime Error
        value_type xor_max_leq(unsigned_value_type x, unsigned_value_type upper) const { return *safe_xor_max_leq(x, upper); }
        // min{ x ^ v | x ^ v >= lower } or Runtime Error
        value_type xor_min_geq(unsigned_value_type x, unsigned_value_type lower) const { return *safe_xor_min_geq(x, lower); }
        // min{ x ^ v | x ^ v > lower } or Runtime Error
        value_type xor_min_gt (unsigned_value_type x, unsigned_value_type lower) const { return *safe_xor_min_gt (x, lower); }

        // 0-indexed
        value_type kth_min(internal_size_type k) const { return xor_kth_min(0, k); }
        // 0-indexed
        value_type kth_max(internal_size_type k) const { return xor_kth_max(0, k); }
        // #{ v in S | v < upper }
        size_type count_lt (unsigned_value_type upper) const { return xor_count_lt (0, upper); }
        // #{ v in S | v <= upper }
        size_type count_leq(unsigned_value_type upper) const { return xor_count_leq(0, upper); }
        // #{ v in S | v >= lower }
        size_type count_geq(unsigned_value_type lower) const { return xor_count_geq(0, lower); }
        // #{ v in S | v > lower }
        size_type count_gt (unsigned_value_type lower) const { return xor_count_gt (0, lower); }

        // max{ v | v < upper } or std::nullopt
        std::optional<value_type> safe_max_lt (unsigned_value_type upper) const { return safe_xor_max_lt(upper); }
        // max{ v | v <= upper } or std::nullopt
        std::optional<value_type> safe_max_leq(unsigned_value_type upper) const { return safe_xor_max_leq(upper); }
        // min{ v | v >= lower } or std::nullopt
        std::optional<value_type> safe_min_geq(unsigned_value_type lower) const { return safe_xor_min_geq(lower); }
        // min{ v | v > lower } or std::nullopt
        std::optional<value_type> safe_min_gt (unsigned_value_type lower) const { return safe_xor_min_gt(lower); }

        // max{ v | v < upper } or Runtime Error
        value_type max_lt (unsigned_value_type upper) const { return *safe_max_lt (upper); }
        // max{ v | v <= upper } or Runtime Error
        value_type max_leq(unsigned_value_type upper) const { return *safe_max_leq(upper); }
        // min{ v | v >= lower } or Runtime Error
        value_type min_geq(unsigned_value_type lower) const { return *safe_min_geq(lower); }
        // min{ v | v > lower } or Runtime Error
        value_type min_gt (unsigned_value_type lower) const { return *safe_min_gt (lower); }

    private:
        node_pointer_type _root = node_type::new_node(0, 0, 0);

        static constexpr unsigned_value_type cut_lower(const unsigned_value_type& val, uint32_t r) {
            return val & ((unsigned_value_type(1) << r) - 1);
        }
        static constexpr uint32_t bit_reverse_u32(uint32_t x) {
            x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
            x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
            x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
            x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
            return ((x >> 16) | (x << 16));
        }
        static constexpr uint64_t bit_reverse_u64(uint64_t x) {
            x = (((x & 0xaaaaaaaaaaaaaaaa) >> 1) | ((x & 0x5555555555555555) << 1));
            x = (((x & 0xcccccccccccccccc) >> 2) | ((x & 0x3333333333333333) << 2));
            x = (((x & 0xf0f0f0f0f0f0f0f0) >> 4) | ((x & 0x0f0f0f0f0f0f0f0f) << 4));
            x = (((x & 0xff00ff00ff00ff00) >> 8) | ((x & 0x00ff00ff00ff00ff) << 8));
            x = (((x & 0xffff0000ffff0000) >> 16) | ((x & 0x0000ffff0000ffff) << 16));
            return ((x >> 32) | (x << 32));
        }
        static constexpr void bit_reverse(unsigned_value_type& x) {
            if constexpr (bit_num <= 32) {
                x = bit_reverse_u32(x) >> (32 - bit_num);
            } else {
                x = bit_reverse_u64(x) >> (64 - bit_num);
            }
        }

        __attribute__((target("bmi"))) bool _insert_if_absent(node_pointer_type cur, uint32_t l, unsigned_value_type val) {
            if (l == bit_num) return false;
            const uint32_t idx = val & (ary - 1);
            node_pointer_type nxt = cur->ch[idx];
            if (not nxt) {
                cur->ch[idx] = node_type::new_node(val, bit_num - l, 1);
                ++cur->siz;
                return true;
            }
            unsigned_value_type x = val ^ nxt->val;
            uint32_t len = nxt->len, tz = len <= 32 ? _tzcnt_u32(x) : _tzcnt_u64(x);
            tz -= tz & (log_ary - 1);
            if (tz >= len) {
                bool inserted = _insert_if_absent(nxt, l + len, val >> len);
                cur->siz += inserted;
                return inserted;
            }
            node_pointer_type br = node_type::new_node(cut_lower(nxt->val, tz), tz, nxt->siz + 1);
            cur->ch[idx] = br;
            nxt->val >>= tz;
            nxt->len -= tz;
            val >>= tz;
            br->ch[nxt->val & (ary - 1)] = nxt;
            br->ch[val & (ary - 1)] = node_type::new_node(val, bit_num - l - tz, 1);
            ++cur->siz;
            return true;
        }

        __attribute__((target("bmi"))) void _insert(node_pointer_type cur, uint32_t l, unsigned_value_type val, internal_size_type num) {
            cur->siz += num;
            if (l == bit_num) return;
            const uint32_t idx = val & (ary - 1);
            node_pointer_type nxt = cur->ch[idx];
            if (not nxt) {
                cur->ch[idx] = node_type::new_node(val, bit_num - l, num);
                return;
            }
            unsigned_value_type x = val ^ nxt->val;
            uint32_t len = nxt->len, tz = len <= 32 ? _tzcnt_u32(x) : _tzcnt_u64(x);
            tz -= tz & (log_ary - 1);
            if (tz >= len) return _insert(nxt, l + len, val >> len, num);
            node_pointer_type br = node_type::new_node(cut_lower(nxt->val, tz), tz, nxt->siz + num);
            cur->ch[idx] = br;
            nxt->val >>= tz;
            nxt->len -= tz;
            val >>= tz;
            br->ch[nxt->val & (ary - 1)] = nxt;
            br->ch[val & (ary - 1)] = node_type::new_node(val, bit_num - l - tz, num);
        }

        bool _erase(node_pointer_type cur, internal_size_type &num, uint32_t l, unsigned_value_type val) {
            if (l == bit_num) {
                if (cur->siz -= num = std::min(num, cur->siz); cur->siz) return false;
                delete cur;
                return true;
            }
            const uint32_t idx = val & (ary - 1);
            node_pointer_type nxt = cur->ch[idx];
            if (not nxt or cut_lower(val ^ nxt->val, nxt->len)) return num = 0, false;
            bool deleted = _erase(nxt, num, l + nxt->len, val >> nxt->len);
            cur->siz -= num;
            if (not deleted) return false;
            cur->ch[idx] = nullptr;
            if (cur == _root) return false;
            if (cur->siz == 0) {
                delete cur;
                return true;
            }
            uint32_t ch_cnt = 0;
            node_pointer_type ch = nullptr;
            for (uint32_t i = 0; i < ary; ++i) if (cur->ch[i]) {
                ++ch_cnt, ch = cur->ch[i];
            }
            if (ch_cnt == 1) {
                cur->val |= ch->val << cur->len;
                cur->len += ch->len;
                for (uint32_t i = 0; i < ary; ++i) cur->ch[i] = std::exchange(ch->ch[i], nullptr);
                delete ch;
            }
            return false;
        }
    };
} // namespace suisen


#endif // SUISEN_BINARY_TRIE_PATRICIA
