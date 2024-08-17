# Copyright (c) the Dviglo project
# License: MIT

set(target_name rapidjson)
file(GLOB_RECURSE source_files repo/include/rapidjson/*.h)
add_library(${target_name} INTERFACE ${source_files})
target_include_directories(${target_name} INTERFACE repo/include)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/repo/include/rapidjson FILES ${source_files})
