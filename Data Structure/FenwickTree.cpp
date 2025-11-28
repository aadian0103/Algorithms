template <typename T>
struct Fenwick {
    int n;
    vector<T> bit;

    Fenwick(int n = 0) {
        init(n);
    }

    void init(int n_) {
        n = n_;
        bit.assign(n, T());
    }

    // build from a vector, optimized build - O(n)
    Fenwick(const vector<T>& b) : Fenwick(static_cast<int>(b.size())) {
        for (int i = 0; i < n; i++) {
            bit[i] += b[i];
            int r = i | (i + 1);
            if (r < n) bit[r] += bit[i];
        }
    }

    inline void add(int x, T v) {
        assert(0 <= x && x < n);
        for(int i = x + 1; i <= n; i += i & -i) {
            bit[i - 1] += v;
        }
    }

    // gives prefix sum on [0, x)
    inline T sum(int x) const {
        assert(0 <= x && x <= n);
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += bit[i - 1];
        }
        return ans;
    }

    // gives sum on [l, r)
    inline T rangeSum(int l, int r) const {
        assert(0 <= l && l < r && r <= n);
        return sum(r) - sum(l);
    }

    // smallest idx(0 based) such that prefix sum > k; returns n if none
    int kth(T k) const {
        int x = 0;
        for (int i = 1 << __lg(n); i > 0; i >>= 1) {
            if (x + i <= n && bit[x + i - 1] <= k) {
                x += i;
                k -= bit[x - 1];
            }
        }
        return x;
    }
};

// Range add, range sum
template <class T>
struct RURQ {
    int n;
    Fenwick<T> f1, f2;

    RURQ(int n_) : n(n_), f1(n_), f2(n_) {}

    RURQ(const vector<T>& a) : RURQ(static_cast<int>(a.size())) {
        for (int i = 0; i < n; i++) {
            range_add(i, i + 1, a[i]);
        }
    }

    // add v to [l, r)
    inline void range_add(int l, int r, T v) {
        assert(0 <= l && l < r && r <= n);
        f1.add(l, v);
        if (r < n) f1.add(r, -v);
        f2.add(l, v * (l - 1));
        if (r < n) f2.add(r, -v * (r - 1));
    }

    // prefix sum [0, x)
    inline T prefix_sum(int x) const {
        assert(0 <= x && x <= n);
        return f1.sum(x) * (x - 1) - f2.sum(x);
    }

    // sum on [l, r)
    inline T range_query(int l, int r) const {
        assert(0 <= l && l < r && r <= n);
        return prefix_sum(r) - prefix_sum(l);
    }
};

