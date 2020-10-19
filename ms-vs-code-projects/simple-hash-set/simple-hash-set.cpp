#include<iostream>

// cheating: since the expected range of key is 0 to 10000000, i can use an 4 mb array.

class MyHashSet {
  const static int MAX_BUCKETS = 10000000;
  int bucket[MAX_BUCKETS];
public:
  MyHashSet() { for (int i = 0 ; i < MAX_BUCKETS; ++i) bucket[i] = 0; }
  void add(int key) { bucket[key] = 1; }
  void remove(int key) { bucket[key] = 0; }
  bool contains(int key) { return bucket[key] != 0; }
};

int main(int argc, char *argv[]) {
  MyHashSet * set = new MyHashSet;
  set->add(2);
  set->add(4);
    for(int i = 0; i < 10; ++i) {
    if (set->contains(i)) {
      std::cout << "Set contains " << i << "\n";
    } else {
      std::cout << "Set doesn't contain " << i << "\n";
    }
  }
  return 0;
}