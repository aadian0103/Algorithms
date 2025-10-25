vector<int> order(m);
ranges::iota(order, 0);
ranges::sort(order, [&](int a, int b) {
    return edges[a][2] < edges[b][2];
});
vector<int> ans_id;
dsu d(n);
ll ans = 0;
for (auto i : order) {
    auto [u, v, w] = edges[i];
    if (d.unite(u, v)) {
        ans += w;
        ans_id.push_back(i);
        if ((int) ans_id.size() == n - 1) break;
    }
}
