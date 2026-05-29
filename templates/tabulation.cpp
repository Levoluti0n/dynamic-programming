#include <vector>
using namespace std;

class Solution {
public:
    int tabulation(vector<int>& nums) {
        int n = nums.size();

        vector<int> dp(n, 0);

        dp[0] = nums[0];

        for (int i = 1; i < n; i++) {

            int take = nums[i];
            if (i > 1) take += dp[i - 2];

            int skip = dp[i - 1];

            dp[i] = max(take, skip);
        }

        return dp[n - 1];
    }
};