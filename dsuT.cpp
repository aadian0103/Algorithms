template<typename T>
class dsu {
    public:
    unordered_map<T, T> p;
    unordered_map<T, int> sz;

    dsu() {}

    T get(const T& x) {
        if (!p.count(x)) {
            p[x] = x;
            sz[x] = 1;
        }
        return (x == p[x] ? x : (p[x] = get(p[x])));
    }

    bool unite(const T& x, const T& y) {
        T a = get(x);
        T b = get(y);
        if (a != b) {
            if (sz[a] < sz[b]) swap(a, b);
            p[b] = a;
            sz[a] += sz[b];
            return true;
        }
        return false;
    }
    
    int size(const T& x) {
        return sz[get(x)];
    }
};