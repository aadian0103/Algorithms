template<typename Info>
struct SimpleSegmentTree {
    int n;
    vector<Info> seg;

    SimpleSegmentTree() : n(0) {}
    SimpleSegmentTree(int n_, Info v_ = Info()) { SimpleSegmentTree(vector<Info>(n_, v_)); }

    template<typename T>
    SimpleSegmentTree(const vector<T>& a) : n(int(a.size())) {
        int lg = bit_width(unsigned(n)) - 1;
        seg.resize(4 << lg);
        build(1, 0, n, a);
    }

    template<typename T>
    void build(int v, int l, int r, const vector<T>& a) {
        if (r - l == 1) {
            seg[v] = Info(a[l]);
            return;
        }
        int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m, r, a);
        seg[v] = seg[2 * v] + seg[2 * v + 1];
    }

    void update(int v, int l, int r, int p, const Info& x) {
        if (r - l == 1) {
            seg[v] = x;
            return;
        }
        int m = (l + r) / 2;
        if (p < m) update(2 * v, l, m, p, x);
        else update(2 * v + 1, m, r, p, x);
        seg[v] = seg[2 * v] + seg[2 * v + 1];
    }
    void update(int p, const Info& x) {
        assert(0 <= p && p < n);
        update(1, 0, n, p, x);
    }

    Info query(int v, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return seg[v];
        }
        int m = (l + r) / 2;
        return query(2 * v, l, m, x, y) + query(2 * v + 1, m, r, x, y);
    }
    Info query(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return query(1, 0, n, l, r);
    }
};

struct Info {
    int mx;
    int cnt;

    // Info() must be identity element for operator+
    Info() : mx(INT_MIN), cnt(0) {}
    Info(int x) : mx(x), cnt(1) {}
};

Info operator+(const Info& a, const Info& b) {
    Info c;
    if (a.mx > b.mx) {
        c = a;
    } else if (a.mx < b.mx) {
        c = b;
    } else {
        c.mx = a.mx;
        c.cnt = a.cnt + b.cnt;
    }
    return c;
}

