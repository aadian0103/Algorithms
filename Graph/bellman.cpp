vector<ll> dist(n, inf);
vector<int> p(n, -1);
dist[start] = 0;

for (int i = 0; i < n - 1; i++) {
    bool flag = 0;
    for (int u = 0; u < n; u++) {
        if (dist[u] == inf) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                p[v] = u;
                flag = 1;
            }
        }
    }
    if (!flag) {
        break;
    }
}

for (int u = 0; u < n; u++) {
    if (dist[u] == inf) continue;
    for (auto [v, w] : adj[u]) {
        if (dist[v] > dist[u] + w) {
            cout << "Negative cycle" << nl;
            return;
        }
    }
}
