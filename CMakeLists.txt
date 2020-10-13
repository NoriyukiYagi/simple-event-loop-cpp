cmake_minimum_required(VERSION 3.8)

project(event_loop)

include_directories(include)

add_executable(event_loop
    main.cpp
    src/TimedMessage.cpp
    src/MessageQueue.cpp
    src/EventLoop.cpp)

