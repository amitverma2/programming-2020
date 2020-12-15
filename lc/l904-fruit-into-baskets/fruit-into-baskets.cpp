#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    class Bucket {
        int count;
        int curFruit;
        int prevFruit;
    public:
        Bucket(): count(0), curFruit(-1), prevFruit(-1) { }
        int getCount(void) { return count; }
        void discardPrevFruit(void) { prevFruit = -1; }
        bool canBePicked(int fruit) {
            if (curFruit == -1 || fruit == curFruit) {
                count++;
                curFruit = fruit;
                return true;
            }
            if (prevFruit == -1 || fruit == prevFruit) {
                count = 1;
                prevFruit = fruit;
                // swap
                int temp = prevFruit;
                prevFruit = curFruit;
                curFruit = temp;
                return true;
            }
            return false;
        }
        void addAfterPrevDiscard(int fruit) {
            canBePicked(fruit);
        }
    };
    int totalFruit(vector<int>& tree) {
        Bucket *bucket = new Bucket;
        
        int maxFruits = 0;
        int count = 0;
        for (int i = 0 ; i < tree.size(); ++i) {
            if (bucket->canBePicked(tree[i])) {
                count++;
            } else {
                if (count > maxFruits) {
                    maxFruits = count;
                }
                count = bucket->getCount();
                bucket->discardPrevFruit();
                bucket->addAfterPrevDiscard(tree[i]);
                count++;
            }
        }
        if (count > maxFruits) { maxFruits = count; }
        return maxFruits;
    }
};

int main() {
  vector<int> tree = { 0, 1, 2, 2 };
  Solution *obj = new Solution;

  std::cout << "Fruits in baskets: " << obj->totalFruit(tree) << std::endl;
  return 0;
}