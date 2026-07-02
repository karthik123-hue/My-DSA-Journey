class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();

        health -= grid[0][0];

        if (health <= 0) {
            return false;
        }

        vector<vector<int>> best(m, vector<int>(n, -1));
        queue<pair<int, int>> q;

        best[0][0] = health;
        q.push({0, 0});

        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            if (r == m - 1 && c == n - 1) {
                return true;
            }

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr < 0 || nc < 0 || nr >= m || nc >= n) {
                    continue;
                }

                int nh = best[r][c] - grid[nr][nc];

                if (nh <= 0) {
                    continue;
                }

                if (nh > best[nr][nc]) {
                    best[nr][nc] = nh;
                    q.push({nr, nc});
                }
            }
        }

        return false;
    }
};