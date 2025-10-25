vector<int> EulerianPath(int n, vector<pair<int, int>> &edges) {
    vector<vector<pair<int, int>>> adj(n);
    vector<int> used(edges.size());
    vector<int> deg(n, 0);

    for (int i = 0; i < edges.size(); i++) {
        auto [u, v] = edges[i];
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        deg[u]++; deg[v]++;
    }

    int start = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] % 2 == 1) {
            cnt++;
            start = i;
        }
    }

    if (cnt != 0 && cnt != 2) {
        return {};
    }

    if (cnt == 0) {
        for (int i = 0; i < n; i++) {
            if (deg[i] > 0) {
                start = i;
                break;
            }
        }
    }

    vector<int> stk = {start}, path;
    while (!stk.empty()) {
        int v = stk.back();
        while (!adj[v].empty() && used[adj[v].back().second]) {
            adj[v].pop_back();
        }
        if (adj[v].empty()) {
            path.push_back(v);
            stk.pop_back();
        } else {
            auto [u, id] = adj[v].back();
            adj[v].pop_back();
            used[id] = 1;
            stk.push_back(u);
        }
    }

    reverse(path.begin(), path.end());
    return (path.size() == edges.size() + 1 ? path : {});
}
