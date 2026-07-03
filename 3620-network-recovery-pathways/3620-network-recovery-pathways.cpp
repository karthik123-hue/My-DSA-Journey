class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();

        vector<vector<pair<int,int>>> g(n);
        vector<int> indeg(n, 0);

        int high = 0;

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int c = e[2];

            g[u].push_back({v, c});
            indeg[v]++;
            high = max(high, c);
        }

        // topological sort
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }

        vector<int> topo;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            topo.push_back(u);

            for (auto &[v, c] : g[u]) {
                indeg[v]--;
                if (indeg[v] == 0) {
                    q.push(v);
                }
            }
        }

        auto can = [&](int x) {
            const long long INF = 4e18;

            vector<long long> dist(n, INF);
            dist[0] = 0;

            for (int u : topo) {
                if (dist[u] == INF) continue;

                if (!online[u]) continue;

                for (auto &[v, c] : g[u]) {
                    if (c < x) continue;

                    if (!online[v]) continue;

                    if (dist[u] + c < dist[v]) {
                        dist[v] = dist[u] + c;
                    }
                }
            }

            return dist[n - 1] <= k;
        };

        int low = 0;
        int ans = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (can(mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};