struct TwoSat {
    int n;
    vector<vector<int>> adj;
    vector<bool> ans;

    TwoSat(int n_) : n(n_), adj(2 * n_), ans(n_) {}

    void add_clause(int u, bool f, int v, bool g) {
        adj[2 * u + !f].push_back(2 * v + g);
        adj[2 * v + !g].push_back(2 * u + f);
    }

    bool satisfiable() {
        vector<int> id(2 * n, -1), dfn(2 * n, -1), low(2 * n, -1);
        vector<int> stk;

        int time = 0, cnt = 0;
        auto tarjan = [&](this auto tarjan, int u) -> void {
            stk.push_back(u);
            dfn[u] = low[u] = time++;

            for (auto v : adj[u]) {
                if (dfn[v] == -1) {
                    tarjan(v);
                    low[u] = min(low[u], low[v]);
                } else if (id[v] == -1) {
                    low[u] = min(low[u], dfn[v]);
                }
            }

            if (dfn[u] == low[u]) {
                int v;
                do {
                    v = stk.back();
                    stk.pop_back();
                    id[v] = cnt;
                } while (v != u);
                ++cnt;
            }
        };

        for (int i = 0; i < 2 * n; i++) {
            if (dfn[i] == -1) tarjan(i);
        }

        for (int i = 0; i < n; i++) {
            if (id[2 * i] == id[2 * i + 1]) return false;
            ans[i] = id[2 * i] > id[2 * i + 1];
        }
        return true;
    }

    vector<bool> answer() { return ans; }
};
