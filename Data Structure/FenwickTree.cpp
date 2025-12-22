// query -> prefix sum on [0, x) & [l, r)
// max_pref -> returns max x such that sum[0..x) <= k, /*requires: all values in Fenwick >= 0*/
template <typename T>
struct Fenwick {
    int n;
    vector<T> bit;

    explicit Fenwick() : n(0) {}
    explicit Fenwick(int n_) : n(n_), bit(n_, T{}) {}
    explicit Fenwick(const vector<T>& a) : n((int)a.size()), bit(a) {
        for (int i = 0; i < n; i++) {
            int r = i | (i + 1);
            if (r < n) bit[r] += bit[i];
        }
    }

    void update(int x, T v) {
        assert(0 <= x && x < n);
        for(int i = x + 1; i <= n; i += i & -i) {
            bit[i - 1] += v;
        }
    }

    T query(int x) const {
        assert(0 <= x && x <= n);
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += bit[i - 1];
        }
        return ans;
    }

    T query(int l, int r) const {
        assert(0 <= l && l < r && r <= n);
        return query(r) - query(l);
    }

    int max_pref(T k) {
        int x = 0;
        for (int i = bit_floor(unsigned(n)); i > 0; i /= 2) {
            if (x + i <= n && k >= bit[x + i - 1]) {
                x += i;
                k -= bit[x - 1];
            }
        }
        return x;
    }
};

// range_update -> add v to [l, r)
// range_query -> sum on [0, x) & [l, r)
template <typename T>
struct FenwickRange {
    int n;
    Fenwick<T> f1, f2;

    explicit FenwickRange(int n_) : n(n_), f1(n_), f2(n_) {}
    explicit FenwickRange(const vector<T>& a) : n((int)a.size()), f1(n), f2(n) {
        for (int i = 0; i < n; i++) {
            range_update(i, i + 1, a[i]);
        }
    }

    void range_update(int l, int r, T v) {
        assert(0 <= l && l < r && r <= n);
        f1.update(l, v);
        if (r < n) f1.update(r, -v);
        f2.update(l, v * (l - 1));
        if (r < n) f2.update(r, -v * (r - 1));
    }

    T range_query(int x) const {
        assert(0 <= x && x <= n);
        return f1.query(x) * (x - 1) - f2.query(x);
    }

    T range_query(int l, int r) const {
        assert(0 <= l && l < r && r <= n);
        return range_query(r) - range_query(l);
    }
};

