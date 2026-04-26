#pragma once

#include "eviction/lru_policy.h"

class CacheLevel {
    private:
        LRUCache cache;
    public:
        CacheLevel(int capacity);

        int get(int key);
        std::pair<int,int> put(int key, int value);
        void remove(int key);
        bool exists(int key);
};
