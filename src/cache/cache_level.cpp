#include "cache_level.h"


CacheLevel::CacheLevel(int capacity) : cache(capacity) {}

int CacheLevel::get(int key) {
    return cache.get(key);
}

std::pair<int,int> CacheLevel::put(int key, int value) {
    return cache.put(key, value);
}

void CacheLevel::remove(int key) {
    return cache.remove(key);
}

bool CacheLevel::exists(int key) {
    return cache.exists(key);
}
