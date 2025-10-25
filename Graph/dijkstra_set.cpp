// dijkstra's for non negative weights
vector<ll> dist(n, inf);
set<pair<ll, int>> s;
dist[start] = 0;
s.emplace(dist[start], start);
while (!s.empty()) {
    auto [d, u] = *s.begin();
    s.erase(s.begin());
    for (auto [v, w] : adj[u]) {
        if (dist[u] + w < dist[v]) {
            s.erase({dist[v], v});
            dist[v] = dist[u] + w;
            s.emplace(dist[v], v);
        }
    }
}
