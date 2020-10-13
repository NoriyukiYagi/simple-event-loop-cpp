#include "EventLoop.hpp"

#include "TimedMessage.hpp"
#include <chrono>
#include <memory>

namespace event_loop {

EventLoop::EventLoop()
    : m_isRunning(false)
{}

void EventLoop::Run()
{
    m_isRunning = true;
    while (m_messageQueue.WaitForNextMessage()) {
        m_messageQueue.ProcessNextMessage();
        if (!m_isRunning) {
            return;
        }
    }
}

void EventLoop::Call(std::function<void()> func, std::chrono::milliseconds delay)
{
    auto now = std::chrono::system_clock::now();
    m_messageQueue.SendMessage(std::make_shared<TimedMessage>(now + delay, func));
}

void EventLoop::Stop()
{
    Call([this]() { this->m_isRunning = false; });
}

} // namespace event_loop
