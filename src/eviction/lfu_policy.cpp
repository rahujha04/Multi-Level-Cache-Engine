#include "lfu_policy.h"

void LFUPolicy::touch(int key) {
    int f = freq[key];

    // remove from current freq
    freqList[f].erase(pos[key]);

    // update minFreq
    if (freqList[f].empty() && f == minFreq) {
        minFreq++;
    }

    // move to next freq
    freq[key]++;
    freqList[f+1].push_front(key);
    pos[key] = freqList[f+1].begin();
}

void LFUPolicy::insert(int key) {
    freq[key] = 1;
    minFreq = 1;

    freqList[1].push_front(key);
    pos[key] = freqList[1].begin();
}

int LFUPolicy::evict() {
    int key = freqList[minFreq].back();

    freqList[minFreq].pop_back();

    freq.erase(key);
    pos.erase(key);

    return key;
}

void LFUPolicy::remove(int key) {
    if (freq.find(key) == freq.end()) return;

    int f = freq[key];

    freqList[f].erase(pos[key]);

    if (freqList[f].empty() && f == minFreq) {
        minFreq++;
    }

    freq.erase(key);
    pos.erase(key);
}