#include "eviction/lru_policy.h"
#include "eviction/lfu_policy.h"
#include "cache/multi_level_cache.h"
#include <vector>

int main() {
    std::vector<int> caps = {2, 2, 2};

    std::vector<EvictionPolicy*> policies = {
        new LRUPolicy(),
        new LFUPolicy(),
        new LRUPolicy()
    };

    MultiLevelCache cache(caps, policies);

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);

    std::cout << cache.get(1) << std::endl;
    std::cout << cache.get(2) << std::endl;

    return 0;
}