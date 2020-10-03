#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);

    std::cout << "Arg count is: " << argc << "\n";
    for(int i = 0; i < argc; ++i) {
        std::cout << argv[i] << "\n";
    }

    int n;
    std::cout << "Enter a number:\n";
    std::cin >> n;

    std::vector<int> v;
    for(int i = 0 ; i < n; ++i) {
        std::cout << "Enter a vector member: " ;
        int x;
        std::cin >> x;
        v.emplace_back(x);
    }

    std::cout << "Hello, C++!" << std::endl;

    std::cout << "Here is the vector I created for you:\n";

    for(int x: v) std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}