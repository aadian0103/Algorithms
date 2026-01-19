// gives SCC ids in topological order, i.e if u -> v then id[u] <= id[v]
struct SCC {
    int n, cnt;
    vector<bool> vis;
    vector<int> topo, id;
    vector<vector<int>> adj, rev, dag, scc;

    SCC() {}
    SCC(int n_) { init(n_); }

    void init(int n_) {
        n = n_;
        cnt = 0;
        adj.assign(n, {});
        rev.assign(n, {});
        id.assign(n, -1);
        vis.assign(n, false);
        topo.clear();
        dag.clear();
        scc.clear();
    }

    void add(int u, int v) {
        adj[u].push_back(v);
        rev[v].push_back(u);
    }

    void dfs1(int u) {
        vis[u] = 1;
        for (auto v : adj[u]) {
            if (!vis[v]) {
                dfs1(v);
            }
        }
        topo.push_back(u);
    }

    void dfs2(int u) {
        scc.back().push_back(u);
        for (auto v : rev[u]) {
            if (id[v] == -1) {
                id[v] = id[u];
                dfs2(v);
            }
        }
    }

    vector<int> solve() {
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs1(i);
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            int j = topo[i];
            if (id[j] == -1) {
                scc.push_back({});
                id[j] = cnt++;
                dfs2(j);
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
