class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<vector<bool>> dp(4, vector<bool>(MAXX, false));
        dp[0][0] = true;

        for (int x : nums) {
            for (int cnt = 2; cnt >= 0; cnt--) {
                for (int val = 0; val < MAXX; val++) {
                    if (dp[cnt][val]) {
                        dp[cnt + 1][val ^ x] = true;
                    }
                }
            }
        }

        unordered_set<int> ans;

        // Triplets with three distinct indices
        for (int x = 0; x < MAXX; x++)
            if (dp[3][x])
                ans.insert(x);

        // Cases where indices are equal (i <= j <= k)
        for (int x : nums) {
            ans.insert(x); // x ^ x ^ x = x

            for (int y : nums) {
                ans.insert(x ^ y ^ y); // = x
                ans.insert(x ^ x ^ y); // = y
            }
        }

        return ans.size();
    }
};