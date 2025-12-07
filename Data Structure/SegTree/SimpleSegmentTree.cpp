// builds segment trees [l, r) (exclusive)
// Supports queries over any interval [tl, tr) (exclusive)
template<class Info>
class SimpleSegmentTree {
public:
    int n;
    vector<Info> segTree;

    SimpleSegmentTree() : n(0) {}
    SimpleSegmentTree(int size, Info v = Info()) {
        this->n = size;
        segTree.assign(4 << __lg(n), Info());
    }
    template <typename T>
    SimpleSegmentTree(const vector<T> &a) {
        this->n = (int)a.size();
        segTree.assign(4 << __lg(n), Info());
        build(1, 0, n, a);
    }

    template <typename T>
    void build(int v, int l, int r, const vector<T> &a) {
        if (r - l == 1) {
            segTree[v] = a[l];
            return;
        }
        else {
            int m = (l + r) / 2;
            build(2 * v, l, m, a);
            build(2 * v + 1, m, r, a);
            segTree[v] = segTree[2 * v] + segTree[2 * v + 1];
        }
    }

    void pointUpdate(int pos, const Info &value, int v = 1, int l = -1, int r = -1) {
        if (l == -1 && r == -1) { l = 0; r = n; }
        assert(pos >= 0);
        if (r - l == 1) segTree[v] = value;
        else {
            int m = (l + r) / 2;
            if (pos < m) pointUpdate(pos, value, 2 * v, l, m);
            else pointUpdate(pos, value, 2 * v + 1, m, r);
            segTree[v] = segTree[2 * v] + segTree[2 * v + 1];
        }
    }

    Info rangeQuery(int tl, int tr, int v = 1, int l = -1, int r = -1) {
        if (l == -1 && r == -1) { l = 0; r = n; }
        assert(tl >= 0 && tl <= tr && tr <= n);
        if (l >= tr || r <= tl) return Info();
        if (l >= tl && r <= tr) return segTree[v];
        int m = (l + r) / 2;
        return rangeQuery(tl, tr, 2 * v, l, m) + rangeQuery(tl, tr, 2 * v + 1, m, r);
    }
};

struct Info {
    ll sum = 0;
    int cnt = 0;
};

Info operator+(Info a, Info b) {
    Info c;
    c.sum = a.sum + b.sum;
    c.cnt = a.cnt + b.cnt;
    return c;
}
