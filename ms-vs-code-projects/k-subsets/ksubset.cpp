#include<iostream>

// k-subsets
// Given a set S of N elements, how many subsets of k elements
// does it have?
// Example S = {a, b, c,d }, has four 3 subsets
// {a, b, c}, {a, b, d}, {a, c, d} and, {b, c, d}

#define MAXN (100)

long long unsigned int memo[MAXN+1][MAXN+1] = { -1 };

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N; // set size
    int K; // subset size

    // Input
    std::cin >> N;
    std::cin >> K;

    if (N > MAXN) {
        std::cerr << "Size of set is more than permitted " << N << " > " << MAXN << std::endl;
        return -1;
    }
    if (K == 0) {
        if (N == 0) {
            std::cout << 0 << std::endl; // NULL set has 0 subsets of 0 elements
        }
        std::cout << 1 << std::endl; // a non NULL set has 1 subset of 0 elements
        return 0;
    }
    if (K > N) {
        std::cout << 0 << std::endl; // a non NULL set has zero subsets that have more elements than the set itself
        return 0;
    }
    if (K == N) {
        std::cout << 1 << std::endl; // a non NULL set has one subset that has same number of elements as the set itself
        return 0;
    }

    // if we are here N <= MAXN, N > 0, k > 0 and k < N
    // logic
    // if c(n, k) is the number of k-subsets for a set of n element
    // then it should be 
    // c(n, k) = c(n-1, k) + c(n-1, k-1)

    // set initial values
    // 1. all 1-subset of any set is = set size
    for (int n = 1; n <= MAXN; n++)
        memo[n][1] = n;
    // 2. all k-subset of set size k is 1
    for (int k = 1; k <= MAXN; k++)
        memo[k][k] = 1;
    // 3. all k-subset of set size < k is 0
    for (int n = 1; n <= MAXN; ++n)
        for (int k = n+1; k <= MAXN; ++k)
            memo[n][k] = 0;
    
    for (int n = 2; n <= N; ++n) {
        for (int k = 2 ; k <= K; ++k) {
            memo[n][k] = memo[n-1][k] + memo[n-1][k-1];
        }
    }
    std::cout << memo[N][K] << std::endl;
    return 0;
}