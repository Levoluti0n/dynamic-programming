#include <vector>

int maxProfit(std::vector<int>& prices) {
    int profit = 0;
    int buy = prices[0];

    for(int num : prices) {
        if(num - buy > profit) profit = num - buy;
        else if(num < buy) buy = num;
    }
    
    return profit;
}