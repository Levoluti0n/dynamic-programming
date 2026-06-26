#include <vector>
#include <algorithm>
using namespace std;

// Memoization

int solve(int day, int last, vector<vector<int>>& points, vector<vector<int>>& dp) {
    if(day == 0) {
        int res{};
        for(int i{}; i < 3; ++i) {
            if(i != last)
                res = max(res, points[day][i]);
        }
        return res;
    }
    if(dp[day][last] != -1) return dp[day][last];
    int res{};
    for(int i{}; i < 3; ++i) {
        if(i != last) 
            res = max(res, points[day][i] + solve(day-1, i, points, dp));
    }
    return dp[day][last] = res;
}

int ninjaTraining(int n, vector<vector<int>>& points) {
    vector<vector<int>> dp(n, vector<int>(4, -1));
    return solve(n-1, 3, points, dp);
}

// Tabulation 2D

int ninjaTraining(int n, vector<vector<int>>& points) {
    vector<vector<int>> dp(n, vector<int>(4, -1));

    dp[0][0] = max(points[0][1], points[0][2]);
    dp[0][1] = max(points[0][0], points[0][2]);
    dp[0][2] = max(points[0][0], points[0][1]);
    dp[0][3] = max({points[0][0], points[0][1], points[0][2]});

    for(int day{1}; day < n; ++day) {
        for(int last{}; last < 4; ++last) {
            for(int task{}; task < 3; ++task) {
                if(task != last) {
                    dp[day][last] = max(dp[day][last], points[day][task] + dp[day-1][task]);
                }
            }
        }
    }
    return dp[n - 1][3];
}

// Tabulation Space Optimized

int ninjaTraining(int n, vector<vector<int>>& points) {
    vector<int> prev(4, 0); 
    prev[0] = max(points[0][1], points[0][2]);
    prev[1] = max(points[0][0], points[0][2]);
    prev[2] = max(points[0][0], points[0][1]);
    prev[3] = max({points[0][0], points[0][1], points[0][2]});

    for(int day{1}; day < n; ++day) {
        vector<int> curr(4, 0);
        for(int last{}; last < 4; ++last) {
            for(int task{}; task < 3; ++task) {
                if(task != last)
                    curr[last] = max(curr[last], prev[task] + points[day][task]);
            }
        }
        prev = curr;
    }
    return prev[3];
}

// test 1
int ninjaTraining(int n, vector<vector<int>>& points) {
    vector<vector<int>> dp(n, vector<int>(3, 0));

    // base case
    for (int task = 0; task < 3; task++) {
        dp[0][task] = points[0][task];
    }

    for (int day = 1; day < n; day++) {
        for (int task = 0; task < 3; task++) {

            int bestPrev = 0;
            for (int prev = 0; prev < 3; prev++) {
                if (prev != task) {
                    bestPrev = max(bestPrev, dp[day - 1][prev]);
                }
            }

            dp[day][task] = points[day][task] + bestPrev;
        }
    }

    return max({dp[n-1][0], dp[n-1][1], dp[n-1][2]});
}

// test 2

int ninjaTraining(int n, vector<vector<int>>& points) {
    vector<int> prev(3, 0);

    // base case (day 0)
    for (int task = 0; task < 3; task++) {
        prev[task] = points[0][task];
    }

    for (int day = 1; day < n; day++) {
        vector<int> curr(3, 0);

        for (int task = 0; task < 3; task++) {

            int bestPrev = 0;

            for (int prevTask = 0; prevTask < 3; prevTask++) {
                if (prevTask != task) {
                    bestPrev = max(bestPrev, prev[prevTask]);
                }
            }

            curr[task] = points[day][task] + bestPrev;
        }

        prev = curr;
    }

    return max({prev[0], prev[1], prev[2]});
}