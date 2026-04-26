# MultiLevelCacheEngine

A compact C++ project that demonstrates a multi-level caching system with LRU eviction and promotion of accessed items to the highest cache tier.

## Overview

This engine manages several cache levels in a single container. When data is accessed, it is promoted toward the top level so that hot items stay in the fastest tier. Each cache level uses an LRU policy to evict the least recently used item when capacity is reached.

## Key concepts

- Multi-level cache stack: each level has a fixed capacity
- LRU eviction within each level
- Promotion on `get`: a found entry is moved back to the top level
- Transparent cascading: evicted items move downward through lower levels

## Build

Requires:

- CMake 3.10 or newer
- A C++17-compatible compiler

From the project root:

```powershell
mkdir -Force build
cd build
cmake ..
cmake --build .
```

## Run

After building, run the generated executable:

```powershell
.\build\cache_app.exe
```

The sample `main.cpp` demonstrates basic usage and should print:

```text
10
20
```

## Project structure

- `src/main.cpp` - example usage and simple runtime flow
- `src/cache/multi_level_cache.h` / `.cpp` - multi-level cache orchestration
- `src/cache/cache_level.h` / `.cpp` - single cache tier wrapper
- `src/eviction/lru_policy.h` / `.cpp` - least-recently-used eviction implementation
- `config/` - configuration assets placeholder
- `tests/` - intended location for future unit tests

## Design notes

- `MultiLevelCache::put` removes duplicates across all levels before inserting
- `get` searches from the top level down and promotes a hit back to level 1
- Each level returns an evicted key/value pair, allowing downstream propagation

## Future improvements

- add persistent storage or a disk-backed level
- support additional eviction policies beyond LRU
- add configuration-driven cache topology from JSON or YAML
- add unit tests under `tests/`


