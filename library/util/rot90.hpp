#ifndef SUISEN_ROT_90
#define SUISEN_ROT_90

#include <string>
#include <vector>

namespace suisen {
    /**
     * O|             O|       
     * -+------->j    -+----->j
     *  | a c e    =>  | e f   
     *  | b d f        | c d   
     *  v              | a b   
     *   i             v       
     *                  i      
     */
    template <typename T>
    std::vector<std::vector<T>> rot90(const std::vector<std::vector<T>> &A) {
        if (A.empty()) return A;
        const int N = A.size(), M = A[0].size();
        std::vector<std::vector<T>> B(M, std::vector<T>(N));
        for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) B[j][i] = A[i][M - j - 1];
        return B;
    }
    std::vector<std::string> rot90(const std::vector<std::string> &A) {
        if (A.empty()) return A;
        const int N = A.size(), M = A[0].size();
        std::vector<std::string> B(M, std::string(N, '\0'));
        for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) B[j][i] = A[i][M - j - 1];
        return B;
    }
} // namespace suisen


#endif // SUISEN_ROT_90
