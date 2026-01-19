template <typename Info>
struct SegmentTree {
    int n;
    vector<Info> info;

    explicit SegmentTree() : n(0) {}
    explicit SegmentTree(int n_, Info v_ = Info()) : SegmentTree(vector<Info>(n_, v_)) {}

    template<typename T>
    explicit SegmentTree(const vector<T>& a) : n((int)a.size()) {
        int lg = bit_width(unsigned(n)) - 1;
        info.resize(4 << lg);
        build(1, 0, n, a);
    }

    template<typename T>
    void build(int p, int l, int r, const vector<T>& a) {
        if (r - l == 1) {
            info[p] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * p, l, m, a);
        build(2 * p + 1, m, r, a);
        info[p] = info[2 * p] + info[2 * p + 1];
    }

    void update(int p, int l, int r, int x, const Info& v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            update(2 * p, l, m, x, v);
        } else {
            update(2 * p + 1, m, r, x, v);
        }
        info[p] = info[2 * p] + info[2 * p + 1];
    }

    void update(int x, const Info& v) {
        assert(0 <= x && x < n);
        update(1, 0, n, x, v);
    }

    Info query(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return query(2 * p, l, m, x, y) + query(2 * p + 1, m, r, x, y);
    }

    Info query(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return query(1, 0, n, l, r);
    }

    template <typename F>
    int find_first(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = find_first(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = find_first(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }

    template <typename F>
    int find_first(int l, int r, F pred) {
        assert(0 <= l && l <= r && r <= n);
        return find_first(1, 0, n, l, r, pred);
    }

    template <typename F>
    int find_last(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = find_last(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = find_last(2 * p, l, m, x, y, pred);
        }
        return res;
    }

    template <typename F>
    int find_last(int l, int r, F pred) {
        assert(0 <= l && l <= r && r <= n);
        return find_last(1, 0, n, l, r, pred);
    }
};

constexpr ll inf = 9e18;
struct Info {
    ll mx, pref, suff, sum;

    Info() : mx(-inf), pref(-inf), suff(-inf), sum(0) {}
    Info(int x) : mx(x), pref(x), suff(x), sum(x) {}
};

Info operator+(const Info& a, const Info& b) {
    Info c;
    c.mx = max({a.mx, b.mx, a.suff + b.pref});
    c.pref = max(a.pref, a.sum + b.pref);
    c.suff = max(b.suff, b.sum + a.suff);
    c.sum = a.sum + b.sum;
    return c;
}

