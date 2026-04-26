#include "multi_level_cache.h"

MultiLevelCache::MultiLevelCache(const std::vector<int> &capacity) {
    for (int i = 0; i < static_cast<int>(capacity.size()); i++) {
        levels.push_back(new CacheLevel(capacity[i]));
    }
}

void MultiLevelCache::removeFromAllLevels(int key) {
    for (auto &level: levels) {
        level->remove(key);
    }
}

void MultiLevelCache::promoteToTopLevel(int key, int value, int levelIdx) {
    levels[levelIdx]->remove(key);

    std::pair<int,int> evicted = levels[0]->put(key, value);

    for (int i = 1; i <= levelIdx; i++) {
        if (evicted.first == -1) break;
        evicted = levels[i]->put(evicted.first, evicted.second);
    }
}

int MultiLevelCache::get(int key) {
    for (int i=0;i<levels.size();i++) {
        int val = levels[i]->get(key);

        if (val != -1) {
            promoteToTopLevel(key, val, i);
            return val;
        }
    }
    return -1;
}
void MultiLevelCache::put(int key, int value) {
    // ensure no duplicates
    removeFromAllLevels(key);

    std::pair<int,int> evicted = levels[0]->put(key, value);

    for (int i = 1; i < levels.size(); i++) {
        if (evicted.first == -1) break;
        evicted = levels[i]->put(evicted.first, evicted.second);
    }
}
