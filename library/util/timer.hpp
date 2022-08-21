#ifndef SUISEN_TIMER
#define SUISEN_TIMER

#include <chrono>

namespace suisen {
    struct Timer {
        using minutes_t = std::chrono::minutes;
        using seconds_t = std::chrono::seconds;
        using milliseconds_t = std::chrono::milliseconds;
        using microseconds_t = std::chrono::microseconds;
        using nanoseconds_t = std::chrono::nanoseconds;

        Timer() { start(); }

        void start() {
            _start = std::chrono::system_clock::now();
        }
        template <typename TimeUnit = std::chrono::milliseconds>
        double elapsed() const {
            return std::chrono::duration_cast<TimeUnit>(std::chrono::system_clock::now() - _start).count();
        }

        template <typename TimeUnit = std::chrono::milliseconds, typename Proc>
        static double measure(Proc &&proc) {
            Timer timer;
            proc();
            return timer.elapsed<TimeUnit>();
        }
    private:
        decltype(std::chrono::system_clock::now()) _start;
    };
} // namespace suisen


#endif // SUISEN_TIMER
