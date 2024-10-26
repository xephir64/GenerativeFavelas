cmake_minimum_required(VERSION 3.5)
project(GenerativeFavelas)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(dependencies/glfw)

include_directories(dependencies/glad/include/
                    dependencies/glfw/include/
                    dependencies/glm/
                    dependencies/stb/)


file(GLOB VENDORS_SOURCES dependencies/glad/src/glad.c)
file(GLOB_RECURSE PROJECT_HEADERS "src/*.h")
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")

include_directories(include)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -std=c++14 -g")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

add_executable(GenerativeFavelas ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${VENDORS_SOURCES})

target_link_libraries(GenerativeFavelas glfw)
