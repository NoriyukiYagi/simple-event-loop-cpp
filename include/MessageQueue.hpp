#pragma once

#include "TimedMessage.hpp"
#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>
#include <queue>

namespace event_loop {

class MessagePriorityComparator
{
public:
    constexpr bool operator()(const std::shared_ptr<TimedMessage>& lhs,
                              const std::shared_ptr<TimedMessage>& rhs) const
    {
        return lhs->Time() > rhs->Time();
    }
};

class MessageQueue
{
public:
    MessageQueue();
    bool WaitForNextMessage();
    void ProcessNextMessage();
    void SendMessage(std::shared_ptr<TimedMessage> message);

private:
    std::priority_queue<std::shared_ptr<TimedMessage>,
                        std::deque<std::shared_ptr<TimedMessage>>,
                        MessagePriorityComparator>
        m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cond;
};
} // namespace event_loop
