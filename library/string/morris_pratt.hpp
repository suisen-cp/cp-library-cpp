#ifndef SUISEN_MORRIS_PRATT
#define SUISEN_MORRIS_PRATT

#include <string>
#include <vector>

namespace suisen {
    namespace morris_pratt {
        template <typename RandomAccessIterator>
        std::vector<int> morris_pratt(RandomAccessIterator start, RandomAccessIterator last) {
            const int n = last - start;
            std::vector<int> mp(n + 1);
            mp[0] = -1;
            int j = -1;
            for (int i = 0; i < n; ++i) {
                while (j >= 0 and *(start + i) != *(start + j)) j = mp[j];
                mp[i + 1] = ++j;
            }
            return mp;
        }
        template <typename RandomAccessibleContainer>
        auto morris_pratt(const RandomAccessibleContainer &s) { return morris_pratt(s.begin(), s.end()); }

        template <typename RandomAccessIterator>
        std::vector<int> all_periods(RandomAccessIterator start, RandomAccessIterator last, bool accept_fragment = true) {
            auto mp = morris_pratt(start, last);
            const int n = mp.size() - 1;
            std::vector<int> res;
            for (int r = n; r; r = mp[r]) {
                if (int p = n - mp[r]; accept_fragment or n % p == 0) res.push_back(p);
            }
            return res;
        }

        template <typename RandomAccessIterator, typename OutputIterator>
        void min_period(RandomAccessIterator start, RandomAccessIterator last, OutputIterator result, bool accept_fragment = true) {
            int p = all_periods(start, last, accept_fragment)[0];
            while (p --> 0) *result++ = *start++;
        }
        template <typename RandomAccessibleContainer>
        RandomAccessibleContainer min_period(RandomAccessibleContainer s, bool accept_fragment = true) {
            RandomAccessibleContainer res;
            min_period(s.begin(), s.end(), std::back_inserter(res), accept_fragment);
            return res;
        }

        template <typename RandomAccessibleContainer>
        struct MatcherMP {
            MatcherMP() = default;
            MatcherMP(const RandomAccessibleContainer &s) : s(s), mp(morris_pratt(s)) {}
            vector<int> operator()(const RandomAccessibleContainer &t) const {
                const int n = s.size(), m = t.size();
                std::vector<int> res;
                for (int i = 0, j = 0; i < m; ++i) {
                    while (j >= 0 and s[j] != t[i]) j = mp[j];
                    if (++j == n) res.push_back(i - n + 1);
                }
                return res;
            }
            vector<int> enumerate_occurences(const RandomAccessibleContainer &t) const {
                return (*this)(t);
            }
        private:
            RandomAccessibleContainer s;
            std::vector<int> mp;
        };
    }
} // namespace suisen


#endif // SUISEN_MORRIS_PRATT
