#pragma once


#include <chrono>
#include <ostream>

namespace Feather {
    // Wrapper around std::chrono::duration to allow direct float arithmetic defaulting to seconds
    class Time {
    public:
        Time(std::chrono::duration<float> time): time(time) {}

        Time(const Time& other) = default;
        Time(Time&& other) = default;
        ~Time() = default;


        constexpr operator float() const { return this->Seconds(); }

        constexpr float Seconds() const { return time.count(); }
        constexpr float Milliseconds() const { return std::chrono::duration<float, std::milli>(time).count(); }
        constexpr float Microseconds() const { return std::chrono::duration<float, std::micro>(time).count(); }
        constexpr float Nanoseconds()  const { return std::chrono::duration<float, std::nano >(time).count(); }


        friend std::ostream& operator<<(std::ostream& output, Time time) { return output << time.Seconds() << 's'; }

    private:
        const std::chrono::duration<float> time;
    };
}
