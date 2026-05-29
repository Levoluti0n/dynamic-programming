#include <vector>
using namespace std;

class Solution {
public:
    int optimized(vector<int>& nums) {

        int prev2 = 0;
        int prev1 = nums[0];

        for (int i = 1; i < nums.size(); i++) {

            int take = nums[i] + prev2;
            int skip = prev1;

            int curr = max(take, skip);

            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};