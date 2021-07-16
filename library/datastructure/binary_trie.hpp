#ifndef SUISEN_BINARY_TRIE
#define SUISEN_BINARY_TRIE

#include <limits>
#include <optional>
#include <string>
#include <vector>

namespace suisen {
template <typename T, int bit_length = std::numeric_limits<std::make_unsigned_t<T>>::digits>
class BinaryTrie {
    using U = std::make_unsigned_t<T>;
    struct Node {
        int siz;
        Node *ch[2] {nullptr, nullptr};
        Node() : siz(0) {}
        ~Node() {
            delete ch[0];
            delete ch[1];
        }
        inline Node* get_or_create(bool b) noexcept {
            if (is_absent(b)) ch[b] = new Node();
            return ch[b];
        }
        inline Node* operator[](bool b) const noexcept { return ch[b]; }
        inline bool is_absent (bool b) const noexcept { return ch[b] == nullptr; }
        inline bool is_present(bool b) const noexcept { return ch[b] != nullptr; }
        static inline int size(const Node *const node) noexcept { return node == nullptr ? 0 : node->siz; }
        inline void update_size() noexcept { siz = size(ch[0]) + size(ch[1]); }

        std::string to_string(const int k = bit_length - 1, const U val = 0, const std::string &prefix = "") const {
            static const std::string zo[2] {"+-[0]- ", "+-[1]- "};
            static const std::string branch = '|' + std::string(zo[0].size() - 1, ' ');
            auto res = std::to_string(siz) + ' ';
            if (is_absent(0) and is_absent(1)) {
                return res + "(" + std::to_string(val) + ")\n";
            }
            auto pref0 = prefix + std::string(res.size(), ' ');
            auto prefb = pref0 + branch;
            auto pref1 = pref0 + std::string(zo[0].size(), ' ');
            if (is_absent(0) or is_absent(1)) {
                bool b = is_absent(0);
                return res + zo[b] + ch[b]->to_string(k - 1, val | (b << k), pref1);
            }
            res += zo[0] + ch[0]->to_string(k - 1, val, prefb);
            res += pref0 + "|\n";
            res += pref0 + zo[1] + ch[1]->to_string(k - 1, val | (1 << k), pref1);
            return res;
        }
    };
    public:
        BinaryTrie() : root(new Node) {}
        ~BinaryTrie() { delete root; }

        inline int size() const noexcept { return Node::size(root); }
        inline bool empty() const noexcept { return size() == 0; }

        void insert(const U val) noexcept {
            Node *cur = root;
            ++cur->siz;
            for (unsigned int i = bit_length; i --> 0;) {
                cur = cur->get_or_create(bit(val, i));
                ++cur->siz;
            }
        }
        int erase(const U val, const int num = 1) noexcept {
            return erase(root, bit_length - 1, val, num);
        }
        int erase_all(const U val) noexcept {
            return erase(val, std::numeric_limits<int>::max());
        }
        int prefix_count(const U val, const unsigned int l) const noexcept {
            Node *cur = root;
            for (unsigned int i = bit_length; i --> l;) {
                if (cur == nullptr) return 0;
                cur = (*cur)[bit(val, i)];
            }
            return Node::size(cur);
        }
        inline int count(const U val) const noexcept { return prefix_count(val, 0); }
        inline bool contains(const U val) const noexcept { return count(val) > 0; }

        inline U xor_kth_min(const U x, const int k) const {
            assert(0 <= k and k < size());
            return unchecked_xor_kth_min(x, k);
        }
        inline U xor_min(const U x) const { return xor_kth_min(x, 0);  }
        inline U xor_max(const U x) const { return xor_kth_min(~x, 0); }
        int xor_count_lt(const U x, const U val) const noexcept {
            int res = 0;
            Node *cur = root;
            for (int i = bit_length - 1; i >= 0; --i) {
                if (cur == nullptr) break;
                bool bx = bit(x, i);
                bool bv = bit(x ^ val, i);
                if (bx != bv) {
                    res += Node::size((*cur)[bx]);
                }
                cur = (*cur)[bv];
            }
            return res;
        }
        inline int xor_count_leq(const U x, const U val) const noexcept { return xor_count_lt(x, val) + count(val); }
        inline int xor_count_gt (const U x, const U val) const noexcept { return size() - xor_count_leq(x, val);    }
        inline int xor_count_geq(const U x, const U val) const noexcept { return size() - xor_count_lt(x, val);     }
        inline std::optional<U> xor_lower(const U x, const U val) const noexcept {
            int k = size() - xor_count_geq(x, val) - 1;
            return k < 0 ? std::nullopt : std::make_optional(unchecked_xor_kth_min(x, k));
        }
        inline std::optional<U> xor_floor(const U x, const U val) const noexcept {
            int k = size() - xor_count_gt(x, val) - 1;
            return k < 0 ? std::nullopt : std::make_optional(unchecked_xor_kth_min(x, k));
        }
        inline std::optional<U> xor_higher(const U x, const U val) const noexcept {
            int k = xor_count_leq(x, val);
            return k == size() ? std::nullopt : std::make_optional(unchecked_xor_kth_min(x, k));
        }
        inline std::optional<U> xor_ceil(const U x, const U val) const noexcept {
            int k = xor_count_lt(x, val);
            return k == size() ? std::nullopt : std::make_optional(unchecked_xor_kth_min(x, k));
        }

        inline U kth_min(const int k) const { return xor_kth_min(0, k); }
        inline U min() const { return xor_kth_min(0, 0); }
        inline U max() const { return xor_kth_min(~U(0), 0); }
        inline int count_lt (const U val) const noexcept { return xor_count_lt(0, val);  }
        inline int count_leq(const U val) const noexcept { return xor_count_leq(0, val); }
        inline int count_gt (const U val) const noexcept { return xor_count_gt(0, val);  }
        inline int count_geq(const U val) const noexcept { return xor_count_geq(0, val); }
        inline std::optional<U> lower (const U val) const noexcept { return xor_lower(0, val);  }
        inline std::optional<U> floor (const U val) const noexcept { return xor_floor(0, val);  }
        inline std::optional<U> higher(const U val) const noexcept { return xor_higher(0, val); }
        inline std::optional<U> ceil  (const U val) const noexcept { return xor_ceil(0, val);   }

        inline std::string to_string() const noexcept { return root->to_string(); }
        friend std::ostream& operator<<(std::ostream& out, const BinaryTrie &bt) { return out << bt.to_string(); }
    private:
        Node *const root;
        static constexpr bool bit(const U val, const int i) noexcept {
            return (val >> i) & 1;
        }
        int erase(Node *cur, const int k, const U val, const int num) {
            if (k == -1) {
                int removed = std::min(cur->siz, num);
                cur->siz -= removed;
                return removed;
            }
            bool b = bit(val, k);
            if (cur->is_absent(b)) return 0;
            int removed = erase((*cur)[b], k - 1, val, num);
            cur->update_size();
            return removed;
        }
        U unchecked_xor_kth_min(const U x, const int k) const noexcept {
            U res = 0;
            int rest = k;
            Node *cur = root;
            for (int i = bit_length - 1; i >= 0; --i) {
                bool b = bit(x, i);
                int sz = Node::size((*cur)[b]);
                if (sz <= rest) rest -= sz, b = not b;
                res |= U(b) << i;
                cur = (*cur)[b];
            }
            return x ^ res;
        }
};
} // namespace suisen

#endif // SUISEN_BINARY_TRIE
