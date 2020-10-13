#pragma once

#include <chrono>
#include <functional>

namespace event_loop {
class TimedMessage
{
public:
    TimedMessage(std::chrono::system_clock::time_point time, std::function<void()> callback);
    std::chrono::system_clock::time_point Time() const;
    void Process();

private:
    std::chrono::system_clock::time_point m_time;
    std::function<void()> m_callback;
};
} // namespace event_loop
