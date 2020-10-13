#pragma once

#include "MessageQueue.hpp"
#include <atomic>
#include <chrono>
#include <functional>

namespace event_loop {

class EventLoop
{
public:
    EventLoop();
    void Run();
    void Call(std::function<void()> func,
              std::chrono::milliseconds delay = std::chrono::milliseconds::zero());
    void Stop();

private:
    MessageQueue m_messageQueue;
    std::atomic<bool> m_isRunning;
};

} // namespace event_loop
