cmake_minimum_required(VERSION 3.15)

file(GLOB SRC
    "**.h"
    "**.cpp"
)

add_executable(Sandbox ${SRC})