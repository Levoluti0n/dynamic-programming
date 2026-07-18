#include <vector>
#include <string>

int minInsertions(std::string& s1) {
    int n = s1.size();
    std::string s2(s1.rbegin(), s1.rend());
    std::vector<int> dp(n+1);

    for(int i{1}; i <= n; ++i) {
        int diag{};
        for(int j{1}; j <= n; ++j) {
            int tmp = dp[j];
            if(s1[i-1] == s2[j-1]) 
                dp[j] = diag + 1;
            else
                dp[j] = std::max(dp[j-1], dp[j]);
            diag = tmp;
        }
    }

    return n - dp[n];
}
