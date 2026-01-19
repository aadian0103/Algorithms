struct TwoSat {
    int n;
    vector<bool> ans;
    vector<vector<int>> adj;
    vector<int> stk, dfn, low, id;

    TwoSat(int n_) : n(n_), adj(2 * n_), ans(n_) {}

    void add_clause(int u, bool f, int v, bool g) {
        adj[2 * u + !f].push_back(2 * v + g);
        adj[2 * v + !g].push_back(2 * u + f);
    }

    bool satisfiable() {
        id.assign(2 * n, -1);
        dfn.assign(2 * n, -1);
        low.assign(2 * n, -1);
        stk.clear();

        int time = 0, cnt = 0;
        auto dfs = [&](this auto dfs, int u) -> void {
            stk.push_back(u);
            dfn[u] = low[u] = time++;
            for (auto v : adj[u]) {
                if (dfn[v] == -1) {
                    dfs(v);
                    low[u] = min(low[u], low[v]);
                } else if (id[v] == -1) {
                    low[u] = min(low[u], dfn[v]);
                }
            }
            if (dfn[u] == low[u]) {
                while (true) {
                    int v = stk.back();
                    stk.pop_back();
                    id[v] = cnt;
                    if (v == u) break;
                }
                cnt++;
            }
        };

        for (int i = 0; i < 2 * n; i++) {
            if (dfn[i] == -1) {
                dfs(i);
            }
        }

        for (int i = 0; i < n; i++) {
            if (id[2 * i] == id[2 * i + 1]) return false;
            ans[i] = id[2 * i] > id[2 * i + 1];
        }
        return true;
    }

    vector<bool> answer() { return ans; }
};
