#include <iostream>
#include <chrono>
#include <random>
#include "cache/multi_level_cache.h"
#include "eviction/lru_policy.h"
#include "eviction/lfu_policy.h"

using namespace std;
using namespace std::chrono;

void runRandomWorkload(MultiLevelCache& cache, int N) {
    mt19937 rng(42);
    uniform_int_distribution<int> dist(1, 1000);

    for (int i = 0; i < N; i++) {
        int key = dist(rng);

        if (i % 2 == 0)
            cache.put(key, key * 10);
        else
            cache.get(key);
    }
}

void runHotKeyWorkload(MultiLevelCache& cache, int N) {
    mt19937 rng(42);
    uniform_int_distribution<int> dist(1, 1000);

    for (int i = 0; i < N; i++) {
        int key;

        // 80% access to hot key
        if (i % 5 != 0)
            key = 1;
        else
            key = dist(rng);

        if (i % 2 == 0)
            cache.put(key, key * 10);
        else
            cache.get(key);
    }
}

void runSequentialWorkload(MultiLevelCache& cache, int N) {
    for (int i = 0; i < N; i++) {
        int key = i % 1000;

        if (i % 2 == 0)
            cache.put(key, key * 10);
        else
            cache.get(key);
    }
}

int main() {
    const int N = 100000;

    vector<int> caps = {50, 200, 500};

    vector<EvictionPolicy*> policies = {
        new LRUPolicy(),  // L1
        new LFUPolicy(),  // L2
        new LRUPolicy()   // L3
    };

    MultiLevelCache cache(caps, policies);

    // ===============================
    cout << "=== RANDOM WORKLOAD ===" << endl;
    auto start = high_resolution_clock::now();

    runRandomWorkload(cache, N);

    auto end = high_resolution_clock::now();
    cout << "Time: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms" << endl;

    cache.printMetrics();


    // ===============================
    cout << "\n=== HOT KEY WORKLOAD ===" << endl;

    MultiLevelCache cache2(caps, policies); // fresh cache

    start = high_resolution_clock::now();

    runHotKeyWorkload(cache2, N);

    end = high_resolution_clock::now();
    cout << "Time: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms" << endl;

    cache2.printMetrics();


    // ===============================
    cout << "\n=== SEQUENTIAL WORKLOAD ===" << endl;

    MultiLevelCache cache3(caps, policies); // fresh cache

    start = high_resolution_clock::now();

    runSequentialWorkload(cache3, N);

    end = high_resolution_clock::now();
    cout << "Time: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms" << endl;

    cache3.printMetrics();

    return 0;
}