cmake_minimum_required(VERSION 3.14)
project(MovieTicketBookingSystem
    VERSION 1.0.0
    DESCRIPTION "Object-Oriented C++17 Cinema Ticket Booking System"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

add_executable(cinema_app main.cpp)
