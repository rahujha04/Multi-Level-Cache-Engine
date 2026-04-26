#pragma once
#include <unordered_map>

struct Node {
    int key, value;
    Node* prev;
    Node* next;

    Node(int key, int value) : key(key), value(value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
    private:
        int capacity;
        Node* head;
        Node* tail;
        std::unordered_map<int, Node*> mp;

        void addToFront(Node* node);
        void removeNode(Node* node);

    public:
        LRUCache(int cap);

        int get(int key);
        std::pair<int,int> put(int key, int value); // it returns the evicted {key, value} pair
        void remove(int key);
        bool exists(int key); 

};