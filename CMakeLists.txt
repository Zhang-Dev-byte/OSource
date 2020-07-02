cmake_minimum_required(VERSION 3.15)

project(Sandbox)

add_subdirectory(OSource/src/)
add_subdirectory(Sandbox/src/)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set_target_properties( Sandbox PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_PROJECT_NAME} )

add_subdirectory(lib/glfw)

target_link_libraries(Sandbox glfw)

add_subdirectory(lib/glad)

target_link_libraries(Sandbox glad)


target_link_libraries(OSource glfw)

target_link_libraries(OSource glad)


target_include_directories(Sandbox PRIVATE ${PROJECT_SOURCE_DIR}/OSource/src)

target_include_directories(Sandbox PRIVATE ${PROJECT_SOURCE_DIR}/lib/spdlog/include)

target_include_directories(Sandbox PRIVATE ${PROJECT_SOURCE_DIR}/lib/glm)

