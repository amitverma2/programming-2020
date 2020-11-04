#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class LFUCache {
    struct KeyRecord {
        int key;
        int value;
        int frequency;
        int timestamp;
        KeyRecord() : key(-1), value(-1), frequency(-1), timestamp(-1) { }
        KeyRecord(int _key, int _value, int _frequency, int _timestamp) : key(_key), value(_value), frequency(_frequency), timestamp(_timestamp) { }
        bool operator()(KeyRecord const& r1, KeyRecord const& r2) {
            if (r1.frequency > r2.frequency) return true;
            if (r1.frequency < r2.frequency) return false;
            if (r1.timestamp > r2.timestamp) return true;
            return false;
        }
    };
public:
    vector<int> kvpair;
    vector<int> frequency;
    int timestamp;
    vector<int> lastaccess;
    int capacity;
    int current;
    priority_queue<KeyRecord, vector<KeyRecord>, KeyRecord> lfuHeap;
    LFUCache(int capacity) : capacity(capacity), current(0), kvpair(10000, -1), frequency(10000, -1), lastaccess(10000, -1), timestamp(0) { }
    
    int get(int key) {
        if (capacity == 0) return -1;
        
        if (kvpair[key] == -1) {
            return -1; // key not found
        }
        frequency[key]++;
        timestamp++;
        lastaccess[key] = timestamp;
        KeyRecord rec = lfuHeap.top();
        if (rec.key == key) {
            rec.value = kvpair[key];
            rec.frequency = frequency[key];
            rec.timestamp = lastaccess[key];
            lfuHeap.pop();
            lfuHeap.push(rec);
        }
        return kvpair[key];
    }
    
    void put(int key, int value) {
        if (capacity == 0) return;
        
        if (kvpair[key] != -1) {
            // not a new addition, update values, frequency and timestamp
            kvpair[key] = value;
            frequency[key]++;
            timestamp++;
            lastaccess[key] = timestamp;
            // heap will be updated later during eviction
            return;
        }
        if (current < capacity) { // still have capacity and new addition
            current++;
            kvpair[key] = value;
            frequency[key] = 1;
            timestamp++;
            lastaccess[key] = timestamp;
            KeyRecord rec(key, value, frequency[key], lastaccess[key]);
            lfuHeap.push(rec);
            return;
        }
        // capacity full, need to discard lfu key
        bool cleared = false;
        while(!cleared) {
            KeyRecord rec = lfuHeap.top();
            lfuHeap.pop();
            if (frequency[rec.key] == rec.frequency ||
                lastaccess[rec.key] == rec.timestamp) {
                // actually the lfu
                cleared = true;
                kvpair[rec.key] = frequency[rec.key] = lastaccess[rec.key] = -1;
                current--;
            } else {
                // update and add back
                rec.frequency = frequency[rec.key];
                rec.timestamp = lastaccess[rec.key];
                lfuHeap.push(rec);
            }
        }
        // now add new key
        current++;
        kvpair[key] = value;
        frequency[key] = 1;
        timestamp++;
        lastaccess[key] = timestamp;
        KeyRecord newRec(key, value, frequency[key], lastaccess[key]);
        lfuHeap.push(newRec);
        return;
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
  LFUCache* obj = new LFUCache(2);
  obj->put(1,1);
  obj->put(2,2);
  std::cout << "get 1 = " << obj->get(1) << std::endl;
  obj->put(3,3);
  std::cout << "get 2 = " << obj->get(2) << std::endl;
  std::cout << "get 3 = " << obj->get(3) << std::endl;
  obj->put(4,4);
  std::cout << "get 1 = " << obj->get(1) << std::endl;
  std::cout << "get 3 = " << obj->get(3) << std::endl;
  std::cout << "get 4 = " << obj->get(4) << std::endl;
  
  return 0;
}