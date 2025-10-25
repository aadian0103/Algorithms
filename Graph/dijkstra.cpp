vector<ll> dist(n, inf);
vector<int> p(n, -1);
priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
dist[start] = 0;
pq.emplace(dist[start], start);
while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (dist[u] != d) continue;
    for (auto [v, w] : adj[u]) {
        if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            pq.emplace(dist[v], v);
            p[v] = u;
        }
    }
}