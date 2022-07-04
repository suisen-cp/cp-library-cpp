#include <iostream>
#include <optional>
#include <string>

namespace suisen::parsing {
    using State = std::string::const_iterator;

    struct ParseError {
        ParseError(const std::string& message = "") {
            std::cerr << message << std::endl;
        }
    };

    namespace internal {
        void print_rest_of_string(State it) {
            cerr << "Rest string is '";
            while (*it) cerr << *it++;
            cerr << "'" << endl;
        }
    }

    void consume(State& it, char expected) {
        if (*it == expected) {
            *it++;
        } else {
            cerr << "Expected '" << expected << "' but got '" << *it << "'" << endl;
            internal::print_rest_of_string(it);
            throw ParseError{};
        }
    }

    bool in(const State& it, char l, char r) {
        return l <= *it and *it <= r;
    }
    bool is(const State& it, char c) {
        return *it == c;
    }

    void assert_range(const State& it, char lo, char hi) {
        if (in(it, lo, hi)) {
            cerr << "Expected [" << lo << "-" << hi << "] but got '" << *it << "'" << endl;
            internal::print_rest_of_string(it);
            throw ParseError{};
        }
    }
    void assert_exact(const State& it, char c) {
        if (not is(it, c)) {
            cerr << "Expected '" << c << "' but got '" << *it << "'" << endl;
            internal::print_rest_of_string(it);
            throw ParseError{};
        }
    }

    long long nonnegative_number(State& it) {
        long long res = 0;
        assert_range(it, '0', '9');
        while (in(it, '0', '9')) res = res * 10 + (*it++ - '0');
        return res;
    }
    long long number(State& it) {
        long long res = 0;
        bool neg = false;
        while (is(it, '-')) neg = not neg, consume(it, '-');
        while (in(it, '0', '9')) res = res * 10 + (*it++ - '0');
        if (neg) res = -res;
        return res;
    }

    namespace normal_expression {
        namespace internal {
            long long expr(State& it);
            long long term(State& it);
            long long factor(State& it);

            long long expr(State& it) {
                long long res = term(it);
                while (true) {
                    if (*it == '+') {
                        consume(it, '+');
                        res = res + term(it);
                    } else if (*it == '-') {
                        consume(it, '-');
                        res = res - term(it);
                    } else break;
                }
                return res;
            }
            long long term(State& it) {
                long long res = factor(it);
                while (true) {
                    if (*it == '*') {
                        consume(it, '*');
                        res = res * factor(it);
                    } else if (*it == '/') {
                        consume(it, '/');
                        res = res / factor(it);
                    } else break;
                }
                return res;
            }
            long long factor(State& it) {
                bool neg = false;
                while (is(it, '-')) neg = not neg, consume(it, '-');
                long long res;
                if (is(it, '(')) {
                    consume(it, '(');
                    res = expr(it);
                    consume(it, ')');
                } else {
                    res = nonnegative_number(it);
                }
                if (neg) res = -res;
                return res;
            }
        }

        long long parse(State& it) {
            return internal::expr(it);
        }
    }
}
