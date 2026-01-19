template <typename Info, typename Tag>
struct LazySegmentTree {
    int n;
    vector<Info> info;
    vector<Tag> tag;

    explicit LazySegmentTree() : n(0) {}
    explicit LazySegmentTree(int n_, Info v_ = Info()) : LazySegmentTree(vector<Info>(n_, v_)) {}

    template<typename T>
    explicit LazySegmentTree(const vector<T>& a) : n((int)a.size()) {
        int lg = bit_width(unsigned(n)) - 1;
        info.resize(4 << lg);
        tag.resize(4 << lg);
        build(1, 0, n, a);
    }

    template<typename T>
    void build(int v, int l, int r, const vector<T>& a) {
        if (r - l == 1) {
            info[p] = init_[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * p, l, m);
        build(2 * p + 1, m, r);
        pull(p);
    }

    void apply(int p, const Tag& v) {
        info[p].apply(v);
        tag[p].apply(v);
    }

    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }

    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }

    void update(int p, int l, int r, int x, const Info& v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        push(p);
        int m = (l + r) / 2;
        if (x < m) {
            update(2 * p, l, m, x, v);
        } else {
            update(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }

    void update(int x, const Info& v) {
        assert(0 <= x && x < n);
        update(1, 0, n, x, v);
    }

    Info range_query(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        push(p);
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }

    Info range_query(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return range_query(1, 0, n, l, r);
    }

    void range_update(int p, int l, int r, int x, int y, const Tag& v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }

    void range_update(int l, int r, const Tag& v) {
        assert(0 <= l && l <= r && r <= n);
        return range_update(1, 0, n, l, r, v);
    }

    template <typename F>
    int find_first(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        push(p);
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
    int findLast(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        push(p);
        int m = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }

    template <typename F>
    int findLast(int l, int r, F pred) {
        assert(0 <= l && l <= r && r <= n);
        return findLast(1, 0, n, l, r, pred);
    }
};

struct Tag {
    double mul = 1;
    double add = 0;

    void apply(Tag t) {
        mul *= t.mul;
        add *= t.mul;
        add += t.add;
    }
};

struct Info {
    double sum = 0;
    int cnt = 0;

    void apply(Tag t) {
        sum *= t.mul;
        sum += t.add * cnt;
    }
};

Info operator+(Info& a, Info& b) {
    Info c;
    c.sum = a.sum + b.sum;
    c.cnt = a.cnt + b.cnt;
    return c;
}
