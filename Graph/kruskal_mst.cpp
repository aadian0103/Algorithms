vector<int> order(m);
ranges::iota(order, 0);
ranges::sort(order, [&](auto a, auto b) { edges[a][2] < edges[b][2]; });

dsu d(n);
ll ans = 0;
vector<int> used;
for (auto id : order) {
    int u = edges[id][0], v = edges[id][1], w = edges[id][2];
    if (d.unite(u, v)) {
        ans += w;
        used.push_back(id);
        if ((int)used.size() == n - 1) break;
    }
}
