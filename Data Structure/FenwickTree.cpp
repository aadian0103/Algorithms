// sum -> prefix sum on [0, x), rangeSum -> sum on [l, r)
template <typename T>
struct Fenwick {
    int n;
    vector<T> bit;

    constexpr Fenwick() noexcept : n(0) {}
    explicit Fenwick(int n) : n(n), bit(n, T{}) {}

    explicit Fenwick(const vector<T>& a) : n(int(a.size())), bit(a) {
        for (int i = 0; i < n; i++) {
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

    inline T sum(int x) const {
        assert(0 <= x && x <= n);
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += bit[i - 1];
        }
        return ans;
    }

    inline T rangeSum(int l, int r) const {
        assert(0 <= l && l < r && r <= n);
        return sum(r) - sum(l);
    }

    int maxPref(T k) {
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

// Range add -> add v to [l, r)
// prefixSum -> sum on [0, x), rangeSum -> [l, r)
template <class T>
struct RURQ {
    int n;
    Fenwick<T> f1, f2;

    explicit RURQ(int n) : n(n), f1(n), f2(n) {}

    explicit RURQ(const vector<T>& a) : n(int(a.size())), f1(int(a.size())), f2(int(a.size())) {
        for (int i = 0; i < n; i++) {
            rangeAdd(i, i + 1, a[i]);
        }
    }

    inline void rangeAdd(int l, int r, T v) {
        assert(0 <= l && l < r && r <= n);
        f1.add(l, v);
        if (r < n) f1.add(r, -v);
        f2.add(l, v * (l - 1));
        if (r < n) f2.add(r, -v * (r - 1));
    }

    inline T prefixSum(int x) const {
        assert(0 <= x && x <= n);
        return f1.sum(x) * (x - 1) - f2.sum(x);
    }

    inline T RangeSum(int l, int r) const {
        assert(0 <= l && l < r && r <= n);
        return prefixSum(r) - prefixSum(l);
    }
};

