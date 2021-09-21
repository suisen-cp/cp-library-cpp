// cannot find testcases in drop box...

// #define PROBLEM "https://atcoder.jp/contests/past202104-open/tasks/past202104_m"

// #include <iostream>
// #include <tuple>
// #include <vector>

// #include "library/util/coordinate_compressor.hpp"
// #include "library/util/range_set.hpp"
// using suisen::CoordinateCompressorBuilder;
// using suisen::RangeSet;

// int main() {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);

//     int n;
//     std::cin >> n;

//     CoordinateCompressorBuilder<int> builder;

//     std::vector<int> init(n);
//     for (int &e : init) {
//         std::cin >> e;
//         builder.push(e);
//     }

//     int q;
//     std::cin >> q;
//     std::vector<std::tuple<int, int, int>> queries(q);
//     for (auto &[l, r, x] : queries) {
//         std::cin >> l >> r >> x;
//         --l;
//         builder.push(x);
//     }

//     auto compressor = builder.build();
//     for (int &e : init) {
//         e = compressor[e];
//     }
//     for (auto &query : queries) {
//         std::get<2>(query) = compressor[std::get<2>(query)];
//     }

//     int m = compressor.size();
//     std::vector<RangeSet<int>> sets(m);

//     int log = 0;
//     while (1 << log < m) ++log;
//     std::vector<RangeSet<int>> bits(log);

//     for (int i = 0; i < n; ++i) {
//         int v = init[i];
//         for (int bit = 0; bit < log; ++bit) {
//             if ((v >> bit) & 1) bits[bit].insert(i);
//         }
//         sets[v].insert(i);
//     }

//     auto get = [&](int i) {
//         int res = 0;
//         for (int bit = 0; bit < log; ++bit) {
//             res |= bits[bit].contains(i) << bit;
//         }
//         return res;
//     };

//     auto update = [&](int l, int r, int x) {
//         for (int bit = 0; bit < log; ++bit) {
//             if ((x >> bit) & 1) {
//                 bits[bit].insert(l, r - 1);
//             } else {
//                 bits[bit].erase(l, r - 1);
//             }
//         }
//     };

//     long long ans = 0;
//     for (const auto &set : sets) {
//         long long sz = set.size();
//         ans += sz * (sz - 1) / 2;
//     }
    
//     for (int i = 0; i < q; ++i) {
//         auto [l, r, x] = queries[i];

//         std::vector<int> rem;
//         for (int cur = l; cur < r;) {
//             const int v = get(cur);
//             rem.push_back(v);
//             cur = std::min(r, sets[v].minimum_excluded(cur));
//         }

//         for (int v : rem) {
//             auto &set = sets[v];
//             long long sz = set.size();
//             ans -= sz * (sz - 1) / 2;
//             sz -= set.erase(l, r - 1);
//             ans += sz * (sz - 1) / 2;
//         }

//         auto &set = sets[x];
//         long long sz = set.size();
//         ans -= sz * (sz - 1) / 2;
//         sz += set.insert(l, r - 1);
//         ans += sz * (sz - 1) / 2;

//         update(l, r, x);

//         std::cout << ans << '\n';
//     }
//     return 0;
// }