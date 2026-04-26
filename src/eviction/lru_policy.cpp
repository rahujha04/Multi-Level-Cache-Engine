#include "lru_policy.h"

LRUCache::LRUCache(int cap) : capacity(cap) {
    head = new Node(-1, -1);
    tail = new Node(-1, -1);

    head->next = tail;
    tail->prev = head;
}

void LRUCache::addToFront(Node* node) {
    node->next = head->next;
    node->prev = head;

    head->next->prev = node;
    head->next = node;
}

void LRUCache::removeNode(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

int LRUCache::get(int key) {
    if (mp.find(key) == mp.end()) // key not found
        return -1;
    
    // key exits in the cache
    Node* node = mp[key];
    removeNode(node);
    addToFront(node);
    return node->value;
}

std::pair<int,int> LRUCache::put(int key, int value) {
    if (mp.find(key) != mp.end()) { // key already present, just need to bring it in front
        Node* node = mp[key];
        node->value = value;

        removeNode(node);
        addToFront(node);
        return {-1, -1}; // no node is evicted
    }
    if (mp.size() == capacity) { // cache is full, need to evict the least recently used node
        Node* lru = tail->prev;
        removeNode(lru);
        mp.erase(lru->key);

        std::pair<int,int> evicted = {lru->key, lru->value};
        delete lru;

        Node* newNode = new Node(key, value);
        mp[key] = newNode;
        addToFront(newNode);

        return evicted;
    }
    Node* newNode = new Node(key, value);
    addToFront(newNode);
    mp[key] = newNode;

    return {-1, -1};
}

void LRUCache::remove(int key) {
    if (mp.find(key) == mp.end()) // key not found in the cache
        return;
    Node* node = mp[key];
    removeNode(node);
    mp.erase(key);
    delete node;
}

bool LRUCache::exists(int key) {
    return mp.find(key) != mp.end();
}