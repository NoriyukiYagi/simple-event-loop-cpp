#include "MessageQueue.hpp"

#include <chrono>

namespace event_loop {

MessageQueue::MessageQueue() {}

bool MessageQueue::WaitForNextMessage()
{
    std::unique_lock<std::mutex> lock(m_mutex);

    while (true) {
        if (!m_queue.empty()) {
            auto message = m_queue.top();
            auto estimated = message->Time();
            auto now = std::chrono::system_clock::now();
            if (estimated > now) {
                auto status = m_cond.wait_for(lock, estimated - now);
                if (status == std::cv_status::timeout) {
                    return true;
                } else {
                    continue;
                }
            } else {
                return true;
            }
        } else {
            m_cond.wait(lock);
        }
    }
}

void MessageQueue::ProcessNextMessage()
{
    std::shared_ptr<TimedMessage> message = nullptr;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (!m_queue.empty()) {
            message = m_queue.top();
            m_queue.pop();
        } else {
            return;
        }
    }
    message->Process();
}

void MessageQueue::SendMessage(std::shared_ptr<TimedMessage> message)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(message);
    }
    m_cond.notify_one();
}

} // namespace event_loop
