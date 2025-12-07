struct dsu {
    vector<int> parent, sz;
    int comps;

    dsu(int n) : parent(n), sz(n, 1), comps(n) {
        ranges::iota(parent, 0);
    }

    int get(int x) noexcept {
        return parent[x] = (x == parent[x] ? x : get(parent[x]));
    }

    bool unite(int a, int b) noexcept {
        a = get(a); b = get(b);
        if (a == b) return false;

        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        comps--;
        return true;
    }

    int size(int x) noexcept { return sz[get(x)]; }
    int count() const noexcept { return comps; }
    bool same(int a, int b) { return get(a) == get(b); }
};
