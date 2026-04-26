#include <iostream>
#include "cache/multi_level_cache.h"

int main() {
    MultiLevelCache cache({2, 2, 2});

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30); // 1 goes to L2

    std::cout << cache.get(1) << std::endl; // should promote to L1

    cache.put(4, 40);
    cache.put(5, 50);

    std::cout << cache.get(2) << std::endl;

    return 0;
}