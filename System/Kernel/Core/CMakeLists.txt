cmake_minimum_required(VERSION 3.10)
project(MCS-Core C)

# Quellen
file(GLOB CORE_SOURCES "core/*.c")

# Bibliothek (statisch)
add_library(mcs-core STATIC ${CORE_SOURCES})
target_include_directories(mcs-core PUBLIC ${CMAKE_SOURCE_DIR}/include)

# CLI-Tool
add_executable(mcs-run main.c)
target_link_libraries(mcs-run mcs-core)
