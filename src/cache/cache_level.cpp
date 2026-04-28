#include "cache_level.h"

CacheLevel::CacheLevel(int cap, EvictionPolicy* p)
    : capacity(cap), policy(p) {}

int CacheLevel::get(int key) {
    std::lock_guard<std::mutex> lock(mtx);
    if (data.find(key) == data.end()) {
        metrics.misses++;
        return -1;
    }

    metrics.hits++;
    policy->touch(key);
    return data[key];
}

std::pair<int,int> CacheLevel::put(int key, int value) {
    std::lock_guard<std::mutex> lock(mtx);
    if (data.find(key) != data.end()) {
        data[key] = value;
        policy->touch(key);
        return {-1, -1};
    }

    if (data.size() == capacity) {
        int evictKey = policy->evict();
        int evictVal = data[evictKey];
        data.erase(evictKey);
        metrics.evictions++;

        data[key] = value;
        policy->insert(key);

        return {evictKey, evictVal};
    }

    data[key] = value;
    policy->insert(key);
    return {-1, -1};
}

void CacheLevel::remove(int key) {
    std::lock_guard<std::mutex> lock(mtx);
    if (data.find(key) == data.end()) return;

    data.erase(key);
    policy->remove(key);
}

bool CacheLevel::exists(int key) {
    return data.find(key) != data.end();
}

void CacheLevel::printMetrics(int level) {
    metrics.print(level);
}