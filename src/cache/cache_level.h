#pragma once
#include <unordered_map>
#include "eviction/eviction_policy.h"
#include "utils/metrics.h"
#include <mutex>

class CacheLevel {
private:
    int capacity;
    std::unordered_map<int, int> data;
    EvictionPolicy* policy;
    Metrics metrics;
    std::mutex mtx;

public:
    CacheLevel(int cap, EvictionPolicy* p);

    int get(int key);
    std::pair<int,int> put(int key, int value);
    void remove(int key);
    bool exists(int key);
    void printMetrics(int level);
};