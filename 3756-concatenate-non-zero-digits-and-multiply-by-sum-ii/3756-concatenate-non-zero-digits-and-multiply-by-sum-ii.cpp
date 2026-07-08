class Solution {
public:
    static constexpr int MOD = 1000000007;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();

        vector<int> digit;
        vector<int> pos;

        vector<int> first(n + 1, -1);
        vector<int> last(n + 1, -1);

        for (int i = 0; i < n; i++) {
            if (s[i] != '0') {
                pos.push_back(i);
                digit.push_back(s[i] - '0');
            }
        }

        int m = digit.size();

        vector<int> idx(n, -1);
        for (int i = 0; i < m; i++) idx[pos[i]] = i;

        int cur = -1;
        for (int i = n - 1; i >= 0; i--) {
            if (idx[i] != -1) cur = idx[i];
            first[i] = cur;
        }

        cur = -1;
        for (int i = 0; i < n; i++) {
            if (idx[i] != -1) cur = idx[i];
            last[i] = cur;
        }

        vector<long long> pow10(m + 1), invPow10(m + 1);
        pow10[0] = 1;
        for (int i = 1; i <= m; i++)
            pow10[i] = pow10[i - 1] * 10 % MOD;

        auto modpow = [&](long long a, long long e) {
            long long r = 1;
            while (e) {
                if (e & 1) r = r * a % MOD;
                a = a * a % MOD;
                e >>= 1;
            }
            return r;
        };

        invPow10[m] = modpow(pow10[m], MOD - 2);
        for (int i = m - 1; i >= 0; i--)
            invPow10[i] = invPow10[i + 1] * 10 % MOD;

        vector<long long> prefNum(m + 1, 0);
        vector<long long> prefSum(m + 1, 0);

        for (int i = 0; i < m; i++) {
            prefNum[i + 1] = (prefNum[i] * 10 + digit[i]) % MOD;
            prefSum[i + 1] = prefSum[i] + digit[i];
        }

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0], r = q[1];

            int L = first[l];
            int R = last[r];

            if (L == -1 || R == -1 || L > R) {
                ans.push_back(0);
                continue;
            }

            int len = R - L + 1;

            long long x =
                (prefNum[R + 1] -
                 prefNum[L] * pow10[len] % MOD +
                 MOD) % MOD;

            long long sum = prefSum[R + 1] - prefSum[L];

            ans.push_back((x * sum) % MOD);
        }

        return ans;
    }
};