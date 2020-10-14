#include<iostream>
#include<vector>

class BSearch {
    public:
        static int search(std::vector<int>&nums, int target) {
            int left = 0;
            int right = nums.size() - 1;

            while (right >= left) {
                int middle = (left + right)/2;
                if (nums[middle] == target)
                    return middle;
                else if (nums[middle] > target)
                    right = middle - 1;
                else // nums[middle] < target
                    left = middle + 1;
            }
            return -1; // target not found
        }
};

int main (int argc, char *argv[]) {
    int target;
    int num;

    std::cout << "Enter target:\n";
    std::cin >> target;
    std::cout << "Enter array size:\n";
    std::cin >> num;
    std::vector<int> nums(num);
    for (int i = 0; i < num; ++i) {
        std::cout << "Enter a number:\n";
        std::cin >> nums[i];
    }
    int pos = BSearch::search(nums, target);
    if (pos == -1) {
        std::cout << "Target not found.\n";
    } else {
        std::cout << "Target found at " << pos << std::endl;
    }
    return 0;
}