struct tree {
    int n, l;
    vector<int> depth;
    vector<vector<int>> up, adj;

    tree(const vector<vector<int>>& g) {
        n = int(g.size());
        l = bit_width(unsigned(n)) - 1;
        depth.assign(n, 0);
        up.assign(n, vector<int>(l + 1));
        adj = g;
    }

    // remember to call t.dfs(root, root)
    void dfs(int u, int p) {
        up[u][0] = p;
        for (int i = 1; i <= l; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (auto v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }

    inline int kth(int u, int k) const {
        for (int i = l; i >= 0; i--) {
            if (k & (1 << i)) {
                u = up[u][i];
            }
        }
        return u;
    }

    inline int lca(int u, int v) const {
        if (depth[u] < depth[v]) swap(u, v);
        int k = depth[u] - depth[v];
        for (int i = l; i >= 0; i--) {
            if (k & (1 << i)) {
                u = up[u][i];
            }
        }
        if (u == v) return u;
        for (int i = l; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

    inline int dist(int u, int v) const {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};
