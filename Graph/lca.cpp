struct Tree {
    int n, lg, time;
    vector<int> in, out, depth, sz;
    vector<vector<int>> up, adj;

    explicit Tree(const vector<vector<int>>& g) : n((int)g.size()), adj(g) { init(); }
    explicit Tree(int n_) : n(n_) { adj.resize(n_); init(); }

    void init() {
        lg = bit_width(unsigned(n - 1));
        time = 0;
        in.resize(n); out.resize(n);
        depth.resize(n); sz.resize(n);
        up.assign(n, vector<int>(lg + 1));
    }

    void add(int u, int v) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    // remember to call t.dfs(root, root)
    void dfs(int u, int p) {
        in[u] = ++time;

        up[u][0] = p;
        for (int i = 1; i <= lg; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }

        for (auto v : adj[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                dfs(v, u);
                sz[u] += sz[v];
            };
        }

        out[u] = ++time;
    }

    bool is_ancestor(int u, int v) const {
        return in[u] <= in[v] && out[u] >= out[v];
    }

    int kth(int u, int k) const {
        for (int i = lg; i >= 0; i--) {
            if (k & (1 << i)) {
                u = up[u][i];
            }
        }

        return u;
    }

    int lca(int u, int v) const {
        if (is_ancestor(u, v)) {
            return u;
        }
        if (is_ancestor(v, u)) {
            return v;
        }

        for (int i = lg; i >= 0; i--) {
            if (!is_ancestor(up[u][i], v)) {
                u = up[u][i];
            }
        }

        return up[u][0];
    }

    int dist(int u, int v) const {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};

