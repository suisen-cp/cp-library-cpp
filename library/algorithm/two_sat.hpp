#ifndef SUISEN_TWO_SAT
#define SUISEN_TWO_SAT

#include <atcoder/twosat>

namespace suisen {
    struct TwoSAT : public atcoder::two_sat {
        using base_type = atcoder::two_sat;
        using base_type::base_type;

        void implies(int x, bool f, int y, bool g) {
            base_type::add_clause(x, not f, y, g);
        }
        void set(int x, bool f) {
            base_type::add_clause(x, f, x, f);
        }
        void at_most_one(int x, bool f, int y, bool g) {
            base_type::add_clause(x, not f, y, not g);
        }
        void exactly_one(int x, bool f, int y, bool g) {
            base_type::add_clause(x, f, y, g);
            base_type::add_clause(x, not f, y, not g);
        }
    };
} // namespace suisen


#endif // SUISEN_TWO_SAT
