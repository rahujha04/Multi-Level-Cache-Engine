#pragma once

#include <vector>
#include "cache_level.h"

class MultiLevelCache {
    private:
        std::vector<CacheLevel*> levels;
        void removeFromAllLevels(int key);
        void promoteToTopLevel(int key, int value, int levelIdx);
    public:
        MultiLevelCache(const std::vector<int> &capacity);

        int get(int key);
        void put(int key, int value);

};