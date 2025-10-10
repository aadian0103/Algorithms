// kosaraju algorithm to find the scc in a directed graph
// The SCCs are labeled in topological order, i.e., for any edge u -> v, c[u] ≤ c[v].
vector<vector<int>> rev(n);
for (int u = 0; u < n; u++) {
    for (int v : g[u]) {
        rev[v].push_back(u);
    }
}
vector<int> order;
vector<bool> vis(n, false);
function<void(int)> dfs1 = [&](int u) {
    vis[u] = 1;
    for (auto v : g[u]) {
        if (!vis[v]) {
            dfs1(v);
        }
    }
    order.push_back(u);
};
for (int i = 0; i < n; i++) {
    if (!vis[i]) {
        dfs1(i);
    }
}
int cnt = 0; // this gives the no of strongly connected components
vector<int> c(n, -1); // // c[i] = component id of node i
function<void(int)> dfs2 = [&](int u) {
    for (auto v : rev[u]) {
        if (c[v] == -1) {
            c[v] = c[u];
            dfs2(v);
        }
    }
};
for (int id = n - 1; id >= 0; id--) {
    int i = order[id];
    if (c[i] == -1) {
        c[i] = cnt++;
        dfs2(i);
    }
}
vector<vector<int>> scc(cnt);
for (int i = 0; i < n; ++i) {
    scc[c[i]].push_back(i);
}
vector<vector<int>> dag(cnt); // condensation graph
set<pair<int, int>> seen;

for (int u = 0; u < n; u++) {
    for (int v : g[u]) {
        int cu = c[u], cv = c[v];
        if (cu != cv && !seen.count({cu, cv})) {
            dag[cu].push_back(cv);
            seen.insert({cu, cv});
        }
    }
}