template<typename Info, typename Tag>
struct LazySegmentTree {
    int n;
    vector<Info> seg;
    vector<Tag> tag;

    LazySegmentTree() : n(0) {}
    LazySegmentTree(int n_, Info v_ = Info()) { LazySegmentTree(vector(n_, v_)); }

    template<typename T>
    LazySegmentTree(const vector<T>& a) : n(int(a.size())) {
        int lg = bit_width(unsigned(n)) - 1;
        seg.resize(4 << lg);
        tag.resize(4 << lg);
        build(1, 0, n, a);
    }

    template<typename T>
    void build(int v, int l, int r, const vector<T>& a) {
        if (r - l == 1) {
            seg[v] = Info(a[l]);
            return;
        }
        int m = (l + r) >> 1;
        build(v << 1, l, m, a);
        build(v << 1 | 1, m, r, a);
        seg[v] = seg[v << 1] + seg[v << 1 | 1];
    }

    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }

    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }

    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        seg[v] = seg[v << 1] + seg[v << 1 | 1];
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }

    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }

    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
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
        seg[v] = seg[v << 1] + seg[v << 1 | 1];
    }
    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n, l, r, v);
    }

    template<class F>
    int findFirst(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template<class F>
    int findLast(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F pred) {
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
 
Info operator+(Info a, Info b) {
    Info c;
    c.sum = a.sum + b.sum;
    c.cnt = a.cnt + b.cnt;
    return c;
}
