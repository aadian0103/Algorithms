struct DSU {
    vector<int> par, sz;
    int comps;

    DSU(int n) : par(n), sz(n, 1), comps(n) {
        ranges::iota(par, 0);
    }

    int get(int x) {
        while (x != par[x]) {
            x = par[x] = par[par[x]];
        }
        return x;
    }

    bool unite(int a, int b) {
        a = get(a); b = get(b);
        if (a == b) return false;

        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        comps--;

        return true;
    }

    int size(int x) { return sz[get(x)]; }
    int count() const { return comps; }
    bool same(int a, int b) { return get(a) == get(b); }
};
