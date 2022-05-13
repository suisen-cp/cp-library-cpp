---
title: Array Matrix
documentation_of: //library/linear_algebra/array_matrix.hpp
---
## Array Matrix

行列のサイズがコンパイル時定数として書ける場合は、`std::array` を用いることで定数倍高速化を図ることが出来る (特に、行列のサイズが小さい場合)。
