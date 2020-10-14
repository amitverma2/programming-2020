#include<iostream>

class Sqrt {
    public:
        static int mySqrt(int x) {
            if (x < 2) return x;

            int low = 2;
            int high = x/2;

            while (low <= high) {
                int mid = low + (high - low)/2;
                long mid2 = (long)mid * (long)mid;
                if (mid2 == x)
                    return mid;
                else if (mid2 > x)
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            return high;
        }
};

int main (int argc, char *argv[])
{
    int x;
    std::cout << "Enter x:\n";
    std::cin >> x;

    std::cout << "Integer square root is : " << Sqrt::mySqrt(x) << std::endl;

    return 0;
}