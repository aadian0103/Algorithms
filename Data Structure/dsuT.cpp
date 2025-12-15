template<typename T>
struct Dsu {
    unordered_map<T, T> parent;
    unordered_map<T, int> sz;
    int comps = 0;

    Dsu() = default;
    Dsu(const vector<T>& a) {
        for (const auto& x : a) {
            add(x);
        }
    }

    T add(const T& x) {
        if (!parent.count(x)) {
            parent[x] = x;
            sz[x] = 1;
            comps++;
        }
        return parent[x];
    }

    T get(const T& x) {
        if (!parent.count(x)) return add(x);
        return parent[x] = (parent[x] == x ? x : get(parent[x]));
    }

    bool unite(const T& a, const T& b) {
        T ra = get(a), rb = get(b);
        if (ra == rb) return false;

        if (sz[ra] < sz[rb]) swap(ra, rb);
        parent[rb] = ra;
        sz[ra] += sz[rb];
        comps--;
        return true;
    }

    int size(const T& x) { return sz[get(x)]; }
    int count() const { return comps; }
    bool same(const T& a, const T& b) { return get(a) == get(b); }
};
