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

# Создаёт ссылку для папки. Если ссылку создать не удалось, то копирует папку
function(dv_create_dir_link from to)
    if(NOT CMAKE_HOST_WIN32)
        execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${from} ${to}
                        OUTPUT_QUIET ERROR_QUIET RESULT_VARIABLE RESULT)
    else()
        # Не используем create_symlink в Windows, так как создание symbolic links
        # [требует админских прав](https://ss64.com/nt/mklink.html),
        # а поддержка junctions из CMake
        # [была удалена](https://gitlab.kitware.com/cmake/cmake/-/merge_requests/7530)
        string(REPLACE / \\ from ${from})
        string(REPLACE / \\ to ${to})
        execute_process(COMMAND cmd /C mklink /J ${to} ${from}
                        OUTPUT_QUIET ERROR_QUIET RESULT_VARIABLE RESULT)
    endif()

    if(NOT RESULT EQUAL 0)
        # Причиной неудачи может быть перезаписанная переменная PATH, в которой нет %SystemRoot%\system32
        message("Не удалось создать ссылку для папки, поэтому копируем папку")
        execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory  ${from} ${to})
    endif()
endfunction()

# Куда будут помещены следующие скомпилированные экзешники и динамические библиотеки.
# Функцию нужно вызывать перед созданием таргетов
function(dv_set_bin_dir bin_dir)
    # Для одноконфигурационных генераторов (MinGW)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_dir} PARENT_SCOPE)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${bin_dir} PARENT_SCOPE)

    # Для многоконфигурационных генераторов (Visual Studio)
    foreach(config_name ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${config_name} config_name)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config_name} ${bin_dir} PARENT_SCOPE)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${config_name} ${bin_dir} PARENT_SCOPE)
    endforeach()
endfunction()

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/result)
dv_set_bin_dir(${CMAKE_BINARY_DIR}/result)
dv_create_dir_link(${CMAKE_SOURCE_DIR}/result/data ${CMAKE_BINARY_DIR}/result/data)

set(target_name format_benchmarks)
file(GLOB_RECURSE source_files src/*.cpp src/*.hpp)
add_executable(${target_name} ${source_files})
target_link_libraries(${target_name} PRIVATE benchmark::benchmark pugixml::pugixml rapidjson ryml yaml-cpp::yaml-cpp)

# Отладочная версия приложения будет иметь суффикс _d
set_property(TARGET ${target_name} PROPERTY DEBUG_POSTFIX _d)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src FILES ${source_files})
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${target_name})
