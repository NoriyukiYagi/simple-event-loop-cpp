#include "TimedMessage.hpp"

namespace event_loop {
TimedMessage::TimedMessage(std::chrono::system_clock::time_point time,
                           std::function<void()> callback)
    : m_time(time)
    , m_callback(callback)
{}

std::chrono::system_clock::time_point TimedMessage::Time() const
{
    return m_time;
}

void TimedMessage::Process()
{
    m_callback();
}
} // namespace event_loop
