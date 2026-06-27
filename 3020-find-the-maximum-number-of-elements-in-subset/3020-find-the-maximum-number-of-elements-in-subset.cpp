class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> cnt;

        for (int x : nums) {
            cnt[x]++;
        }

        int ans = 1;

        // Special case for 1
        if (cnt.count(1)) {
            int c = cnt[1];
            if (c % 2 == 0) c--;
            ans = max(ans, c);
        }

        for (auto &p : cnt) {
            long long x = p.first;

            if (x == 1) continue;

            int len = 0;
            long long cur = x;

            while (true) {
                if (!cnt.count(cur)) {
                    break;
                }

                // If only one copy, it can only be the middle
                if (cnt[cur] == 1) {
                    len += 1;
                    break;
                }

                // cnt[cur] >= 2 now
                // To use 2 copies of cur, we need cur^2 to exist after it
                if (cur > 1000000000LL / cur) {
                    len += 1;
                    break;
                }

                long long nxt = cur * cur;

                if (!cnt.count(nxt)) {
                    len += 1;
                    break;
                }

                len += 2;
                cur = nxt;
            }

            ans = max(ans, len);
        }

        return ans;
    }
};