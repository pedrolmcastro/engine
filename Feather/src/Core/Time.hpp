#pragma once


namespace Feather {
    class Time {
    public:
        Time(float time = 0.0f): time(time) {}

        operator float() const { return time; }

        float GetSeconds() { return time; }
        float GetMilliseconds() { return time * 1000.0f; }
    private:
        float time;
    };
}
