cmake_minimum_required(VERSION 3.25)
project(ecosys_sim)

set(CMAKE_CXX_STANDARD 17)

add_executable(ecosys_sim main.cpp humanoid.hpp humanoid.cpp human.hpp human.cpp zombie.hpp zombie.cpp map.hpp map.cpp tile.hpp tile.cpp humanoid_controller.cpp humanoid_controller.hpp print_color.hpp print_color.cpp)
