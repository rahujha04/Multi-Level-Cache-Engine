#include "lru_policy.h"

void LRUPolicy::touch(int key) {
    dll.erase(mp[key]);
    dll.push_front(key);
    mp[key] = dll.begin();
}

void LRUPolicy::insert(int key) {
    dll.push_front(key);
    mp[key] = dll.begin();
}

int LRUPolicy::evict() {
    int key = dll.back();
    dll.pop_back();
    mp.erase(key);
    return key;
}

void LRUPolicy::remove(int key) {
    if (mp.find(key) == mp.end()) return;
    dll.erase(mp[key]);
    mp.erase(key);
}