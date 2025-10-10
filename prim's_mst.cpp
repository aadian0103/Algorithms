vector<int> vis(n, 0);
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

auto process = [&](int u) {
    vis[u] = 1;
    for (auto [w, v] : g[u]) {
        if (!vis[v]) {
            pq.emplace(w, v);
        }
    }
};
process(0);
ll ans = 0, cnt = 0;
while (!pq.empty()) {
    auto [w, u] = pq.top(); pq.pop();
    if (!vis[u]) {
        ans += w;
        process(u);
        cnt++;
        if (cnt == n - 1) break;
    }
}