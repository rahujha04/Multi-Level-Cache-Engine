#pragma once
#include "eviction_policy.h"
#include <unordered_map>
#include <list>

class LFUPolicy : public EvictionPolicy {
private:
    std::unordered_map<int, int> freq;
    std::unordered_map<int, std::list<int>> freqList;
    std::unordered_map<int, std::list<int>::iterator> pos;

    int minFreq = 0;

public:
    void touch(int key) override;
    void insert(int key) override;
    int evict() override;
    void remove(int key) override;
};