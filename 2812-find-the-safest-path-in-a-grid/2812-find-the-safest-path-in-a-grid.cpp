class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();

        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        queue<pair<int, int>> q;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr < 0 || nc < 0 || nr >= n || nc >= n) {
                    continue;
                }

                if (dist[nr][nc] > dist[r][c] + 1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        priority_queue<pair<int, pair<int, int>>> pq;
        vector<vector<int>> best(n, vector<int>(n, -1));

        best[0][0] = dist[0][0];
        pq.push({dist[0][0], {0, 0}});

        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();

            int safe = top.first;
            int r = top.second.first;
            int c = top.second.second;

            if (r == n - 1 && c == n - 1) {
                return safe;
            }

            if (safe < best[r][c]) {
                continue;
            }

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr < 0 || nc < 0 || nr >= n || nc >= n) {
                    continue;
                }

                int nsafe = min(safe, dist[nr][nc]);

                if (nsafe > best[nr][nc]) {
                    best[nr][nc] = nsafe;
                    pq.push({nsafe, {nr, nc}});
                }
            }
        }

        return 0;
    }
};