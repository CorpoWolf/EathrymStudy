cmake_minimum_required(VERSION 3.10)

project(Eathrym)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the C++ standard and other common flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")

if(MSVC)
    # Set Multi-threaded Debug (/MTd) for Debug configuration
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

    # Set Multi-threaded (/MT) for Release configuration
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
else()
    # Set appropriate flags for Clang
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")

set(LIBS "H:/Coding/00_LIBRARIES")

include_directories(${LIBS}/GLFW/include)
include_directories(${LIBS}/GLAD/include)
include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${LIBS}/GLFW/lib)

set(SOURCE_FILES
    src/main.cpp
    src/shader.cpp
    src/triangle.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ./external/glad/glad.c)

target_link_libraries(${PROJECT_NAME} glfw3)