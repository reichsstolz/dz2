cmake_minimum_required(VERSION 3.19)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#set(SFML_STATIC_LIBRARIES TRUE)
project(dz2)
add_executable(dz2
        hit.cpp
        main.cpp
        map.cpp
        ship.cpp
        player.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/headers)


find_package(SFML 2.5 REQUIRED network audio graphics window system REQUIRED)
target_link_libraries(dz2 sfml-graphics sfml-window sfml-system)




