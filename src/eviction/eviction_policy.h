#pragma once
#include <unordered_map>

class EvictionPolicy {
public:
    virtual void touch(int key) = 0;   // when accessed
    virtual void insert(int key) = 0;  // new key
    virtual int evict() = 0;           // returns key to evict
    virtual void remove(int key) = 0;
    virtual ~EvictionPolicy() {}
};