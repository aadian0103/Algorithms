template <typename T>
struct Fenwick {
    int n;
    vector<T> bit;

    constexpr Fenwick() noexcept : n(0) {}
    explicit Fenwick(int n_) : n(n_), bit(n_, T{}) {}

    // build from a vector, optimized build - O(n)
    explicit Fenwick(const vector<T>& a) : n((int)a.size()), bit(a) {
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

    // Returns largest x such that sum[0, x) <= k
    int maxPrefix(T k) const {
        if (n == 0) return 0;

        int x = 0;
        T sum = T();
        for (int i = 1 << __lg(n); i > 0; i >>= 1) {
            if (x + i <= n) {
                T new_sum = sum + bit[x + i - 1];
                if (new_sum <= k) {
                    sum = new_sum;
                    x += i;
                }
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

    explicit RURQ(int n_) : n(n_), f1(n_), f2(n_) {}

    explicit RURQ(const vector<T>& a) : n((int)a.size()), f1((int)a.size()), f2((int)a.size()) {
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

