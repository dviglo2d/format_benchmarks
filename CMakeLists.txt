# Copyright (c) the Dviglo project
# License: MIT

cmake_minimum_required(VERSION 3.16)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(third_party/benchmark)
add_subdirectory(third_party/pugixml)
add_subdirectory(third_party/rapidjson)
add_subdirectory(third_party/rapidyaml)
add_subdirectory(third_party/yaml-cpp)

project(format_benchmarks)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/utf-8)
endif()

set(target_name format_benchmarks)
file(GLOB source_files src/*.cpp src/*.hpp src/*.inl)
add_executable(${target_name} ${source_files})
target_link_libraries(${target_name} PRIVATE benchmark::benchmark pugixml::pugixml rapidjson ryml yaml-cpp::yaml-cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src FILES ${source_files})
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${target_name})
