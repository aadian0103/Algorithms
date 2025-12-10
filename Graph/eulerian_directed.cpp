vector<int> EulerianPath(int n, vector<pair<int, int>>& edges) {
    vector<vector<pair<int, int>>> adj(n);
    vector<int> indeg(n), outdeg(n), used(edges.size());

    for (int i = 0; i < (int)edges.size(); i++) {
        auto [u, v] = edges[i];
        adj[u].emplace_back(v, i);
        outdeg[u]++; indeg[v]++;
    }

    int start = -1, cntS = 0, cntE = 0;
    for (int i = 0; i < n; i++) {
        if (outdeg[i] - indeg[i] == 1) {
            start = i;
            cntS++;
        } else if (indeg[i] - outdeg[i] == 1) {
            cntE++;
        } else if (indeg[i] != outdeg[i]) {
            return {};
        }
    }

    if (!((cntS == 1 && cntE == 1) || (cntS == 0 && cntE == 0))) {
        return {};
    }

    if (start == -1) {
        for (int i = 0; i < n; i++) {
            if (outdeg[i] > 0) {
                start = i;
                break;
            }
        }
    }

    vector<int> stk = {start}, path;
    while (!stk.empty()) {
        int v = stk.back();
        while (!adj[v].empty() && used[adj[v].back().second]) adj[v].pop_back();
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
