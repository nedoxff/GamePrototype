cmake_minimum_required(VERSION 3.21)
project(GamePrototype)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")

# MSVC stuff
set(CMAKE_CXX_FLAGS "/EHa /ZI")

# GCC stuff
# set(CMAKE_CXX_FLAGS "-g")

add_subdirectory(Dependencies)

file(GLOB_RECURSE FILES Core/* Helpers/* States/* UI/* Extensions/*)
add_executable(GamePrototype ${FILES} main.cpp Helpers/Updateable.hpp)

target_link_libraries(GamePrototype ImGui-SFML::ImGui-SFML sfml-graphics sfml-audio sfml-system sfml-window spdlog tweeny Motion pugixml)

add_custom_command(TARGET GamePrototype POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:GamePrototype>
        $<TARGET_FILE_DIR:GamePrototype>
        COMMAND_EXPAND_LISTS)