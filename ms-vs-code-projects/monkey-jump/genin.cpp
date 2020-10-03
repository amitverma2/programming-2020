#include<iostream>

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);

    int n = 100;
    std::cout << n << std::endl;
    for(int i = 1; i <= n; ++i)
        std::cout << i << std::endl;
    return 0;
}
