#include <iostream>
#include<list>
#include<utility>

// Simple implementation of a hash map using a list and with separate chaining

class MyHashMapBucket
{
  std::list<std::pair<int, int> > chain;

public:
  void put(int key, int value)
  {
    std::list<std::pair<int, int> >::iterator i = chain.begin();
    for (; i != chain.end(); ++i)
    {
      std::pair<int, int> &p = *i;
      if (p.first == key)
      {
        p.second = value;
        return;
      }
    }
    chain.push_front(std::make_pair(key, value));
  }
  void remove(int key)
  {
    std::list<std::pair<int, int> >::iterator i = chain.begin();
    for (; i != chain.end(); ++i)
    {
      std::pair<int, int> &p = *i;
      if (p.first == key)
      {
        //chain.remove(std::make_pair(key, p.second));
        chain.erase(i);
        // now iterator i is not to be used.
        return;
      }
    }
  }
  int get(int key)
  {
    std::list<std::pair<int, int> >::iterator i = chain.begin();
    for (; i != chain.end(); ++i)
    {
      std::pair<int, int> &p = *i;
      if (p.first == key)
      {
        return p.second;
      }
    }
    return -1;
  }
};

class MyHashMap
{
  static const int MAX_BUCKETS = 769;
  MyHashMapBucket buckets[MAX_BUCKETS];

public:
  /** Initialize your data structure here. */
  MyHashMap()
  {
    // no-op
  }

  /** value will always be non-negative. */
  void put(int key, int value)
  {
    int bucket = key % MAX_BUCKETS;
    buckets[bucket].put(key, value);
  }

  /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
  int get(int key)
  {
    int bucket = key % MAX_BUCKETS;
    return buckets[bucket].get(key);
  }

  /** Removes the mapping of the specified value key if this map contains a mapping for the key */
  void remove(int key)
  {
    int bucket = key % MAX_BUCKETS;
    buckets[bucket].remove(key);
  }
};

int main(int argc, char *argv[]) {
  MyHashMap* obj = new MyHashMap;
  obj->put(1, 2);
  int param_2 = obj->get(1);
  std::cout << "1 => " << param_2 << std::endl;
  obj->remove(1);
  param_2 = obj->get(1);
  std::cout << "1 => " << param_2 << std::endl;
  return 0;
}