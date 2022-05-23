cmake_minimum_required(VERSION 3.20)
project(OOP5)

set(CMAKE_CXX_STANDARD 20)
find_package(Threads REQUIRED)

add_executable(OOP5 main.cpp Crawler.cpp)
target_link_libraries(OOP5 Threads::Threads)