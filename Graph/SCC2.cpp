struct SCC {
    int n, cnt, time;
    vector<int> stk, dfn, low, id;
    vector<vector<int>> adj, dag, scc;

    SCC() {}
    SCC(int n_) { init(n_); }

    void init(int n_) {
        n = n_;
        cnt = time = 0;
        adj.assign(n, {});
        dfn.assign(n, -1);
        id.assign(n, -1);
        low.resize(n);
        stk.clear();
        scc.clear();
        dag.clear();
    }

    void add(int u, int v) {
        adj[u].push_back(v);
    }

    void dfs(int u) {
        stk.push_back(u);
        dfn[u] = low[u] = time++;
        for (int v : adj[u]) {
            if (dfn[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (id[v] == -1) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            scc.push_back({});
            while (true) {
                int v = stk.back();
                stk.pop_back();
                id[v] = cnt;
                scc.back().push_back(v);
                if (v == u) break;
            }
            cnt++;
        }
    }

    vector<int> solve() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                dfs(i);
            }
        }
        // ~ topological order (default ~ reverse topological)
        reverse(scc.begin(), scc.end());
        for (int i = 0; i < cnt; i++) {
            for (int u : scc[i]) {
                id[u] = i;
            }
        }
        return id;
    }

    vector<vector<int>> condensation() {
        dag.assign(cnt, {});
        vector<int> mark(cnt, -1);
        for (int i = 0; i < cnt; i++) {
            for (int u : scc[i]) {
                for (int v : adj[u]) {
                    int j = id[v];
                    if (i != j && mark[j] != i) {
                        dag[i].push_back(j);
                        mark[j] = i;
                    }
                }
            }
        }
        return dag;
    }
};

