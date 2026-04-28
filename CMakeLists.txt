cmake_minimum_required(VERSION 3.10)
project(MultiLevelCache)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------
# Include directories
# -------------------------
include_directories(
    src
    src/cache
    src/eviction
    src/utils
)

# -------------------------
# Core source files
# -------------------------
set(CORE_SOURCES
    src/cache/multi_level_cache.cpp
    src/cache/cache_level.cpp
    src/eviction/lru_policy.cpp
    src/eviction/lfu_policy.cpp
)

# -------------------------
# Main executable
# -------------------------
add_executable(cache_app
    src/main.cpp
    ${CORE_SOURCES}
)

# -------------------------
# Benchmark executable
# -------------------------
add_executable(cache_benchmark
    benchmarks/benchmark.cpp
    ${CORE_SOURCES}
)