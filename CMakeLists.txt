# required
cmake_minimum_required(VERSION 3.10)

# set some flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE "Debug")

add_compile_options(-Wall -Wextra -Werror -O4)

# set the project name and version
project(dwproto VERSION 0.1)

# add the NSEngine lib directory
# TODO find a way to not need a link
add_subdirectory(NSEngineGit)

# get source files
file(GLOB_RECURSE SRCS src/*.cpp src/*.c)
file(GLOB_RECURSE INCLUDES src/*.hpp src/*.h)

file(GLOB_RECURSE EDITOR_SRCS editor/*.cpp editor/*.c imgui/*.cpp imgui/*.c)
file(GLOB_RECURSE EDITOR_INCLUDES editor/*.hpp editor/*.h)

# add the executable
add_executable(dwproto ${SRCS} ${INCLUDES})
add_executable(dwedit ${EDITOR_SRCS} ${EDITOR_INCLUDES})

# add the build directory as an include directory (for the config header)
target_include_directories(dwproto PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/imgui"
                          )
target_include_directories(dwedit PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/imgui"
                          )

find_package(imgui REQUIRED)

# link the NSEngine library. All the dependencies are added directly to the engine
target_link_libraries(dwproto PUBLIC NSEngine
                                 -ljsoncpp
                                 imgui::imgui)

target_link_libraries(dwedit PUBLIC NSEngine
                                 -ljsoncpp
                                 imgui::imgui)

# TODO do this better (copy assets in build directory)
file(COPY assets DESTINATION ${PROJECT_BINARY_DIR})
