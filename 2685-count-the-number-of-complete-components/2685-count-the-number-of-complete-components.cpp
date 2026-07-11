class Solution {
public:
    void dfs(int u,
             vector<vector<int>>& g,
             vector<int>& vis,
             int &nodes,
             int &degreeSum) {

        vis[u] = 1;
        nodes++;

        degreeSum += g[u].size();

        for (int v : g[u]) {
            if (!vis[v]) {
                dfs(v, g, vis, nodes, degreeSum);
            }
        }
    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {

        vector<vector<int>> g(n);

        for (auto &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        vector<int> vis(n, 0);

        int ans = 0;

        for (int i = 0; i < n; i++) {

            if (vis[i]) continue;

            int nodes = 0;
            int degreeSum = 0;

            dfs(i, g, vis, nodes, degreeSum);

            int edgeCount = degreeSum / 2;
            int expected = nodes * (nodes - 1) / 2;

            if (edgeCount == expected)
                ans++;
        }

        return ans;
    }
};