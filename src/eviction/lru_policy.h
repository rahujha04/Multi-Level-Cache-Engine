#pragma once
#include "eviction_policy.h"
#include <list>
#include <unordered_map>

class LRUPolicy : public EvictionPolicy {
private:
    std::list<int> dll;
    std::unordered_map<int, std::list<int>::iterator> mp;

public:
    void touch(int key) override;
    void insert(int key) override;
    int evict() override;
    void remove(int key) override;
};