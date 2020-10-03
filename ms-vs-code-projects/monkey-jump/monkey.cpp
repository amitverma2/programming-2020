#include<iostream>

// how many paths a monkey can take to reach from tile 1 to tile n
// if the money at tile (i) can go to either (i+1) tile or (i+2)
// tile

#define MAXN (50)
long long int memo[MAXN+1];
long long int findPath(int n)
{
    for(int i = 1; i <= MAXN; i++) memo[i] = -1; // initialize memo array

    memo[1] = 1;
    memo[2] = 1;
    memo[3] = 2;

    for(int i = 4; i <= n; i++) memo[i] = memo[i-1] + memo[i-2];

    return memo[n];
}

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false); // speed things up

    // input file format is
    // N => number of test cases
    // n1 => number of tiles for test case 1
    // n2
    // ...
    // nN

    // output file
    // p1
    // p2
    // ...
    // pN

    int N;
    std::cin >> N;

    while(N-- > 0) {
        int n;
        std::cin >> n;

        if (n > MAXN) {
            std::cerr << n << " exceeded MAXN(" << MAXN << ")" << std::endl;
            continue;
        }
        std::cout << findPath(n) << std::endl;
    }
    return 0;
}