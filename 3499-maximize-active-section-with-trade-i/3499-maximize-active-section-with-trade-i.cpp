class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.size();

        int ones = 0;
        for (char c : s)
            if (c == '1') ones++;

        string t = "1" + s + "1";

        vector<pair<char, int>> runs;

        for (char c : t) {
            if (runs.empty() || runs.back().first != c)
                runs.push_back({c, 1});
            else
                runs.back().second++;
        }

        int ans = ones;

        // Look for pattern: 0-run, 1-run, 0-run
        for (int i = 1; i + 1 < runs.size(); i++) {
            if (runs[i].first == '1' &&
                runs[i - 1].first == '0' &&
                runs[i + 1].first == '0') {

                int leftZero = runs[i - 1].second;
                int rightZero = runs[i + 1].second;

                // Remove this 1-block, then convert merged 0-block
                ans = max(ans, ones + leftZero + rightZero);
            }
        }

        return ans;
    }
};