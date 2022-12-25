#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// Structure for an item which stores weight and corresponding
// value of Item
struct Item
{
    unsigned long value, weight;
};

// function to get maximum value
unsigned long knapSack(int W, std::vector<Item>& arr, int n)
{
    std::vector<unsigned long> dp(W + 1, 0);

    for (int i = 0; i < n; i++)
    {
        for (int w = W; w >= arr[i].weight; w--)
        {
            dp[w] = std::max(dp[w], arr[i].value + dp[w - arr[i].weight]);
        }
    }

    return (unsigned long) dp[W];
}

// driver code
int main()
{
    // std::vector<Item> arr = {{60, 10}, {100, 20}, {120, 30}};
    // unsigned long n = arr.size();
    std::vector<Item> arr = std::vector<Item>();

    std::ifstream file = std::ifstream("inputs/course3/week4/knapsack_big.txt");
    unsigned long W,n;
    file >> W >> n;

    unsigned long v, w;
    while (file >> v >> w) {
        auto item = Item {v,w};
        arr.push_back({v,w});
    }

    std::cout << "Maximum value in knapsack is " << knapSack(W, arr, n) << std::endl;

    return 0;
}
