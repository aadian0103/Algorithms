ranges::sort(edges, [&](auto a, auto b) { return edges[a][2] < edges[b][2]; });
vector<int> used;

dsu d(n);
ll ans = 0;
for (auto e : edges) {
    int u = e[0], v = e[1], w = e[2];
    if (d.unite(u, v)) {
        ans += w;
        used.emplace_back(i);
        if (int(used.size()) == n - 1) break;
    }
}
