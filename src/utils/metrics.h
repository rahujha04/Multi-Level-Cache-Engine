#pragma once
#include <iostream>

struct Metrics {
    int hits = 0;
    int misses = 0;
    int evictions = 0;

    void print(int level) const {
        std::cout << "Level " << level << " -> "
                  << "Hits: " << hits
                  << ", Misses: " << misses
                  << ", Evictions: " << evictions
                  << std::endl;
    }
};