cmake_minimum_required(VERSION 3.14)
project(pddlParser)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_directories(/home/hejia/Projects/VAL/build/linux64/Release/bin)

include_directories(/home/hejia/Projects/VAL/libraries/VAL/include)

add_executable(pddlParser main.cpp)
target_link_libraries(pddlParser VAL)