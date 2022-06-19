#ifndef SUISEN_VARIANT_UTILS
#define SUISEN_VARIANT_UTILS

#include <cassert>
#include <variant>

namespace suisen {

template <typename ...Types>
class Match {
    public:
        Match(std::variant<Types...> &&v) : v_(std::move(v)) {}
        Match(const std::variant<Types...> &v) : v_(v) {}

        template <typename T, typename F>
        Match&& with(F &&f) && {
            if (std::holds_alternative<T>(v_)) {
                assert(not matched);
                matched = true;
                f(std::get<T>(v_));
            }
            return std::move(*this);
        }
        template <typename F>
        void otherwise(F &&f) && {
            if (not matched) f();
        }
    private:
        std::variant<Types...> v_;
        bool matched = false;
};

template <typename ...Types>
Match(std::variant<Types...>) -> Match<Types...>;

} // namespace suisen


#endif // SUISEN_VARIANT_UTILS
