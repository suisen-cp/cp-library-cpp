#ifndef SUISEN_TRANSPOSE
#define SUISEN_TRANSPOSE

#include <string>
#include <vector>

namespace suisen {
    template <typename T>
    std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>> &A) {
        if (A.empty()) return A;
        const int N = A.size(), M = A[0].size();
        std::vector<std::vector<T>> B(M, std::vector<T>(N));
        for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) B[j][i] = A[i][j];
        return B;
    }
    std::vector<std::string> transpose(const std::vector<std::string> &A) {
        if (A.empty()) return A;
        const int N = A.size(), M = A[0].size();
        std::vector<std::string> B(M, std::string(N, '\0'));
        for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) B[j][i] = A[i][j];
        return B;
    }
} // namespace suisen


#endif // SUISEN_TRANSPOSE
