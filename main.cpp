#include "EventLoop.hpp"
#include <iostream>
#include <thread>

using namespace event_loop;

static void loop(EventLoop& eventLoop)
{
    static int count = 0;
    std::cout << "loop: " << count++ << std::endl;
    eventLoop.Call([&eventLoop]() { loop(eventLoop); }, std::chrono::milliseconds(100));
}

int main(void)
{
    EventLoop eventLoop;

    // priority test
    eventLoop.Call([]() { std::cout << "pri: 1" << std::endl; });
    eventLoop.Call([]() { std::cout << "pri: 2" << std::endl; });
    eventLoop.Call([]() { std::cout << "pri: 5" << std::endl; }, std::chrono::milliseconds(100));
    eventLoop.Call([]() { std::cout << "pri: 8" << std::endl; }, std::chrono::milliseconds(400));
    eventLoop.Call([]() { std::cout << "pri: 9" << std::endl; }, std::chrono::milliseconds(500));
    eventLoop.Call([]() { std::cout << "pri: 3" << std::endl; });
    eventLoop.Call([]() { std::cout << "pri: 6" << std::endl; }, std::chrono::milliseconds(200));
    eventLoop.Call([]() { std::cout << "pri: 4" << std::endl; });
    eventLoop.Call([]() { std::cout << "pri: 7" << std::endl; }, std::chrono::milliseconds(300));

    // loop test
    loop(eventLoop);

    // quit event
    eventLoop.Call([&eventLoop]() { eventLoop.Stop(); }, std::chrono::milliseconds(3000));

    eventLoop.Run();
    return 0;
}
