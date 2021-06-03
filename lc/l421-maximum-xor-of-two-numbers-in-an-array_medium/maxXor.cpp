#include<unordered_set>
#include<iostream>
#include<vector>

using namespace std;

class Solution {
    struct BitTrieNode {
        bool eow; // may not be needed
        BitTrieNode *left; // for 0
        BitTrieNode *right;// for 1
        BitTrieNode() : eow(false), left(0), right(0) { }
    };
    BitTrieNode * root;
    int L; //  = sizeof(int) * 8 - 1; // max number is a 31 bit number (2^31-1 max val)
public:
    int findMaximumXOR(vector<int>& nums) {
        int maxXor = 0;

        root = new BitTrieNode(); // fake root
        
        int max = 0;
        for (int i = 0 ; i < nums.size(); ++i) {
            if (nums[i] > max) max = nums[i];
        }
        L = findL(max);
        
        for(int i = 0 ; i < nums.size(); ++i) {
            addNumber(nums[i]);
            int curXorMax = findMaxXorForANumber(nums[i]);
            if (curXorMax > maxXor) { maxXor = curXorMax; }
        }
        return maxXor;
    }
    
    int findL(int n) {
        for (int i = sizeof(int) * 8 - 1; i >= 0; --i) {
            if (bitPos(n, i)) return i;
        }
        return 1;
    }
    
    void addNumber(int num) {
        BitTrieNode * cur = root;
        
        for(int i = L; i >= 0; --i) {
            if (bitPos(num, i)) { // it is 1
                if (cur->right) {
                    cur = cur->right;
                } else {
                    cur->right = new BitTrieNode();
                    cur = cur->right;
                }
            } else {
                if (cur->left) {
                    cur = cur->left;
                } else {
                    cur->left = new BitTrieNode();
                    cur = cur->left;
                }
            }
        }
    }
    
    // is bit pos of num set?
    bool bitPos(int num, int pos) {
        // 0 <= pos <= sizeof(int) * 8 - 1
        int mask = 0x1 << pos;
        return num & mask;
    }
    
    void bitSet(int *num, int pos) {
        (*num) |= (0x1 << pos);
    }
    
    int findMaxXorForANumber(int num) {
        BitTrieNode * cur = root;
        
        int curXor = 0;
        for (int i = L; i >= 0; --i) {
            if (bitPos(num, i)) {
                if (cur->left) {
                    cur = cur->left;
                    bitSet(&curXor, i);
                } else {
                    cur = cur->right;
                }
            } else {
                if (cur->right) {
                    cur = cur->right;
                    bitSet(&curXor, i);
                } else {
                    cur = cur->left;
                }
            }
        }
        return curXor;
    }
};

class Solution2 {
public:
    int findMaximumXOR(vector<int>& nums) {
        
        int maxXor = 0;
        for (int i = sizeof(int) * 8 - 1; i >=0; --i) {
            maxXor <<= 1;
            int curXor = maxXor | 1;

            unordered_set<int> hashMap;
            for (int j = 0; j < nums.size(); ++j) {
                hashMap.insert(nums[j] >> i);
            }
            bool found = false;
            for (int j = 0; j < nums.size(); ++j) {
                if (hashMap.find((nums[j] >> i) ^ curXor) != hashMap.end()) {
                    found = true;
                }
            }
            if (found) {
                maxXor = curXor;
            }
        }
        return maxXor;
    }
};

int main (void) {
  vector<int> nums = { 3, 10, 5, 25, 2, 8 };

  Solution * obj = new Solution;
  cout << "Max XOR = " << obj->findMaximumXOR(nums) << endl;

  return 0;
}