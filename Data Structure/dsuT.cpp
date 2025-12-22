template<typename T>
struct Dsu {
    unordered_map<T, T> par;
    unordered_map<T, int> sz;
    int comps = 0;

    Dsu() = default;
    Dsu(const vector<T>& a) {
        for (const auto& x : a) {
            add(x);
        }
    }

    T add(const T& x) {
        if (!par.count(x)) {
            par[x] = x;
            sz[x] = 1;
            comps++;
        }
        return par[x];
    }

    T get(const T& x) {
        if (!par.count(x)) return add(x);
        return par[x] = (par[x] == x ? x : get(par[x]));
    }

    bool unite(const T& a, const T& b) {
        T ra = get(a), rb = get(b);
        if (ra == rb) return false;

        if (sz[ra] < sz[rb]) swap(ra, rb);
        par[rb] = ra;
        sz[ra] += sz[rb];
        comps--;

        return true;
    }

    int size(const T& x) { return sz[get(x)]; }
    int count() const { return comps; }
    bool same(const T& a, const T& b) { return get(a) == get(b); }
};
