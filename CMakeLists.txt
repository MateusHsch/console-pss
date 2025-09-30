cmake_minimum_required(VERSION 3.16)
project(process_scheduler_simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(process_scheduler_simulator src/main.cpp)

target_sources(process_scheduler_simulator PRIVATE
    src/Core.cpp
    src/Process.cpp
    src/Scheduler.cpp
    src/Simulator.cpp
)

target_include_directories(process_scheduler_simulator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)