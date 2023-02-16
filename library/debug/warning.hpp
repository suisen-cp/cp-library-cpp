#ifndef SUISEN_WARNING
#define SUISEN_WARNING

#include <iostream>

namespace suisen {
    struct warning {
        warning(const std::string &msg) {
            std::cerr << "\033[33m[WARNING] " << msg << "\033[0m" << std::endl;
        }
    };
} // namespace suisen

#endif // SUISEN_WARNING
