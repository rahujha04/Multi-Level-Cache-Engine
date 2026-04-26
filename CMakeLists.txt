cmake_minimum_required(VERSION 3.10)
project(MultiLevelCache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    src/main.cpp
    src/cache/multi_level_cache.cpp
    src/cache/cache_level.cpp
    src/eviction/lru_policy.cpp
)

add_executable(cache_app ${SOURCES})

target_include_directories(cache_app PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)