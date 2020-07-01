cmake_minimum_required(VERSION 3.15)

file(GLOB SRC
    "**.h"
    "**.cpp"
)

add_library(OSource ${SRC})

target_include_directories(OSource PRIVATE ${PROJECT_SOURCE_DIR}/lib/spdlog/include)